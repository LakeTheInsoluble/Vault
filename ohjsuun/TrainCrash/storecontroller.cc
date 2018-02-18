#include "storecontroller.hh"

StoreController *StoreController::instance_;

StoreController *StoreController::instance()
{
    if (instance_ == nullptr) {
        instance_ = new StoreController();
    }
    return instance_;
}

StoreController::StoreController() : QObject() {}

void StoreController::repairTrain(GameState *game, ServiceTrain *train, uint amount,
                                  uint cost) const
{
    train->repair(amount);
    game->player()->chargeCoupons(cost);
}

void StoreController::buyTrain(GameState *game, QString model, uint price, uint maxHealth,
                               uint speed) const
{
    game->player()->chargeCoupons(price);
    game->serviceTrains()->addTrain(
                std::unique_ptr<ServiceTrain>(new ServiceTrain(model, maxHealth, price, speed)),
                game->stations()->location(game->stations()->getStation("JY")));
}
