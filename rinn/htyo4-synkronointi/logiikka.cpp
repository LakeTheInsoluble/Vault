// TIE-02500 rinnakkaisuus harjoitustyö-04
// Henri Laakso 240062
// Antti Tolonen 247589
// Niko Lappalainen 253002

#include "logiikka.h"
#include <QLabel>
#include <memory>
#include <iostream>
#include "barrier.h"
#include <functional>

const unsigned int PALOJA = 6;

Logiikka::Logiikka():
    barrieri_(PALOJA+1, []{}),
    palaVekit_(PALOJA)
{
    std::cout << "logiikka luotu; muista alustaa muuttujat yms." << std::endl;
    // pääikkuna luo Logiikka-tyyppisen olion ohjelman suorituksen alkaessa
    // tämä on hyvä hetki luoda logiikalle tarvittavat privaatit muuttujat
    // ja esim. laittaa säikeet nukkumaan ja odottamaan pääikkunan puolelta tulevia
    // jäsenfunktiokutsuja muunnaKaistaleelle

    for (unsigned int i = 0; i < PALOJA; i++) {
        saikeet_.push_back(std::thread(&Logiikka::saieAlku, this, i));
    }
}

Logiikka::~Logiikka()
{
    for (auto& saie : saikeet_) {
        saie.detach();
    }
}

void Logiikka::muunnaKaistale(const QImage& kuva, int vasen, int oikea, std::vector<QColor>& tallennusVektori)
{
    kuva_ = &kuva;
    vasen_ = vasen;
    oikea_ = oikea;

    // Käynnistetään säikeet ja odotetaan valmistumista
    bool lippu = false;
    barrieri_.saavuJaOdota(&lippu);
    barrieri_.saavuJaOdota(&lippu);

    for (unsigned int i = 0; i < palaVekit_.size(); i += 1) {
        for (unsigned int j = 0; j < palaVekit_[i].size(); j += 1) {
            tallennusVektori.push_back(palaVekit_[i][j]);
        }
        palaVekit_[i].clear();
    }
}

void Logiikka::muunnaPala(const QImage& kuva, int alkux, int alkuy, int leveys, int korkeus, std::vector<QColor>& vekki) {

    // käsitellään aina suorakaiteen (tai neliön) muotoinen alue
    // alkux, alkuy on alueen vasemman yläkulman koordinaatti kuvan sisällä
    // leveys on käsiteltävän palan leveys ja korkeus sen korkeus

    // esimerkkitapaukesssa esim. aivan ensimmäinen muunnettava pala koko ohjelman
    // suorituksen aikana on kuvan vasen yläkulma: alkux 0, alkuy 0, leveys 100, korkeus 100
    // toisena käsitellään tämän palan alta löytyvä pala: alkux 0, alkuy 100, leveys 100, korkeus 100

    // QT:n koordinaatistossa origo on vasemmassa yläkulmassa

    // silmukassa rivi kerrallaan
    for (int k = 0; k < korkeus; k += 1) {

        // rivin pikselit
        for (int l = 0; l < leveys; l += 1) {

            // muutetaan ensin ylhäältä alas lukien ensimmäisen rivin
            // ensimmäinen eli vasemmanpuolimmaisin pikseli
            // sitten toinen pikseli, kolmas jne.

            // tämä on vain havainnollistus! tämä piirtää mustan laatikon
            // muunnettavan alueen ympärille, joka havainnollistaa, eri
            // säikeiden "työalueiden" rajoja
            // tätä EI TARVITA ja ehtolauseen voi poistaa kokonaan
            if (k == 0 || l == 0 || k == korkeus - 1 || l == leveys - 1) {
                vekki.push_back(QColor(0, 0, 0));
                continue;
            }

            // otetaan kuvasta tietyn pikselin kohdalta väri
            QColor vari = kuva.pixelColor(alkux + l, alkuy + k);
            // tehdään mv-konversio: joko otetaan värien keskiarvo TAI otetaan jokaista
            // väriä määrä x oheisten kertoimien osoittamalla tavalla
            // -> molemmat tavat tuottavat mv-kuvan, joista kertoimilla muodostettu
            // on "aidompi"

            //int mv = ( vari.red() + vari.green() + vari.blue() ) / 3;
            int mv = 0.2126*vari.red() + 0.7152*vari.green() + 0.0722*vari.blue();

            vekki.push_back(QColor(mv, mv, mv));
        }
    }
}

void Logiikka::saieAlku(const unsigned short index)
{
    bool lippu = false;
    while (not lopetetaan_) {
        // Synkronoidaan säikeet
        barrieri_.saavuJaOdota(&lippu);

        Q_ASSERT(kuva_ != nullptr);
        Q_ASSERT(index < PALOJA);

        int alku_y = kuva_->height() / PALOJA * index;
        int leveys = oikea_ - vasen_;
        int korkeus = kuva_->height() / PALOJA;
        // Jaetaan ylimääräiset rivit ensimmäisten palojen välille
        int ylimRiveja = kuva_->height() % PALOJA;
        if (ylimRiveja != 0) {
            if (index < ylimRiveja) {
                korkeus += 1;
                alku_y += index;
            } else {
                alku_y += ylimRiveja;
            }
        }

        muunnaPala(*kuva_, vasen_, alku_y, leveys, korkeus, palaVekit_[index]);

        // Synkronoidaan säikeet
        barrieri_.saavuJaOdota(&lippu);
    }
}
