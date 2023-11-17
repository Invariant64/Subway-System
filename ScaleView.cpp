//
// Created by Noah on 2023/11/16.
//

#include "ScaleView.h"


ScaleView::ScaleView(QWidget *parent) : QGraphicsView(parent) {}

void ScaleView::wheelEvent(QWheelEvent *event) {
    // setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.05;
    if (event->angleDelta().y() > 0) {
        scale(scaleFactor, scaleFactor);
    }
    else {
        scale(1 / scaleFactor, 1 / scaleFactor);
    }
}
