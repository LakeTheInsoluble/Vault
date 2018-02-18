// TIE-02500 rinnakkaisuus harjoitustyö-04
// Henri Laakso 240062
// Antti Tolonen 247589
// Niko Lappalainen 253002

#ifndef LOGIIKKA_H
#define LOGIIKKA_H
#include <QImage>
#include <memory>
#include <thread>
#include "barrier.h"
#include <thread>

class Logiikka
{
public:
    Logiikka();
    ~Logiikka();
    void muunnaKaistale(const QImage& kuva, int vasen, int oikea,
                        std::vector<QColor>& vekki);
    void muunnaPala(const QImage &kuva, int alkux, int alkuy,
                    int leveys, int korkeus, std::vector<QColor>& vekki);
private:
    void saieAlku(const unsigned short index);

    std::vector<std::thread> saikeet_;
    Barrier barrieri_;
    bool lopetetaan_ = false;
    std::vector<std::vector<QColor> > palaVekit_;
    const QImage* kuva_ = nullptr;
    int vasen_ = 0;
    int oikea_ = 0;
};

#endif // LOGIIKKA_H
