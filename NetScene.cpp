//
// Created by Noah on 2023/11/8.
//

#include "NetScene.h"
#include "StationButton.h"

NetScene::NetScene() {
    selection_widget_ = new SelectionWidget();
    proxy_selection_widget_ = addWidget(selection_widget_);
    proxy_selection_widget_->setPos(0, 0);
    proxy_selection_widget_->hide();
}

NetScene::~NetScene() {
    delete selection_widget_;
    delete proxy_selection_widget_;
}

void NetScene::initStationButtons() {
    QMap<int, Station> *stations = net->getStations();
    for (auto station : *stations) {
        StationButton *station_button = new StationButton(&station);
        connect(station_button, &StationButton::clicked, this, [=](){
            selection_widget_->move(station_button->getPosition().x(), station_button->getPosition().y() + 50);
            selection_widget_->show();
            selection_widget_->setCurrentStationName(station_button->getName());
        });
        QGraphicsProxyWidget *proxyWidget = addWidget(station_button);
        proxyWidget->setPos(station_button->getPosition());
        addWidget(station_button);
    }
}

void NetScene::initEdges() {
    QMap<int, Line*> *lines = net->getLines();
    for (auto line : *lines) {
        QList<int> *stations_id = line->getStationsId();
        for (int i = 0; i < stations_id->size() - 1; i++) {
            Station start_station = net->getStationById(stations_id->at(i));
            Station end_station = net->getStationById(stations_id->at(i + 1));
            QGraphicsLineItem *line_item = new QGraphicsLineItem(start_station.getPosition().x(),
                                                                 start_station.getPosition().y(),
                                                                 end_station.getPosition().x(),
                                                                 end_station.getPosition().y());
            QPen *pen = new QPen();
            pen->setWidth(5);
            pen->setColor(line->getColor());
            line_item->setPen(*pen);
            addItem(line_item);
        }
    }
}

void NetScene::setNet(Net *net) {
    this->net = net;
}

bool NetScene::init() {
    if (net == nullptr) {
        return false;
    }
    initEdges();
    initStationButtons();
    // 把selection放到最顶层显示
    proxy_selection_widget_->setZValue(1);
    // selection不随着scene的缩放而缩放
    proxy_selection_widget_->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    return true;
}
