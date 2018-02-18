#include "station.hh"

Station::Station(QString name, QString code, QGeoCoordinate location, bool passengerTrafic,
                 QObject *parent) :
    QObject(parent),
    name_(name),
    code_(code),
    location_(location),
    passengerTraffic_(passengerTrafic)
{
    Q_ASSERT(location.isValid());
    Q_ASSERT(invariant());
}

QString Station::name() const { return name_; }

QString Station::code() const { return code_; }

QGeoCoordinate Station::location() const { return location_; }

bool Station::passengerTraffic() const { return passengerTraffic_; }

bool Station::invariant() const { return location_.isValid(); }
