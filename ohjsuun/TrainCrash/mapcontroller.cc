#include "mapcontroller.hh"
#include "gamestate.hh"

MapController *MapController::instance_ = nullptr;

MapController *MapController::instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new MapController();
    }
    return instance_;
}

void MapController::serviceTrainTo(GameState *game,
                                   std::shared_ptr<RelativeCoordinate> location) const
{
    ServiceTrain *activeTrain = game->serviceTrains()->activeTrain();
    if ( activeTrain != nullptr && !activeTrain->isBroken() && location != nullptr)
    {
        auto oldLocation = activeTrain->location();
        auto plan = game->tracks()->getShortestPath(oldLocation, location);
        game->serviceTrains()->setPlan(activeTrain, plan);
    }
    // hitObstacles(game, oldLocation, location);
}

void MapController::serviceTrainToStation(GameState *game, Station *station) const
{
    Q_ASSERT(game != nullptr);
    serviceTrainTo(game, game->stations()->location(station));
}

void MapController::serviceTrainToTrack(GameState *game, Track *track) const
{
    Q_ASSERT(game != nullptr);
    serviceTrainTo(game,
        std::shared_ptr<TrackCoordinate>(new TrackCoordinate(track, 0.5)));
}

void MapController::addRandomObstacle(GameState *game)
{
    Track *track  = game->tracks()->getRandomTrack();
    Obstacle::Type type = static_cast<Obstacle::Type>(qrand() % Obstacle::Type::count);
    float progress = float(qrand()) / RAND_MAX;
    game->obstacles()->addObstacle(
                std::unique_ptr<Obstacle>(new Obstacle(type)),
                std::unique_ptr<TrackCoordinate>(new TrackCoordinate(track, progress)));
}

void MapController::setActiveTrain(GameState *game, ServiceTrain *train)
{
    if (train != nullptr)
    {
        game->serviceTrains()->setActiveTrain(train);
    }
}

MapController::MapController() : QObject() {}
