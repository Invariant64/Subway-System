//
// Created by Noah on 2023/11/8.
//

#include <QHBoxLayout>
#include "SelectionWidget.h"

SelectionWidget::SelectionWidget(QWidget *parent) {
    current_station_name_ = "";
    initUI();
    initConnect();
}

SelectionWidget::~SelectionWidget() {
    delete set_start_button_;
    delete set_end_button_;
    delete cancel_button_;
}

void SelectionWidget::initUI() {
    set_start_button_ = new QPushButton("设为起点", this);
    set_end_button_ = new QPushButton("设为终点", this);
    cancel_button_ = new QPushButton("取消", this);

    auto v_layout = new QVBoxLayout();
    v_layout->addWidget(set_start_button_);
    v_layout->addWidget(set_end_button_);
    v_layout->addWidget(cancel_button_);

    setLayout(v_layout);
}

void SelectionWidget::initConnect() {
    connect(cancel_button_, &QPushButton::clicked, this, [=](){
        this->hide();
        current_station_name_ = "";
    });
}

void SelectionWidget::setCurrentStationName(QString name) {
    current_station_name_ = name;
}

QString SelectionWidget::getCurrentStationName() const {
    return current_station_name_;
}
