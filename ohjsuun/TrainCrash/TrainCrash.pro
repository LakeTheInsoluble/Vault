QT += quick
CONFIG += c++11
QT += positioning
QT += network

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cc \
    train.cc \
    passengertrain.cc \
    station.cc \
    track.cc \
    medal.cc \
    obstacle.cc \
    servicetrain.cc \
    stationsmodel.cc \
    tracksmodel.cc \
    startcontroller.cc \
    resultscontroller.cc \
    storecontroller.cc \
    obstaclesmodel.cc \
    player.cc \
    passengertrainsmodel.cc \
    gamestate.cc \
    mapcontroller.cc \
    stationcoordinate.cc \
    relativecoordinate.cc \
    trackcoordinate.cc \
    servicetrainsmodel.cc \
    gamecontroller.cc \
    filedownloader.cc \
    playersmodel.cc \
    traincatalog.cc

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    City.qml

HEADERS += \
    train.hh \
    passengertrain.hh \
    station.hh \
    track.hh \
    medal.hh \
    obstacle.hh \
    servicetrain.hh \
    stationsmodel.hh \
    tracksmodel.hh \
    startcontroller.hh \
    resultscontroller.hh \
    storecontroller.hh \
    passengertrainsmodel.hh \
    obstaclesmodel.hh \
    player.hh \
    gamestate.hh \
    mapcontroller.hh \
    stationcoordinate.hh \
    relativecoordinate.hh \
    trackcoordinate.hh \
    servicetrainsmodel.hh \
    gamecontroller.hh \
    filedownloader.hh \
    playersmodel.hh \
    traincatalog.hh \
    util.hh
