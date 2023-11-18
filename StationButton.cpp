//
// Created by Noah on 2023/11/3.
//

#include "StationButton.h"

StationButton::StationButton(Station *station, SelectionWidget *selection_widget) :
        station_(station), position_(station->getPosition()), QGraphicsEllipseItem(), selection_widget_(selection_widget) {
    initUI();
}

void StationButton::initUI() {
    setRect(position_.x() - RADIUS, position_.y() - RADIUS, RADIUS * 2, RADIUS * 2);
    QPen pen = this->pen();
    pen.setWidth(RADIUS / 10);
    pen.setColor(Qt::white);
    this->setPen(pen);
    this->setBrush(QBrush(QColor(0, 160, 230)));

    // 显示名字
    QGraphicsTextItem *text_item = new QGraphicsTextItem(station_->getName());
    text_item->setZValue(1);
    text_item->setScale(5);
    text_item->setPos(position_.x() - text_item->boundingRect().width() / 2 * 5, position_.y() - 3 * RADIUS);
    text_item->setParentItem(this);
}

int StationButton::getId() const {
    return station_->getId();
}

QString StationButton::getName() const {
    return station_->getName();
}

QPoint StationButton::getPosition() const {
    return position_ - QPoint(RADIUS, RADIUS);
}

Station *StationButton::getStation() const {
    return station_;
}

void StationButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setBrush(Qt::gray);
}

void StationButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setBrush(QBrush(QColor(0, 160, 230)));

    position_ = event->scenePos().toPoint();
    selection_widget_->move(position_.x(), position_.y() + 30);
    selection_widget_->show();
    selection_widget_->setCurrentStationName(station_->getName());
    selection_widget_->label->setText(QString("%1 %2").arg(position_.x()).arg(position_.y()));
}










