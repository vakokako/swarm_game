#pragma once

#include <QGuiApplication>
#include <QKeyEvent>
#include <QObject>
#include <QQmlApplicationEngine>

class HotReloadPathProvider : public QObject {
    Q_OBJECT

public:
    explicit HotReloadPathProvider() = default;
    Q_INVOKABLE QString getLoadPath();
    Q_INVOKABLE QString getReloadPath();

    void setSourcePath(const QString& aSourcePath);
    const QString& getSourcePath() const;

    void setLoadPathPrefix(const QString& aLoadPathPrefix);
    const QString& getLoadPathPrefix() const;

    void setReloadPathPrefix(const QString& aReloadPathPrefix);
    const QString& getReloadPathPrefix() const;

private:
    QString mSourcePath;
    QString mLoadPathPrefix = "qrc:/";
    QString mReloadPathPrefix = "file:///";
};

class HotReloadQGuiApplication : public QGuiApplication {
    Q_OBJECT
public:
    explicit HotReloadQGuiApplication(int& argc, char** argv, int flags = ApplicationFlags);

    bool notify(QObject* recv, QEvent* e);

signals:
    void reloadRequested();
};

class HotReloadQmlApplicationEngine : public QQmlApplicationEngine {
    Q_OBJECT
public:
    explicit HotReloadQmlApplicationEngine(QObject* parent = nullptr);

    void load(const QString& aFilePath);

    void setGuiApplication(HotReloadQGuiApplication* aGuiApplication);

    HotReloadPathProvider& getHotReloadPathProvider();

    Q_INVOKABLE void clearCache();

private:
    using QQmlApplicationEngine::load;

    HotReloadPathProvider mHotReloadPathProvider;
};