#include "SceneModel.hpp"

namespace sw {

SceneModel::SceneModel(Base* aParent) : Base(aParent) {
}

entt::registry& SceneModel::getRegistry() {
    return mRegistry;
}

void SceneModel::clear() {
    mRegistry.clear<>();
}

void SceneModel::addCircle(const QRectF& aBoundingBox) {
    auto vCircle = mRegistry.create();
    mRegistry.emplace<BoundingBox>(vCircle, aBoundingBox);
}

void SceneModel::addCircleSelectable(const QRectF& aBoundingBox, bool aSelected) {
    auto vCircle = mRegistry.create();
    mRegistry.emplace<BoundingBox>(vCircle, aBoundingBox);
    mRegistry.emplace<Selection>(vCircle, aSelected);
}


}