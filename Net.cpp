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
    stations_ = new QMap<int, Station*>;
    edges_ = new QMap<int, Edge*>;
    lines_ = new QMap<int, Line*>;
    station_name_to_id_ = new QMap<QString, int>;
}

Net::Net(const QString& stations_file_name, const QString& edges_file_name, const QString& lines_file_name) {
    station_num_ = 0;
    edge_num_ = 0;
    stations_ = new QMap<int, Station*>;
    edges_ = new QMap<int, Edge*>;
    lines_ = new QMap<int, Line*>;
    station_name_to_id_ = new QMap<QString, int>;

    loadNetFromFile(stations_file_name, edges_file_name, lines_file_name);
}

Net::~Net() {
    delete stations_;
    delete edges_;
    delete lines_;
    delete station_name_to_id_;
    delete[] adj_list_;
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
    buildAdjList();
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
        if (fields.size() != 4 && fields.size() != 2) {
            return false;
        }
        int station_id = fields[0].toInt();
        QString station_name = fields[1];
        int station_position_x = fields.size() == 4 ? fields[2].toInt() : random() % 4500;
        int station_position_y = fields.size() == 4 ? fields[3].toInt() : random() % 3000;
        QPoint station_position(station_position_x, station_position_y);
        Station *station = new Station(station_id, station_name, station_position);
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
        Edge *edge = new Edge(edge_id, edge_line_id, edge_station_id,
                  edge_next_station_id, edge_weight_time,
                  edge_weight_distance);
        addEdge(edge);
    }
    return true;
}

// each line of the file should be in the format:
// line_id line_name station_num
// station_id station_id station_id ...
bool Net::loadLinesFromFile(const QString& file_name) {
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
        int line_id = fields[0].toInt();
        QString line_name = fields[1];
        int station_num = fields[2].toInt();
        QColor line_color = QColor(fields[3]);
        line = in.readLine();
        fields = line.split(" ");
        Line *line1 = new Line(line_id, line_name, line_color);
        for (int i = 0; i < station_num; i++) {
            line1->addStationId(fields[i].toInt());
        }
        lines_->insert(line_id, line1);
    }
    return true;
}

void Net::addStation(Station *station) {
    station_num_++;
    stations_->insert(station->getId(), station);
    station_name_to_id_->insert(station->getName(), station->getId());
}

void Net::addEdge(Edge* edge) {
    edge_num_++;
    edges_->insert(edge->getId(), edge);
}

QMap<int, Station*> *Net::getStations() const {
    return stations_;
}

QMap<int, Edge*> *Net::getEdges() const {
    return edges_;
}

QMap<int, Line*> *Net::getLines() const {
    return lines_;
}

Station* Net::getStationById(int id) const {
    return stations_->value(id);
}

Edge* Net::getEdgeById(int id) const {
    return edges_->value(id);
}

// use Dijkstra algorithm to get the shortest path
// weight_mode = 0: time, weight_mode = 1: distance
int Net::getShortestPath(int start_station_id, int end_station_id, QList<Edge*>& path, int weight_mode) {
    // initialize distance and path
    int* distance = new int[station_num_];
    int* visited = new int[station_num_];
    int* prev = new int[station_num_];
    ArcNode** pre_node = new ArcNode*[station_num_];
    for (int i = 0; i < station_num_; i++) {
        distance[i] = -1;
        visited[i] = 0;
        prev[i] = -1;
        pre_node[i] = nullptr;
    }
    for (ArcNode *arc_node = adj_list_[start_station_id].next; arc_node != nullptr; arc_node = arc_node->next) {
        distance[arc_node->adj_vex] = getEdgeWeight(nullptr, arc_node, weight_mode);
        prev[arc_node->adj_vex] = start_station_id;
        pre_node[arc_node->adj_vex] = arc_node;
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

        for (ArcNode *arc_node = adj_list_[k].next; arc_node != nullptr; arc_node = arc_node->next) {
            if (!visited[arc_node->adj_vex] && (distance[arc_node->adj_vex] == -1 ||
                    distance[k] + getEdgeWeight(pre_node[k], arc_node, weight_mode) < distance[arc_node->adj_vex])) {
                distance[arc_node->adj_vex] = distance[k] + getEdgeWeight(pre_node[k], arc_node, weight_mode);
                prev[arc_node->adj_vex] = k;
                pre_node[arc_node->adj_vex] = arc_node;
            }
        }
    }

    // get path
    int current_station_id = end_station_id;
    while (current_station_id != start_station_id) {
        path.append(pre_node[current_station_id]->edge);
        current_station_id = prev[current_station_id];
    }

    // reverse path
    for (int i = 0; i < path.size() / 2; i++) {
        Edge *temp = path[i];
        path[i] = path[path.size() - i - 1];
        path[path.size() - i - 1] = temp;
    }

    int ans = distance[end_station_id];

    delete[] distance;
    delete[] visited;
    delete[] prev;
    delete[] pre_node;

    return ans;
}

