import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import ohjsuunn.traincrash 0.1

ToolBar {
    RowLayout {
        anchors.fill: parent

        Button {
            text: qsTr("to Store")
            onClicked: MapController.toStore()
        }

        Button {
            text: qsTr("Pause Game")
            onClicked: GameController.pause()
        }

        Label { text: "Points: " + game.points }

        Label { text: game.player.name }
    }
}
