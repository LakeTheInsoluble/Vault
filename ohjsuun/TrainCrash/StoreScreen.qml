import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

import ohjsuunn.traincrash 0.1

Item {
    ScrollView {
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.horizontalCenter
        }

        ListView {
            model: game.serviceTrains
            header: Rectangle {
                width: parent.width
                height: 48
                color: "forestGreen"

                Text {
                    anchors.centerIn: parent
                    font.bold: true
                    color: "white"
                    text: game.player.name + " (" + game.player.coupons + " coupons)"
                }
            }
            delegate: Rectangle {
                property int damage: train.maxHealth - train.health
                property int repairCost: Math.ceil(damage / train.maxHealth * train.price)

                width: parent.width
                height: 60
                border.color: "grey"

                RowLayout {
                    anchors {
                        fill: parent
                        margins: 8
                    }
                    Column {
                        Text { text: "<b>" + train.model + "</b>" }
                        Text { text: "<b>Condition: </b>" + train.health + "/" + train.maxHealth }
                        Text { text: "<b>Location: </b>" + location }
                    }
                    Button {
                        Layout.fillHeight: true
                        enabled: damage > 0 && game.player.coupons >= repairCost
                        text: qsTr("Repair (" + repairCost + " coupons)")
                        onClicked: StoreController.repairTrain(game, train, damage, repairCost)
                    }
                }
            }
        }
    }

    ScrollView {
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.horizontalCenter
            right: parent.right
        }

        ListView {
            model: game.catalog
            header: Rectangle {
                width: parent.width
                height: 48
                color: "navy"

                Text {
                    anchors.centerIn: parent
                    font.bold: true
                    color: "white"
                    text: "the Store"
                }
            }
            delegate: Rectangle {
                width: parent.width
                height: 48
                border.color: "grey"

                RowLayout {
                    anchors {
                        fill: parent
                        margins: 8
                    }

                    Text {
                        Layout.fillWidth: true
                        text: model
                    }
                    Button {
                        Layout.fillHeight: true
                        enabled: game.player.coupons >= price
                        text: qsTr("Buy" + " (" + price + " coupons)")
                        onClicked: StoreController.buyTrain(game, model, price, maxHealth, speed)
                    }
                }
            }
        }
    }
}
