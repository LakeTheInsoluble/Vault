#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"

namespace Student {

static const int MAX_LOAN_ALLOWANCE = 1000;
static const unsigned CREDITS_IN_BEGINNING = 5000;

/**
 * @brief Statistics pitää yllä tietoja pelin tilastoista.
 *
 * Lisää ja poistaa pelastettuja ja pelastamattomia aluksia.
 * Hallinnoi pelaajan crediittejä ja pisteitä.
 */
class Statistics : public Common::IStatistics
{
public:
    Statistics();

    /**
     * @brief addSavedShip lisää yhden pelastetun aluksen.
     */
    void addSavedShip();
    /**
     * @brief getSavedShips palauttaa pelastetuttujen alusten määrän.
     * @return pelastamatta jääneiden alusten määrä.
     */
    unsigned getSavedShips() const;

    /**
     * @brief addLostShip lisää yhden pelastamatta jääneen aluksen.
     */
    void addLostShip();
    /**
     * @brief getLostShips palauttaa pelastamatta jääneiden alusten määrän.
     * @return pelastamatta jääneiden alusten määrä.
     */
    unsigned getLostShips() const;

    /**
     * @brief addPoints lisää pelaajalle pisteitä.
     * @param amount lisättävien pisteiden määrä.
     */
    void addPoints(unsigned amount);
    /**
     * @brief reducePoints vähentää pelaajalta pisteitä.
     * @param amount vähennettävien pisteiden määrä.
     */
    void reducePoints(unsigned amount);
    /**
     * @brief getPoints palautaa pelaajan pisteet.
     * @return pelaajan pisteiden määrä.
     */
    unsigned getPoints() const;

    /**
     * @brief addCredits lisää pelaajalle crediittejä.
     * @param amount lisättävien crediittien määrä.
     */
    void addCredits(unsigned amount);
    /**
     * @brief reduceCredits vähentää pelaajalta crediittejä.
     * @param amount vähennettävien crediittien määrä.
     */
    void reduceCredits(unsigned amount);
    /**
     * @brief getCreditBalance palauttaa pelaajan crediitit.
     * @return pelaajan crediittien määrä.
     */
    int getCreditBalance() const;

private:
    //! pelastettujen alusten määrä.
    unsigned savedShips;
    //! pelastamatta jääneiden alusten määrä.
    unsigned lostShips;
    //! pelaajan pisteet.
    unsigned points;
    //! pelaajan crediitit.
    int credits;

};
}//Student

#endif // STATISTICS_HH
