#ifndef PASSENGERTRAINSMODEL_HH
#define PASSENGERTRAINSMODEL_HH

#include "passengertrain.hh"
#include "tracksmodel.hh"
#include "util.hh"

#include <QObject>
#include <QAbstractListModel>

/**
 * @brief Kaikki matkustajajunat
 */
class PassengerTrainsModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief Rakentaja
     * @param stations Asemat junien liikkumiseen
     * @param tracks Radat junien liikkumiseen
     * @param parent Edeltäjä
     * @pre stations != nullptr && tracks != nullptr
     */
    explicit PassengerTrainsModel(StationsModel *stations, TracksModel *tracks, QObject *parent);

    /**
     * @brief Lukee junat aikatauluineen JSON-tiedostosta
     * @param file avoin JSON data, joka luetaan
     * @throws std::runtime_error jos juna dataa ei voi lukea tai se on virheellistä
     */
    void readTrains(const QByteArray &file);

    /**
     * @brief Siirtää junat uusille paikoilleen
     * @param time Ajanhetki, jolle paikat lasketaan
     */
    void moveTrains(QDateTime time);

    /**
     * @brief Aiheuttaa junaan vahinkoa
     * Jos junaa ei ole mallissa, tai se ei ole liikkessä, ei tehdä mitään
     * @param train Juna, johon vahinko kohdistuu
     * @param damage Vahingon suuruus
     */
    void causeDamage(PassengerTrain* train, uint damage);

    /**
     * @brief Etsii junat, jotka ovat kahden rataverkosto koordinaatin välissä
     * @param one Ensimmäinen koordinaatti
     * @param two Toinen koordinaatti
     * @return Junat, jotka ovat koordinaattien välissä
     */
    QVector<PassengerTrain *> trainsBetween(const RelativeCoordinate &one,
                                            const RelativeCoordinate &two);

    // QAbstractItemModel rajapinta

    /**
     * @brief Roolit näkymiä varten
     */
    enum Roles
    {
        LocationRole = Qt::UserRole + 1,
        HealthRole
    };

    /**
     * @brief Palauttaa ajossa olevien junien määrän
     * @param parent Tämän alla olevien junien määrä palautetaan
     * @return Ajossa olevien junien määrä, 0 jos parent ei ole validi
     */
    int rowCount(const QModelIndex &parent) const override;

    /**
     * @brief Palauttaa tiety junan roolin mukaisen datan
     * @param index Yksilöi käsiteltävän junan
     * @param role Rooli, jonka mukainen data palautetaan
     * @return index:n mukaisen junan data, invalidi QVariant,
     *         jos juna tai rooli ei ole validi
     */
    QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief Palauttaa sallittujen roolien nimet
     * @return Roolien nimet
     */
    QHash<int, QByteArray> roleNames() const override;

signals:

    /**
     * @brief Juna on liikkunut
     * @param train Liikkunut juna
     * @param from Täältä lähdettiin
     * @param to Tänne päädyttiin
     */
    void passengerTrainMoved(PassengerTrain* train, const RelativeCoordinate &from,
                             const RelativeCoordinate &to);

    /**
     * @brief Juna pääsi määränpäähänsä
     */
    void passengerTrainFinished();

    /**
     * @brief Juna hajosi kesken matkan
     */
    void passengerTrainBroken();

    /**
     * @brief Mallissa ei ole enää junia
     */
    void noMoreTrains();

private:
    /**
     * @brief Asettaa ajoon junat ajoon annetulla ajanhetkellä.
     * Laskee myös uusille junille aloituspaikat.
     * @param time Ajanhetki, jota käsitellään
     */
    void checkRunningTrains(QDateTime time);

    /**
     * @brief Tarkistaa määrän päihinsä saapuneet ja hajonneet junat, ja tuhoaa ne.
     * @param time Ajanhetki, jota käsitellään
     */
    void checkFinishedTrains(QDateTime time);

    /**
     * @brief Laskee kaikille ajossa oleville junille paikat
     * @param time Ajanhetki jota käsitellään
     */
    void calculateLocations(QDateTime time);

    /**
     * @brief Laskee yhdelle junalle uuden paikan
     * @param train Juna jolle paikka lasketaan
     * @param time Ajanhetki, jota käsitellään
     * @return Paikka, jossa juna on annetulla ajanhetkellä
     */
    std::shared_ptr<RelativeCoordinate> calculateLocation(PassengerTrain *train, QDateTime time);

    StationsModel* stations_;                 ///< Asemat, joilla junat liikkuvat
    TracksModel* tracks_;                     ///< Raiteet, joilla junat liikkuvat
    QVector<PassengerTrain*> trainsWaiting_;  ///< Junat, jotka eivät ole vielä lähteneet liikkeelle
    QVector<PassengerTrain*> trainsRunning_;  ///< Junat, jotka ovat tällä hetkellä ajossa
};

#endif // PASSENGERTRAINSMODEL_HH
