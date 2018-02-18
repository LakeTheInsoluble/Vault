TEMPLATE = app

# käytetään uusimpia ominaisuuksia
CONFIG += console c++14
LIBS += -pthread

# poistetaan Qt käytöstä
CONFIG -= app_bundle
CONFIG -= qt

include( rinn2017lib/rinn2017.pri )
SOURCES += main.cpp