int Net::getShortestPath(const QString& start_station_name, const QString& end_station_name, QList<Edge*>& path, int weight_mode) {
    return getShortestPath(station_name_to_id_->value(start_station_name),
                           station_name_to_id_->value(end_station_name), path, weight_mode);
}

void Net::buildAdjList() {
    adj_list_ = new ArcNode[station_num_];
    for (int i = 0; i < station_num_; i++) {
        adj_list_[i].adj_vex = i;
        adj_list_[i].edge = nullptr;
        adj_list_[i].next = nullptr;
    }
    for (auto edge : *edges_) {
        ArcNode *arc_node = new ArcNode();
        arc_node->adj_vex = edge->getStationId();
        arc_node->edge = edge;
        arc_node->next = adj_list_[edge->getNextStationId()].next;
        adj_list_[edge->getNextStationId()].next = arc_node;
    }
}

int Net::getEdgeWeight(ArcNode *pre_node, ArcNode *arc_node, int weight_mode) {
    if (arc_node == nullptr) {
        return -1;
    }
    switch (weight_mode) {
        case 0:
            if (pre_node == nullptr) {
                return arc_node->edge->getWeightDistance() / TRAIN_SPEED;
            }
            if (pre_node->edge->getLineId() != arc_node->edge->getLineId()) {
                return arc_node->edge->getWeightDistance() / TRAIN_SPEED + TRANSFER_TIME;
            }
            return arc_node->edge->getWeightDistance() / TRAIN_SPEED;
        case 1:
            return arc_node->edge->getWeightDistance();
        case 2:
            if (pre_node == nullptr) {
                return 0;
            }
            if (pre_node->edge->getLineId() != arc_node->edge->getLineId()) {
                return 1;
            }
            return 0;
        default:
            return -1;
    }
}

int Net::getStationIdByName(const QString& station_name) const {
    return station_name_to_id_->value(station_name);
}

Edge* Net::getEdgeByStationId(int station_id, int next_station_id) const {
    ArcNode *arc_node = adj_list_[station_id].next;
    while (arc_node != nullptr) {
        if (arc_node->adj_vex == next_station_id) {
            return arc_node->edge;
        }
        arc_node = arc_node->next;
    }
    return nullptr;
}

Line* Net::getLineById(int line_id) const {
    return lines_->value(line_id);
}

Line *Net::getFirstLineByStationName(const QString &station_name) const {
    int station_id = station_name_to_id_->value(station_name);
    for (auto line : *lines_) {
        if (line->getStationsId()->contains(station_id)) {
            return line;
        }
    }
    return nullptr;
}

QString Net::getPathString(const QList<Edge *> &path) const {
    QString result = "";

    result += "乘车路线为：\n";
    result += "从 " + getStationById(path[0]->getStationId())->getName().toStdString() +
              " 乘坐 " + getLineById(path[0]->getLineId())->getName().toStdString() +
              " 出发\n" + getStationById(path[0]->getStationId())->getName().toStdString();
    for (int i = 0; i < path.size(); i++) {
        result += " -> " + getStationById(path[i]->getStationId())->getName().toStdString() + " ";
        if (i != 0) {
            int line_id = path[i]->getLineId();
            int last_line_id = path[i - 1]->getLineId();
            if (last_line_id != line_id && last_line_id != -1) {
                result += "\n(从 " + getLineById(last_line_id)->getName().toStdString()
                          + " 转乘至 " + getLineById(line_id)->getName().toStdString() + ") ";
            }
        }
    }
    result += " -> " + getStationById(path[path.size() - 1]->getNextStationId())->getName().toStdString() + " ";

    return result;
}

QString Net::getShortestPathString(const QString &start_station_name, const QString &end_station_name, int weight_mode) {
    QList<Edge*> path;
    int sum = getShortestPath(start_station_name, end_station_name, path, weight_mode);
    if (path.empty()) {
        return "";
    }
    QString result = "";
    switch (weight_mode) {
        case 0:
            result += "最短时间为 " + QString::number(sum) + " 分钟\n";
            break;
        case 1:
            result += "最短距离为 " + QString::number(sum) + " 米\n";
            break;
        case 2:
            result += "最少换乘为 " + QString::number(sum) + " 次\n";
            break;
    }
    result += getPathString(path);
    return result;
}




