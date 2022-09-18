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

        SceneDisplay {
            id: scene_display

            sceneModel: SceneModel {
                
            }

            Button {
                id: button_generate
                text: "qsTr(Generate)"
                onClicked: {
                    scene_display.sceneModel.clear();

                    var diameter = 5;
                    for (var i = 0; i < 1000; ++i) {
                        var posX = Math.random() * (scene_display.width - diameter);
                        var posY = Math.random() * (scene_display.height - diameter);
                        scene_display.sceneModel.addCircle(Qt.rect(posX, posY, diameter, diameter));
                    }

                    for (var i = 0; i < 1000; ++i) {
                        var posX = Math.random() * (scene_display.width - diameter);
                        var posY = Math.random() * (scene_display.height - diameter);
                        scene_display.sceneModel.addCircleSelectable(Qt.rect(posX, posY, diameter, diameter), false);
                    }
                    scene_display.update();
                }
            }
            
        }
    }
}