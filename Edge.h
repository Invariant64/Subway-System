//
// Created by Noah on 2023/9/18.
//

#ifndef SUBWAY_SYSTEM_EDGE_H
#define SUBWAY_SYSTEM_EDGE_H


class Edge {
private:
    int id_;
    int line_id_;
    int station_id_;
    int next_station_id_;
    int weight_time_;
    int weight_distance_;

public:
    Edge() = default;
    ~Edge() = default;
    Edge(int id, int line_id, int station_id, int next_station_id, int weight_time, int weight_distance);

    int getId() const;
    int getLineId() const;
    int getStationId() const;
    int getNextStationId() const;
    int getWeightTime() const;
    int getWeightDistance() const;
};


#endif //SUBWAY_SYSTEM_EDGE_H
