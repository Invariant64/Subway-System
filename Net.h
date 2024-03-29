//
// Created by Noah on 2023/9/18.
//

#ifndef SUBWAY_SYSTEM_NET_H
#define SUBWAY_SYSTEM_NET_H


#include <QString>
#include <QList>
#include <queue>
#include "Station.h"
#include "Edge.h"
#include "Line.h"
#include "Sight.h"

class Net {
private:
    int station_num_;
    int edge_num_;

    QMap<int, Station*> *stations_;
    QMap<int, Edge*> *edges_;
    QMap<int, Line*> *lines_;
    QMap<QString, Sight*> *sights_;

    QMap<QString, int> *station_name_to_id_;

    struct ArcNode {
        int adj_vex;
        Edge *edge;
        ArcNode *next;
    };

    ArcNode *adj_list_;
    QMap< std::pair<int, int>, int > *station_line_to_adj_;

    static double getEdgeWeight(ArcNode *arc_node, int weight_mode);

public:
    Net();
    ~Net();
    explicit Net(const QString& stations_file_name, const QString& edges_file_name, const QString& lines_file_name, const QString& sights_file_name);

    bool loadNetFromFile(const QString& stations_file_name, const QString& edges_file_name, const QString& lines_file_name, const QString& sights_file_name);
    bool loadStationsFromFile(const QString& file_name);
    bool loadEdgesFromFile(const QString& file_name);
    bool loadLinesFromFile(const QString& file_name);
    bool loadSightsFromFile(const QString& file_name);

    void addStation(Station *station);
    void addEdge(Edge *edge);

    QMap<int, Station*> *getStations() const;
    QMap<int, Edge*> *getEdges() const;
    QMap<int, Line*> *getLines() const;
    QMap<QString, Sight*> *getSights() const;

    Station* getStationById(int id) const;
    Edge* getEdgeById(int id) const;

    double getShortestPath(int start_station_id, int end_station_id, QList<Edge*>& path, int weight_mode = 0);
    double getShortestPath(const QString& start_station_name, const QString& end_station_name, QList<Edge*>& path, int weight_mode = 0);

    void buildAdjList();

    int getStationIdByName(const QString& station_name) const;

    Edge* getEdgeByStationId(int station_id, int next_station_id) const;

    Line* getLineById(int line_id) const;

    Line* getFirstLineByStationName(const QString& station_name) const;

    QString getPathString(const QList<Edge*>& path) const;

    QString getShortestPathString(const QString& start_station_name, const QString& end_station_name, int weight_mode = 0);

    void statPath(const QList<Edge*>& path, int& station_num, int& transfer_num, double& time, double& distance) const;

    QString getEndStationNameByEdge(Edge* edge) const;

    int getSinglePathTimeMinutes(const QList<Edge*>& path) const;

    void getLinesOfStation(int station_id, QList<Line*>& lines) const;

    static double getPriceByDistance(double distance);

    Station* getStationBySightName(const QString& sight) const;

    constexpr static const double TRAIN_SPEED = 35.0 * 1000 / 60 / 60; // 35 km/h
    constexpr static const double TRANSFER_TIME = 3 * 60; // 3 minutes

};


#endif //SUBWAY_SYSTEM_NET_H
