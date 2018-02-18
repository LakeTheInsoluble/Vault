#include "obstacle.hh"
#include <QMap>

const QMap<Obstacle::Type, uint> DAMAGES {{Obstacle::Type::bike, 20},
                                          {Obstacle::Type::leaves, 5},
                                          {Obstacle::Type::rabbit, 10},
                                          {Obstacle::Type::reindeer, 100},
                                          {Obstacle::Type::rock, 15}};

Obstacle::Obstacle(Obstacle::Type type) :
    QObject(),
    type_(type),
    damage_(DAMAGES[type]) {}

Obstacle::Type Obstacle::type() const { return type_; }

uint Obstacle::damage() const { return damage_; }
