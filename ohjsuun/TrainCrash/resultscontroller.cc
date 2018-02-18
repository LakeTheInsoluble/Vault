#include "resultscontroller.hh"

ResultsController *ResultsController::instance_;

ResultsController *ResultsController::instance()
{
    if (instance_ == nullptr) {
        instance_ = new ResultsController();
    }
    return instance_;
}

ResultsController::ResultsController() : QObject() {}
