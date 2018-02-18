import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtPositioning 5.5
import QtLocation 5.6 as Loc

import ohjsuunn.traincrash 0.1

Item {
    property var centerCoordinate: game.stations.getStation("JY").location

    Loc.Map {
        id: map

        anchors.fill: parent
        plugin: Loc.Plugin { name: "osm" }
        center: centerCoordinate
        zoomLevel: 6.3

        Loc.MapItemView {
            model: game.stations
            delegate: Component {
                Loc.MapQuickItem {
                    sourceItem: Rectangle {
                        width: draw ? 15 : 1;
                        height: draw ? 15 : 1;
                        color: "red";
                        smooth: true;
                        radius: draw ? 15 : 1;
                    }
                    coordinate : location
                    opacity: 1.0
                    anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)

                    MouseArea {
                        anchors.fill: parent
                        onClicked: MapController.serviceTrainToStation(game, station)
                    }
                    z: 1
                }
            }
        }

        Loc.MapItemView {
            model: game.tracks
            delegate: Component {
                Loc.MapPolyline {
                    line {
                        width: 3
                        color: "red"
                    }
                    path : coordinates

                    MouseArea {
                        anchors.fill: parent
                        onClicked: MapController.serviceTrainToTrack(game, track)
                    }
                    z: 0
                }
            }
        }

        Loc.MapItemView {
            model: game.obstacles
            delegate: Component {
                Loc.MapQuickItem {
                    sourceItem: Rectangle {
                        width: 20;
                        height: 20;
                        color: "darkOrange";
                        smooth: true;
                        radius: 15;
                    }
                    coordinate: location
                    opacity: 1.0;
                    anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2);
                    z: 3
                }
            }
        }

        Loc.MapItemView {
            model: game.passengerTrains
            delegate: Component {
                Loc.MapQuickItem {
                    sourceItem: Rectangle {
                        width: 20;
                        height: 20;
                        color: "darkBlue"
                        smooth: true;
                        radius: 15
                        opacity: health;
                    }
                    coordinate: location
                    opacity: 1.0 ;
                    anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2);
                    z: 2
                }
            }
        }

        Loc.MapItemView {
            model: game.serviceTrains
            delegate: Component {
                Loc.MapQuickItem {
                    sourceItem: Rectangle {
                        width: 20;
                        height: 20;
                        color: active ? "yellow" : "green";
                        smooth: true;
                        radius: 15;
                        opacity: health;
                    }
                    coordinate: location
                    anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)

                    MouseArea {
                        anchors.fill: parent
                        onClicked: MapController.setActiveTrain(game, train)
                    }
                    z: 4
                    visible: health > 0

                }
            }
        }
    }
}
