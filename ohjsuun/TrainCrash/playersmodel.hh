#ifndef PLAYERSMODEL_H
#define PLAYERSMODEL_H

#include "player.hh"

#include <QAbstractListModel>
#include <QFile>
#include <QObject>

/**
 * @brief Kaikki pelaajat
 */
class PlayersModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief Antaa, ja luo tarvittaessa, pelaajamalliolion
     * Lukee olemassa olevat pelaajat asetustiedostosta
     * @return Pelaajamalli singleton-olio
     */
    static PlayersModel *instance();

    /**
     * @brief Lisää pelaajan
     * @param name Lisättävän pelaajan nimi
     */
    Q_INVOKABLE  void addPlayer(const QString &name);

    /**
     * @brief Lisää pelaajan malliin
     * @param player Lisättävä pelaaja
     */
    void addPlayer(Player *player);

    // QAbstractItemModel interface

    /**
     * @brief Roolit näkymiä varten
     */
    enum PlayersRoles
    {
        NameRole = Qt::UserRole + 1,
        PlayerRole
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private slots:
    /**
     * @brief Tallentaa pelaajat tiedostoon
     */
    void savePlayers();

private:
    /**
     * @brief Rakentaja
     * @param parent Edeltäjä
     */
    PlayersModel(QObject *parent = nullptr);

    /**
     * @brief Muodostaa pelaajista JSON-rakenteen
     * @return JSON-rakenne, joka voidaan tallentaa tiedostoon
     */
    QJsonDocument createPlayerJson();

    /**
     * @brief Palauttaa polun pelaajatiedostoon
     * @return Polku pelaaja asetustiedostoon
     */
    QString playerFile();

    /**
     * @brief Lukee pelaajat JSON-tiedostosta
     */
    void readPlayerJson();

    QVector<Player*> players_;       ///< Kaikki pelaajat
    Player *activePlayer_;           ///< Aktiivinen pelaaja
    static PlayersModel *instance_;  ///< Singleton-instanssi

};

#endif // PLAYERSMODEL_H
