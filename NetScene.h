//
// Created by Noah on 2023/11/8.
//

#ifndef SUBWAY_SYSTEM_NETSCENE_H
#define SUBWAY_SYSTEM_NETSCENE_H


#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "SelectionWidget.h"
#include "Net.h"

class NetScene : public QGraphicsScene {
    Q_OBJECT

private:
    Net *net;
    void initStationButtons();
    void initEdges();

public:
    SelectionWidget *selection_widget_;
    QGraphicsProxyWidget *proxy_selection_widget_;

    NetScene();
    ~NetScene();

    void setNet(Net *net);

    bool init();
};


#endif //SUBWAY_SYSTEM_NETSCENE_H
