#include "track.hh"

Track::Track(unsigned id, Station *start, Station *end, double length, QString code,
             QObject *parent) :
    QObject(parent),
    id_(id),
    code_(code),
    start_(start),
    end_ (end),
    length_ (length)
{
    Q_ASSERT(invariant());
}

uint Track::id() const { return id_; }

QString Track::code() const { return code_; }

Station *Track::start() const { return start_; }

Station *Track::end() const { return end_; }

double Track::length() const { return length_; }

bool Track::touchesStation(const Station *station) const
{
    return start() == station || end() == station;
}

Station* Track::commonStation(const Track &other) const
{
    if (start_ == other.start_ || start_ == other.end_)
    {
        return start_;
    }
    else if (end_ == other.start_ || end_ == other.end_)
    {
        return end_;
    }
    return nullptr;
}

bool Track::invariant() const { return start_ != nullptr && end_ != nullptr && length_ >= 0.0; }
