#include "galaxy.hh"

namespace Student {

Galaxy::Galaxy()
{

}

Galaxy::~Galaxy()
{

}

void Galaxy::addShip(std::shared_ptr<Common::Ship> ship)
{
    for(auto shipIt : *ships)
    {
        if(shipIt == ship)
        {
            throw Common::StateException();
        }
    }
    ships->push_back(ship);
}

void Galaxy::removeShip(std::shared_ptr<Common::Ship> ship)
{
    bool found = false;
    for(unsigned int i = 0; i < ships->size(); i++)
    {
        if(ships->at(i) == ship)
        {
            ships->erase(ships->begin()+i);
            found = true;
        }
    }
    if(found == false)
    {
        throw Common::ObjectNotFoundException();
    }
}

void Galaxy::addStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{
    for(auto shipIt : starSystems)
    {
        if(shipIt->getName() == starSystem->getName() || shipIt->getId() == starSystem->getId() || shipIt->getCoordinates() == starSystem->getCoordinates())
        {
            throw Common::StateException();
        }
    }
    starSystems.push_back(starSystem);
}

std::shared_ptr<Common::IGalaxy::ShipVector> Galaxy::getShips()
{
    return ships;
}

Common::StarSystem::StarSystemVector Galaxy::getSystemsInRange(std::shared_ptr<Common::StarSystem> origin, int range)
{
    Common::StarSystem::StarSystemVector systemsInRange;
    bool found = false;
    for(auto systemIt : starSystems)
    {
        if(origin == systemIt)
        {
            found = true;
        }
    }
    if(found == false)
    {
        throw Common::ObjectNotFoundException();
    }
    for(auto systemIt : starSystems)
    {
        if(Common::distance(origin->getCoordinates().x, origin->getCoordinates().y,
                            systemIt->getCoordinates().x, systemIt->getCoordinates().y) <= range
                && systemIt->getId() != origin->getId())
        {
            systemsInRange.push_back(systemIt);
        }
    }
    return systemsInRange;
}

std::shared_ptr<Common::StarSystem> Galaxy::getRandomSystem()
{
    if(starSystems.size() == 0)
    {
        throw Common::ObjectNotFoundException();
    } else
    {
        return starSystems.at(Common::randomMinMax(0, starSystems.size()-1));
    }
}

Common::IGalaxy::ShipVector Galaxy::getShipsInStarSystem(std::__cxx11::string name)
{
    Common::IGalaxy::ShipVector shipsInSystem;
    bool found = false;
    for(auto systemIt : starSystems)
    {
        if(systemIt->getName() == name)
        {
            found = true;
        }
    }
    if(found == false)
    {
        throw Common::ObjectNotFoundException();
    }
    for(auto ship : *ships)
    {
        if(ship->getLocation()->getName() == name)
        {
            shipsInSystem.push_back(ship);
        }
    }
    return shipsInSystem;
}

std::vector<std::__cxx11::string> Galaxy::getSystemNames()
{
    std::vector<std::__cxx11::string> names;
    for(auto systemIt : starSystems)
    {
        names.push_back(systemIt->getName());
    }
    return names;
}

std::shared_ptr<Common::StarSystem> Galaxy::getStarSystemByName(std::__cxx11::string name)
{
    for(std::shared_ptr<Common::StarSystem> starsystem : starSystems)
    {
        if(starsystem->getName() == name) {
            return starsystem;
        }
    }
    throw Common::ObjectNotFoundException();
}

std::shared_ptr<Common::StarSystem> Galaxy::getStarSystemById(unsigned id)
{
    for(std::shared_ptr<Common::StarSystem> starsystem : starSystems)
    {
        if(starsystem->getId() == id) {
            return starsystem;
        }
    }
    throw Common::ObjectNotFoundException();
}

}//student
