#ifndef TRACK_HH
#define TRACK_HH

#include "station.hh"
#include "util.hh"

#include <QObject>

/// @brief Raideyhteys asemalta toiselle.
class Track : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Rakentaja
     * @param id Tunnistenumero
     * @param start Alkuasema
     * @param end Loppuasema
     * @param length Pituus (metriä)
     * @param code Tunnistemerkkijono
     * @param parent QObject, joka omistaa tämän raiteen.
     * @pre Ei ole jo olemassa raidetta samalla tunnistenumerolla.
     */
    Track(unsigned id, Station *start, Station *end, double length, QString code,
          QObject *parent = nullptr);

    /**
     * @brief Hae tunnistenumero
     */
    uint id() const;

    /**
     * @brief Hae tunnistemerkkijono
     * @return
     */
    QString code() const;

    /**
     * @brief Hae alkuasema
     * @return alkuasema
     */
    Station *start() const;

    /**
     * @brief Hae loppuasema
     * @return loppuasema
     */
    Station *end() const;

    /**
     * @brief Hae pituus
     * @return Pituus (metriä)
     */
    double length() const;

    /**
     * @brief Alkaako tai loppuuko raide asemalle?
     * @param station Asema, josta kysellään
     * @return true, jos alkaa tai loppuu
     */
    bool touchesStation(const Station *station) const;

    /**
     * @brief Millä asemalla (jos millään) tämä raide kohtaa toisen raiteen?
     * @param other Toinen raide
     * @return Asema, jolla kohtaavat. Jos ei missään, nullptr.
     */
    Station *commonStation(const Track &other) const;

private:
    /**
     * @brief Luokkainvariantti
     * @return start_ != nullptr && end_ != nullptr && length_ >= 0.0
     */
    bool invariant() const;

    uint id_;        ///< Tunnistenumero
    QString code_;   ///< Tunnistemerkkijono
    Station* start_; ///< Alkuasema
    Station* end_;   ///< Loppuasema
    double length_;  ///< Pituus (metriä)
};

#endif // TRACK_HH
