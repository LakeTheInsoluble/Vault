#include "tracksmodel.hh"
#include "track.hh"
#include "stationcoordinate.hh"
#include "trackcoordinate.hh"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGeoCoordinate>

#include <cmath> // INFINITY
#include <queue>

using std::dynamic_pointer_cast;

// yhteys reititysalgoritmille
struct connection
{
    Station* to;
    double distance;
    bool operator<(const connection& other) const { return distance > other.distance; }
};

TracksModel::TracksModel(StationsModel* stations, QObject *parent) :
    QAbstractListModel(parent),
    stations_ (stations),
    tracks_ ()
{}

void TracksModel::readTracks(const QString &filename)
{
    // Luetaan tiedosto
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        // avaus epäonnistui
        file.close();
        throw std::runtime_error("Ei voitu avata tiedostoa: " + filename.toStdString());
    }
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll()));
    file.close();

    QJsonArray trackArray = doc.object().value("tracks").toArray();
    for (auto trackRef: trackArray)
    {
        if (trackRef.isObject()){
            QJsonObject trackObject = trackRef.toObject();
            QString code = trackObject.value("trackCode").toString();
            QJsonArray stationArray = trackObject.value("stations").toArray();
            QVector<QString> stationlist;
            for (auto stationRef : stationArray)
            {
                if (stationRef.isObject())
                {
                    QJsonObject station = stationRef.toObject();
                    QString code = station.value("name").toString();
                    if (stations_->getStation(code) != nullptr)
                    {
                        if (stationlist.empty() || stationlist.last() != code)
                        {
                            stationlist << code;
                        }
                    }
                }
                else
                {
                    throw std::runtime_error("Virheellinen tiedosto: " + filename.toStdString());
                }
            }
            if (stationlist.size() >= 2)
            {
                for (int i = 1; i < stationlist.size(); ++i)
                {
                    Station *start = stations_->getStation(stationlist[i-1]);
                    Station *end = stations_->getStation(stationlist[i]);
                    double length = stations_->distanceBetween(start, end);
                    addTrack(
                        std::unique_ptr<Track>(
                            new Track(tracks_.size(), start, end, length, code)));
                }
            }
        }
        else
        {
            throw std::runtime_error("Virheellinen tiedosto: " + filename.toStdString());
        }
    }
    stations_->removeStationsWithoutTracks(tracks_);
}

Track *TracksModel::getTrack(Station *one, Station *two) const
{
    if (one != nullptr && two != nullptr)
    {
        for (Track *track : tracks_)
        {
            if ((track->start() == one || track->end() == one)
                    && (track->start() == two || track->end() == two))
            {
                return track;
            }
        }
    }
    return nullptr;
}

Track *TracksModel::getRandomTrack() const { return tracks_.at(qrand() % tracks_.size()); }

