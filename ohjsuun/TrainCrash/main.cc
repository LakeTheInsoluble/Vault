#include "player.hh"
#include "medal.hh"
#include "station.hh"
#include "servicetrain.hh"
#include "relativecoordinate.hh"
#include "stationcoordinate.hh"
#include "trackcoordinate.hh"
#include "startcontroller.hh"
#include "gamecontroller.hh"
#include "mapcontroller.hh"
#include "storecontroller.hh"
#include "resultscontroller.hh"
#include "gamestate.hh"
#include "passengertrainsmodel.hh"
#include "playersmodel.hh"
#include "stationsmodel.hh"
#include "tracksmodel.hh"
#include "util.hh"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

char const *appId = "ohjsuunn.traincrash";
uint const versionMajor = 0;
uint const versionMinor = 1;

template<typename T>
static QObject *singletonProvider(QQmlEngine*, QJSEngine*) { return T::instance(); }

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register types for QML:
    qmlRegisterType<Player>(appId, versionMajor, versionMinor, "Player");
    qmlRegisterType<Medal>(appId, versionMajor, versionMinor, "Medal");
    qmlRegisterType<Obstacle>();
    qmlRegisterType<Station>();
    qmlRegisterType<Track>();
    qmlRegisterType<ServiceTrain>();
    qmlRegisterType<GameState>(appId, versionMajor, versionMinor, "GameState");
    qmlRegisterSingletonType<PlayersModel>(appId, versionMajor, versionMinor, "PlayersModel",
                                                     singletonProvider<PlayersModel>);

    qmlRegisterSingletonType<GameController>(appId, versionMajor, versionMinor, "GameController",
                                             singletonProvider<GameController>);
    qmlRegisterSingletonType<StartController>(appId, versionMajor, versionMinor, "StartController",
                                              singletonProvider<StartController>);
    qmlRegisterSingletonType<MapController>(appId, versionMajor, versionMinor, "MapController",
                                            singletonProvider<MapController>);
    qmlRegisterSingletonType<StoreController>(appId, versionMajor, versionMinor, "StoreController",
                                              singletonProvider<StoreController>);
    qmlRegisterSingletonType<ResultsController>(appId, versionMajor, versionMinor,
                                                "ResultsController",
                                                singletonProvider<ResultsController>);

    // Create QML engine:
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) { return -1; }

    return app.exec();
}
