#ifndef STATIONCOORDINATE_HH
#define STATIONCOORDINATE_HH

#include "station.hh"
#include "relativecoordinate.hh"

/**
 * @brief Sijainti asemalla.
 */
class StationCoordinate : public RelativeCoordinate
{
public:
    /**
     * @brief Rakentaja.
     * @param station Asema, jonka sijainti halutaan luoda
     * @pre station != nullptr
     */
    explicit StationCoordinate(Station *station);

    /**
     * @brief Hae asema, jonka sijainti tämä on.
     * @return Asema
     */
    Station *station() const;

    QGeoCoordinate absolute() const override;

    bool routeToPasses(const RelativeCoordinate &to,
                       const TrackCoordinate &checkpoint) const override;
    bool routeToPasses(const TrackCoordinate &to,
                       const TrackCoordinate &checkpoint) const override;
    bool routeToPasses(const StationCoordinate &to,
                       const TrackCoordinate &checkpoint) const override;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteTo(const RelativeCoordinate &to, double speed, const TracksModel &tracks)
        const override;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteTo(const StationCoordinate &to, double speed, const TracksModel &tracks)
        const override;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteTo(const TrackCoordinate &to, double speed, const TracksModel &tracks)
        const override;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteFrom(const RelativeCoordinate &from, double speed,
                      const TracksModel &tracks) const override;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteFrom(const StationCoordinate &from, double speed, const TracksModel &tracks)
        const override;

    virtual QVector<std::shared_ptr<RelativeCoordinate>>
    quantizeRouteFrom(const TrackCoordinate &from, double speed, const TracksModel &tracks)
        const override;

private:
    StationCoordinate() = delete;

    /**
     * @brief Luokkainvariantti.
     * @return station != nullptr
     */
    bool invariant() const;

    Station *station_; ///< Asema, jonka sijainti on kyseessä
};

#endif // STATIONCOORDINATE_HH
