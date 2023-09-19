//
// Created by Noah on 2023/9/18.
//

#include "Edge.h"

Edge::Edge(int id, int line_id, int station_id, int next_station_id, int weight_time, int weight_distance) :
        id_(id), line_id_(line_id), station_id_(station_id), next_station_id_(next_station_id),
        weight_time_(weight_time), weight_distance_(weight_distance) {}

int Edge::getId() const {
    return id_;
}

int Edge::getLineId() const {
    return line_id_;
}

int Edge::getStationId() const {
    return station_id_;
}

int Edge::getNextStationId() const {
    return next_station_id_;
}

int Edge::getWeightTime() const {
    return weight_time_;
}

int Edge::getWeightDistance() const {
    return weight_distance_;
}
