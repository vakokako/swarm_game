#pragma once

#include <QtCore/QObject>
#include <QtQuick/QQuickItem>

#include <entt/entt.hpp>

namespace sw {

struct BoundingBox {
    QRectF mBoundingBox;
};

struct Selection {
    bool mIsSelected;
};

class SceneModel : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    using Base = QObject;
    explicit SceneModel(Base* aParent = nullptr);
    ~SceneModel() override = default;

    entt::registry& getRegistry();

    Q_INVOKABLE void clear();
    Q_INVOKABLE void addCircle(const QRectF& aBoundingBox);
    Q_INVOKABLE void addCircleSelectable(const QRectF& aBoundingBox, bool aSelected);

private:
    entt::registry mRegistry;
};

}