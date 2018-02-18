#ifndef OBSTACLE_HH
#define OBSTACLE_HH

#include <QObject>

/**
 * @brief Este, joita pelaaja huoltojunillaan poistaa.
 */
class Obstacle : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Roskien tyypit
     */
    enum Type
    {
        bike,
        leaves,
        rabbit,
        reindeer,
        rock,
        count  // the count of different types
    };

    /**
     * @brief Rakentaja
     * @param Uuden esteen tyyppi
     */
    Obstacle(Type type);

    /**
     * @brief Esteen tyyppi
     * @return Esteen tyyppi
     */
    Type type() const;

    /**
     * @brief Esteen junalle törmäyksessä aiheuttama vahinko
     * @return Vahingon suuruus
     */
    uint damage() const;

private:
    Type type_;    ///< Esteen tyyppi
    uint damage_;  ///< Esteen aiheuttama vahinko
};

#endif // OBSTACLE_HH
