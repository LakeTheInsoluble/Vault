#ifndef SERVICETRAIN_HH
#define SERVICETRAIN_HH

#include "train.hh"
#include "relativecoordinate.hh"
#include "util.hh"

#include <QVector>
#include <QObject>
#include <QVariantList>

/**
 * @brief Pelaaja liikuttelee huoltojunia suojellakseen matkustajajunia.
 */
class ServiceTrain : public Train
{
    Q_OBJECT
    Q_PROPERTY(uint price READ price NOTIFY priceChanged)

public:
    /**
     * @brief Rakentaja
     * @param model Mallin nimi
     * @param maxHealth Kunnon enimmäismäärä
     * @param price Hinta
     * @param speed Nopeus
     * @param parent Edeltäjä
     */
    explicit ServiceTrain(QString model, uint maxHealth, uint price, uint speed,
                          QObject *parent = nullptr);

    /**
     * @brief Antaa junan hinnan
     * @return Junan hinta
     */
    uint price() const;

    /**
     * @brief Antaa junan nopeuden
     * @return Junan nopeus
     */
    uint speed()const;

    /**
     * @brief Antaa junan paikan
     * @return Junan paikka
     */
    std::shared_ptr<RelativeCoordinate> location() const;

    /**
     * @brief Asettaa junalle uuden paikan
     * @param location Uusi paikka
     */
    void setLocation(std::shared_ptr<RelativeCoordinate> location);

    /**
     * @brief Antaa junan reittisuunnitelman
     * @return Lista junan seuraavista paikoista
     */
    QVector<std::shared_ptr<RelativeCoordinate>> plan() const;

    /**
     * @brief Asettaa junalle uuden reittisuunnitelman
     * @param plan Asetettava reittisuunnitelma
     */
    void setPlan(QVector<std::shared_ptr<RelativeCoordinate> > plan);

    /**
     * @brief Siirtää junan seuraavan määränpään reittisuunnitelman mukaisesti
     */
    void progressPlan();

    /**
     * @brief Palauttaa junan reitin kohti seuraavaa määränpäätään
     * @return Paikat reitillä
     */
    QVector<std::shared_ptr<RelativeCoordinate>> route() const;

    /**
     * @brief Asettaa junalle reitin seuraavaan määränpäähän
     * @param route Asetettava reitti
     */
    void setRoute(QVector<std::shared_ptr<RelativeCoordinate> > route);

    /**
     * @brief Siirtää junan reittiä yhden askeleen eteenpäin
     */
    void progressRoute();

signals:
    /**
     * @brief Junan hinta on muuttunut
     * @param price Uusi hinta
     */
    void priceChanged(uint price);

private:
    uint price_;  ///< hinta
    uint speed_;  ///< nopeus
    std::shared_ptr<RelativeCoordinate> location_;        ///< paikka
    QVector<std::shared_ptr<RelativeCoordinate>> plan_;   ///< suunnitelma
    QVector<std::shared_ptr<RelativeCoordinate>> route_;  ///< reitti
};

#endif // SERVICETRAIN_HH
