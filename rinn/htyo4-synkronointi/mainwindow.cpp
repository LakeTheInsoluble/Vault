// Koodin versio: 2017-03-24
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logiikka.h"

#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <memory>

// FIXME: käyttöliittymä ei skaalaudu ruudulla (jos kuva on ui editorin kokoa isompi, niin
// ikkuna ei suurene eikä scrollbar:a tule käyttöön)

// FIXME: ei testattu toimiiko jos siipaletta muutetaan:
const int LEVEYS_SIIPALE = 100;

MainWindow::MainWindow(QWidget *parent, QString workdir) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    workdir_(workdir)
{
    ui->setupUi(this);

    QObject::connect(ui->buttonValitse, SIGNAL(clicked(bool)),
                     this, SLOT(valitseKuva()));

    QObject::connect(ui->buttonAloita, SIGNAL(clicked(bool)),
                     this, SLOT(muunnaSeuraavaKaistale()));

    QObject::connect(ui->buttonLopeta, SIGNAL(clicked(bool)),
                     this, SLOT(close()));

    kasitellytKaistaleet_ = 0;

    QImage yritys;
    if (yritys.load(":/default")) {

        std::cout << "Oletuskuva löytyi. Ladataan..." << std::endl;
        kuva_ = yritys;
        kohdeKuva_ = yritys;
        this->asetaKuva();

    } else {
        std::cout << "Oletuskuvaa ei löytynyt. Siirrä build-hakemistoon "
                     "default.jpg, niin se latautuu automaattisesti." << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::korvaaPikselit()
{
    std::cout << "korvaaPikselit" << std::endl;
    // int korkeus = kohdeKuva_.height(); // korkeutta ei tällä hetkellä tarvita
    int leveys = LEVEYS_SIIPALE;

    // käydään läpi vektoria niin, että vektorin ensimmäinen alkio
    // on kuvan ensimmäisen rivin ensimmäinen pikseli, toinen alkio
    // ensimmäisen rivin toinen pikseli jne. eli rivi kerrallaan
    // jokaisella rivillä aina LEVEYS_SIIPALE verran pikseleitä
    // -> jakojäännöksellä selville, mille riville pikseliä ollaan
    // tuuppaamassa

    for (unsigned int i = 0; i < pikseliTalletus_.size(); i += 1) {

        int x = kasitellytKaistaleet_ * LEVEYS_SIIPALE + i % leveys;
        int y = i / LEVEYS_SIIPALE;
        QColor vari = pikseliTalletus_.at(i);
        kohdeKuva_.setPixelColor(x, y, vari);
    }

    this->asetaKuva();
}

void MainWindow::valitseKuva()
{

    std::cout << "valitseTiedosto" << std::endl;

    QFileDialog dialogi(this, "Valitse käsiteltävä kuva", workdir_ );
    dialogi.setFileMode(QFileDialog::AnyFile);
    dialogi.setViewMode(QFileDialog::Detail);
    QString tiedostoNimi;
    if(dialogi.exec()) {
        tiedostoNimi = dialogi.selectedFiles()[0];
    } else {
        tiedostoNimi = ":/default";
    }

    // toinen annetaan viitteenä aina muunnokseen
    // toiseen istutetaan pikselit ja asetetaan
    // näytölle näkyviin
    kuva_ = QImage(tiedostoNimi);
    kohdeKuva_ = QImage(tiedostoNimi);

    // kaistaleiden toiminta nollautuu aina uudelle kuvalle
    this->reset();

    this->asetaKuva();
}

void MainWindow::asetaKuva()
{
    ui->labelKuva->setPixmap(QPixmap::fromImage(kohdeKuva_));
}

void MainWindow::muunnaSeuraavaKaistale()
{
    // annetaan aina tyhjä vektori
    pikseliTalletus_.clear();

    // kaistaleen alku- ja loppureuna käsiteltyjen kaistaleiden perusteella
    logiikka_.muunnaKaistale(kuva_,
                             kasitellytKaistaleet_ * LEVEYS_SIIPALE,
                             (kasitellytKaistaleet_ + 1) * LEVEYS_SIIPALE,
                             pikseliTalletus_);
    this->korvaaPikselit();

    kasitellytKaistaleet_ += 1;

    // jos kaistaleet muunnettu, ei anneta pyytää lisämuunnoksia
    if (kasitellytKaistaleet_ == (kuva_.width() / LEVEYS_SIIPALE)) {
        ui->buttonAloita->setEnabled(false);
    }
}

void MainWindow::reset()  // nollataan toiminta uudelle kuvalle
{
    kasitellytKaistaleet_ = 0;
    ui->buttonAloita->setEnabled(true);
}
