//
// Created by Noah on 2023/9/18.
//

#ifndef SUBWAY_SYSTEM_NET_H
#define SUBWAY_SYSTEM_NET_H


#include <QString>
#include <QList>
#include "Station.h"
#include "Edge.h"

class Net {
private:
    int station_num_;
    int edge_num_;

    QMap<int, Station> *stations_;
    QMap<int, Edge> *edges_;

    struct EdgeMatrix {
        int** matrix;
        int station_num;
        int edge_num;
    } edges_matrix_;

    int getEdgeWeight(int start_station_id, int end_station_id, int weight_mode);

public:
    Net();
    ~Net();
    explicit Net(const QString& stations_file_name, const QString& edges_file_name);

    bool loadNetFromFile(const QString& stations_file_name, const QString& edges_file_name);
    bool loadStationsFromFile(const QString& file_name);
    bool loadEdgesFromFile(const QString& file_name);

    void addStation(const Station& station);
    void addEdge(const Edge& edge);

    QMap<int, Station> *getStations() const;
    QMap<int, Edge> *getEdges() const;

    Station getStationById(int id) const;
    Edge getEdgeById(int id) const;

    int getShortestPath(int start_station_id, int end_station_id, QList<int>& path, int weight_mode = 0);

    void flushEdgesMatrix();

};


#endif //SUBWAY_SYSTEM_NET_H