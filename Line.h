//
// Created by Noah on 2023/10/10.
//

#ifndef SUBWAY_SYSTEM_LINE_H
#define SUBWAY_SYSTEM_LINE_H


#include <QString>
#include <QList>

class Line {
private:
    int id_;
    QString name_;
    QList<int> *stations_id_;

public:
    Line();
    ~Line();
    Line(int id, QString name);

    int getId() const;
    QString getName() const;

    QList<int> *getStationsId() const;

    void addStationId(int station_id);
};


#endif //SUBWAY_SYSTEM_LINE_H
