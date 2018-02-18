#ifndef TRACKCOORDINATE_HH
#define TRACKCOORDINATE_HH

#include "relativecoordinate.hh"
#include "track.hh"
#include "stationsmodel.hh"

#include <QGeoCoordinate>

#include <memory>

/**
 * @brief Sijainti tietyllä raidevälillä (`Track`).
 */
class TrackCoordinate : public RelativeCoordinate
{
public:
    /**
     * @brief Kuinka pitkälle radalla pitää mennä, että päästään sen päätyasemalle?
     * @param track Rata
     * @param station Asema
     * @pre track->touchesStation(station)
     * @return Edistysluku (0.0 tai 1.0)
     */
    static float progressAt(Track *track, Station *station);

    /**
     * @brief Rakentaja.
     * @param track Raide, jolla sijaita
     * @param progress Raiteen osuus, joka on kuljettu (välillä [0.0, 1.0]).
     * @pre track != nullptr && progress >= 0.0 && progress <= 1.0
     */
    TrackCoordinate(Track *track, float progress);

    /**
     * @brief Hae raide, jolla sijaitaan.
     * @return Raide
     */
    Track *track() const;

    /**
     * @brief Hae kuljettu osuus.
     * @return Kuljettu osuus (välillä [0.0, 1.0])
     */
    float progress() const;

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
    TrackCoordinate() = delete;

    /**
     * @brief Luo sijainti, joka on raiteen asemanpuoleisessa päässä.
     * @param track Raide, jolla sijaita
     * @param station Asema, jonka päässä sijaita
     * @pre track->touchesStation(station)
     */
    TrackCoordinate(Track *track, Station *station);

    /**
     * @brief Luokkainvariantti.
     * @return track_ != nullptr && progress_ >= 0.0 && progress_ <= 1.0
     */
    bool invariant() const;

    Track *track_; ///< Raide, jolla sijaitaan
    float progress_; ///< Raiteen osuus, joka on kuljettu (välillä [0.0, 1.0]).
};

#endif // TRACKCOORDINATE_HH
