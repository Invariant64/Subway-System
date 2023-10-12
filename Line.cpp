//
// Created by Noah on 2023/10/10.
//

#include "Line.h"


Line::Line(int id, QString name) : id_(id), name_(std::move(name)) {}

int Line::getId() const {
    return id_;
}

QString Line::getName() const {
    return name_;
}