#ifndef TRAIN_HH
#define TRAIN_HH

#include "relativecoordinate.hh"
#include "util.hh"

#include <QObject>

#include <memory>

/**
 * @brief Mikä tahansa juna.
 */
class Train : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString model READ model NOTIFY modelChanged)
    Q_PROPERTY(uint maxHealth READ maxHealth NOTIFY maxHealthChanged)
    Q_PROPERTY(uint health READ health WRITE setHealth NOTIFY healthChanged)

public:
    /**
     * @brief Rakentaja
     * @param model Mallinimi
     * @param maxHealth Maksimikunto
     * @param parent QObject, joka omistaa tämän junan
     */
    Train(QString model, uint maxHealth, QObject *parent = nullptr);

    /**
     * @brief Hae mallinimi
     * @return mallinimi
     */
    QString model() const;

    /**
     * @brief Hae tämänhetkinen sijainti
     * @return tämänhetkinen sijainti
     */
    std::shared_ptr<RelativeCoordinate> location() const;

    /**
     * @brief Aseta tämänhetkinen sijainti
     * @param location Uusi sijainti
     * @post location() == location
     */
    void setLocation(std::shared_ptr<RelativeCoordinate> location);

    /**
     * @brief Hae maksimikunto
     * @return Maksimikunto
     */
    uint maxHealth() const;

    /**
     * @brief Hae tämänhetkinen kunto
     * @return Tämänhetkinen kunto
     */
    uint health() const;

    /**
     * @brief Aseta tämänhetkinen kunto
     * @param health Uusi kunto
     * @post this->health() == health
     */
    void setHealth(uint health);

    /**
     * @brief Korjaa junaa
     * @param amount Kunnon lisäyksen määrä
     * @post health() == min(health()(vanha) + amount, maxHealth())
     */
    void repair(uint amount);

    /**
     * @brief Vahingoita junaa
     * @param damage Kunnon vähennyksen määrä
     * @post health == max(health()(vanha) - damage, 0)
     */
    void causeDamage(uint damage);

    /**
     * @brief Onko juna käyttökelvoton?
     * @return true jos on
     */
    bool isBroken() const;

    /**
     * @brief Onko juna annettujen sijaintien välissä?
     * @param one Sijainti
     * @param two Toinen sijainti
     * @return true jos on
     * @pre Reitti ei kulje yli yhden aseman läpi.
     */
    bool isBetween(const RelativeCoordinate &one, const RelativeCoordinate &two) const;

signals:
    /**
     * @brief Malli muuttui (olemassa vain QML:n mieliksi).
     * @param model Uusi malli
     */
    void modelChanged(QString model);

    /**
     * @brief Maksimikunto muuttui (olemassa vain QML:n mieliksi).
     * @param maxHealth Uusi maksimikunto
     */
    void maxHealthChanged(uint maxHealth);

    /**
     * @brief Kunto muuttui
     * @param health Uusi kunto
     */
    void healthChanged(uint health);

private:
    /**
     * @brief Luokkainvariantti
     * @return health_ <= maxHealth_
     */
    bool invariant() const;

    QString model_;                                ///< Mallinimi
    std::shared_ptr<RelativeCoordinate> location_; ///< Tämänhetkinen sijainti
    uint maxHealth_;                               ///< Maksimikunto
    uint health_;                                  ///< Tämänhetkinen kunto
};

#endif // TRAIN_HH
