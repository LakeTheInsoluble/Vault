#include "stationsmodel.hh"
#include "station.hh"
#include "stationcoordinate.hh"

#include <QSet>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <stdexcept>

StationsModel::StationsModel(QObject *parent) : QAbstractListModel(parent)
{
    Q_ASSERT(invariant());
}

void StationsModel::readStations(const QString &filename)
{
    Q_ASSERT(invariant());
    // Luetaan tiedosto
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        // avaus epäonnistui
        file.close();
        throw std::runtime_error("Ei voitu avata tiedostoa: " + filename.toStdString());
    }
    QByteArray rawData = file.readAll();
    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(rawData));
    QJsonArray stationArray = doc.array();
    for (auto stationRef: stationArray)
    {
        if (stationRef.isObject()){

            QJsonObject stationObject = stationRef.toObject();

            QString stationName = stationObject.value("stationName").toString();
            QString stationShortCode = stationObject.value("stationShortCode").toString();
            double latitude = stationObject.value("latitude").toDouble();
            double longitude = stationObject.value("longitude").toDouble();
            bool passengerTraffic = stationObject.value("passengerTraffic").toBool();

            addStation(std::unique_ptr<Station>(
                           new Station(stationName, stationShortCode,
                                       QGeoCoordinate(latitude, longitude), passengerTraffic)));
        }
        else
        {
            throw std::runtime_error("Virheellinen tiedosto: " + filename.toStdString());
        }
    }
    Q_ASSERT(invariant());
}

Station *StationsModel::getStation(QString code) const
{
    Q_ASSERT(invariant());
    auto station_iter = stationCodes_.find(code);
    return station_iter != stationCodes_.end() ? station_iter.value() : nullptr;
}

std::shared_ptr<StationCoordinate> StationsModel::location(Station *station) const
{
    Q_ASSERT(invariant());
    auto locationIter = locations_.find(station);
    return locationIter != locations_.end() ? locationIter.value() : nullptr;
}

double StationsModel::distanceBetween(Station *station1, Station *station2) const
{
    Q_ASSERT(invariant());
    if (!stations_.contains(station1) || !stations_.contains(station2))
    {
        return 0;
    }
    else
    {
        return station1->location().distanceTo(station2->location());
    }
}

void StationsModel::addStation(std::unique_ptr<Station>&& station)
{
    Q_ASSERT(invariant());
    Station *rawStation = station.release();
    rawStation->setParent(this);

    beginInsertRows(QModelIndex(), stations_.size(), stations_.size());
    stations_.append(rawStation);
    stationCodes_.insert(rawStation->code(), rawStation);
    locations_.insert(rawStation,
                      std::shared_ptr<StationCoordinate>(new StationCoordinate(rawStation)));
    endInsertRows();
    Q_ASSERT(invariant());
}

void StationsModel::removeStation(Station *station)
{
    Q_ASSERT(invariant());
    stations_.removeAll(station);
    stationCodes_.remove(station->code());
    locations_.remove(station);
    delete station;
    Q_ASSERT(invariant());
}

void StationsModel::removeStationsWithoutTracks(const QVector<Track*> &tracks)
{
    Q_ASSERT(invariant());
    QSet<Station*> foundStations;
    for (Track *track : tracks)
    {
        foundStations.insert(track->start());
        foundStations.insert(track->end());
    }
    auto iter = stations_.begin();
    while(iter != stations_.end())
    {
        Station *station = *iter;
        if (!foundStations.contains(station))
        {
            removeStation(station);
        }
        else
        {
            ++iter;
        }
    }
    Q_ASSERT(invariant());
}

int StationsModel::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(invariant());
    return parent.isValid() ? 0 : stations_.size();
}

QVariant StationsModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(invariant());
    if (!index.isValid() || index.row() >= stations_.size())
    {
        return QVariant();
    }
    else
    {
        Station* station = stations_.at(index.row());
        switch (role)
        {
        case Qt::DisplayRole: return QVariant(station->name());
        case StationRole: return QVariant::fromValue(station);
        case NameRole: return QVariant(station->name());
        case CodeRole: return QVariant(station->code());
        case LocationRole: return QVariant::fromValue(station->location());
        case DrawRole: return QVariant(station->passengerTraffic());
        default: return QVariant();
        }
    }
}

QHash<int, QByteArray> StationsModel::roleNames() const
{
    Q_ASSERT(invariant());
    return {{StationRole, "station"},
            {NameRole, "name"},
            {CodeRole, "code"},
            {LocationRole, "location"},
            {DrawRole, "draw"}};
}

QVector<Station *> StationsModel::stations() const
{
    Q_ASSERT(invariant());
    return stations_;
}

bool StationsModel::invariant() const
{
    return stations_.size() == stationCodes_.size() && stations_.size() == locations_.size();
}
