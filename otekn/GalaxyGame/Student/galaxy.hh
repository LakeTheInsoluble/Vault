#ifndef GALAXY_HH
#define GALAXY_HH

#include "igalaxy.hh"
#include "ship.hh"
#include "starsystem.hh"
#include "ieventhandler.hh"
#include "objectnotfoundexception.hh"
#include "stateexception.hh"

namespace Student {

/**
 * @brief Galaxy luokka säilöö ja ylläpitää tietoa galaksista ja sen aluksista
 *
 * Galaxy tarjoaa funktioita eri tietojen hakemiseen eri galaksin systeemeistä.
 */
class Galaxy : public Common::IGalaxy, public std::enable_shared_from_this<Galaxy>
{
public:
    Galaxy();
    ~Galaxy();
    /**
     * @brief addShip lisää aluksen galaxiin.
     * @param ship lisättävä alus.
     */
    virtual void addShip(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief removeShip poistaa aluksen galaxista.
     * @param ship poistettava alus.
     */
    virtual void removeShip(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief addStarSystem lisää systeemn galaxiin.
     * @param starSystem lisättävä systeemi.
     */
    virtual void addStarSystem(std::shared_ptr<Common::StarSystem> starSystem);

    /**
     * @brief getShips hakee kaikki galaxin alukset.
     * @return shipvector vektori, joka sisältää galaksin alukset.
     */
    virtual std::shared_ptr<ShipVector> getShips();

    /**
     * @brief getSystemsInRange hakee systeemin lähellä olevat toiset systeemit.
     * @param origin tutkittava systeemi, jonka ympäriltä etsitään.
     * @param range tutkittava matka, jolla etsintä suoritetaan.
     * @return vektori, joka sisältää tarpeeksi lähellä olleet systeemit.
     */
    virtual Common::StarSystem::StarSystemVector getSystemsInRange
    (std::shared_ptr<Common::StarSystem> origin, int range);
    /**
     * @brief getRandomSystem hakee satunnaisen systeemin galaksista.
     * @return satunnainen systeemi.
     */
    virtual std::shared_ptr<Common::StarSystem> getRandomSystem();

    /**
     * @brief getShipsInStarSystem hakee systeemissä olevat alukset.
     * @param name tutkittavan systeemin nimi.
     * @return vektori,joka sisältää systeemin alukset.
     */
    ShipVector getShipsInStarSystem(std::string name);
    /**
     * @brief getSystemNames palauttaa kaikkien galaksin systeemien nimet.
     * @return vektori systeemien nimistä.
     */
    std::vector<std::string> getSystemNames();
    /**
     * @brief getStarSystemByName hakee systeemiä galaksista nimellä.
     * @param name haettavan systeemin nimi.
     * @return löydetty systeemi.
     */
    std::shared_ptr<Common::StarSystem> getStarSystemByName(std::string name);
    /**
     * @brief getStarSystemById hakee systeemiä galaksista id:llä.
     * @param id haettavan systemin id.
     * @return löydetty systeemi
     */
    std::shared_ptr<Common::StarSystem> getStarSystemById(unsigned id);

private:
    //! shipvector kaikista galaksin aluksista poislukien pelaajan aluksen.
    std::shared_ptr<Common::IGalaxy::ShipVector> ships = std::make_shared<Common::IGalaxy::ShipVector>();
   //! starsystemvector galaksin kaikista systeemeistä.
    Common::StarSystem::StarSystemVector starSystems;

};
}//Student

#endif // GALAXY_HH
