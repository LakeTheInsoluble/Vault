#include "gamecontroller.hh"

GameController *GameController::instance_;

GameController *GameController::instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new GameController();
    }
    return instance_;
}

GameController::GameController() : QObject() {}

void GameController::performTickUpdates(GameState *game) const
{
    game->moveTime(30);
    if (qrand() % 200 == 0)
    {
        game->obstacles()->addRandomObstacle();
    }
    game->passengerTrains()->moveTrains(game->time());
    game->serviceTrains()->moveTrains();
    emit game->obstaclesChanged(game->obstacles());
}
