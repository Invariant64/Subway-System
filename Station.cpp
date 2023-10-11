//
// Created by Noah on 2023/9/18.
//

#include "Station.h"

#include <utility>

Station::Station(int id, QString name) :
        id_(id), name_(std::move(name)) {}

int Station::getId() const {
    return id_;
}

QString Station::getName() const {
    return name_;
}
