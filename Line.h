//
// Created by Noah on 2023/10/10.
//

#ifndef SUBWAY_SYSTEM_LINE_H
#define SUBWAY_SYSTEM_LINE_H


#include <QString>
#include <QList>
#include <QColor>

class Line {
private:
    int id_;
    QString name_;
    QColor color_;
    QList<int> *stations_id_;

public:
    Line();
    ~Line();
    Line(int id, QString name, QColor color);

    int getId() const;
    QString getName() const;
    QColor getColor() const;

    QList<int> *getStationsId() const;

    void addStationId(int station_id);
};


#endif //SUBWAY_SYSTEM_LINE_H
