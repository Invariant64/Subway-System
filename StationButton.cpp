//
// Created by Noah on 2023/11/3.
//

#include "StationButton.h"

StationButton::StationButton(Station *station, QWidget *parent) :
    id_(station->getId()), name_(station->getName()), position_(station->getPosition()), QPushButton(parent) {

    initUI();
    initConnect();
}

void StationButton::initUI() {
    resize (2 * RADIUS, 2 * RADIUS);
    setStyleSheet(normal_style);
    setText(name_);
}

void StationButton::initConnect() {
    connect(this, &StationButton::pressed, this, [=](){
        setStyleSheet(pressed_style);
    });
    connect(this, &StationButton::released, this, [=](){
        setStyleSheet(normal_style);
    });
}








