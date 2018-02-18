import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

import ohjsuunn.traincrash 0.1

Item {
    ColumnLayout{
        anchors.fill: parent
        ScrollView {
            Layout.fillWidth: true
            anchors.top : parent.top
            ListView {
                model: PlayersModel
                header: Rectangle {
                    width: parent.width
                    height: 48
                    color: "forestGreen"

                    Text {
                        anchors.centerIn: parent
                        font.bold: true
                        color: "white"
                        text: "Choose player"
                    }
                }
                delegate: Rectangle {

                    width: parent.width
                    height: 60
                    Button {
                        anchors.centerIn: parent
                        text: name
                        font.bold: true
                        onClicked: {
                            usedPlayer = player;
                            StartController.startGame();
                        }
                    }
                }
                footer: Rectangle {
                    width: parent.width
                    height: 60
                    RowLayout{
                        anchors.centerIn: parent
                        TextField {
                            id: newPlayerName
                            placeholderText: qsTr("Enter name")
                        }
                        Button {
                            text: "Create new player"
                            font.bold: true
                            onClicked: {
                                if (newPlayerName.text.trim().length > 0) {
                                    PlayersModel.addPlayer(newPlayerName.text.trim())
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
