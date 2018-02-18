#include "train.hh"
#include "stationcoordinate.hh"
#include "trackcoordinate.hh"

Train::Train(QString model, uint maxHealth, QObject *parent) :
    QObject(parent),
    model_(model),
    location_ (nullptr),
    maxHealth_(maxHealth),
    health_(maxHealth)
{
    Q_ASSERT(invariant());
}

QString Train:: model() const
{
    Q_ASSERT(invariant());
    return model_;
}

std::shared_ptr<RelativeCoordinate> Train::location() const
{
    Q_ASSERT(invariant());
    return location_;
}

void Train::setLocation(std::shared_ptr<RelativeCoordinate> location)
{
    Q_ASSERT(invariant());
    location_ = location;
    Q_ASSERT(invariant());
}

uint Train::maxHealth() const
{
    Q_ASSERT(invariant());
    return maxHealth_;
}

uint Train::health() const
{
    Q_ASSERT(invariant());
    return health_;
}

void Train::setHealth(uint health)
{
    Q_ASSERT(invariant());
    health_ = health;
    emit healthChanged(health);
    Q_ASSERT(invariant());
}

void Train::repair(uint amount)
{
    Q_ASSERT(invariant());
    setHealth(std::min(health() + amount, maxHealth()));
    Q_ASSERT(invariant());
}

void Train::causeDamage(uint damage)
{
    Q_ASSERT(invariant());
    setHealth(damage > health_ ? 0 : health_ - damage);
    Q_ASSERT(invariant());
}

bool Train::isBroken() const
{

    Q_ASSERT(invariant());
    return health_ == 0;
}

bool Train::isBetween(const RelativeCoordinate &one, const RelativeCoordinate &two) const
{
    Q_ASSERT(invariant());
    try
    {
        return one.routeToPasses(two, dynamic_cast<TrackCoordinate&>(*location_));
    }
    catch (const std::bad_cast&)
    {
        return false;
    }
}

bool Train::invariant() const { return health_ <= maxHealth_; }
