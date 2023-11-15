//
// Created by Noah on 2023/11/15.
//

#ifndef SUBWAY_SYSTEM_EDGEITEM_H
#define SUBWAY_SYSTEM_EDGEITEM_H


#include <QGraphicsLineItem>
#include "Edge.h"

class EdgeItem : public QGraphicsLineItem {
private:
    Edge *edge_;
public:
    EdgeItem(Edge *edge, QGraphicsItem *parent = nullptr);

    Edge *getEdge() const;

};


#endif //SUBWAY_SYSTEM_EDGEITEM_H
