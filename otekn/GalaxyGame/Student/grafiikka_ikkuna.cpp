#include "grafiikka_ikkuna.h"


const double skaala = 1.15;

GrafiikkaIkkuna::GrafiikkaIkkuna(QWidget *parent) : QGraphicsView(parent)
{
}

GrafiikkaIkkuna::~GrafiikkaIkkuna()
{

}

void GrafiikkaIkkuna::mousePressEvent(QMouseEvent *klikkaus)
{
    if( klikkaus->button() == Qt::LeftButton ) {
        lahetaHiirenVasenPiste(mapToScene(klikkaus->pos()));
    }
}

void GrafiikkaIkkuna::wheelEvent(QWheelEvent *rullaus)
{
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    if( rullaus->delta() > 0 ) {
        this->scale(skaala, skaala);
    }
    else {
        this->scale(1/skaala, 1/skaala);
    }
}


