// import People 1.0
import QtQuick 2.15  // For QColor
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts
import QtQml.Models 2.2

import SwarmCpp 1.0
// import BDAQuick 1.0

// Don't import, this disables hot reload
// import BDAQuick 1.0

ApplicationWindow {
    visible: true
    width: Screen.width / 2
    x: Screen.width / 2
    height: 8 * Screen.height / 10
    y: 1.5 * Screen.height / 10

    minimumWidth: layout.Layout.minimumWidth
    minimumHeight: layout.Layout.minimumHeight

    header: TabBar {
        id: bar
        width: parent.width

        TabButton {
            text: qsTr("Swarm")
        }
    }


    StackLayout {
        id: layout
        anchors.fill: parent
        currentIndex: bar.currentIndex
        objectName: "stack_layout"

        Rectangle {
            color: "red"
            Rectangle {
                anchors.centerIn: parent
                width: parent.width / 2
                height: parent.height / 2
                color: "blue"
            }
        }
    }
}