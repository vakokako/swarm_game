import QtQuick 2.15  // For QColor
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.15

Window {
    id: titlebar_reload_window
    visible: true

    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.WA_TranslucentBackground | Qt.WA_ShowWithoutActivating
    color: "#00000000"
    
    x: loader.status == Loader.Ready ? loader.item.x : 0
    y: loader.status == Loader.Ready ? loader.item.y - this.height : 0
    height: 30
    width: 100

    onHeightChanged: {
        console.log('titlebar_reload_window.height changed : ', this.height);
        this.height = 30
    }


    component TitleBarButton : Image {
        property string icon_active;
        property string icon_pressed;
        property string icon_hovered;

        id: title_bar_button
        source: {
            if (!mouseArea.containsMouse) {
                return icon_active;
            } else if (mouseArea.pressed) {
                return icon_pressed;
            } else {
                return icon_hovered;
            }
        }

        signal clicked(var mouse)

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true
        }

        Component.onCompleted: {
            mouseArea.clicked.connect(clicked)
        }
    }

    Row {
        id: title_buttons_row
        anchors.fill: parent
        spacing: 5
        anchors.margins: 5
        
        TitleBarButton {
            width: title_buttons_row.height
            height: this.width
            icon_active: "icons/exit_idle.svg"
            icon_pressed: "icons/exit_pressed.svg"
            icon_hovered: "icons/exit_active.svg"
            onClicked: {
                Qt.callLater(Qt.quit)
            }
        }

        TitleBarButton {
            width: title_buttons_row.height
            height: this.width
            icon_active: "icons/refresh_idle.svg"
            icon_pressed: "icons/refresh_pressed.svg"
            icon_hovered: "icons/refresh_active.svg"
            onClicked: {
                loader.reload()
            }
        }
    }

    Loader {
        id: loader
        objectName: "loader"
        anchors.centerIn: parent
        asynchronous: true
        source: gHotReloadPathProvider.getLoadPath()
        readonly property double reloadCooldownMs: 1000

        property double lastReloadTime: 0
        property bool isLoading: false

        function reload() {
            var currTime = new Date().getTime()
            if (currTime - lastReloadTime < reloadCooldownMs) {
                return;
            }
            lastReloadTime = currTime
            if (this.isLoading) {
                return;
            }
            this.isLoading = true;
            
            source = "";
            gQmlEngine.clearCache();
            let sourcePath = gHotReloadPathProvider.getReloadPath();
            console.log("Reloading path: ", sourcePath);
            source = sourcePath;
        }

        onStatusChanged: {
            this.isLoading = loader.status == Loader.Loading ? true : false;
        }
    }

    Connections {
        target: gReloadSignaler
        function onReloadRequested() {
            loader.reload();
        }
    }

    Connections {
        target: loader
        function onStatusChanged() {
            if (loader.status != Loader.Ready) {
                return;
            }
            if (! loader.item instanceof Window) {
                return;
            }

            loader.item.activeChanged.connect(updateTitleBarVisibility);
        }
    }

    onActiveChanged: {
        if (this.active && loader.item) {
            // console.log("requesting loader item activate");
            loader.item.requestActivate();
        }
    }

    function updateTitleBarVisibility() {
        // console.log('window, reload : ', loader.item.active, ", ", titlebar_reload_window.visible);
        let isWindowVisible = loader.item.active;

        if (isWindowVisible == titlebar_reload_window.visible) {
            return;
        }
        
        titlebar_reload_window.visible = isWindowVisible;
    }
}