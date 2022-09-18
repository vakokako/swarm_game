// #include <QApplication>
#include <QtWidgets/qapplication.h>

#include "HotReload/HotReload.hpp"

#include <QDirIterator>

int main(int argc, char** argv) {
    HotReloadQGuiApplication vApp(argc, argv);

    HotReloadQmlApplicationEngine vQmlEngine;
    vQmlEngine.setGuiApplication(&vApp);
    vQmlEngine.getHotReloadPathProvider().setLoadPathPrefix("qrc:/");
    vQmlEngine.getHotReloadPathProvider().setReloadPathPrefix("file:///home/mvankovych/dev/cpp/projects/swarm_game/src/");
    vQmlEngine.load("SwarmMainWindow.qml");

    // QDirIterator it(":", QDirIterator::Subdirectories);
    // while (it.hasNext()) {
    //     qDebug() << it.next();
    // }

    return QApplication::exec();
}
