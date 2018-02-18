#include "stationcoordinate.hh"
#include "trackcoordinate.hh"
#include "tracksmodel.hh"

#include <cmath> // round

StationCoordinate::StationCoordinate(Station *station) : RelativeCoordinate(), station_(station)
{
    Q_ASSERT(station != nullptr);
    Q_ASSERT(invariant());
}

Station *StationCoordinate::station() const
{
    Q_ASSERT(invariant());
    return station_;
}

QGeoCoordinate StationCoordinate::absolute() const
{
    Q_ASSERT(invariant());
    return station_->location();
}

bool StationCoordinate::routeToPasses(const RelativeCoordinate &to,
                                      const TrackCoordinate &checkpoint) const
{
    Q_ASSERT(invariant());
    return to.routeToPasses(*this, checkpoint);
}

bool StationCoordinate::routeToPasses(const TrackCoordinate &to,
                                      const TrackCoordinate &checkpoint) const
{
    Q_ASSERT(invariant());
    return to.routeToPasses(*this, checkpoint);
}

bool StationCoordinate::routeToPasses(const StationCoordinate &to,
                                      const TrackCoordinate &checkpoint) const
{
    Q_ASSERT(invariant());
    if (*this == to)
    {
        return false;
    }
    auto start = station();
    auto end = to.station();
    auto track = checkpoint.track();
    return (track->start() == start || track->end() == start)
            && (track->start() == end || track->end() == end);
}

QVector<std::shared_ptr<RelativeCoordinate>>
StationCoordinate::quantizeRouteTo(const RelativeCoordinate &to, double speed,
                                   const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    return to.quantizeRouteFrom(*this, speed, tracks);
}

QVector<std::shared_ptr<RelativeCoordinate>>
StationCoordinate::quantizeRouteTo(const StationCoordinate &to, double speed,
                                   const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    Track *track = tracks.getTrack(station(), to.station());
    float fromProgress = TrackCoordinate::progressAt(track, station());
    float toProgress = 1.0 - fromProgress;
    auto result = TrackCoordinate(track, fromProgress)
                      .quantizeRouteTo(TrackCoordinate(track, toProgress), speed, tracks);
    result[0] = std::shared_ptr<StationCoordinate>(new StationCoordinate(to));
    return result;
}

QVector<std::shared_ptr<RelativeCoordinate>>
StationCoordinate::quantizeRouteTo(const TrackCoordinate &to, double speed,
                                   const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    TrackCoordinate fromT(to.track(), TrackCoordinate::progressAt(to.track(), station()));
    return fromT.quantizeRouteTo(to, speed, tracks);
}

QVector<std::shared_ptr<RelativeCoordinate>>
StationCoordinate::quantizeRouteFrom(const RelativeCoordinate &from, double speed,
                                     const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    return from.quantizeRouteTo(*this, speed, tracks);
}

QVector<std::shared_ptr<RelativeCoordinate>>
StationCoordinate::quantizeRouteFrom(const StationCoordinate &from, double speed,
                                     const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    return from.quantizeRouteTo(*this, speed, tracks);
}

QVector<std::shared_ptr<RelativeCoordinate>>
StationCoordinate::quantizeRouteFrom(const TrackCoordinate &from, double speed,
                                     const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    return from.quantizeRouteTo(*this, speed, tracks);
}

bool StationCoordinate::invariant() const { return station_ != nullptr; }
