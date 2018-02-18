#ifndef STORECONTROLLER_HH
#define STORECONTROLLER_HH

#include "gamestate.hh"
#include "servicetrain.hh"
#include "util.hh"

#include <QObject>
#include <QString>

/// @brief Toiminnot, joita voi suorittaa kaupassa/korjaamossa
class StoreController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Ainokainen ilmentymä
     * @return ilmentymä
     */
    static StoreController *instance();

    /**
     * @brief Korjaa huoltojunaa
     * @param game Peli
     * @param train Korjattava huoltojuna
     * @param amount Kunnon lisäyksen määrä
     * @param cost Korjauksen hinta
     * @pre Pelaajalla on ainakin hinnan verran kuponkeja
     * @post Junaa on korjattu pyydetyn määrän verran (tai täyteen) ja pelaajalta on vähennetty
     *       hinnan verran kuponkeja.
     */
    Q_INVOKABLE void repairTrain(GameState *game, ServiceTrain *train, uint amount,
                                 uint cost) const;

    /**
     * @brief Osta uusi huoltojuna.
     * @param game Peli
     * @param model Ostettavan junan mallinimi
     * @param price Ostettavan junan hinta
     * @param maxHealth Ostettavan junan maksimi- (ja aloitus-) kunto.
     * @param speed Ostettavan junan nopeus
     * @pre Pelaajalla on ainakin hinnan verran kuponkeja
     * @post Ostettu juna on pelaajan omistuksessa ja käytettävissä (Jyväskylässä) ja elaajalta on
     *       vähennetty hinnan verran kuponkeja.
     */
    Q_INVOKABLE void buyTrain(GameState *game, QString model, uint price, uint maxHealth,
                              uint speed) const;

signals:
    /**
     * @brief Siirry karttanäkymään.
     */
    void toMap();

private:
    static StoreController *instance_; ///< Ainokainen ilmentymä (tai nullptr jos ei ole tarvittu)

    /**
     * @brief Rakentaja
     */
    StoreController();
};

#endif // STORECONTROLLER_HH
