#ifndef OBSTACLESMODEL_HH
#define OBSTACLESMODEL_HH

#include "obstacle.hh"
#include "trackcoordinate.hh"
#include "stationcoordinate.hh"
#include "tracksmodel.hh"

#include <QAbstractListModel>

#include <memory>

/**
 * @brief Kaikki tämän hetkiset esteet
 */
class ObstaclesModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief Rakentaja
     * @param tracks Raiteet, joilla esteet ovat
     */
    explicit ObstaclesModel(TracksModel* tracks);

    /**
     * @brief Lisää esteen
     * @param obstacle Lisättävä este
     * @param location Paikka, johon roska asetetaan
     */
    void addObstacle(std::unique_ptr<Obstacle>&& obstacle,
                     std::shared_ptr<TrackCoordinate> location);

    /**
     * @brief Lisää satunnaisen esteen satunnaiseen paikkaan
     */
    void addRandomObstacle();

    /**
     * @brief Poistaa esteen
     * @param toRemove poistettava este
     */
    void removeObstacle(Obstacle* toRemove);

    /**
     * @brief Poistaa esteet kahden ratapisteen välillä
     * @param start Alkupiste
     * @param end Loppupiste
     */
    void removeObstaclesBetween(const RelativeCoordinate &start,
                                const RelativeCoordinate &end);

    /**
     * @brief Kertoo pisteiden välillä olevien roskien junalle aiheuttaman vahingon
     * @param start Alkupiste
     * @param end Loppupiste
     * @return Junalle pisteiden välillä aiheutuvan vahingon määrä
     */
    uint damageBetween(const RelativeCoordinate &start,
                       const RelativeCoordinate &end) const;

    // QAbstractItemModel interface
    enum Roles
    {
        LocationRole = Qt::UserRole + 1,
        ColorRole
    };
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    /**
     * @brief Roska on poistettu
     */
    void obstacleRemoved();

private:
    /**
     * @brief Invariantti
     * @return Tosi, jos invariantti on tosi
     */
    bool invariant() const;

    QVector<Obstacle*> obstacles_;   ///< Kaikki tämän hetkiset esteet
    QMap<Obstacle*, std::shared_ptr<TrackCoordinate>> locations_;   ///< Esteiden sijainnit
    TracksModel *tracks_;  ///< Kaikki radat
};

#endif // OBSTACLESMODEL_HH