QVector<std::shared_ptr<RelativeCoordinate>>
TracksModel::getShortestPath(std::shared_ptr<RelativeCoordinate> coordFrom,
                             std::shared_ptr<RelativeCoordinate> coordTo)
{
    // Dijkstran algoritmi

    auto stationOld = dynamic_pointer_cast<StationCoordinate>(coordFrom);
    auto stationNew = dynamic_pointer_cast<StationCoordinate>(coordTo);
    auto trackOld = dynamic_pointer_cast<TrackCoordinate>(coordFrom);
    auto trackNew = dynamic_pointer_cast<TrackCoordinate>(coordTo);

    bool startOnTrack;
    bool endOnTrack;
    stationStruct *current;
    Station* from;
    Station* to;
    Station* toAlt;
    std::priority_queue<connection> priorityQueue;
    QVector<std::shared_ptr<RelativeCoordinate>> route;

    createStationStructs();

    if (trackOld != nullptr && trackNew != nullptr && trackOld->track() == trackNew->track())
    {
        route << trackNew;
        return route;
    }
    if (stationOld != nullptr && stationNew != nullptr
        && stationOld->station() == stationNew->station())
    {
        route << stationNew;
        return route;
    }

    for (stationStruct *station : stationStructs_)
    {
        station->distance = INFINITY;
        station->last = nullptr;
        station->visited = false;
    }

    if (trackOld != nullptr)
    {
        double length = trackOld->track()->length();
        float progress = trackOld->progress();
        startOnTrack = true;

        from = trackOld->track()->start();
        current = stationStructs_[from];
        current->distance = 0;
        current->visited = true;
        priorityQueue.push(connection{from,length*progress});

        from = trackOld->track()->end();
        current = stationStructs_[from];
        current->distance = 0;
        current->visited = true;
        priorityQueue.push(connection{from,length-length*progress});
    }
    else
    {
        startOnTrack = false;

        from = stationOld->station();
        current = stationStructs_[from];
        current->distance = 0;
        current->visited = true;
        priorityQueue.push(connection{from,0});
    }
    if (trackNew != nullptr)
    {
        endOnTrack = true;

        to = trackNew->track()->start();
        toAlt = trackNew->track()->end();
    }
    else
    {
        endOnTrack = false;
        to = stationNew->station();
    }
    while (!priorityQueue.empty())
    {
        connection top = priorityQueue.top();
        priorityQueue.pop();
        current = stationStructs_[top.to];

        if (top.to == to || top.to == toAlt)
        {
            if (endOnTrack)
            {
                route << trackNew;
            }
            while (current->last != nullptr)
            {
                route << stations_->location(current->station);
                current = stationStructs_[current->last];
            }
            if (startOnTrack)
            {
                route << stations_->location(current->station);
            }
            while(!priorityQueue.empty())
            {
                priorityQueue.pop();
            }
            return route;
        }
        for (std::pair<Station*, double> it : current->connected)
        {
            stationStruct *next = stationStructs_[it.first];
            next->visited = true;
            if (top.distance + it.second < next->distance)
            {
                next->distance = top.distance + it.second;
                next->last = current->station;
                priorityQueue.push(connection{next->station, top.distance + it.second});
            }
        }
    }
    // route << newCoordinate;
    return route;
}

int TracksModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : tracks_.size();
}

QVariant TracksModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= tracks_.size())
    {
        return QVariant();
    }
    else
    {
        Track *track = tracks_.at(index.row());
        switch (role)
        {
        case Qt::DisplayRole: return QVariant(track->code());
        case TrackRole: return QVariant::fromValue(track);
        case CodeRole: return QVariant(track->code());
        case IdRole: return QVariant(track->id());
        case PathRole:
        {
            QGeoCoordinate from = track->start()->location();
            QGeoCoordinate to = track->end()->location();
            QVariantList list;
            list << QVariant::fromValue(from) << QVariant::fromValue(to);
            return list;
        }
        default: return QVariant();
        }
    }
}

QHash<int, QByteArray> TracksModel::roleNames() const
{
    return {{TrackRole, "track"},
            {CodeRole, "code"},
            {IdRole, "id"},
            {PathRole, "coordinates"}};
}


void TracksModel::addTrack(std::unique_ptr<Track>&& track)
{
    Track *rawTrack = track.release();
    rawTrack->setParent(this);

    beginInsertRows(QModelIndex(), tracks_.size(), tracks_.size());
    tracks_ << rawTrack;
    endInsertRows();
}

void TracksModel::createStationStructs(bool force)
{
    if (force || stationStructs_.size() == 0)
    {
        for (Station *s : stations_->stations())
        {
            stationStructs_[s] = new stationStruct();
            stationStructs_[s]->station = s;
        }
        for (Track* track : tracks_)
        {
            Station* from = track->start();
            Station* to = track->end();
            double length = track->length();

            stationStructs_[from]->connected.push_back(std::make_pair(to, length));
            stationStructs_[to]->connected.push_back(std::make_pair(from, length));
        }
    }
}
