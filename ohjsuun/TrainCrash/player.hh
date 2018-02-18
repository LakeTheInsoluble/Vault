#ifndef PLAYER_HH
#define PLAYER_HH

#include "medal.hh"
#include "util.hh"

#include <QObject>
#include <QVector>
#include <QQmlListProperty>

/**
 * @brief Pelaaja
 */
class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(uint coupons READ coupons WRITE setCoupons NOTIFY couponsChanged)
    Q_PROPERTY(QQmlListProperty<Medal> medals READ medals NOTIFY medalsChanged)

public:

    /**
     * @brief Rakentaja
     */
    explicit Player();

    /**
     * @brief Rakentaja
     * @param name Pelaajan nimi
     * @param parent Edeltäjä
     */
    explicit Player(QString name, QObject *parent);

    /**
     * @brief Antaa pelaajan nimen
     * @return nimi
     */
    QString name() const;

    /**
     * @brief Asettaa pelaajalle nimen
     * @param newName nimi
     */
    void setName(QString newName);

    /**
     * @brief Antaa pelaajan kuponkien määrän
     * @return kuponkien määrä
     */
    uint coupons() const;

    /**
     * @brief Asettaa pelaajan kuponkien määrän
     * @param newCoupons Asetettava määrä
     */
    void setCoupons(uint newCoupons);

    /**
     * @brief Lisää pelaajalle annetun määrän kuponkeja
     * @param amount Lisättävien kuponkien määrä
     */
    void addCoupons(uint amount);

    /**
     * @brief Vähentää pelaajalta kuponkeja annetun määrän
     * @param amount Vähennettävien kuponkien määrä
     */
    void chargeCoupons(uint amount);

    /**
     * @brief Antaa listan pelaajan mitaleista
     * @return Pelaajan mitalit
     */
    QQmlListProperty<Medal> medals();

    /**
     * @brief Antaa listan pelaajan mitaleista
     * @return Pelaajan mitalit
     */
    QVector<Medal*> medalList() const;

    /**
     * @brief Lisää pelaajalle mitalin
     * @param medal Lisättävä mitali
     */
    void addMedal(Medal *medal);

signals:
    /**
     * @brief Pelaajan nimi on vaihtunut
     * @param newName Uusi nimi
     */
    void nameChanged(QString newName);

    /**
     * @brief Kuponkien määrä on muuttunut
     * @param coupons Uusi kuponkien määrä
     */
    void couponsChanged(uint coupons);

    /**
     * @brief Mitalit ovat muuttuneet
     * @param medals Lista uusista mitaleista
     */
    void medalsChanged(QQmlListProperty<Medal> medals);

private:

    // TODO: mihin näitä käytetään?
    static void appendMedal(QQmlListProperty<Medal> *medals, Medal *newMedal);
    static int medalCount(QQmlListProperty<Medal> *medals);
    static Medal *medalAt(QQmlListProperty<Medal> *medals, int index);
    static void clearMedals(QQmlListProperty<Medal> *medals);

    QString name_;            ///< nimi
    uint coupons_;            ///< kuponkien määrä
    QVector<Medal*> medals_;  ///< mitalit
};

#endif // PLAYER_HH
