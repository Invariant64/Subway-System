//
// Created by Noah on 2023/9/18.
//

#include "Net.h"

#include <QFile>
#include <QTextStream>
#include <QMap>


Net::Net() {
    stations_ = new QMap<int, Station>();
    edges_ = new QMap<int, Edge>();
}

Net::Net(const QString& stations_file_name, const QString& edges_file_name) {
    stations_ = new QMap<int, Station>();
    edges_ = new QMap<int, Edge>();
    loadNetFromFile(stations_file_name, edges_file_name);
}

Net::~Net() {
    delete stations_;
    delete edges_;
}

// load stations and edges from file
bool Net::loadNetFromFile(const QString& stations_file_name, const QString& edges_file_name) {
    if (loadStationsFromFile(stations_file_name)) {
        return false;
    }
    if (loadEdgesFromFile(edges_file_name)) {
        return false;
    }
    return true;
}

// each line of the file should be in the format:
// station_id station_name station_position_x station_position_y
bool Net::loadStationsFromFile(const QString& file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        if (fields.size() != 4) {
            return false;
        }
        int station_id = fields[0].toInt();
        QString station_name = fields[1];
        QPointF station_position = QPointF(fields[2].toDouble(), fields[3].toDouble());
        Station station(station_id, station_name, station_position);
        addStation(station);
    }
    return true;
}

// each line of the file should be in the format:
// edge_id edge_line_id edge_station_id edge_next_station_id edge_weight_time edge_weight_distance
bool Net::loadEdgesFromFile(const QString& file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        if (fields.size() != 6) {
            return false;
        }
        int edge_id = fields[0].toInt();
        int edge_line_id = fields[1].toInt();
        int edge_station_id = fields[2].toInt();
        int edge_next_station_id = fields[3].toInt();
        int edge_weight_time = fields[4].toInt();
        int edge_weight_distance = fields[5].toInt();
        Edge edge(edge_id, edge_line_id, edge_station_id,
                  edge_next_station_id, edge_weight_time,
                  edge_weight_distance);
        addEdge(edge);
    }
    return true;
}

void Net::addStation(const Station& station) {
    stations_->insert(station.getId(), station);
}

void Net::addEdge(const Edge& edge) {
    edges_->insert(edge.getId(), edge);
}

QMap<int, Station> *Net::getStations() const {
    return stations_;
}

QMap<int, Edge> *Net::getEdges() const {
    return edges_;
}

Station Net::getStationById(int id) const {
    return stations_->value(id);
}

Edge Net::getEdgeById(int id) const {
    return edges_->value(id);
}


