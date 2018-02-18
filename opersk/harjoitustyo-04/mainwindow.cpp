#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QActionGroup* sp_group = new QActionGroup(this);
    sp_group->addAction(ui->actionNainen);
    sp_group->addAction(ui->actionMies);
    ui->actionNainen->setChecked(true);
    sp_group->setVisible(true);

    connect(ui->paino_spinBox, SIGNAL(valueChanged(int)), this, SLOT(laske_bmi()));
    connect(ui->pituus_spinBox, SIGNAL(valueChanged(int)), this, SLOT(laske_bmi()));

    connect(ui->actionNainen, SIGNAL(triggered(bool)), this, SLOT(sp_paivita()));
    connect(ui->actionMies, SIGNAL(triggered(bool)), this, SLOT(sp_paivita()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLopeta_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAlkutila_triggered() {
    ui->paino_spinBox->setValue(0);
    ui->paino_slider->setValue(0);
    ui->pituus_spinBox->setValue(0);
    ui->pituus_slider->setValue(0);
    ui->bmi->setText("-");
    ui->tulkinta->setText("-");
    ui->actionNainen->trigger();
    ui->sukupuoli->setText("Nainen");
}

void MainWindow::sp_paivita() {
    if(ui->actionNainen->isChecked()) {
        ui->sukupuoli->setText("Nainen");
    } else {
        ui->sukupuoli->setText("Mies");
    }
    laske_bmi();
}

void MainWindow::laske_bmi() {
    double tulos;
    double paino = (double) ui->paino_spinBox->value();
    double pituus = (double) ui->pituus_spinBox->value();

    tulos = paino*10000/(pituus*pituus);

    if(isnan(tulos) || isinf(tulos) || tulos == 0) {
        ui->bmi->setText("-");
    } else {
        ui->bmi->setText(QString::number(tulos, 'f', 2));
    }

    if(ui->sukupuoli->text() == "Mies"){
        if(isnan(tulos) || isinf(tulos) || tulos == 0) {
            ui->tulkinta->setText("-");
        } else if(tulos <= 20.7) {
            ui->tulkinta->setText("alipainoa");
        } else if(tulos <= 26.4) {
            ui->tulkinta->setText("normaali");
        } else if(tulos <= 27.8) {
            ui->tulkinta->setText("lievää ylipainoa");
        } else if(tulos <= 31.1) {
            ui->tulkinta->setText("ylipainoa");
        } else {
            ui->tulkinta->setText("paljon ylipainoa");
        }
    } else {
        if(isnan(tulos) || isinf(tulos) || tulos == 0) {
            ui->tulkinta->setText("-");
        } else if(tulos <= 19.1) {
            ui->tulkinta->setText("alipainoa");
        } else if(tulos <= 25.8) {
            ui->tulkinta->setText("normaali");
        } else if(tulos <= 27.3) {
            ui->tulkinta->setText("lievää ylipainoa");
        } else if(tulos <= 32.2) {
            ui->tulkinta->setText("ylipainoa");
        } else {
            ui->tulkinta->setText("paljon ylipainoa");
        }
    }
}
