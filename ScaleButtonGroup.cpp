//
// Created by Noah on 2023/11/15.
//

#include <QHBoxLayout>
#include "ScaleButtonGroup.h"

void ScaleButtonGroup::initUI() {
    expand_button_ = new QPushButton("放大", this);
    shrink_button_ = new QPushButton("缩小", this);

    auto h_layout = new QHBoxLayout();
    h_layout->addWidget(expand_button_);
    h_layout->addWidget(shrink_button_);

    setLayout(h_layout);
}

void ScaleButtonGroup::initConnect() {
    connect(expand_button_, &QPushButton::clicked, this, [=](){
        if (view_->transform().m11() < scale_max_.x()) {
            view_->scale(scale_expand_.x(), scale_expand_.y());
        }
    });
    connect(shrink_button_, &QPushButton::clicked, this, [=](){
        if (view_->transform().m11() > scale_min_.x()) {
            view_->scale(scale_shrink_.x(), scale_shrink_.y());
        }
    });
}

ScaleButtonGroup::ScaleButtonGroup(QPointF scale_expand, QPointF scale_shrink, QPointF scale_max, QPointF scale_min, QGraphicsView *view, QWidget *parent) : QWidget(parent) {
    scale_expand_ = scale_expand;
    scale_shrink_ = scale_shrink;
    scale_max_ = scale_max;
    scale_min_ = scale_min;
    view_ = view;
    initUI();
    initConnect();
}

ScaleButtonGroup::~ScaleButtonGroup() {
    delete expand_button_;
    delete shrink_button_;
}
