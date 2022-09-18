#pragma once

#include "SceneModel.hpp"

#include <QtQuick/QQuickPaintedItem>

class QPainter;

namespace sw {

class SceneDisplay : public QQuickPaintedItem {
    Q_OBJECT
    QML_ELEMENT
public:
    using Base = QQuickPaintedItem;
    explicit SceneDisplay(Base* aParent = nullptr);
    ~SceneDisplay() override = default;

    void paint(QPainter* aPainter) override;

    bool setSceneModel(SceneModel* aSceneModel);
    SceneModel* getSceneModel() const;

protected:
    void mousePressEvent(QMouseEvent* aEvent) override;
    void mouseMoveEvent(QMouseEvent* aEvent) override;
    void mouseReleaseEvent(QMouseEvent* aEvent) override;

private:
    Q_PROPERTY(SceneModel* sceneModel READ getSceneModel WRITE setSceneModel FINAL REQUIRED)
    SceneModel* mSceneModel;

    bool mIsSelecting = false;
    QRectF mSelectionRect;
};

}