#include "paaikkuna.h"
#include "ui_paaikkuna.h"

Paaikkuna::Paaikkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Paaikkuna)
{
    ui->setupUi(this);

    connect(ui->nollaa_button, SIGNAL(clicked()), this, SLOT(nollaa_kaikki_arvot()));
    connect(ui->kmh_spinbox, SIGNAL(valueChanged(int)), this, SLOT(aseta_mailit()));
}

Paaikkuna::~Paaikkuna()
{
    delete ui;
}

void Paaikkuna::nollaa_kaikki_arvot()
{
  ui->kmh_spinbox->setValue(0);
  ui->kmh_slider->setValue(0);
  ui->miles_lcd->display(0.0);
}

void Paaikkuna::aseta_mailit()
{
    double kmh = (double) ui->kmh_spinbox->value();
    ui->miles_lcd->display(kmh * 0.6213712);
}
