import QtQuick 2.0
import QtQml.StateMachine 1.0 as DSM

import ohjsuunn.traincrash 0.1

DSM.StateMachine {
    property var window
    property var pauseDialog

    initialState: startScreen
    running: true

    DSM.State {
        id: startScreen

        DSM.SignalTransition {
            targetState: gameScreens
            signal: StartController.startGame
        }

        onEntered: {
            window.removeHeader();
            window.loadContents("StartScreen.qml");
        }
    }

    DSM.State {
        id: gameScreens
        initialState: activeGameScreens

        DSM.State {
            id: activeGameScreens
            initialState: mapScreen

            DSM.State {
                id: mapScreen

                DSM.SignalTransition {
                    targetState: storeScreen
                    signal: MapController.toStore
                }

                onEntered: {
                    window.loadHeader("MapScreenHeader.qml");
                    window.loadContents("MapScreen.qml");
                }
            }

            DSM.State {
                id: storeScreen

                DSM.SignalTransition {
                    targetState: mapScreen
                    signal: StoreController.toMap
                }

                onEntered: {
                    window.loadHeader("StoreScreenHeader.qml");
                    window.loadContents("StoreScreen.qml");
                    gameTicker.stop();
                }
                onExited: {
                    pauseDialog.close();
                    gameTicker.start();
                }
            }

            DSM.HistoryState {
                id: activeGameScreenHistory
                defaultState: mapScreen
            }

            DSM.SignalTransition {
                targetState: gamePaused
                signal: GameController.pause
            }

            DSM.SignalTransition {
                targetState: resultsScreen
                signal: GameController.toResults
            }
        }

        DSM.State {
            id: gamePaused

            DSM.SignalTransition {
                targetState: activeGameScreenHistory
                signal: pauseDialog.resume
            }

            DSM.SignalTransition {
                targetState: resultsScreen
                signal: pauseDialog.forfeit
            }

            onEntered: {
                pauseDialog.open();
                gameTicker.stop()
            }
            onExited: {
                pauseDialog.close();
                gameTicker.start();
            }
        }

        onEntered: window.createGame()
    }

    DSM.State {
        id: resultsScreen

        DSM.SignalTransition {
            targetState: finalState
            signal: ResultsController.quit
        }


        DSM.SignalTransition {
            targetState: startScreen
            signal: ResultsController.toStart
        }

        onEntered: {
            window.removeHeader();
            window.loadContents("ResultsScreen.qml");
            gameTicker.stop();
        }
        onExited: window.destroyGame()
    }

    DSM.FinalState {
        id: finalState
    }

    onFinished: Qt.quit()
}
