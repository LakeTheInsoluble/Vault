#ifndef STATIONSMODEL_HH
#define STATIONSMODEL_HH

#include "station.hh"
#include "track.hh"
#include "stationcoordinate.hh"

#include <QObject>
#include <QAbstractListModel>
#include <QString>
#include <QVector>

#include <memory>

/**
 * @brief Kaikki asemat
 */
class StationsModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief Rakentaja
     * @param Edeltäjä
     */
    explicit StationsModel(QObject *parent);

    /**
     * @brief Lukee asemat JSON-tiedostosta
     * @param filename Polku tiedostoon, joka luetaan
     * @throws std::exception, jos tiedostoa ei voida avata tai lukea
     */
    void readStations(const QString &filename);

    /**
     * @brief Etsii aseman, joka vastaa annettua koodia
     * @param code Koodi jolle asema etsitään
     * @return Asema, jolla on oikea koodi, nullptr, jos asemaa ei löydy
     */
    Q_INVOKABLE Station *getStation(QString code) const;

    /**
     * @brief Palauttaa aseman paikan
     * @param station Asema, jonka paikka halutaan tietää
     * @return Koordinaatti, jossa asema sijaitsee
     */
    std::shared_ptr<StationCoordinate> location(Station *station) const;

    /**
     * @brief Laskee kahden aseman välisen välimatkan linnuntietä
     * @param station1 Asema yksi
     * @param station2 Asema kaksi
     * @return Palauttaa välimatkan kahden aseman välillä,
     *         0, jos jompaa kumpaa asemaa ei ole olemassa
     */
    double distanceBetween(Station *station1, Station *station2) const;

    /**
     * @brief Palauttaa kaikki asemat
     * @return Kaikki asemat
     */
    QVector<Station*> stations() const;

    /**
     * @brief Poistaa kaikki asemat, joilta ei ole ratoja annetussa ratalistassa
     * @param tracks Radat, joita vastaavat asemat säilytetään
     */
    void removeStationsWithoutTracks(const QVector<Track *> &tracks);

    // QAbstractItemModel interface
    enum StationsRoles
    {
        StationRole = Qt::UserRole,
        NameRole,
        CodeRole,
        LocationRole,
        DrawRole
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    /**
     * @brief Lisää aseman malliin
     * @param station Asema joka lisätään
     */
    void addStation(std::unique_ptr<Station>&& station);

    /**
     * @brief Poistaa aseman mallista
     * @param station Asema joka poistetaan
     */
    void removeStation(Station* station);

    /**
     * @brief Luokkainvariantti
     * @return stations_.size() == stationCodes_.size() == locations_.size()
     */
    bool invariant() const;

    QVector<Station*> stations_;             ///< Kaikki asemat
    QHash<QString, Station*> stationCodes_;  ///< Koodeja vastaavat asemat
    QHash<Station*, std::shared_ptr<StationCoordinate>> locations_;  ///< Asemien paikat
};

#endif // STATIONSMODEL_HH
