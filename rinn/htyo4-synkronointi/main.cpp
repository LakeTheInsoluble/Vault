// Koodin versio: 2017-03-24
#include "mainwindow.h"
#include "logiikka.h"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <iostream>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString CWD = a.applicationDirPath(); // työskentelyhakemistoksi asetetaan binäärin sijainti
    QDir::setCurrent( CWD );

    MainWindow w(nullptr, CWD );
    w.show();

    return a.exec();
}
