//
// Created by Noah on 2023/12/15.
//

#include "Sight.h"

Sight::Sight(int id, const QString &name, const QString &description, double price, int related_station_id)
    : id_(id), name_(name), description_(description), price_(price), related_station_id_(related_station_id) {}

int Sight::getId() const {
    return id_;
}

const QString &Sight::getName() const {
    return name_;
}

const QString &Sight::getDescription() const {
    return description_;
}

double Sight::getPrice() const {
    return price_;
}

int Sight::getRelatedStationId() const {
    return related_station_id_;
}
