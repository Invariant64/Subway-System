//
// Created by Noah on 2023/11/16.
//

#include "ScaleView.h"


ScaleView::ScaleView(QWidget *parent) : QGraphicsView(parent) {
    setDragMode(QGraphicsView::ScrollHandDrag);
    scale(0.25, 0.25);
}

void ScaleView::wheelEvent(QWheelEvent *event) {
    double scaleFactor = 1.02;
    if (event->angleDelta().y() > 0) {
        if (transform().m11() < 0.5) {
            scale(scaleFactor, scaleFactor);
        }
    }
    else {
        if (transform().m11() > 0.0625) {
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
}
