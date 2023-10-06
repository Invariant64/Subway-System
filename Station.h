//
// Created by Noah on 2023/9/18.
//

#ifndef SUBWAY_SYSTEM_STATION_H
#define SUBWAY_SYSTEM_STATION_H


#include <QString>
#include <QPointF>

class Station {
private:
    int id_;
    QString name_;
    QPointF position_;

public:
    Station() = default;
    Station(int id, QString name, QPointF position);
    ~Station() = default;

    int getId() const;
    QString getName() const;
    QPointF getPosition() const;
};


#endif //SUBWAY_SYSTEM_STATION_H