import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import QtQml.StateMachine 1.0 as DSM

import ohjsuunn.traincrash 0.1

Dialog {
    id: pauseDialog_
    
    signal resume()
    signal forfeit()
    
    modal: true
    title: qsTr("Game Paused")
    
    RowLayout {
        anchors.fill: parent
        
        Button {
            text: qsTr("Resume")
            onClicked: pauseDialog_.resume()
        }
        
        Button {
            text: qsTr("Forfeit")
            onClicked: pauseDialog_.forfeit()
        }
    }
}
