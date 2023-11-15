//
// Created by Noah on 2023/11/8.
//

#include <QHBoxLayout>
#include "NetScene.h"

NetScene::NetScene() {
    net_ = nullptr;
    station_buttons_ = new QList<StationButton *>;
    edges_items_ = new QList<EdgeItem *>;
    initUI();
}

NetScene::~NetScene() {
    delete selection_widget_;

    for (auto station_button : *station_buttons_) {
        delete station_button;
    }
    delete station_buttons_;

    for (auto edge_item : *edges_items_) {
        delete edge_item;
    }
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
//    QImageReader::setAllocationLimit(0);
//    QPixmap pixmap = QPixmap("../resources/newmap.jpeg");
//    if (pixmap.isNull()) {
//        qDebug() << "Failed to load background image!";
//    }
//    setBackgroundBrush(QBrush(pixmap));
}

void NetScene::initStationButtons() {
    QMap<int, Station*> *stations = net_->getStations();
    for (auto station : *stations) {
        StationButton *station_button = new StationButton(station, selection_widget_);
        station_buttons_->append(station_button);
        addItem(station_button);
    }
}

void NetScene::initEdges() {
    QMap<int, Edge*> *edges = net_->getEdges();
    for (auto edge : *edges) {
        QPoint start = net_->getStationById(edge->getStationId())->getPosition();
        QPoint end = net_->getStationById(edge->getNextStationId())->getPosition();
        auto *edge_item = new EdgeItem(edge);
        QPen pen = edge_item->pen();
        pen.setWidth(50);
        pen.setColor(net_->getLineById(edge->getLineId())->getColor());
        edge_item->setPen(pen);
        edge_item->setLine(start.x(), start.y(), end.x(), end.y());
        edges_items_->append(edge_item);
        addItem(edge_item);
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

void NetScene::highlightPath(QList<Edge *> &path) {
    clearHighlight();
    for (auto edge_item : *edges_items_) {
        bool flag = false;
        for (auto edge : path) {
            if (edge == edge_item->getEdge()) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            QPen pen = edge_item->pen();
            QColor color = pen.color();
            color.setAlpha(20);
            pen.setBrush(color);
            edge_item->setPen(pen);
        }
    }

    QList<int> stations_id;
    for (auto edge : path) {
        stations_id.append(edge->getStationId());
    }
    stations_id.append(path.last()->getNextStationId());

    for (auto station_button : *station_buttons_) {
        bool flag = false;
        for (auto station_id : stations_id) {
            if (station_id == station_button->getId()) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            QPen pen = station_button->pen();
            QColor color = pen.color();
            color.setAlpha(20);
            pen.setBrush(color);
            station_button->setPen(pen);
        }
    }
}

void NetScene::clearHighlight() {
    for (auto edge_item : *edges_items_) {
        QPen pen = edge_item->pen();
        QColor color = pen.color();
        color.setAlpha(255);
        pen.setBrush(color);
        edge_item->setPen(pen);
    }

    for (auto station_button : *station_buttons_) {
        QPen pen = station_button->pen();
        QColor color = pen.color();
        color.setAlpha(255);
        pen.setBrush(color);
        station_button->setPen(pen);
    }
}
