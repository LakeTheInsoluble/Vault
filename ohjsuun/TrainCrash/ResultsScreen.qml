import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

import ohjsuunn.traincrash 0.1

Item {
    ColumnLayout {
        width: parent.width
        spacing: 50
        Rectangle {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            //color: "crimson"
            color: game.status === 3 ? "green" : "crimson"
            Text {
                anchors.centerIn: parent
                text : game != null ? (game.status === 3 ? "Day ended! You won!" : "You lost!") : "";
                font.bold: true
                font.pointSize: 20
                color: "white"
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            Button {
                text: qsTr("Quit")
                onClicked: ResultsController.quit()
            }
        }
    }
}
