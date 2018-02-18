#include "gamestate.hh"
#include "stationcoordinate.hh"

constexpr uint COUPONS_PER_OBSTACLE = 10;
constexpr uint POINTS_PER_CRASHED_TRAIN = 5;
constexpr uint POINTS_PER_FINISHED_TRAIN = 1;

GameState::GameState(QObject *parent) :
    QObject(parent),
    player_(nullptr),
    stations_(this),
    tracks_(&stations_, this),
    obstacles_(&tracks_),
    passengerTrains_(&stations_, &tracks_, this),
    serviceTrains_(&stations_, &tracks_, this),
    catalog_(this),
    time_ (QDate::currentDate().addDays(-1)),
    points_(5),
    fileDownloader_(trainUrl(), this),
    status_(NotStarted)
{
    connect(&fileDownloader_, &FileDownloader::downloaded, this, &GameState::loadPassengerTrains);
    stations_.readStations(":/asemadata.json");
    tracks_.readTracks(":/ratadata.json");

    serviceTrains_.addTrain(std::unique_ptr<ServiceTrain>(
                                new ServiceTrain("Standard", 40, 75, 5000)),
                            stations_.location(stations_.getStation("JY")));

    connect(&serviceTrains_, &ServiceTrainsModel::serviceTrainMoved,
            this, &GameState::serviceTrainMoved);
    connect(&passengerTrains_, &PassengerTrainsModel::passengerTrainMoved,
            this, &GameState::passengerTrainMoved);
    connect(&passengerTrains_, &PassengerTrainsModel::passengerTrainFinished,
            this, &GameState::passengerTrainFinished);
    connect(&passengerTrains_, &PassengerTrainsModel::passengerTrainBroken,
            this, &GameState::passengerTrainBroken);
    connect(&passengerTrains_, &PassengerTrainsModel::noMoreTrains,
            this, &GameState::noMorePassengerTrains);
    connect(&obstacles_, &ObstaclesModel::obstacleRemoved, this, &GameState::obstacleRemoved);

    qsrand(QTime::currentTime().msecsSinceStartOfDay());
}

Player *GameState::player() const { return player_; }

void GameState::setPlayer(Player *player)
{
    player_ = player;
    player->setParent(this);
    emit playerChanged(player);
}

StationsModel *GameState::stations() { return &stations_; }

TracksModel *GameState::tracks() { return &tracks_; }

ObstaclesModel *GameState::obstacles() { return &obstacles_; }

PassengerTrainsModel *GameState::passengerTrains() { return &passengerTrains_; }

ServiceTrainsModel *GameState::serviceTrains() { return &serviceTrains_; }

QDateTime GameState::time() const { return time_; }

void GameState::moveTime(uint seconds) { status_ = Running; time_ = time_.addSecs(seconds); }

void GameState::loadPassengerTrains()
{
    passengerTrains_.readTrains(fileDownloader_.downloadedData());
}

void GameState::serviceTrainMoved(ServiceTrain *train, const RelativeCoordinate &oldLoc,
                                  const RelativeCoordinate &newLoc)
{
    obstacles_.removeObstaclesBetween(oldLoc, newLoc);
    for (PassengerTrain* passengerTrain : passengerTrains_.trainsBetween(oldLoc, newLoc))
    {
        passengerTrains()->causeDamage(passengerTrain, passengerTrain->health());
        serviceTrains()->causeDamage(train, 10);
    }
}

void GameState::passengerTrainMoved(PassengerTrain *train, const RelativeCoordinate &oldLoc,
                                    const RelativeCoordinate &newLoc)
{
    uint damage = obstacles_.damageBetween(oldLoc, newLoc);
    if (damage > 0)
    {
        passengerTrains()->causeDamage(train, damage);
    }
    for (ServiceTrain* serviceTrain : serviceTrains_.trainsBetween(oldLoc, newLoc))
    {
        passengerTrains()->causeDamage(train, train->health());
        serviceTrains()->causeDamage(serviceTrain, 10);
    }
}

void GameState::obstacleRemoved()
{
    player()->addCoupons(COUPONS_PER_OBSTACLE);
}

void GameState::passengerTrainBroken()
{
    points_ -= POINTS_PER_CRASHED_TRAIN;
    if (points_ <= 0)
    {
        status_ = Lost;
        emit finished();
    }
    emit(pointsChanged());
}

void GameState::passengerTrainFinished()
{
    points_ += POINTS_PER_FINISHED_TRAIN;
    emit(pointsChanged());
}

GameState::GameStatus GameState::status() const
{
    return status_;
}

void GameState::noMorePassengerTrains()
{
    if (status_ >= Running)
    {
        status_ = Won;
        emit finished();
    }
}

QUrl GameState::trainUrl()
{
    return QUrl("http://rata.digitraffic.fi/api/v1/trains/"
                + time_.date().toString(Qt::ISODate) + "/");
}

uint GameState::points() const { return points_; }

TrainCatalog *GameState::catalog() { return &catalog_; }
