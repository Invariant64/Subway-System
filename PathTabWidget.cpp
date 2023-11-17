//
// Created by Noah on 2023/11/17.
//

#include "PathTabWidget.h"

PathTabWidget::PathTabWidget() {
    scene_time_ = new PathScene;
    scene_distance_ = new PathScene;
    scene_transfer_ = new PathScene;

    view_time_ = new QGraphicsView(scene_time_);
    view_distance_ = new QGraphicsView(scene_distance_);
    view_transfer_ = new QGraphicsView(scene_transfer_);

    view_time_->setRenderHint(QPainter::Antialiasing);
    view_distance_->setRenderHint(QPainter::Antialiasing);
    view_transfer_->setRenderHint(QPainter::Antialiasing);

    this->addTab(view_time_, "最短时间");
    this->addTab(view_distance_, "最短距离");
    this->addTab(view_transfer_, "最少换乘");
}

PathTabWidget::~PathTabWidget() {
    delete scene_time_;
    delete scene_distance_;
    delete scene_transfer_;
    delete view_time_;
    delete view_distance_;
    delete view_transfer_;
}

void PathTabWidget::setNet(Net *net) {
    scene_time_->setNet(net);
    scene_distance_->setNet(net);
    scene_transfer_->setNet(net);
}

void PathTabWidget::drawPath(QList<Edge *> &path, int weight_mode) {
    scene_time_->drawPath(path);
    scene_distance_->drawPath(path);
    scene_transfer_->drawPath(path);
}
