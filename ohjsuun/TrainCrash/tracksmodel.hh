#ifndef TRACKSMODEL_HH
#define TRACKSMODEL_HH

#include "stationsmodel.hh"
#include "relativecoordinate.hh"
#include "track.hh"

#include <QObject>
#include <QAbstractListModel>
#include <QVector>

#include <memory>


/**
 * @brief Kaikki raideyhteydet
 */
class TracksModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief Rakentaja
     * @param stations Asemat joiden väleille radat muodostuvat
     * @param parent Edeltäjä
     * @pre stations != nullptr
     */
    explicit TracksModel(StationsModel *stations, QObject *parent);

    /**
     * @brief Lukee radat JSON tiedostosta
     * @param filename Tiedoston polku, josta radat luetaan
     */
    void readTracks(const QString &filename);

    /**
     * @brief Etsii radan kahden aseman väliltä
     * @param one Ensimmäinen etsittävistä asemista
     * @param two Toinen etsittävistä asemista
     * @return Radan asemien välillä,
     *         nullptr, jos asemien välillä ei ole yhteyttä, tai jompikumpi
     *         asemista on nullptr
     */
    Track *getTrack(Station *one, Station *two) const;

    /**
     * @brief Palauttaa satunnaisen radan
     * @return Staunnaisesti valittu rata
     */
    Track *getRandomTrack() const;

    /**
     * @brief Palauttaa lyhimmän reitin kahden paikan välillä
     * @param coordFrom Aloitus koordinaatti
     * @param coordTo Määränpään koordinaatti
     * @return Koordinaatit, joiden kautta reitti kulkee
     */
    QVector<std::shared_ptr<RelativeCoordinate>>
    getShortestPath(std::shared_ptr<RelativeCoordinate> coordFrom,
                    std::shared_ptr<RelativeCoordinate> coordTo);

    // QAbstractItemModel interface

    /**
     * @brief Roolit näkymiä varten
     */
    enum TracksRoles
    {
        TrackRole = Qt::UserRole,
        CodeRole,
        IdRole,
        PathRole
    };

    /**
     * @brief Palauttaa ajossa olevien junien määrän
     * @param parent Tämän alla olevien junien määrä palautetaan
     * @return Ajossa olevien junien määrä, 0 jos parent ei ole validi
     */
    int rowCount(const QModelIndex &parent) const override;

    /**
     * @brief Palauttaa tiety junan roolin mukaisen datan
     * @param index Yksilöi käsiteltävän junan
     * @param role Rooli, jonka mukainen data palautetaan
     * @return index:n mukaisen junan data, invalidi QVariant,
     *         jos juna tai rooli ei ole validi
     */
    QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief Palauttaa sallittujen roolien nimet
     * @return Roolien nimet
     */
    QHash<int, QByteArray> roleNames() const override;

private:

    /**
     * @brief addTrack
     * @param track
     */
    void addTrack(std::unique_ptr<Track>&& track);

    /**
     * @brief createStationStructs
     * @param force
     */
    void createStationStructs(bool force=false);

    /**
     * @brief Datasäilö reititysalgoritmia varten
     */
    struct stationStruct {
        Station* station;
        QVector<std::pair<Station*, double>> connected;
        bool visited;
        Station* last;
        double distance;
    };

    StationsModel* stations_;                        ///< Kaikki asemat
    QVector<Track*> tracks_;                         ///< Kaikki radat
    QMap<Station*, stationStruct*> stationStructs_;  ///< Reititysalgoritmin tietosäilö
};

#endif // TRACKSMODEL_HH
