// Koodin versio: 2017-03-24
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logiikka.h"
#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QString workdir = "");
    ~MainWindow();
    void korvaaPikselit();
    void asetaKuva();

public slots:
    void valitseKuva();
    void muunnaSeuraavaKaistale();

private:
    void reset();

    Ui::MainWindow *ui;
    QString workdir_;

    QImage kuva_;
    QImage kohdeKuva_;
    int kasitellytKaistaleet_;
    std::vector<QColor> pikseliTalletus_;

    Logiikka logiikka_;
};

#endif // MAINWINDOW_H
