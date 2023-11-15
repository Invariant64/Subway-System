//
// Created by Noah on 2023/11/15.
//

#ifndef SUBWAY_SYSTEM_SCALEBUTTONGROUP_H
#define SUBWAY_SYSTEM_SCALEBUTTONGROUP_H


#include <QPushButton>
#include <QGraphicsView>

class ScaleButtonGroup : public QWidget {
    Q_OBJECT
private:
    QPointF scale_expand_;
    QPointF scale_shrink_;
    QPointF scale_max_;
    QPointF scale_min_;
    QGraphicsView *view_;

    QPushButton *expand_button_;
    QPushButton *shrink_button_;

    void initUI();
    void initConnect();

public:
    ScaleButtonGroup(QPointF scale_expand, QPointF scale_shrink, QPointF scale_max, QPointF scale_min, QGraphicsView *view, QWidget *parent = nullptr);
    ~ScaleButtonGroup();
};


#endif //SUBWAY_SYSTEM_SCALEBUTTONGROUP_H
