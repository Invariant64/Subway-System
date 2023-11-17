//
// Created by Noah on 2023/11/16.
//

#ifndef SUBWAY_SYSTEM_SCALEVIEW_H
#define SUBWAY_SYSTEM_SCALEVIEW_H


#include <QGraphicsView>
#include <QWheelEvent>

class ScaleView : public QGraphicsView {
    Q_OBJECT

public:
    ScaleView(QWidget *parent = nullptr);

    void wheelEvent(QWheelEvent *event) override;
};


#endif //SUBWAY_SYSTEM_SCALEVIEW_H
