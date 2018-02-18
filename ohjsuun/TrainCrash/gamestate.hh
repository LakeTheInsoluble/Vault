#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "player.hh"
#include "obstaclesmodel.hh"
#include "stationsmodel.hh"
#include "tracksmodel.hh"
#include "servicetrainsmodel.hh"
#include "passengertrainsmodel.hh"
#include "filedownloader.hh"
#include "traincatalog.hh"
#include "util.hh"

#include <QObject>
#include <QDateTime>

/**
 * @brief Käynnissä olevan pelin tila.
 */
class GameState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Player* player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(StationsModel* stations READ stations NOTIFY stationsChanged)
    Q_PROPERTY(TracksModel* tracks READ tracks NOTIFY tracksChanged)
    Q_PROPERTY(ObstaclesModel* obstacles READ obstacles NOTIFY obstaclesChanged)
    Q_PROPERTY(PassengerTrainsModel* passengerTrains READ passengerTrains
               NOTIFY passengerTrainsChanged)
    Q_PROPERTY(ServiceTrainsModel* serviceTrains READ serviceTrains NOTIFY serviceTrainsChanged)
    Q_PROPERTY(TrainCatalog* catalog READ catalog NOTIFY catalogChanged)
    Q_PROPERTY(uint points READ points NOTIFY pointsChanged)
    Q_PROPERTY(uint status READ status NOTIFY statusChanged)

public:
    explicit GameState(QObject *parent = nullptr);

    /**
     * @brief Pelin mahdolliset tilat
     */
    enum GameStatus
    {
        NotStarted,
        Running,
        Lost,
        Won
    };

    /**
     * @brief Antaa pelaajan
     * @return pelaaja
     */
    Player *player() const;
    /**
     * @brief Asettaa pelille pelaajan
     * @param player Pelaaja
     */
    Q_INVOKABLE void setPlayer(Player *player);

    /**
     * @brief Antaa pelin asemat
     * @return Malli pelin asemista
     */
    StationsModel *stations();

    /**
     * @brief Pelin raiteet
     * @return Malli perin raiteista
     */
    TracksModel *tracks();

    /**
     * @brief Pelin tämän hetkiset esteet
     * @return Malli esteistä
     */
    ObstaclesModel *obstacles();

    /**
     * @brief Pelin matkustajajunat
     * @return Malli matkustajajunat
     */
    PassengerTrainsModel *passengerTrains();

    /**
     * @brief Pelin huoltojunat
     * @return Malli huoltojunista
     */
    ServiceTrainsModel *serviceTrains();

    /**
     * @brief Katalogi peliln junatyypeistä
     * @return Pelin junatyyppikatalogin
     */
    TrainCatalog *catalog();

    /**
     * @brief Siirtää pelin kelloa annetun ajan eteenpäin
     * @param Siirrettävien sekutien määrä
     */
    void moveTime(uint seconds = 60);

    /**
     * @brief Antaa pelin tämänhetkisen ajan
     * @return Tämänhetkinen aika
     */
    QDateTime time() const;

    /**
     * @brief Pelin tämän hetkiset pisteet
     * @return Pelin tämänhetkiset pisteet
     */
    uint points() const;

    /**
     * @brief Palauttaa pelin statuksen
     * @return Pelin status
     */
    GameStatus status() const;

signals:
    /**
     * @brief Pelaajaa on muutettu
     * @param player Muuttunut pelaaja
     */
    void playerChanged(Player *player);

    /**
     * @brief Pelin asemissa on tapahtunut muutos
     * @param stations Muuttunut asemamalli
     */
    void stationsChanged(StationsModel *stations);

    /**
     * @brief Pelin raiteissa on tapahtunut muutos
     * @param tracks Muuttunut ratamalli
     */
    void tracksChanged(TracksModel *tracks);

    /**
     * @brief Pelin esteet ovat muuttuneet
     * @param obstacles Muuttunut estemalli
     */
    void obstaclesChanged(ObstaclesModel *obstacles);

    /**
     * @brief Pelin matkustajajunat ovat muuttuneet
     * @param passengerTrains Muuttunut matkustajajunamalli
     */
    void passengerTrainsChanged(PassengerTrainsModel *passengerTrains);

    /**
     * @brief Pelin huoltojunat ovat muuttuneet
     * @param serviceTrains Muuttunut huoltojunamalli
     */
    void serviceTrainsChanged(ServiceTrainsModel *serviceTrains);

    /**
     * @brief Pelin junakatalogi on muuttunut
     * @param catalog Muuttunut katalogi
     */
    void catalogChanged(TrainCatalog *catalog);

    /**
     * @brief Pelin pisteet ovat muuttuneet
     */
    void pointsChanged();

    /**
     * @brief Pelin status on muuttunut
     */
    void statusChanged();

    /**
     * @brief Peli loppui
     */
    void finished();

private slots:
    /**
     * @brief Matkustajajunat loppuivat
     */
    void noMorePassengerTrains();
private:
    /**
     * @brief Matkustajajuna data ladataan tästä osoitteesta
     * @return URL junadataan
     */
    QUrl trainUrl();

    /**
     * @brief Lataa pelin matkustajajunat
     */
    void loadPassengerTrains();

    /**
     * @brief Suorittaa toimenpiteet, kun huoltojuna on liikkunut.
     * Tarittaessa poistaa esteet, vahingoittaa junia, laskee pisteet ja kupongit..
     * @param train Liikkunut huoltojuna
     * @param oldLoc Vanha sijainti
     * @param newLoc Uusi sijainti
     */
    void serviceTrainMoved(ServiceTrain*train, const RelativeCoordinate &oldLoc,
                           const RelativeCoordinate &newLoc);

    /**
     * @brief Suorittaa toimenpiteet, kun matkustajajuna on liikkunut.
     * Aiheuttaa junille tarvittaessa vahinkoa, ja laskee pisteet.
     * @param train Liikkunut juna
     * @param oldLoc Alkupiste
     * @param newLoc Loppupiste
     */
    void passengerTrainMoved(PassengerTrain*train, const RelativeCoordinate &oldLoc,
                             const RelativeCoordinate &newLoc);
    /**
     * @brief Antaa kuponkeja poistetuista roskista
     */
    void obstacleRemoved();

    /**
     * @brief Laskee pisteet, kun matkustajajuna hajoaa
     */
    void passengerTrainBroken();

    /**
     * @brief Laskee pisteet, kun matkustajajuna pääsee perille
     */
    void passengerTrainFinished();
    
    Player *player_;                        ///< pelaaja
    StationsModel stations_;                ///< asemat
    TracksModel tracks_;                    ///< radat
    ObstaclesModel obstacles_;              ///< esteet
    PassengerTrainsModel passengerTrains_;  ///< matkustajajunat
    ServiceTrainsModel serviceTrains_;      ///< huoltojunat
    TrainCatalog catalog_;                  ///< junakatalogi
    QDateTime time_;                        ///< pelin ajanhetki
    int points_;                            ///< pelin pisteet
    FileDownloader fileDownloader_;         ///< tiedostonlataaja
    GameStatus status_;                     ///< pelin status
};

#endif // GAMESTATE_HH
