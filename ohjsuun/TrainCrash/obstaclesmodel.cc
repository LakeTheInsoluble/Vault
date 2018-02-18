#include "obstaclesmodel.hh"

ObstaclesModel::ObstaclesModel(TracksModel *tracks) : QAbstractListModel(), tracks_(tracks)
{
    Q_ASSERT(invariant());
}

void ObstaclesModel::addObstacle(std::unique_ptr<Obstacle> &&obstacle,
                                 std::shared_ptr<TrackCoordinate> location)
{
    Q_ASSERT(invariant());
    Obstacle *rawObstacle = obstacle.release();
    rawObstacle->setParent(this);

    beginInsertRows(QModelIndex(), obstacles_.size(), obstacles_.size());
    obstacles_.push_back(rawObstacle);
    locations_.insert(rawObstacle, location);
    endInsertRows();
    Q_ASSERT(invariant());
}

void ObstaclesModel::addRandomObstacle()
{
    Q_ASSERT(invariant());
    Track *track  = tracks_->getRandomTrack();
    Obstacle::Type type = static_cast<Obstacle::Type>(qrand() % Obstacle::Type::count);
    float progress = float(qrand()) / RAND_MAX;
    addObstacle(std::unique_ptr<Obstacle>(new Obstacle(type)),
                std::shared_ptr<TrackCoordinate>(new TrackCoordinate(track, progress)));
    Q_ASSERT(invariant());
}

void ObstaclesModel::removeObstacle(Obstacle *toRemove)
{
    Q_ASSERT(invariant());
    if (obstacles_.contains(toRemove))
    {
        int index = obstacles_.indexOf(toRemove);
        beginRemoveRows(QModelIndex(), index, index);
        if (locations_.contains(toRemove))
        {
            locations_.remove(toRemove);
        }
        obstacles_.removeAll(toRemove);
        delete toRemove;
        emit obstacleRemoved();
        endRemoveRows();
    }
    Q_ASSERT(invariant());
}

void ObstaclesModel::removeObstaclesBetween(const RelativeCoordinate &start,
                                            const RelativeCoordinate &end)
{
    Q_ASSERT(invariant());
    QVector<Obstacle*> toRemove;
    for (Obstacle* obstacle : obstacles_)
    {
        if (start.routeToPasses(end, *locations_.value(obstacle)))
        {
            toRemove.push_back(obstacle);
        }
    }
    for (Obstacle* obstacle : toRemove)
    {
        removeObstacle(obstacle);
    }
    Q_ASSERT(invariant());
}

uint ObstaclesModel::damageBetween(const RelativeCoordinate &start,
                                   const RelativeCoordinate &end) const
{
    Q_ASSERT(invariant());
    uint damage = 0;
    for (Obstacle *obstacle : obstacles_)
    {
        if (start.routeToPasses(end, *locations_.value(obstacle)))
        {
            damage += obstacle->damage();
        }
    }
    return damage;
}

int ObstaclesModel::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(invariant());
    return parent.isValid() ? 0 : obstacles_.size();
}

QVariant ObstaclesModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(invariant());
    if (!index.isValid() || index.row() >= obstacles_.size())
    {
        return QVariant();
    }
    else
    {
        switch (role)
        {
        case Qt::DisplayRole: return QVariant("obstacle");
        case LocationRole:
        {
            Obstacle *obstacle = obstacles_.at(index.row());
            return QVariant::fromValue(locations_.value(obstacle)->absolute());
        }
        default: return QVariant();
        }
    }
}

QHash<int, QByteArray> ObstaclesModel::roleNames() const
{
    Q_ASSERT(invariant());
    return {{LocationRole, "location"}};
}

bool ObstaclesModel::invariant() const
{
    return tracks_ != nullptr && obstacles_.size() == locations_.size();
}
