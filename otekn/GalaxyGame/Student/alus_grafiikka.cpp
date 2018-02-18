#include "alus_grafiikka.h"

#include <iostream>

#include <QPainter>
#include <QPolygon>
#include <qmath.h>

static const double PI = 3.1415926535;




AlusGrafiikka::AlusGrafiikka(QColor vari, double koko)
{
    this->setScale(koko/10);
    vari_ = vari;
    nopeus_ = 0;
}

AlusGrafiikka::~AlusGrafiikka()
{

}

QRectF AlusGrafiikka::boundingRect() const
{
    return QRectF(-10.5, -10.5, 21, 21);
}

void AlusGrafiikka::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //runko
    painter->setBrush(vari_);
    painter->drawEllipse(-10, -2, 20, 4);

    //siivet
    QPolygonF vasen_siipi;
    vasen_siipi.append(QPointF(2,8));
    vasen_siipi.append(QPointF(2,1.5));
    vasen_siipi.append(QPointF(-3,1.5));
    painter->drawPolygon(vasen_siipi);

    QPolygonF oikea_siipi;
    oikea_siipi.append(QPointF(2,-8));
    oikea_siipi.append(QPointF(2,-1.5));
    oikea_siipi.append(QPointF(-3,-1.5));
    painter->drawPolygon(oikea_siipi);

    //perasin
    QPolygonF perasin;
    perasin.append(QPointF(10,-4));
    perasin.append(QPointF(10,4));
    perasin.append(QPointF(8,4));
    perasin.append(QPointF(8,-4));
    painter->drawPolygon(perasin);
}

void AlusGrafiikka::asetaSijainti(double x, double y)
{
    sijaintiX_ = x;
    sijaintiY_ = y;
    kohdeX_ = x;
    kohdeY_ = y;
    this->setPos(sijaintiX_, sijaintiY_);
}

void AlusGrafiikka::asetaKohde(QPointF uusiPaikka)
{
    matkalla_ = true;

    kohdeX_ = uusiPaikka.x();
    kohdeY_ = uusiPaikka.y();

    kulma_ = qAtan2((kohdeY_-sijaintiY_),(kohdeX_-sijaintiX_));
    this->setRotation(kulma_/PI*180-180);
}

void AlusGrafiikka::asetaNopeus(double nopeus)
{
    nopeus_ = nopeus;
}

double AlusGrafiikka::etene()
{
    double ret = 0.0;
    double jaljella = sqrt(pow(sijaintiX_-kohdeX_,2)+pow(sijaintiY_-kohdeY_,2));

    if( jaljella > nopeus_ ) {
        sijaintiX_ += qCos(kulma_)*nopeus_;
        sijaintiY_ += qSin(kulma_)*nopeus_;
        this->setPos(QPointF(sijaintiX_, sijaintiY_));
        ret = nopeus_;
    }
    else if(jaljella <= nopeus_) {
        sijaintiX_ = kohdeX_;
        sijaintiY_ = kohdeY_;
        this->setPos(QPointF(kohdeX_,kohdeY_));
        ret = jaljella;

        matkalla_ = false;
    }
    return ret;
}

bool AlusGrafiikka::matkalla()
{
    return matkalla_;
}


