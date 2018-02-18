#ifndef SERVICETRAINSMODEL_HH
#define SERVICETRAINSMODEL_HH

#include "servicetrain.hh"
#include "trackcoordinate.hh"
#include "tracksmodel.hh"
#include "util.hh"

#include <QObject>
#include <QAbstractListModel>
#include <QVector>

#include <memory>

/**
 * @brief Kaikki huoltojunat
 */
class ServiceTrainsModel : public QAbstractListModel
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
    explicit ServiceTrainsModel(StationsModel *stations, TracksModel *tracks, QObject *parent);

    /**
     * @brief Lisää junan malliin
     * @param train Juna joka lisätään
     * @param location Paikka johon juna lisätään
     */
    void addTrain(std::unique_ptr<ServiceTrain>&& train,
                  std::shared_ptr<RelativeCoordinate> location);

    /**
     * @brief Liikuttaa junat uusiin paikkoihin
     */
    void moveTrains();

    /**
     * @brief setPlan
     * @param train
     * @param plan
     */
    void setPlan(ServiceTrain *train, QVector<std::shared_ptr<RelativeCoordinate>> plan);

    /**
     * @brief Aiheuttaa junalle vahinkoa.
     * Jos junaa ei ole olemassa, ei tee mitään
     * @param train Juna johon vahinko aiheutetaan
     * @param damage Aiheutettavan vahingon suuruus
     */
    void causeDamage(ServiceTrain* train, uint damage);

    /**
     * @brief Etsii junat, jotka ovat kahden rataverkosto koordinaatin välissä
     * @param one Ensimmäinen koordinaatti
     * @param two Toinen koordinaatti
     * @return Junat, jotka ovat koordinaattien välissä
     */
    QVector<ServiceTrain *> trainsBetween(const RelativeCoordinate &one,
                                          const RelativeCoordinate &two);

    /**
     * @brief Palauttaa actiivisen junan
     * @return Aktiivinen juna
     */
    ServiceTrain *activeTrain() const;

    /**
     * @brief Vaihtaa aktiivisen junan.
     * Jos annettua junaa ei ole, ei tee mitään
     * @param activeTrain Uusi aktiivinen juna
     */
    void setActiveTrain(ServiceTrain *activeTrain);


    // QAbstractListModel rajapinta

    /**
     * @brief Roolit näkymiä varten
     */
    enum Roles
    {
        TrainRole = Qt::UserRole,
        LocationRole,
        PlanRole,
        HealthRole,
        ActiveRole
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
     */
    void serviceTrainMoved(ServiceTrain*, const RelativeCoordinate &, const RelativeCoordinate &);

private:
    /**
     * @brief Palauttaa junan paikan
     * @param train Juna jonka paikka palautetaan
     * @return Junan paikka
     */
    std::shared_ptr<RelativeCoordinate> location(ServiceTrain *train);

    /**
     * @brief Asettaa junan paikan
     * @param train Juna jonka paikka asetetaan
     * @param location Paikka johon juna asetetaan
     */
    void setLocation(ServiceTrain *train, std::shared_ptr<RelativeCoordinate> location);

    /**
     * @brief Laskee yhdelle junalle paikat sen reitin varrelta
     * @param train Juna jonka paikat lasketaan
     * @return Paikat junalle määrän päähän
     */
    QVector<std::shared_ptr<RelativeCoordinate>> calculateLocations(ServiceTrain *train);

    StationsModel* stations_;        ///< Asemat, joilla junat likkuvat
    TracksModel* tracks_;            ///< Radat joilla junat liikkuvat
    QVector<ServiceTrain*> trains_;  ///< Kaikki junat
    ServiceTrain *activeTrain_;      ///< Aktiivinen juna
};

#endif // SERVICETRAINSMODEL_HH
