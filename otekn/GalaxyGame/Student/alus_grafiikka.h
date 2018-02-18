#ifndef ALUSGRAFIIKKA_H
#define ALUSGRAFIIKKA_H

#include <QGraphicsItem>

#include <grafiikka_ikkuna.h>

/**
 * @brief AlusGrafiikka huolehtii alusten grafikoista.
 *
 * Alusgrafiikka luo, piirtää ja liikuttaa pelissä olevien alusten
 * grafiikkoja, ja lisäksi pitää yllä tietoa liikkeen kohteesta.
 */
class AlusGrafiikka : public QGraphicsItem
{
public:
    /**
     * @brief AlusGrafiikka
     * @param vari aluksen väri.
     * @param koko aluksen koko.
     */
    AlusGrafiikka(QColor vari, double koko);

    ~AlusGrafiikka();

    /**
     * @brief boundingRect luo laatikon, joka määrittää aluksen koon.
     * @return laatikko aluksen luomiselle.
     */
    QRectF boundingRect() const override;
    /**
     * @brief paint
     * @param painter osoitin maalaajaan.
     * @param option
     * @param widget maalattava widgetti.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /**
     * @brief asetaSijainti asettaa grafiikan paikan kartalla.
     * @param x sijainnin x.
     * @param y sijainnin y.
     */
    void asetaSijainti(double x, double y);
    /**
     * @brief asetaKohde asettaa grafiikalle kohteen, mitä kohti liikkua.
     * @param uusiPaikka kohteen paikka.
     */
    void asetaKohde(QPointF uusiPaikka);
    /**
     * @brief asetaNopeus asettaa nopeuden, jolla grafiikka liikkuu kohti kohdetta.
     * @param nopeus grafiikan nopeus.
     */
    void asetaNopeus(double nopeus);

    /**
     * @brief etene liikuttaa grafikkaa nopeuden verran kohti kohdetta.
     * @return palauttaa liikutun matkan.
     */
    double etene();
    /**
     * @brief matkalla palauttaa aluksen liikkeen tilan.
     * @return onko alus matkalla.
     */
    bool matkalla();

private:
    //! Aluksen väri.
    QColor vari_;
    //! Aluksen sijainnin x.
    double sijaintiX_;
    //! Aluksen sijainnin y.
    double sijaintiY_;
    //! Aluksen kohteen x.
    double kohdeX_;
    //! Aluksen kohteen y.
    double kohdeY_;
    //! Kulma, jossa alus liikkuu.
    double kulma_;
    //! Aluksen nopeus.
    double nopeus_;
    //! Onko alus matkalla.
    bool matkalla_;

};

#endif // ALUSGRAFIIKKA_H
