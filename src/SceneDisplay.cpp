#include "SceneDisplay.hpp"

#include <QtGui/QPainter>

#include <iostream>

namespace sw {

SceneDisplay::SceneDisplay(Base* aParent) : Base(aParent) {
    this->setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}

void SceneDisplay::paint(QPainter* aPainter) {
    if (!mSceneModel) {
        return;
    }

    aPainter->setRenderHint(QPainter::Antialiasing);

    auto& vRegistry = mSceneModel->getRegistry();

    aPainter->setPen(Qt::NoPen);

    auto vDrawableEntities = vRegistry.view<sw::BoundingBox>();
    for (auto&& vEntity : vDrawableEntities) {
        auto&& vBoundingBox = vDrawableEntities.get<sw::BoundingBox>(vEntity);
        aPainter->setBrush(QBrush(QColor(255, 0, 0, 255)));
        aPainter->drawEllipse(vBoundingBox.mBoundingBox);
    }

    auto vSelectableEntities = vRegistry.view<sw::Selection, sw::BoundingBox>();
    for (auto&& vEntity : vSelectableEntities) {
        const bool vIsSelected = vSelectableEntities.get<sw::Selection>(vEntity).mIsSelected;
        if (!vIsSelected) {
            continue;
        }

        auto&& vBoundingBox = vSelectableEntities.get<sw::BoundingBox>(vEntity);
        aPainter->setBrush(QBrush(QColor(0, 0, 255, 100)));
        aPainter->drawRect(vBoundingBox.mBoundingBox);
    }

    if (mIsSelecting) {
        aPainter->setBrush(QBrush(QColor(0, 0, 255, 100)));
        aPainter->drawRect(mSelectionRect);
    }
}

bool SceneDisplay::setSceneModel(SceneModel* aSceneModel) {
    if (mSceneModel != aSceneModel) {
        mSceneModel = aSceneModel;
        return true;
    }
    return false;
}

SceneModel* SceneDisplay::getSceneModel() const {
    return mSceneModel;
}

void SceneDisplay::mousePressEvent(QMouseEvent* aEvent) {
    std::cout << "mouse pressed\n";
    // Base::mousePressEvent(aEvent);

    mIsSelecting = true;
    mSelectionRect.setTopLeft(aEvent->position());
    mSelectionRect.setBottomRight(aEvent->position());
}

void SceneDisplay::mouseMoveEvent(QMouseEvent* aEvent) {
    std::cout << "mouse moved\n";
    // Base::mouseMoveEvent(aEvent);

    if (mIsSelecting) {
        mSelectionRect.setBottomRight(aEvent->position());
    }
    update();
}

void SceneDisplay::mouseReleaseEvent(QMouseEvent* aEvent) {
    std::cout << "mouse released\n";
    (void)aEvent;
    // Base::mouseReleaseEvent(aEvent);

    mIsSelecting = false;

    auto& vRegistry = mSceneModel->getRegistry();
    auto vSelectableEntities = vRegistry.view<sw::Selection, sw::BoundingBox>();
    for (auto&& vEntity : vSelectableEntities) {

        auto&& vBoundingBox = vSelectableEntities.get<sw::BoundingBox>(vEntity);
        auto& vIsSelected = vSelectableEntities.get<sw::Selection>(vEntity).mIsSelected;
        vIsSelected = mSelectionRect.intersects(vBoundingBox.mBoundingBox);
    }

    update();
}


}