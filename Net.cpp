//
// Created by Noah on 2023/9/18.
//

#include "Net.h"

#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QDebug>

using std::priority_queue;
using std::pair;

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
double Net::getShortestPath(int start_station_id, int end_station_id, QList<Edge*>& path, int weight_mode) {
    QList<Line*> start_lines, end_lines;
    getLinesOfStation(start_station_id, start_lines);
    getLinesOfStation(end_station_id, end_lines);
    double ans = 10000000;

    for (auto & start_line : start_lines) {
        for (auto & end_line : end_lines) {
            int start_adj = station_line_to_adj_->value(std::make_pair(start_station_id, start_line->getId()));
            int end_adj = station_line_to_adj_->value(std::make_pair(end_station_id, end_line->getId()));

            // initialize distance and path
            auto* distance = new double[station_num_ * 2];
            auto* pre_adj = new int[station_num_ * 2];
            auto** pre_node = new ArcNode*[station_num_ * 2];
            for (int i = 0; i < station_num_ * 2; i++) {
                distance[i] = 10000000;
                pre_adj[i] = -1;
                pre_node[i] = nullptr;
            }

            priority_queue< pair<double, int> > q;
            distance[start_adj] = 0.0;
            q.emplace(0.0, start_adj);

            // Dijkstra algorithm
            while (!q.empty()) {
                int k = q.top().second;
                q.pop();

                for (ArcNode *arc_node = adj_list_[k].next; arc_node != nullptr; arc_node = arc_node->next) {
                    double weight = distance[k] + getEdgeWeight(arc_node, weight_mode);
                    if (weight < distance[arc_node->adj_vex]) {
                        distance[arc_node->adj_vex] = weight;
                        pre_adj[arc_node->adj_vex] = k;
                        pre_node[arc_node->adj_vex] = arc_node;
                        q.emplace(-weight, arc_node->adj_vex);
                    }
                }
            }

            if (distance[end_adj] < ans) {
                ans = distance[end_adj];
                path.clear();
                while (end_adj != start_adj) {
                    if (pre_node[end_adj]->edge != nullptr) {
                        path.append(pre_node[end_adj]->edge);
                    }
                    end_adj = pre_adj[end_adj];
                }
            }

            delete[] distance;
            delete[] pre_adj;
            delete[] pre_node;
        }
    }

    // reverse path
    for (int i = 0; i < path.size() / 2; i++) {
        Edge *temp = path[i];
        path[i] = path[path.size() - i - 1];
        path[path.size() - i - 1] = temp;
    }

    return ans;
}

double Net::getShortestPath(const QString& start_station_name, const QString& end_station_name, QList<Edge*>& path, int weight_mode) {
    return getShortestPath(station_name_to_id_->value(start_station_name),
                           station_name_to_id_->value(end_station_name), path, weight_mode);
}

void Net::buildAdjList() {
    station_line_to_adj_ = new QMap< pair<int, int>, int >;

    int sum = 0;
    auto *cnt = new QList<int>[station_num_];
    for (auto line : *lines_) {
        for (auto station_id : *line->getStationsId()) {
            cnt[station_id].append(line->getId());
            sum++;
        }
    }
    adj_list_ = new ArcNode[sum];
    int tot = 0;
    for (int i = 0; i < station_num_; i++) {
        for (int j = 0; j < cnt[i].size(); j++) {
            adj_list_[tot].adj_vex = tot;
            adj_list_[tot].edge = nullptr;
            adj_list_[tot].next = nullptr;
            station_line_to_adj_->insert(std::make_pair(i, cnt[i][j]), tot);
            tot++;
        }
    }

    for (auto edge : *edges_) {
        auto *arc_node = new ArcNode;
        int from = edge->getStationId();
        int to = edge->getNextStationId();
        int line_id = edge->getLineId();
        int from_adj = station_line_to_adj_->value(std::make_pair(from, line_id));
        int to_adj = station_line_to_adj_->value(std::make_pair(to, line_id));
        arc_node->adj_vex = to_adj;
        arc_node->edge = edge;
        arc_node->next = adj_list_[from_adj].next;
        adj_list_[from_adj].next = arc_node;
    }
    // 插入换乘边
    for (int i = 0; i < station_num_; i++) {
        for (int j = 0; j < cnt[i].size(); j++) {
            int from_adj = station_line_to_adj_->value(std::make_pair(i, cnt[i][j]));
            for (int k = 0; k < cnt[i].size(); k++) {
                if (k == j) {
                    continue;
                }
                int to_adj = station_line_to_adj_->value(std::make_pair(i, cnt[i][k]));
                auto *arc_node = new ArcNode;
                arc_node->adj_vex = to_adj;
                arc_node->edge = nullptr;
                arc_node->next = adj_list_[from_adj].next;
                adj_list_[from_adj].next = arc_node;
            }
        }
    }
    delete[] cnt;
}

