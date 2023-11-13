//
// Created by Noah on 2023/11/3.
//

#include "StationButton.h"

StationButton::StationButton(Station *station, SelectionWidget *selection_widget) :
        id_(station->getId()), name_(station->getName()), position_(station->getPosition()),
        QGraphicsEllipseItem(), selection_widget_(selection_widget) {
    initUI();
}

void StationButton::initUI() {
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setRect(position_.x() - RADIUS, position_.y() - RADIUS, RADIUS * 2, RADIUS * 2);
    QPen pen = this->pen();
    pen.setWidth(RADIUS / 10);
    pen.setColor(Qt::white);
    this->setPen(pen);
    this->setBrush(QBrush(QColor(0, 160, 230)));

    // 显示名字
    QGraphicsTextItem *text_item = new QGraphicsTextItem(name_);
    text_item->setZValue(1);
    text_item->setPos(position_.x() - RADIUS, position_.y() - RADIUS - 20);
    text_item->setParentItem(this);
}

int StationButton::getId() const {
    return id_;
}

QString StationButton::getName() const {
    return name_;
}

QPoint StationButton::getPosition() const {
    return position_ - QPoint(RADIUS, RADIUS);
}

void StationButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setBrush(Qt::gray);
}

void StationButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setBrush(QBrush(QColor(0, 160, 230)));

    position_ = event->scenePos().toPoint();
    selection_widget_->move(position_.x(), position_.y() + 30);
    selection_widget_->show();
    selection_widget_->setCurrentStationName(name_);
    selection_widget_->label->setText(QString("%1 %2").arg(position_.x()).arg(position_.y()));
}










