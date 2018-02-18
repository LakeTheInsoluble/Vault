#ifndef PASSENGERTRAIN_HH
#define PASSENGERTRAIN_HH

#include "station.hh"
#include "train.hh"

#include <QMap>
#include <QDateTime>


/// @brief Matkustajajunat liikkuvat itsestään ja pelaajan pitää suojella niitä.
/**
 * @brief Matkustajajuna: liikkuvat itsestään aikataulun mukaan ja pelaaja
 *        yrittää suojella niitä.
 */
class PassengerTrain : public Train
{
    Q_OBJECT

public:

    /**
     * @brief Rakentaja
     * @param number Junan numero
     * @param type Junan tyyppi
     */
    PassengerTrain(int number, QString type);

    /**
     * @brief Lisää junalle uuden aikataulutapahtuman
     * Ei tee mitään, jos tapahtuman tyyppi on tuntematon
     * @param time Tapahtuman ajanhetki
     * @param type Tapahtuman tyyppi ("departure"/"arrival")
     * @param station Asema, jota taphtuma koskee
     * @pre time.isValid() && station != nullptr
     */
    void addTimetableRow(const QDateTime &time, const QString &type, Station* station);

    /**
     * @brief Antaa junan numeron
     * @return Junan numero
     */
    int number() const;

    /**
     * @brief Antaa junan tyypin
     * @return Junan tyyppi
     */
    QString type() const;

    /**
     * @brief Palauttaa junan ensimmäisen tapahtuman ajankohdan
     * @return Ensimmäisen tapahtuman ajankohta
     */
    QDateTime startTime() const;

    /**
     * @brief Antaa junan viimeisen tapahtuman ajankohdan
     * @return Viimeisen tapahtuman ajankohta
     */
    QDateTime endTime() const;

    /**
     * @brief Aikataulun yksi rivi
     */
    struct TimeTableRow
    {
        /**
         * @brief Tapahtuman tyypit
         */
        enum Type
        {
            arrival,
            departure
        };
        Type type;         ///< Tapahtuman tyyppi
        Station* station;  ///< Asema
        QDateTime time;    ///< Ajankohta
    };

    /**
     * @brief Kertoo, onko junalla aikataulu
     * @return Tosi, jos junalla on aikataulu
     */
    bool hasTimeTable() const;

    /**
     * @brief Poistaa aikataulun alusta ja lopusta turhat tapahtumat.
     * Junan aikataulu alkaa asemalta lähdöllä ja päättyy asemalle saapumiseen.
     */
    void validateTimetable();

    /**
     * @brief Palauttaa ajanhetkeä edeltäneen aikataulutapahtuman
     * @param time Ajanhetki, jota käsitellään
     * @return Viimeisin tapahtuma
     * @pre hasTimeTable() && time >= startTime()
     */
    TimeTableRow latestRow(QDateTime time);

    /**
     * @brief Antaa annettua ajanhetkeä seuraavan tapahtuman
     * @param time Ajanhetki jota käsitellään
     * @return Seuraava tapahtuma
     * @pre hasTimeTable() && time <= endTime()
     */
    TimeTableRow nextRow(QDateTime time);

private:
    int number_;    ///< junan numero
    QString type_;  ///< junan tyyppi
    QMap<QDateTime, TimeTableRow> timeTable_;  ///< junan aikataulu
};

#endif // PASSENGERTRAIN_HH
