#include "servicetrainsmodel.hh"
#include "trackcoordinate.hh"

#include <cmath>

using std::dynamic_pointer_cast;

ServiceTrainsModel::ServiceTrainsModel(StationsModel* stations, TracksModel *tracks
                                       ,QObject *parent) :
    QAbstractListModel(parent),
    stations_ (stations),
    tracks_ (tracks),
    trains_(),
    activeTrain_(nullptr)
{
    Q_ASSERT(stations != nullptr && tracks != nullptr);
}

void ServiceTrainsModel::addTrain(std::unique_ptr<ServiceTrain>&& train,
                                  std::shared_ptr<RelativeCoordinate> location)
{
    ServiceTrain *rawTrain = train.release();
    rawTrain->setParent(this);
    rawTrain->setLocation(location);

    if (trains_.empty())
    {
        setActiveTrain(rawTrain);
    }

    beginInsertRows(QModelIndex(), trains_.size(), trains_.size());
    trains_.append(rawTrain);
    endInsertRows();
}


void ServiceTrainsModel::moveTrains()
{
    for (ServiceTrain* train : trains_)
    {
        if (!train->plan().isEmpty() && train->route().isEmpty())
        {
            QVector<std::shared_ptr<RelativeCoordinate>> route = calculateLocations(train);
            train->setRoute(route);
        }
        if (!train->route().isEmpty())
        {
            std::shared_ptr<RelativeCoordinate> destination = train->route().last();
            train->progressRoute();
            setLocation(train, destination);
        }
    }
}

void ServiceTrainsModel::setPlan(ServiceTrain *train,
                                 QVector<std::shared_ptr<RelativeCoordinate>> plan)
{
    train->setPlan(plan);
    int i = trains_.indexOf(train);
    if ( i >= 0)
    {
        train->setPlan(plan);
        auto j = index(i);
        emit dataChanged(j, j, {PlanRole});
    }
}

void ServiceTrainsModel::causeDamage(ServiceTrain *train, uint damage)
{
    int i = trains_.indexOf(train);
    if (i != -1)
    {
        train->causeDamage(damage);
        emit dataChanged(index(i), index(i));
    }
}

QVector<ServiceTrain *> ServiceTrainsModel::trainsBetween(const RelativeCoordinate &one,
                                                          const RelativeCoordinate &two)
{
    QVector<ServiceTrain*> toReturn;
    for (ServiceTrain *train : trains_)
    {
        auto location = dynamic_pointer_cast<TrackCoordinate>(train->location());
        if (location != nullptr && one.routeToPasses(two, *location))
        {
            toReturn.push_back(train);
        }
    }
    return toReturn;
}

ServiceTrain *ServiceTrainsModel::activeTrain() const { return activeTrain_; }

void ServiceTrainsModel::setActiveTrain(ServiceTrain *activeTrain)
{
    ServiceTrain *oldActiveTrain = activeTrain_;
    int iOld = trains_.indexOf(oldActiveTrain);
    int iNew = trains_.indexOf(activeTrain);

    if (activeTrain != nullptr)
    {
        activeTrain_ = activeTrain;
    }

    if (iOld != -1)
    {
        emit dataChanged(index(iOld), index(iOld), {ActiveRole});
    }

    if (iNew != -1)
    {
        emit dataChanged(index(iNew), index(iNew), {ActiveRole});
    }
}

int ServiceTrainsModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : trains_.length();
}

QVariant ServiceTrainsModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() < trains_.size())
    {
        ServiceTrain *train = trains_.at(index.row());
        switch (role) {
        case TrainRole: return QVariant::fromValue(train);
        case LocationRole: return QVariant::fromValue(train->location()->absolute());
        //TODO: tämä ei jostain syystä toimi
        //case PlanRole: return QVariant::fromValue(train->plan());
        case HealthRole: return QVariant::fromValue((float)train->health()*2/train->maxHealth());
        case ActiveRole: return train == activeTrain_;
        }
    }
    return QVariant();
}

QHash<int, QByteArray> ServiceTrainsModel::roleNames() const
{
    return {{TrainRole, "train"},
            {LocationRole, "location"},
            {PlanRole, "plan"},
            {HealthRole, "health"},
            {ActiveRole, "active"}};
}

std::shared_ptr<RelativeCoordinate> ServiceTrainsModel::location(ServiceTrain *train)
{
    return train->location();
}

void ServiceTrainsModel::setLocation(ServiceTrain *train,
                                     std::shared_ptr<RelativeCoordinate> location)
{
    int i = trains_.indexOf(train);
    if ( i >= 0)
    {
        std::shared_ptr<RelativeCoordinate> oldLocation;
        oldLocation = train->location();
        train->setLocation(location);
        auto j = index(i);
        emit dataChanged(j, j, {LocationRole});
        emit serviceTrainMoved(train, *oldLocation, *location);
    }
}

QVector<std::shared_ptr<RelativeCoordinate>>
ServiceTrainsModel::calculateLocations(ServiceTrain *train)
{
    QVector<std::shared_ptr<RelativeCoordinate> > route =
        train->location()->quantizeRouteTo(*train->plan().last(), train->speed(), *tracks_);
    train->progressPlan();
    return route;
}
