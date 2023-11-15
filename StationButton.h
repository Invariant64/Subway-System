//
// Created by Noah on 2023/11/3.
//

#ifndef SUBWAY_SYSTEM_STATIONBUTTON_H
#define SUBWAY_SYSTEM_STATIONBUTTON_H


#include <QPushButton>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include "Station.h"
#include "SelectionWidget.h"

class StationButton : public QGraphicsEllipseItem {
private:

    Station *station_;

    QPoint position_;

    SelectionWidget *selection_widget_;

    const int RADIUS = 50;

    void initUI();

public:
    StationButton() = default;
    ~StationButton() = default;
    explicit StationButton(Station *station, SelectionWidget *selection_widget);

    int getId() const;
    QString getName() const;
    QPoint getPosition() const;
    Station *getStation() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};


#endif //SUBWAY_SYSTEM_STATIONBUTTON_H
