//
// Created by Noah on 2023/11/8.
//

#ifndef SUBWAY_SYSTEM_NETSCENE_H
#define SUBWAY_SYSTEM_NETSCENE_H


#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QApplication>
#include <QClipboard>
#include <QImageReader>
#include "SelectionWidget.h"
#include "Net.h"
#include "StationButton.h"
#include "EdgeItem.h"

class NetScene : public QGraphicsScene {
    Q_OBJECT

private:
    Net *net_;

    QList<StationButton *> *station_buttons_;
    QList<EdgeItem *> *edges_items_;

    void initStationButtons();
    void initEdges();
    void initUI();

public:
    SelectionWidget *selection_widget_;
    QGraphicsProxyWidget *proxy_selection_widget_;

    NetScene();
    ~NetScene();

    void setNet(Net *net);

    bool init();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void highlightPath(QList<Edge*> &path);

    void clearHighlight();
};


#endif //SUBWAY_SYSTEM_NETSCENE_H
