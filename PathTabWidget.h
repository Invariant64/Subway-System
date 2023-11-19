//
// Created by Noah on 2023/11/17.
//

#ifndef SUBWAY_SYSTEM_PATHTABWIDGET_H
#define SUBWAY_SYSTEM_PATHTABWIDGET_H


#include <qtabwidget.h>
#include <QGraphicsView>
#include "PathScene.h"

class PathTabWidget : public QTabWidget {
    Q_OBJECT

private:
    PathScene *scene_time_;
    PathScene *scene_distance_;
    PathScene *scene_transfer_;

    QGraphicsView *view_time_;
    QGraphicsView *view_distance_;
    QGraphicsView *view_transfer_;

public:
    PathTabWidget();
    ~PathTabWidget();

    void setNet(Net *net);

    void drawPath(QList<Edge*> &path, int weight_mode);

    void clear();
};


#endif //SUBWAY_SYSTEM_PATHTABWIDGET_H
