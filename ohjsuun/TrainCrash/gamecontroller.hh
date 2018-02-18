#ifndef GAMECONTROLLER_HH
#define GAMECONTROLLER_HH

#include "gamestate.hh"

#include <QObject>

/**
 * @brief Ohjaa pelin kulkua
 */
class GameController : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Palauttaa singleton-olion
     * @return Pelinohjaajaolio
     */
    static GameController *instance();

    /**
     * @brief Toteuttaa pelissä seuraavan askeleen muutokset
     * @param game Peli jonka muutokset tehdään
     */
    Q_INVOKABLE void performTickUpdates(GameState *game) const;

signals:
    /**
     * @brief Siirrä peli pauselle
     */
    void pause();

    /**
     * @brief Siirry tuloksiin
     */
    void toResults();

private:
    /**
     * @brief Rakentaja
     */
    GameController();

    static GameController *instance_;  ///< Pelinohjaaja singleton-olio

};

#endif // GAMECONTROLLER_HH
