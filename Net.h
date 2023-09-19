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
    QMap<int, Station> *stations_;
    QMap<int, Edge> *edges_;

public:
    Net();
    explicit Net(const QString& stations_file_name, const QString& edges_file_name);
    ~Net();

    bool loadNetFromFile(const QString& stations_file_name, const QString& edges_file_name);
    bool loadStationsFromFile(const QString& file_name);
    bool loadEdgesFromFile(const QString& file_name);

    void addStation(const Station& station);
    void addEdge(const Edge& edge);

    QMap<int, Station> *getStations() const;
    QMap<int, Edge> *getEdges() const;

    Station getStationById(int id) const;
    Edge getEdgeById(int id) const;
};


#endif //SUBWAY_SYSTEM_NET_H
