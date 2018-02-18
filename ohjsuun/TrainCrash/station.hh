#ifndef STATION_HH
#define STATION_HH

#include <QObject>
#include <QString>
#include <QGeoCoordinate>

/// @brief Rautatieasema
class Station : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate location READ location NOTIFY locationChanged)

public:

    /**
     * @brief Rakentaja
     * @param name Nimi (useimmiten paikkakunta)
     * @param code Lyhytkoodi
     * @param location Aseman sijainti
     * @param passengerTraffic Onko asemalla pamtkustaja liikennettä
     * @param parent Edeltäjä
     * @pre location.isValid()
     */
    Station(QString name, QString code, QGeoCoordinate location, bool passengerTraffic,
            QObject *parent = nullptr);

    /**
     * @brief Antaa aseman nimen
     * @return Nimi
     */
    QString name() const;

    /**
     * @brief Amtaa aseman lyhytkoodin
     * @return koodi
     */
    QString code() const;

    /**
     * @brief Antaa aseman paikan
     * @return Paikka
     */
    QGeoCoordinate location() const;

    /**
     * @brief Kertoo, onko asemalla matkustaja liikennettä
     * @return Tosi, jos asemalla on matkustajaliikennettä
     */
    bool passengerTraffic() const;

signals:
    /**
     * @brief Aseman paikka on muuttunut (olemassa vain QML:n mieliksi).
     * @param newLocation Aseman uusi paikka
     */
    void locationChanged(QGeoCoordinate newLocation);

private:
    /**
     * @brief Invariantti
     * @return Tosi jos location_.isValid()
     */
    bool invariant() const;

    QString name_;             ///< nimi
    QString code_;             ///< koodi
    QGeoCoordinate location_;  ///< sijainti
    bool passengerTraffic_;    ///< onko matkustaja liikennettä
};

#endif // STATION_HH
