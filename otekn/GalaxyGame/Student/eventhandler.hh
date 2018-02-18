#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH

#include "starsystem.hh"
#include "ieventhandler.hh"

#include <QObject>
#include <QWidget>

namespace Student {
/**
 * @brief EventHandler välittää eri eventit pääikkunalle.
 */
class EventHandler: public QObject, public Common::IEventHandler
{
    Q_OBJECT

public:
    explicit EventHandler(QObject *parent = 0);
    ~EventHandler();
    /**
     * @brief shipSpawned aluksen spawnauksen handleri.
     * @param ship spawnattu alus.
     */
    void shipSpawned(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief shipRemoved aluksen poistamisen handleri.
     * @param ship poistettava alus.
     */
    void shipRemoved(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief shipRelocated aluksen siirtymisen handleri.
     * @param ship siirrettävä alus.
     * @param starSystem systeemi, johon alus siirretään.
     */
    void shipRelocated(std::shared_ptr<Common::Ship> ship,
                       std::shared_ptr<Common::StarSystem> starSystem);
    /**
     * @brief shipMoved aluksen liikkumisen handleri.
     * @param ship liikutettava alus.
     * @param origin aluksen lähtöpiste.
     * @param target aluksen kohdepiste.
     */
    void shipMoved(std::shared_ptr<Common::Ship> ship,
                   Common::Point origin,
                   Common::Point target);
    /**
     * @brief exceptionInExecution aluksen toimnnon suorittamisen virheen handleri.
     * @param ship virheen tuotanut alus.
     * @param msg virhee viesti.
     */
    void exceptionInExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg);
    /**
     * @brief distressOn aluksen avunpyynnön handleri.
     * @param ship apua pyytävä alus.
     */
    void distressOn(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief distressOff aluksen avunpyynnön lopettamisen handleri.
     * @param ship avunpyynnön lopettanut alus.
     */
    void distressOff(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief shipAbandoned aluksen hylkäämisen handleri.
     * @param ship hylättävä alus.
     */
    void shipAbandoned(std::shared_ptr<Common::Ship> ship);

signals:
    /**
     * @brief lahetaAlusSpawnattu signaali spawnatusta aluksesta.
     * @param ship spawnattu alus.
     */
    void lahetaAlusSpawnattu(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief lahetaAlusSpawnattu signaali poistetusta aluksesta.
     * @param ship poistettu alus.
     */
    void lahetaAlusPoistettu(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief lahetaLiike signaali alukse liikkeestä.
     * @param ship liikutettava alus.
     * @param origin aluksen lähtöpiste.
     * @param target aluksen kohdepiste.
     */
    void lahetaLiike(std::shared_ptr<Common::Ship> ship,
                     Common::Point origin, Common::Point target);

    /**
     * @brief lahetaPoikkeus signaali aluksen toiminnon suorittamisen virheestä.
     * @param ship virheen tuottanut alus.
     * @param msg virheen viesti.
     */
    void lahetaPoikkeus(std::shared_ptr<Common::Ship> ship,
                        const std::__cxx11::string &msg);
    /**
     * @brief lahetaDistressOn signaali aluksen avunpyynnöstä.
     * @param ship apua pyytänyt alus.
     */
    void lahetaDistressOn(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief lahetaDistressOff signaali avunpyynnön lopettamisesta.
     * @param ship avunpyynnön lpettanut alus.
     */
    void lahetaDistressOff(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief lahetaAlusHylatty signaali aluksen hylkäämisestä.
     * @param ship hylätty alus.
     */
    void lahetaAlusHylatty(std::shared_ptr<Common::Ship> ship);

};
}

#endif // EVENTHANDLER_HH
