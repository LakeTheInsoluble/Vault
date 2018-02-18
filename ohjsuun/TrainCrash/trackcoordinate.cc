#include "trackcoordinate.hh"
#include "station.hh"
#include "stationcoordinate.hh"

#include <cmath>

float TrackCoordinate::progressAt(Track *track, Station *station)
{
    Q_ASSERT(track->touchesStation(station));
    return track->end() == station ? 1.0 : 0.0;
}

TrackCoordinate::TrackCoordinate(Track *track, float progress) :
    RelativeCoordinate(),
    track_(track),
    progress_(progress)
{
    Q_ASSERT(track != nullptr && progress >= 0.0 && progress <= 1.0);
    Q_ASSERT(invariant());
}

TrackCoordinate::TrackCoordinate(Track *track, Station *station) :
    RelativeCoordinate(),
    track_(track),
    progress_(NAN)
{
    Q_ASSERT(track->touchesStation(station));
    if (station == track->start())
    {
        progress_ = 0.0;
    }
    else if (station == track->end())
    {
        progress_ = 1.0;
    }
    Q_ASSERT(invariant());
}

Track *TrackCoordinate::track() const
{
    Q_ASSERT(invariant());
    return track_;
}

float TrackCoordinate::progress() const
{
    Q_ASSERT(invariant());
    return progress_;
}

QGeoCoordinate TrackCoordinate::absolute() const
{
    Q_ASSERT(invariant());
    Station *startStation = track_->start();
    Station *endStation = track_->end();
    if (startStation != nullptr && endStation != nullptr)
    {
        QGeoCoordinate start = startStation->location();
        QGeoCoordinate end = endStation->location();
        if (start.isValid() && end.isValid())
        {
            return start.atDistanceAndAzimuth(progress_ * start.distanceTo(end),
                                              start.azimuthTo(end));
        }
    }
    return QGeoCoordinate();
}

bool TrackCoordinate::routeToPasses(const RelativeCoordinate &to,
                                    const TrackCoordinate &checkpoint) const
{
    Q_ASSERT(invariant());
    return to.routeToPasses(*this, checkpoint);
}

bool TrackCoordinate::routeToPasses(const TrackCoordinate &to,
                                    const TrackCoordinate &checkpoint) const
{
    Q_ASSERT(invariant());
    if (track() == to.track()) {
        if (checkpoint.track() == track())
        {
            float min, max;
            if (progress() <= to.progress())
            {
                min = progress();
                max = to.progress();
            }
            else
            {
                min = to.progress();
                max = progress();
            }

            return min <= checkpoint.progress() && checkpoint.progress() <= max;
        }
    }
    else
    {
        Station *common = track()->commonStation(*to.track());
        if (common != nullptr)
        {
            return routeToPasses(TrackCoordinate(track(), common), checkpoint)
                   || TrackCoordinate(to.track(), common).routeToPasses(to, checkpoint);
        }
    }
    return false;
}

bool TrackCoordinate::routeToPasses(const StationCoordinate &to,
                                    const TrackCoordinate &checkpoint) const
{
    Q_ASSERT(invariant());
    if (track()->touchesStation(to.station()))
    {
        TrackCoordinate temp(track(), to.station());
        return routeToPasses(TrackCoordinate (track(), to.station()), checkpoint);
    }
    else
    {
        return false;
    }
}

QVector<std::shared_ptr<RelativeCoordinate>>
TrackCoordinate::quantizeRouteTo(const RelativeCoordinate &to, double speed,
                                 const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    return to.quantizeRouteFrom(*this, speed, tracks);
}

QVector<std::shared_ptr<RelativeCoordinate>>
TrackCoordinate::quantizeRouteTo(const StationCoordinate &to, double speed,
                                 const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    TrackCoordinate toT(track(), progressAt(track(), to.station()));
    auto result = quantizeRouteTo(toT, speed, tracks);
    result[0] = std::shared_ptr<StationCoordinate>(new StationCoordinate(to));
    return result;
}

QVector<std::shared_ptr<RelativeCoordinate>>
TrackCoordinate::quantizeRouteTo(const TrackCoordinate &to, double speed,
                                 const TracksModel &) const
{
    Q_ASSERT(invariant());
    QVector<std::shared_ptr<RelativeCoordinate>> points;
    points << std::shared_ptr<TrackCoordinate>(new TrackCoordinate(to));

    Track *track = this->track();
    double progress = qAbs(this->progress() - to.progress());
    double length = track->length()*progress;
    double turns = round(length/speed);
    double distance = 0.0;
    for (int i = turns - 1; i > 0; i--)
    {
        distance = (i/turns);
        if (this->progress() < to.progress())
        {
            distance = this->progress() + distance * progress;
        }
        else
        {
            distance = this->progress() - distance * progress;
        }
        points << std::shared_ptr<TrackCoordinate>(new TrackCoordinate(track, distance));
    }

    return points;
}

QVector<std::shared_ptr<RelativeCoordinate>>
TrackCoordinate::quantizeRouteFrom(const RelativeCoordinate &from, double speed,
                                   const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    return from.quantizeRouteTo(*this, speed, tracks);
}

QVector<std::shared_ptr<RelativeCoordinate>>
TrackCoordinate::quantizeRouteFrom(const StationCoordinate &from, double speed,
                                   const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    return from.quantizeRouteTo(*this, speed, tracks);
}

QVector<std::shared_ptr<RelativeCoordinate>>
TrackCoordinate::quantizeRouteFrom(const TrackCoordinate &from, double speed,
                                   const TracksModel &tracks) const
{
    Q_ASSERT(invariant());
    return from.quantizeRouteTo(*this, speed, tracks);
}

bool TrackCoordinate::invariant() const
{
    return track_ != nullptr && progress_ >= 0.0 && progress_ <= 1.0;
}
