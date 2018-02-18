import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import ohjsuunn.traincrash 0.1

ToolBar {
    RowLayout {
        anchors.fill: parent

        Button {
            text: qsTr("Back to Map")
            onClicked: StoreController.toMap()
        }

        Button {
            text: qsTr("Pause Game")
            onClicked: GameController.pause()
        }
    }
}
