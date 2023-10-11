//
// Created by Noah on 2023/9/18.
//

#include "Net.h"

#include <QFile>
#include <QTextStream>
#include <QMap>


Net::Net() {
    station_num_ = 0;
    edge_num_ = 0;
    stations_ = new QMap<int, Station>();
    edges_ = new QMap<int, Edge>();
    lines_ = new QMap<int, Line>();
    station_name_to_id_ = new QMap<QString, int>();

    edges_matrix_.station_num = 0;
}

Net::Net(const QString& stations_file_name, const QString& edges_file_name, const QString& lines_file_name) {
    station_num_ = 0;
    edge_num_ = 0;
    stations_ = new QMap<int, Station>();
    edges_ = new QMap<int, Edge>();
    lines_ = new QMap<int, Line>();
    station_name_to_id_ = new QMap<QString, int>();

    edges_matrix_.station_num = 0;

    loadNetFromFile(stations_file_name, edges_file_name, lines_file_name);
}

Net::~Net() {
    delete stations_;
    delete edges_;
    delete lines_;
    delete station_name_to_id_;

    for (int i = 0; i < edges_matrix_.station_num; i++) {
        delete[] edges_matrix_.matrix[i];
    }
    delete[] edges_matrix_.matrix;
}

// load stations and edges from file
bool Net::loadNetFromFile(const QString& stations_file_name, const QString& edges_file_name, const QString& lines_file_name) {
    if (!loadStationsFromFile(stations_file_name)) {
        return false;
    }
    if (!loadEdgesFromFile(edges_file_name)) {
        return false;
    }
    if (!loadLinesFromFile(lines_file_name)) {
        return false;
    }
    flushEdgesMatrix();
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
        if (fields.size() != 2) {
            return false;
        }
        int station_id = fields[0].toInt();
        QString station_name = fields[1];
        Station station(station_id, station_name);
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

// each line of the file should be in the format:
// line_id line_name
bool Net::loadLinesFromFile(const QString& file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        if (fields.size() != 2) {
            return false;
        }
        int line_id = fields[0].toInt();
        QString line_name = fields[1];
        Line l(line_id, line_name);
        lines_->insert(line_id, l);
    }
    return true;
}

void Net::addStation(const Station& station) {
    station_num_++;
    stations_->insert(station.getId(), station);
    station_name_to_id_->insert(station.getName(), station.getId());
}

void Net::addEdge(const Edge& edge) {
    edge_num_++;
    edges_->insert(edge.getId(), edge);
}

QMap<int, Station> *Net::getStations() const {
    return stations_;
}

QMap<int, Edge> *Net::getEdges() const {
    return edges_;
}

QMap<int, Line> *Net::getLines() const {
    return lines_;
}

Station Net::getStationById(int id) const {
    return stations_->value(id);
}

Edge Net::getEdgeById(int id) const {
    return edges_->value(id);
}

// use Dijkstra algorithm to get the shortest path
// weight_mode = 0: time, weight_mode = 1: distance
int Net::getShortestPath(int start_station_id, int end_station_id, QList<int>& path, int weight_mode) {
    if (edges_matrix_.station_num != station_num_ || edges_matrix_.edge_num != edge_num_) {
        flushEdgesMatrix();
    }

    // initialize distance and path
    int* distance = new int[station_num_];
    int* visited = new int[station_num_];
    int* prev = new int[station_num_];
    for (int i = 0; i < station_num_; i++) {
        distance[i] = getEdgeWeight(start_station_id, i, weight_mode);
        visited[i] = 0;
        if (distance[i] == -1) {
            prev[i] = -1;
        } else {
            prev[i] = start_station_id;
        }
    }
    distance[start_station_id] = 0;
    visited[start_station_id] = 1;

    // Dijkstra algorithm
    for (int i = 1; i < station_num_; i++) {
        int min = INT_MAX;
        int k = -1;
        for (int j = 0; j < station_num_; j++) {
            if (!visited[j] && distance[j] != -1 && distance[j] < min) {
                min = distance[j];
                k = j;
            }
        }
        if (k == -1) {
            break;
        }
        visited[k] = 1;
        for (int j = 0; j < station_num_; j++) {
            if (!visited[j] && edges_matrix_.matrix[k][j] != -1 && (distance[k] + getEdgeWeight(k, j, weight_mode) < distance[j] || distance[j] == -1)){
                distance[j] = distance[k] + getEdgeWeight(k, j, weight_mode);
                prev[j] = k;
            }
        }
    }

    // get path
    int current_station_id = end_station_id;
    while (current_station_id != start_station_id) {
        path.push_front(current_station_id);
        current_station_id = prev[current_station_id];
    }
    path.push_front(start_station_id);

    int ans = distance[end_station_id];

    delete[] distance;
    delete[] visited;
    delete[] prev;

    return ans;
}

int Net::getShortestPath(const QString& start_station_name, const QString& end_station_name, QList<int>& path, int weight_mode) {
    return getShortestPath(station_name_to_id_->value(start_station_name),
                           station_name_to_id_->value(end_station_name), path, weight_mode);
}

// delete the old edges matrix and create a new one
void Net::flushEdgesMatrix() {
    if (edges_matrix_.station_num != 0) {
        for (int i = 0; i < edges_matrix_.station_num; i++) {
            delete[] edges_matrix_.matrix[i];
        }
        delete[] edges_matrix_.matrix;
    }

    edges_matrix_.station_num = station_num_;
    edges_matrix_.matrix = new int*[station_num_];
    for (int i = 0; i < station_num_; i++) {
        edges_matrix_.matrix[i] = new int[station_num_];
        for (int j = 0; j < station_num_; j++) {
            edges_matrix_.matrix[i][j] = -1;
        }
    }

    edges_matrix_.edge_num = edge_num_;
    for (const auto& edge : *edges_) {
        edges_matrix_.matrix[edge.getStationId()][edge.getNextStationId()] = edge.getId();
    }
}

int Net::getEdgeWeight(int start_station_id, int end_station_id, int weight_mode) {
    int edge_id = edges_matrix_.matrix[start_station_id][end_station_id];
    if (edge_id == -1) {
        return -1;
    }
    return weight_mode == 0 ? edges_->value(edge_id).getWeightTime() :
           edges_->value(edge_id).getWeightDistance();
}

int Net::getStationIdByName(const QString& station_name) const {
    return station_name_to_id_->value(station_name);
}

Edge Net::getEdgeByStationId(int station_id, int next_station_id) const {
    return edges_->value(edges_matrix_.matrix[station_id][next_station_id]);
}

Line Net::getLineById(int line_id) const {
    return lines_->value(line_id);
}




