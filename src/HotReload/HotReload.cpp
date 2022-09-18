#include "HotReload.hpp"

#include <QQmlContext>

Q_INVOKABLE QString HotReloadPathProvider::getLoadPath() {
    return getLoadPathPrefix() + getSourcePath();
}
Q_INVOKABLE QString HotReloadPathProvider::getReloadPath() {
    // return QString::fromStdString("file:///" + bda::BaseEnvironment::getEnv("BDASOFTSRC_OSPATH") + "/BDACellAnalyzer/qmlui/");
    return getReloadPathPrefix() + getSourcePath();
}

void HotReloadPathProvider::setSourcePath(const QString& aSourcePath) {
    mSourcePath = aSourcePath;
}

const QString& HotReloadPathProvider::getSourcePath() const {
    return mSourcePath;
}

void HotReloadPathProvider::setLoadPathPrefix(const QString& aLoadPathPrefix) {
    mLoadPathPrefix = aLoadPathPrefix;
}

const QString& HotReloadPathProvider::getLoadPathPrefix() const {
    return mLoadPathPrefix;
}

void HotReloadPathProvider::setReloadPathPrefix(const QString& aReloadPathPrefix) {
    mReloadPathPrefix = aReloadPathPrefix;
}

const QString& HotReloadPathProvider::getReloadPathPrefix() const {
    return mReloadPathPrefix;
}

HotReloadQGuiApplication::HotReloadQGuiApplication(int& argc, char** argv, int flags) : QGuiApplication(argc, argv, flags) {}

bool HotReloadQGuiApplication::notify(QObject* recv, QEvent* e) {
    if (e->type() == QEvent::KeyPress) {
        auto* ke = dynamic_cast<QKeyEvent*>(e);
        if (ke->key() == Qt::Key_F5) {
            emit reloadRequested();
        }
    }
    return QGuiApplication::notify(recv, e);
}

HotReloadQmlApplicationEngine::HotReloadQmlApplicationEngine(QObject* parent) : QQmlApplicationEngine(parent) {
    this->rootContext()->setContextProperty("gQmlEngine", this);
    this->rootContext()->setContextProperty("gHotReloadPathProvider", &mHotReloadPathProvider);
}

void HotReloadQmlApplicationEngine::load(const QString& aFilePath) {
    mHotReloadPathProvider.setSourcePath(aFilePath);
    QQmlApplicationEngine::load("qrc:/qml/HotReload/HotReload.qml");
}

void HotReloadQmlApplicationEngine::setGuiApplication(HotReloadQGuiApplication* aGuiApplication) {
    this->rootContext()->setContextProperty("gReloadSignaler", aGuiApplication);
}

HotReloadPathProvider& HotReloadQmlApplicationEngine::getHotReloadPathProvider() {
    return mHotReloadPathProvider;
}

Q_INVOKABLE void HotReloadQmlApplicationEngine::clearCache() {
    this->trimComponentCache();
    this->clearComponentCache();
    this->trimComponentCache();
}