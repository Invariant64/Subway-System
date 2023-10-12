//
// Created by Noah on 2023/10/10.
//

#include "Line.h"


Line::Line() {
    id_ = 0;
    name_ = "";
    stations_id_ = new QList<int>();
}

Line::~Line() {
    delete stations_id_;
}

Line::Line(int id, QString name) : id_(id), name_(std::move(name)) {
    stations_id_ = new QList<int>();
}

int Line::getId() const {
    return id_;
}

QString Line::getName() const {
    return name_;
}

QList<int> *Line::getStationsId() const {
    return stations_id_;
}

void Line::addStationId(int station_id) {
    stations_id_->append(station_id);
}

