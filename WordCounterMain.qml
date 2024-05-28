import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Dialogs
// import QtQml.StateMachine 6.7

import Mediator 1.0

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

    UiMediator {
        id: mediator
    }

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
            value: 0.5
        }




        Canvas {
            id: histogramCanvas
            width: 200
            height: 200
            Layout.fillHeight: true

            property var histogramData: [5, 10, 15, 20, 25]
            property var histogramOptions: { color: "blue" }

            function drawHistogram(canvas, data, options) {
                if (!canvas.getContext) {
                    return;
                }
                var ctx = canvas.getContext('2d');
                var width = canvas.width;
                var height = canvas.height;
                var barWidth = width / data.length;

                ctx.clearRect(0, 0, width, height);
                ctx.fillStyle = options.color;

                for (var i = 0; i < data.length; i++) {
                    var barHeight = (data[i] / Math.max(...data)) * height;
                    ctx.fillRect(i * barWidth, height - barHeight, barWidth - 1, barHeight);
                }
            }

            onPaint: {
                if (histogramCanvas.available) {
                    var ctx = getContext("2d");
                    ctx.clearRect(0, 0, histogramCanvas.width, histogramCanvas.height);
                    drawHistogram(histogramCanvas, histogramData, histogramOptions);
                }
            }
        }

        Component.onCompleted: {
            if (histogramCanvas.available) {
                drawHistogram(histogramCanvas, histogramData, histogramOptions);
            }
        }



    }
}
