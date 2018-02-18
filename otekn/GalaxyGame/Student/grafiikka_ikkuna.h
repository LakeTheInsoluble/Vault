#ifndef GRAFIIKKA_H
#define GRAFIIKKA_H

#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>

/**
 * @brief GrafiikkaIkkuna
 */
class GrafiikkaIkkuna : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GrafiikkaIkkuna(QWidget *parent = 0);

    ~GrafiikkaIkkuna();

signals:
    /**
     * @brief signaali, joka lähettää hiiren klikkauksen sijainnin
     * @param piste Qt:n QPointF -rakenteeseen talletettu tieto hiiren
     * klikkauksen sijainnista
     */
    void lahetaHiirenVasenPiste(QPointF piste);

public slots:
    /**
     * @brief hiiren painalluksen luoma tapahtuma
     * @param klikkaus osoitin klikkauksen eventtiin.
     */
    void mousePressEvent(QMouseEvent *klikkaus);

    /**
     * @brief hiiren rullan liikuttamisen luoma event
     * @param rullaus osoitin rullauksen eventiin.
     */
    void wheelEvent(QWheelEvent *rullaus);


};

#endif // GRAFIIKKA_H
