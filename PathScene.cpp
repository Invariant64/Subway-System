//
// Created by Noah on 2023/11/17.
//

#include <QPainter>
#include <QGraphicsTextItem>
#include <QDebug>
#include "PathScene.h"


void PathScene::setNet(Net *net) {
    this->net_ = net;
}

void PathScene::drawPath(QList<Edge *> &path) {
    this->clear();

    if (path.empty()) {
        return;
    }

    // 将path以不同的线路分开
    QList< QList<Edge*> > path_list;
    QList<Edge*> tmp;
    tmp.append(path[0]);
    for (int i = 1; i < path.size(); ++i) {
        if (path[i]->getLineId() == path[i - 1]->getLineId()) {
            tmp.append(path[i]);
        }
        else {
            path_list.append(tmp);
            tmp.clear();
            tmp.append(path[i]);
        }
    }
    path_list.append(tmp);

    // 绘制path
    int start_y = 10;
    for (int i = 0; i < path_list.size(); ++i) {
        start_y = drawOneLinePath(path_list[i], start_y);
        start_y += LINE_OFFSET;
        if (i != path_list.size() - 1) {
            start_y = drawTransfer(start_y);
            start_y += LINE_OFFSET;
        }
    }
}

int PathScene::drawOneLinePath(QList<Edge *> &path, int start_y) {
    start_y += KEY_RADIUS;

    QColor color = net_->getLineById(path[0]->getLineId())->getColor();

    int end_y = start_y + KEY_RADIUS + LINE_OFFSET * path.size() + 2 * MID_RADIUS * (path.size() - 1);
    QGraphicsLineItem *line = addLine(LEFT_MID_X, start_y, LEFT_MID_X, end_y, QPen(color));
    QPen pen = line->pen();
    pen.setWidth(LINE_WIDTH);
    line->setPen(pen);

    QGraphicsEllipseItem *start_ellipse = addEllipse(LEFT_MID_X - KEY_RADIUS, start_y - KEY_RADIUS, KEY_RADIUS * 2, KEY_RADIUS * 2, QPen(color), QBrush(Qt::white));
    pen = start_ellipse->pen();
    pen.setWidth(KEY_BORDER_WIDTH);
    start_ellipse->setPen(pen);
    QGraphicsTextItem *start_station_name = addText(net_->getStationById(path[0]->getStationId())->getName());
    start_station_name->setPos(LEFT_MID_X + KEY_RADIUS + TEXT_OFFSET, start_y - start_station_name->boundingRect().height() / 2);

    for (int i = 1; i < path.size(); i++) {
        int y = start_y + KEY_RADIUS + LINE_OFFSET * i + 2 * MID_RADIUS * (i - 1);
        addEllipse(LEFT_MID_X - MID_RADIUS, y - MID_RADIUS, MID_RADIUS * 2, MID_RADIUS * 2, QPen(Qt::white), QBrush(Qt::white));
        QGraphicsTextItem *station_name = addText(net_->getStationById(path[i]->getStationId())->getName());
        station_name->setPos(LEFT_MID_X + MID_RADIUS + TEXT_OFFSET, y - station_name->boundingRect().height() / 2);
    }

    QGraphicsEllipseItem *end_ellipse = addEllipse(LEFT_MID_X - KEY_RADIUS, end_y - KEY_RADIUS,KEY_RADIUS * 2, KEY_RADIUS * 2, QPen(color), QBrush(Qt::white));
    pen = end_ellipse->pen();
    pen.setWidth(KEY_BORDER_WIDTH);
    end_ellipse->setPen(pen);
    QGraphicsTextItem *end_station_name = addText(net_->getStationById(path[path.size() - 1]->getNextStationId())->getName());
    end_station_name->setPos(LEFT_MID_X + KEY_RADIUS + TEXT_OFFSET, end_y - end_station_name->boundingRect().height() / 2);

    return end_y + KEY_RADIUS;
}

int PathScene::drawTransfer(int start_y) {
    start_y += TRS_RADIUS;

    QColor color = Qt::gray;

    for (int i = 0; i < TRS_NUM; i++) {
        int y = start_y + i * (TRS_RADIUS * 2 + TRS_LINE_OFFSET);
        addEllipse(LEFT_MID_X - TRS_RADIUS, y - TRS_RADIUS, TRS_RADIUS * 2, TRS_RADIUS * 2, QPen(color), QBrush(color));
    }

    return start_y + (TRS_NUM - 1) * (TRS_RADIUS * 2 + TRS_LINE_OFFSET) + TRS_RADIUS;
}
