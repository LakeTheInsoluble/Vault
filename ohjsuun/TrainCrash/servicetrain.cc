#include "servicetrain.hh"

ServiceTrain::ServiceTrain(QString model, uint maxHealth, uint price, uint speed, QObject *parent) :
    Train(model, maxHealth, parent),
    price_(price),
    speed_(speed)
{}

uint ServiceTrain::price() const { return price_; }

uint ServiceTrain::speed() const { return speed_; }

std::shared_ptr<RelativeCoordinate> ServiceTrain::location() const { return location_; }

void ServiceTrain::setLocation(std::shared_ptr<RelativeCoordinate> location)
{
    location_ = location;
}

QVector<std::shared_ptr<RelativeCoordinate> > ServiceTrain::plan() const { return plan_; }

void ServiceTrain::setPlan(QVector<std::shared_ptr<RelativeCoordinate>> plan)
{
    plan_ = plan;
    route_.clear();
}

void ServiceTrain::progressPlan() { plan_.removeLast(); }

QVector<std::shared_ptr<RelativeCoordinate> > ServiceTrain::route() const { return route_; }

void ServiceTrain::setRoute(QVector<std::shared_ptr<RelativeCoordinate>> route) { route_ = route; }

void ServiceTrain::progressRoute() { route_.removeLast(); }
