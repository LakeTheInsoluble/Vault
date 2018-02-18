#ifndef RELATIVECOORDINATE_HH
#define RELATIVECOORDINATE_HH

#include <QGeoCoordinate>

#include <memory>

class TracksModel;

class StationCoordinate;
class TrackCoordinate;

/**
 * @brief Sijainti suhteessa raideverkkoon.
 */
class RelativeCoordinate
{
public:
    /**
     * @brief Muunna absoluuttisiksi koordinaateiksi.
     * @return absoluuttinen sijainti
     */
    virtual QGeoCoordinate absolute() const = 0;

    /**
     * @brief Vertaa koordinaatteja toisiinsa.
     * @param other Koordinaatti, johon tätä verrataan
     * @return true, jos sijainnit ovat samat
     */
    bool operator==(const RelativeCoordinate &other) const;

    /**
     * @brief Kulkeeko reitti tästä `to`:hon `checkpoint`:in läpi?
     * @param to Määränpää
     * @param checkpoint Mahdollinen välietappi
     * @return true, jos kulkee
     * @pre Reitti ei kulje yli yhden aseman läpi.
     */
    virtual bool routeToPasses(const RelativeCoordinate &to,
                               const TrackCoordinate &checkpoint) const = 0;
    virtual bool routeToPasses(const StationCoordinate &to,
                               const TrackCoordinate &checkpoint) const = 0;
    virtual bool routeToPasses(const TrackCoordinate &to,
                               const TrackCoordinate &checkpoint) const = 0;

    /**
     * @brief Osittele reitti tästä `to`:hon.
     * @param to Määränpää
     * @param speed Nopeus (m/s)
     * @param tracks Raidemalli (raide pitää ehkä etsiä täältä)
     * @return Reitin välipisteet käänteisessä järjestyksessä
     * @pre Ositeltava reitti sijaitsee kokonaan yhdellä raidevälillä (`Track`).
     */
    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteTo(const RelativeCoordinate &to, double speed,
                    const TracksModel &tracks) const = 0;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteTo(const StationCoordinate &to, double speed, const TracksModel &tracks) const = 0;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteTo(const TrackCoordinate &to, double speed, const TracksModel &tracks) const = 0;

    /**
     * @brief Kuten `quantizeRouteTo`, mutta tämä onkin määränpää ja `from` lähtöpiste.
     */
    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteFrom(const RelativeCoordinate &from,
                      double speed, const TracksModel &tracks) const = 0;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteFrom(const StationCoordinate &from, double speed,
                      const TracksModel &tracks) const = 0;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteFrom(const TrackCoordinate &from, double speed,
                      const TracksModel &tracks) const = 0;
};

#endif // RELATIVECOORDINATE_HH
