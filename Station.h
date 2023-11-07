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
    QPoint position_;

public:
    Station() = default;
    ~Station() = default;
    Station(int id, QString name, QPoint position);

    int getId() const;
    QString getName() const;
    QPoint getPosition() const;
};


#endif //SUBWAY_SYSTEM_STATION_H
