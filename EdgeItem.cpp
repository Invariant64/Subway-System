//
// Created by Noah on 2023/11/15.
//

#include "EdgeItem.h"


EdgeItem::EdgeItem(Edge *edge, QGraphicsItem *parent) : QGraphicsLineItem(parent) {
    edge_ = edge;
}

Edge *EdgeItem::getEdge() const {
    return edge_;
}