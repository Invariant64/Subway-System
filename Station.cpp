//
// Created by Noah on 2023/9/18.
//

#include "Station.h"

#include <utility>

Station::Station(int id, QString name, QPointF position) :
        id_(id), name_(std::move(name)), position_(position) {}

int Station::getId() const {
    return id_;
}

QString Station::getName() const {
    return name_;
}

QPointF Station::getPosition() const {
    return position_;
}