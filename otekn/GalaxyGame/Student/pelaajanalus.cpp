#include "pelaajanalus.h"

#include <iostream>

PelaajanAlus::PelaajanAlus(std::shared_ptr<Common::WarpDrive> engine,
                           std::shared_ptr<Common::StarSystem> initialLocation,
                           std::shared_ptr<Student::EventHandler> events) :

                Common::Ship((std::shared_ptr<Common::ShipEngine>)engine, initialLocation, events),
                moottori_(engine)
{
}

PelaajanAlus::~PelaajanAlus()
{

}

void PelaajanAlus::lisaaGrafiikka(AlusGrafiikka *graf)
{
    grafiikka = graf;
    grafiikka->asetaNopeus(1);
}

AlusGrafiikka* PelaajanAlus::haeGrafiikka()
{
    return grafiikka;
}

void PelaajanAlus::asetaKohdeJarjestelma(std::shared_ptr<Common::StarSystem> systeemi)
{
    kohde_ = systeemi;
    grafiikka->asetaKohde(QPointF(systeemi->getCoordinates().x, systeemi->getCoordinates().y));

}

bool PelaajanAlus::decideAction()
{
    return true;
}


