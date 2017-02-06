import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 2.1

import App 1.0

Window {
    id: window
    width: 400
    height: 300
    title: qsTr("Perlin Islands")
    visible: true

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: "Constant \"A\""
            Layout.alignment: Qt.AlignHCenter
        }

        Slider {
            id: constantASlider
            from: 0.2
            value: 0.3
            to: 0.4
            live: true
            Layout.alignment: Qt.AlignHCenter

            ToolTip {
                parent: constantASlider.handle
                visible: constantASlider.pressed
                text: constantASlider.value.toFixed(2)
            }
        }

        Label {
            text: "Constant \"B\""
            Layout.alignment: Qt.AlignHCenter
        }

        Slider {
            id: constantBSlider
            from: 0.4
            value: 0.4
            to: 0.6
            live: true
            Layout.alignment: Qt.AlignHCenter

            ToolTip {
                parent: constantBSlider.handle
                visible: constantBSlider.pressed
                text: constantBSlider.value.toFixed(2)
            }
        }

        Label {
            text: "Seed"
            Layout.alignment: Qt.AlignHCenter
        }

        Slider {
            id: seedSlider
            from: 0
            value: 0
            to: 10000
            stepSize: 1
            live: true
            Layout.alignment: Qt.AlignHCenter

            ToolTip {
                parent: seedSlider.handle
                visible: seedSlider.pressed
                text: seedSlider.value.toFixed(0)
            }
        }

        PerlinItem {
            constantA: constantASlider.value
            constantB: constantBSlider.value
            seed: seedSlider.value
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
