//
// Created by Noah on 2023/11/8.
//

#include "NetScene.h"
#include "StationButton.h"

NetScene::NetScene() {
    net_ = nullptr;
    initUI();
}

NetScene::~NetScene() {
    delete selection_widget_;
}

void NetScene::initUI() {
    selection_widget_ = new SelectionWidget();
    proxy_selection_widget_ = new QGraphicsProxyWidget();
    proxy_selection_widget_ = addWidget(selection_widget_);
    proxy_selection_widget_->setPos(0, 0);
    proxy_selection_widget_->setZValue(1);
    proxy_selection_widget_->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    proxy_selection_widget_->hide();
    //设置背景图片
    QImageReader::setAllocationLimit(0);
    QPixmap pixmap = QPixmap("../resources/newmap.jpeg");
    if (pixmap.isNull()) {
        qDebug() << "Failed to load background image!";
    }
    setBackgroundBrush(QBrush(pixmap));
}

void NetScene::initStationButtons() {
    QMap<int, Station> *stations = net_->getStations();
    for (auto station : *stations) {
        StationButton *station_button = new StationButton(&station, selection_widget_);
        addItem(station_button);
    }
}

void NetScene::initEdges() {
    QMap<int, Edge*> *edges = net_->getEdges();
    for (auto edge : *edges) {
        QPoint start = net_->getStationById(edge->getStationId()).getPosition();
        QPoint end = net_->getStationById(edge->getNextStationId()).getPosition();
        QGraphicsLineItem *line_item = new QGraphicsLineItem(start.x(), start.y(), end.x(), end.y());
        QPen *pen = new QPen();
        pen->setWidth(50);
        pen->setColor(net_->getLineById(edge->getLineId())->getColor());
        line_item->setPen(*pen);
        addItem(line_item);
    }
}

void NetScene::setNet(Net *net) {
    this->net_ = net;
}

bool NetScene::init() {
    if (net_ == nullptr) {
        return false;
    }
    initEdges();
    initStationButtons();
    return true;
}

void NetScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // 显示坐标
//    selection_widget_->label->setText(QString("%1 %2").arg(event->scenePos().x()).arg(event->scenePos().y()));
//    selection_widget_->move(event->scenePos().x(), event->scenePos().y() + 30);
//    selection_widget_->show();
//    // 将坐标复制到剪贴板
//    QClipboard *clipboard = QApplication::clipboard();
//    clipboard->setText(QString("%1 %2").arg(event->scenePos().x()).arg(event->scenePos().y()));

}
