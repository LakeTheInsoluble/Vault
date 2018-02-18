#ifndef TRAINCATALOG_H
#define TRAINCATALOG_H

#include "servicetrain.hh"
#include "util.hh"

#include <QObject>
#include <QAbstractListModel>
#include <QVector>

/**
 * @brief Sisältää pelissä olevien huoltojunien mahdolliset tyypit
 */
class TrainCatalog : public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief Rakentaja.
     * @param parent Edeltäjä
     */
    explicit TrainCatalog(QObject *parent);

    /**
     * @brief Purkaja
     */
    ~TrainCatalog();

    // QAbstractItemModel interface

    enum CatalogRoles
    {
        ModelRole = Qt::UserRole + 1,
        MaxHealtRole,
        PriceRole,
        MaxHealth,
        SpeedRole,
        TrainRole
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    /**
     * @brief Junatyypin kuvaava tietovarasto
     */
    struct TrainType
    {
        QString model;
        uint price;
        uint maxHealth;
        uint speed;
        TrainType(QString model, uint price, uint maxHealth, uint speed);
    };

    /**
     * @brief Rakentaa uuden junan tyypin perusteella
     * @param type Käytettävä tyyppi
     * @return Rakennettu juna
     */
    ServiceTrain *makeTrain(TrainType *type) const;

    /**
     * @brief Luo junatyypit malliin
     */
    void createDefaultTypes();

    QVector<TrainType*> trainTypes_;  ///< Kaikki pelissä olevat junatyypit
};

#endif // TRAINCATALOG_H
