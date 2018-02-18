#include "statistics.hh"
#include "stateexception.hh"

namespace Student {

Statistics::Statistics()
{
    savedShips = 0;
    lostShips = 0;
    points = 0;
    credits = CREDITS_IN_BEGINNING;
}

void Statistics::addSavedShip()
{
    savedShips++;
}

unsigned Statistics::getSavedShips() const
{
    return savedShips;
}

void Statistics::addLostShip()
{
    lostShips++;
}

unsigned Statistics::getLostShips() const
{
    return lostShips;
}

void Statistics::addPoints(unsigned amount)
{
    points += amount;
}

void Statistics::reducePoints(unsigned amount)
{
    if( points >= amount ) {
        points -= amount;
    }
    else{
        throw Common::StateException("Pisteiden maara ei voi olla negatiivinen");
    }
}

unsigned Statistics::getPoints() const
{
    return points;
}

void Statistics::addCredits(unsigned amount)
{
    credits += amount;
}

void Statistics::reduceCredits(unsigned amount)
{
    if( credits-(int)amount >= -MAX_LOAN_ALLOWANCE ) {
        credits -= (int)amount;
    }
    else {
        throw Common::StateException("Liian paljon velkaa");
    }
}

int Statistics::getCreditBalance() const
{
    return credits;
}

}//student
