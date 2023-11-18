//
// Created by Noah on 2023/11/17.
//

#include <QPainter>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
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
    int origin_start_y = start_y;
    start_y += KEY_RADIUS;

    QColor color = net_->getLineById(path[0]->getLineId())->getColor();

    QGraphicsEllipseItem *start_ellipse = addEllipse(LEFT_MID_X - KEY_RADIUS, start_y - KEY_RADIUS, KEY_RADIUS * 2, KEY_RADIUS * 2, QPen(color), QBrush(Qt::white));
    QPen pen = start_ellipse->pen();
    pen.setWidth(KEY_BORDER_WIDTH);
    start_ellipse->setPen(pen);
    QGraphicsTextItem *start_station_name = addText(net_->getStationById(path[0]->getStationId())->getName() + " 上车");
    QFont font = start_station_name->font();
    font.setBold(true);
    font.setPointSize(KEY_TEXT_FONT_SIZE);
    start_station_name->setFont(font);
    start_station_name->setPos(LEFT_MID_X + KEY_RADIUS + TEXT_OFFSET, start_y - start_station_name->boundingRect().height() / 2);
    start_y += KEY_RADIUS + LINE_OFFSET;

    QGraphicsTextItem *line_name = addText(net_->getLineById(path[0]->getLineId())->getName());
    line_name->setPos(LEFT_MID_X + KEY_RADIUS + TEXT_OFFSET + RECT_OUTER_OFFSET, start_y - line_name->boundingRect().height() / 2 + RECT_OUTER_OFFSET);
    line_name->setDefaultTextColor(Qt::white);
    font = line_name->font();
    font.setBold(true);
    line_name->setFont(font);
    QGraphicsRectItem *rect = addRect(LEFT_MID_X + KEY_RADIUS + TEXT_OFFSET,
                                      start_y - line_name->boundingRect().height() / 2,
                                      line_name->boundingRect().width() + 2 * RECT_OUTER_OFFSET,
                                      line_name->boundingRect().height() + 2 * RECT_OUTER_OFFSET,
                                      QPen(color), QBrush(color));
    rect->setZValue(-1);

    QGraphicsTextItem *end_direction = addText(net_->getEndStationNameByEdge(path[0]) + " 方向");
    end_direction->setPos(rect->boundingRect().right() + RECT_OUTER_OFFSET, start_y + RECT_OUTER_OFFSET - end_direction->boundingRect().height() / 2);

    start_y += LINE_OFFSET + rect->boundingRect().height() / 2;

    QGraphicsTextItem *station_num = addText("乘坐" + QString::number(path.size()) + "站(" + QString::number(net_->getSinglePathTimeMinutes(path)) + "分钟)");
    station_num->setPos(LEFT_MID_X + MID_RADIUS + TEXT_OFFSET, start_y - station_num->boundingRect().height() / 2);
    station_num->setDefaultTextColor(Qt::gray);

    start_y += LINE_OFFSET + MID_RADIUS;

    for (int i = 1; i < path.size(); i++) {
        addEllipse(LEFT_MID_X - MID_RADIUS, start_y - MID_RADIUS, MID_RADIUS * 2, MID_RADIUS * 2, QPen(Qt::white), QBrush(Qt::white));
        QGraphicsTextItem *station_name = addText(net_->getStationById(path[i]->getStationId())->getName());
        station_name->setPos(LEFT_MID_X + MID_RADIUS + TEXT_OFFSET, start_y - station_name->boundingRect().height() / 2);
        start_y += MID_RADIUS * 2 + LINE_OFFSET;
    }

    QGraphicsEllipseItem *end_ellipse = addEllipse(LEFT_MID_X - KEY_RADIUS, start_y - KEY_RADIUS,KEY_RADIUS * 2, KEY_RADIUS * 2, QPen(color), QBrush(Qt::white));
    pen = end_ellipse->pen();
    pen.setWidth(KEY_BORDER_WIDTH);
    end_ellipse->setPen(pen);
    QGraphicsTextItem *end_station_name = addText(net_->getStationById(path[path.size() - 1]->getNextStationId())->getName() + " 下车");
    font = end_station_name->font();
    font.setBold(true);
    font.setPointSize(KEY_TEXT_FONT_SIZE);
    end_station_name->setFont(font);
    end_station_name->setPos(LEFT_MID_X + KEY_RADIUS + TEXT_OFFSET, start_y - end_station_name->boundingRect().height() / 2);

    QGraphicsLineItem *line = addLine(LEFT_MID_X, origin_start_y + KEY_RADIUS, LEFT_MID_X, start_y, QPen(color));
    pen = line->pen();
    pen.setWidth(LINE_WIDTH);
    line->setPen(pen);
    line->setZValue(-1);

    start_y += KEY_RADIUS;

    return start_y;
}

int PathScene::drawTransfer(int start_y) {
    start_y += TRS_RADIUS;

    QColor color = Qt::gray;

    for (int i = 0; i < TRS_NUM; i++) {
        int y = start_y + i * (TRS_RADIUS * 2 + TRS_LINE_OFFSET);
        addEllipse(LEFT_MID_X - TRS_RADIUS, y - TRS_RADIUS, TRS_RADIUS * 2, TRS_RADIUS * 2, QPen(color), QBrush(color));
    }

    int mid_y = start_y + (TRS_NUM - 1) * (TRS_RADIUS * 2 + TRS_LINE_OFFSET) / 2;
    QGraphicsTextItem *text_item = addText("站内换乘");
    text_item->setPos(LEFT_MID_X + TRS_RADIUS + TEXT_OFFSET, mid_y - text_item->boundingRect().height() / 2);

    return start_y + (TRS_NUM - 1) * (TRS_RADIUS * 2 + TRS_LINE_OFFSET) + TRS_RADIUS;
}
