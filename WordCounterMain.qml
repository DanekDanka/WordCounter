import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Dialogs
// import QtQml.StateMachine 6.7

// import Mediator 1.0

// import QtQuick 2.11
// import QtQuick.Controls 2.4
// import QtQuick.Layouts 1.3
// import QtQuick.Dialogs 1.3
// import QtCharts 2.2
// import QtQml 2.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Word Counter")

    color: "green"

    // UiMediator {
    //     id: mediator
    // }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"

        onAccepted: {
            mediator.setUrl(fileDialog.currentFile)
        }
    }

    // StateMachine {
    //     id: stateMachine
    //
    //     State {
    //         name: "initial"
    //     }
    //     State {
    //         name: "playing"
    //     }
    //     State {
    //         name: "paused"
    //     }
    //     State {
    //         name: "stopped"
    //     }
    //
    //     Transition {
    //         from: "initial"
    //         to: "playing"
    //         onTriggered: playButton.clicked
    //     }
    //     Transition {
    //         from: "playing"
    //         to: "paused"
    //         onTriggered: pauseButton.clicked
    //     }
    //     Transition {
    //         from: "paused"
    //         to: "playing"
    //         onTriggered: countinueButton.clicked
    //     }
    //     Transition {
    //         from: ["playing", "paused"]
    //         to: "stopped"
    //         onTriggered: stopButton.clicked
    //     }
    //
    //     initialState: "initial"
    // }



    ColumnLayout {
        width: root.width
        height: root.height

        RowLayout {
            Layout.fillWidth: true
            // Layout.preferredHeight: 50

            Button {
                id: chooseFile
                Layout.fillWidth: true
                text: "Choose file"


                onClicked: {
                    fileDialog.open()
                }
            }

            Button {
                id: playButton
                Layout.fillWidth: true
                text: "Play"
                enabled: stateMachine.state === "initial" || stateMachine.state === "paused"
                onClicked: {
                    // stateMachine.start()
                    mediator.Play = playButton.pressed
                }
            }

            Button {
                id: pauseButton
                Layout.fillWidth: true
                text: "Pause"
                enabled: stateMachine.state === "playing"

                onClicked: {
                    mediator.Pause = pauseButton.pressed
                }
            }

            Button {
                id: countinueButton
                Layout.fillWidth: true
                text: "Continue"
                enabled: stateMachine.state === "paused"

                onClicked: {
                    mediator.Continue = countinueButton.pressed
                }
            }

            Button {
                id: stopButton
                Layout.fillWidth: true
                text: "Stop"
                enabled: stateMachine.state === "playing" || stateMachine.state === "paused"

                onClicked: {
                    mediator.Stop = stopButton.pressed
                }
            }



        }

        ProgressBar {
            Layout.fillWidth: true
            value: mediator.Persentage
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 10
            model: vocabularyModel

            orientation: ListView.Horizontal // Make the list view horizontal

            delegate: Rectangle {
                width: root.width / 15 - 10
                height: Math.min(value * 5, parent.height)
                color: "steelblue"
                border.color: "black"
                border.width: 1

                Text {

                    text: name
                    anchors.top: parent.bottom
                    // anchors.horizontalCenter: parent.horizontalCenter
                    // anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 14
                    transform: Rotation { angle: 270 }
                }
            }

            spacing: 10 // Add some space between each bar
        }


    }

}
