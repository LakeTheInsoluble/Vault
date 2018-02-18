#include "eventhandler.hh"

namespace Student {

EventHandler::EventHandler(QObject *parent) : QObject(parent), Common::IEventHandler()
{

}

EventHandler::~EventHandler()
{

}

void EventHandler::shipSpawned(std::shared_ptr<Common::Ship> ship)
{
    emit lahetaAlusSpawnattu(ship);
}

void EventHandler::shipRemoved(std::shared_ptr<Common::Ship> ship)
{
    emit lahetaAlusPoistettu(ship);
}

void EventHandler::shipRelocated(std::shared_ptr<Common::Ship>, std::shared_ptr<Common::StarSystem>)
{

}

void EventHandler::shipMoved(std::shared_ptr<Common::Ship> ship, Common::Point origin, Common::Point target)
{
    emit lahetaLiike(ship, origin, target);
}

void EventHandler::exceptionInExecution(std::shared_ptr<Common::Ship> ship, const std::__cxx11::string &msg)
{
    emit lahetaPoikkeus(ship, msg);
}

void EventHandler::distressOn(std::shared_ptr<Common::Ship> ship)
{
    emit lahetaDistressOn(ship);
}

void EventHandler::distressOff(std::shared_ptr<Common::Ship> ship)
{
    emit lahetaDistressOff(ship);
}

void EventHandler::shipAbandoned(std::shared_ptr<Common::Ship> ship)
{
    emit lahetaAlusHylatty(ship);
}

}//student
