//
// Created by Noah on 2023/9/18.
//

#ifndef SUBWAY_SYSTEM_NET_H
#define SUBWAY_SYSTEM_NET_H


#include <QString>
#include <QList>
#include "Station.h"
#include "Edge.h"
#include "Line.h"

class Net {
private:
    int station_num_;
    int edge_num_;

    QMap<int, Station> *stations_;
    QMap<int, Edge*> *edges_;
    QMap<int, Line*> *lines_;

    QMap<QString, int> *station_name_to_id_;

    struct EdgeMatrix {
        int** matrix;
        int station_num;
        int edge_num;
    } edges_matrix_;

    int getEdgeWeight(int start_station_id, int end_station_id, int weight_mode);

public:
    Net();
    ~Net();
    explicit Net(const QString& stations_file_name, const QString& edges_file_name, const QString& lines_file_name);

    bool loadNetFromFile(const QString& stations_file_name, const QString& edges_file_name, const QString& lines_file_name);
    bool loadStationsFromFile(const QString& file_name);
    bool loadEdgesFromFile(const QString& file_name);
    bool loadLinesFromFile(const QString& file_name);

    void addStation(const Station& station);
    void addEdge(Edge *edge);

    QMap<int, Station> *getStations() const;
    QMap<int, Edge*> *getEdges() const;
    QMap<int, Line*> *getLines() const;

    Station getStationById(int id) const;
    Edge* getEdgeById(int id) const;

    int getShortestPath(int start_station_id, int end_station_id, QList<int>& path, int weight_mode = 0);
    int getShortestPath(const QString& start_station_name, const QString& end_station_name, QList<int>& path, int weight_mode = 0);

    void flushEdgesMatrix();

    int getStationIdByName(const QString& station_name) const;

    Edge getEdgeByStationId(int station_id, int next_station_id) const;

    Line* getLineById(int line_id) const;

    Line* getFirstLineByStationName(const QString& station_name) const;

};


#endif //SUBWAY_SYSTEM_NET_H