double Net::getEdgeWeight(ArcNode *arc_node, int weight_mode) {
    if (arc_node == nullptr) {
        return -1;
    }
    switch (weight_mode) {
        case 0:
            if (arc_node->edge == nullptr) {
                return TRANSFER_TIME;
            }
            return 1.0 * arc_node->edge->getWeightDistance() / TRAIN_SPEED;
        case 1:
            if (arc_node->edge == nullptr) {
                return 0;
            }
            return arc_node->edge->getWeightDistance();
        case 2:
            if (arc_node->edge == nullptr) {
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
    for (int i = 1; i < path.size(); i++) {
        if (i != 0) {
            int line_id = path[i]->getLineId();
            int last_line_id = path[i - 1]->getLineId();
            if (last_line_id != line_id && last_line_id != -1) {
                result += + " -> " + getStationById(path[i - 1]->getNextStationId())->getName().toStdString()
                          + "\n(从 " + getLineById(last_line_id)->getName().toStdString()
                          + " 转乘至 " + getLineById(line_id)->getName().toStdString() + ")\n"
                          + getStationById(path[i - 1]->getNextStationId())->getName().toStdString();
                continue;
            }
        }
        result += " -> " + getStationById(path[i]->getStationId())->getName().toStdString() + " ";
    }
    result += " -> " + getStationById(path.last()->getNextStationId())->getName().toStdString() + "\n";

    return result;
}

QString Net::getShortestPathString(const QString &start_station_name, const QString &end_station_name, int weight_mode) {
    QList<Edge*> path;
    double sum = getShortestPath(start_station_name, end_station_name, path, weight_mode);
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
        default:
            break;
    }
    result += getPathString(path);
    return result;
}

void Net::statPath(const QList<Edge *> &path, int &station_num, int &transfer_num, double &time, double &distance) const {
    station_num = path.size() + 1;
    transfer_num = 0;
    time = 0;
    distance = 0;
    for (int i = 0; i < path.size(); i++) {
        if (i != 0 && path[i]->getLineId() != path[i - 1]->getLineId()) {
            transfer_num++;
        }
        time += 1.0 * path[i]->getWeightDistance() / TRAIN_SPEED;
        distance += path[i]->getWeightDistance();
    }
    time += transfer_num * TRANSFER_TIME;
}

QString Net::getEndStationNameByEdge(Edge *edge) const {
    Line *line = getLineById(edge->getLineId());
    QList<int> *stations_id = line->getStationsId();
    int from = stations_id->indexOf(edge->getStationId());
    int to = stations_id->indexOf(edge->getNextStationId());
    if (from < to) {
        return getStationById(stations_id->last())->getName();
    }
    else {
        return getStationById(stations_id->first())->getName();
    }
}

int Net::getSinglePathTimeMinutes(const QList<Edge *> &path) const {
    double distance = 0;
    for (auto edge : path) {
        distance += edge->getWeightDistance();
    }
    return distance / TRAIN_SPEED / 60;
}

void Net::getLinesOfStation(int station_id, QList<Line *> &lines) const {
    lines.clear();
    for (auto line : *lines_) {
        if (line->getStationsId()->contains(station_id)) {
            lines.append(line);
        }
    }
}

double Net::getPriceByDistance(double distance) const {
    if (distance <= 0) return -1;
    if (distance <= 6000) return 3;
    if (distance <= 12000) return 4;
    if (distance <= 22000) return 5;
    if (distance <= 32000) return 6;
    if (distance <= 52000) return 7;
    if (distance <= 72000) return 8;
    return 9;
}




