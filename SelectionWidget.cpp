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
    delete setStartButton;
    delete setEndButton;
    delete cancelButton;
}

void SelectionWidget::initUI() {
    setStartButton = new QPushButton("设为起点", this);
    setEndButton = new QPushButton("设为终点", this);
    cancelButton = new QPushButton("取消", this);

    auto v_layout = new QVBoxLayout();
    v_layout->addWidget(setStartButton);
    v_layout->addWidget(setEndButton);
    v_layout->addWidget(cancelButton);

    setLayout(v_layout);
}

void SelectionWidget::initConnect() {
    connect(cancelButton, &QPushButton::clicked, this, [=](){
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
