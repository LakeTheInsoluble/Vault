#ifndef MAPCONTROLLER_HH
#define MAPCONTROLLER_HH

#include "station.hh"
#include "track.hh"
#include "gamestate.hh"
#include "relativecoordinate.hh"

#include <QObject>

/**
 * @brief Ohjaa kartan toimintoja
 */
class MapController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Antaa kartanohjaaja olion
     * @return KSingleton kartanohjaajaolio
     */
    static MapController *instance();

    /**
     * @brief Siirtää huoltojunan uuteen paikkaan
     * @param game Peli jonka aktiivista huoltojunaa siirretään
     * @param location Paikka johon juna siirretään
     */
    void serviceTrainTo(GameState *game, std::shared_ptr<RelativeCoordinate> location) const;


    /**
     * @brief Asettaa junan määränpääksi aseman
     * @param game Peli, jonka aktiivista huoltojunaa käsitellään
     * @param station Määränpääksi asetettava asema
     * @pre game != nullptr
     */
    Q_INVOKABLE void serviceTrainToStation(GameState *game, Station *station) const;

    /**
     * @brief Asettaa junan määränpääksi tietyn raiteen
     * @param game Peli jonka aktiivista huoltojunaa käsitellään
     * @param track Määränpääksi asetettava rata
     * @pre game != nullptr
     */
    Q_INVOKABLE void serviceTrainToTrack(GameState *game, Track* track) const;

    /**
     * @brief Lisää satunnaisen esteen satunnaiseen kohtaan rataverkkoa
     * @param game Peli johon roska lisätään
     * @pre game != nullptr
     */
    Q_INVOKABLE void addRandomObstacle(GameState *game);

    /**
     * @brief Vaihtaa pelin aktiivista huoltojunaa
     * Jos annettua junaa ei ole pelissä, ei tee mitään
     * @param game Peli jonka junaa vaihdetaan
     * @param train Uusi Aktiivinen juna
     * @pre game != nullptr
     */
    Q_INVOKABLE void setActiveTrain(GameState *game, ServiceTrain *train);

signals:
    /**
     * @brief Siirry kauppaan
     */
    void toStore();

private:
    /**
     * @brief Rakentaja
     */
    MapController();

    static MapController *instance_;  ///< Singleton-olio
};

#endif // MAPCONTROLLER_HH
