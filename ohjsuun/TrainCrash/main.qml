import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import QtQml.StateMachine 1.0 as DSM

import ohjsuunn.traincrash 0.1

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("TrainCrash")

    function loadHeader(filename) {
        headerLoader.setSource(filename);
    }

    function removeHeader() { headerLoader.setSource(""); }

    function contentItem() { return screenLoader.item; }

    function loadContents(filename) { screenLoader.setSource(filename); }

    property GameState game: null;
    property Player usedPlayer: null;

    function createGame() {
        game = Qt.createQmlObject( // FIXME: tämä on asynkroninen...
            "import ohjsuunn.traincrash 0.1\n\n" +
            "GameState {\n" +
            "  onFinished: GameController.toResults()\n" +
            "}",
            mainWindow
        );
        game.setPlayer(usedPlayer);
        gameTicker.start(); // ...joten tämä tapahtuu ennen kuin GameState on valmis.
    }

    function destroyGame() {
        gameTicker.stop();
        game.destroy();
        game = null;
    }

    Timer {
        id: gameTicker
        interval: 100
        repeat: true
        onTriggered: GameController.performTickUpdates(game)
    }

    property ScreenState screenState: ScreenState {
        window: mainWindow
        pauseDialog: pauseDialog_
    }

    header: Loader {
        id: headerLoader
        source: ""
    }

    PauseDialog {
        id: pauseDialog_
    }

    Loader {
        id: screenLoader
        anchors.fill: parent
        source: "StartScreen.qml"
    }
}
