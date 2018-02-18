#include "startcontroller.hh"

StartController *StartController::instance_;

StartController *StartController::instance()
{
    if (instance_ == nullptr) {
        instance_ = new StartController();
    }
    return instance_;
}

StartController::StartController() : QObject() {}
