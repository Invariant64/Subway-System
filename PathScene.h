//
// Created by Noah on 2023/11/17.
//

#ifndef SUBWAY_SYSTEM_PATHSCENE_H
#define SUBWAY_SYSTEM_PATHSCENE_H


#include <QGraphicsScene>
#include "Net.h"

class PathScene : public QGraphicsScene {

private:
    Net *net_;

    int drawOneLinePath(QList<Edge*> &path, int start_y);
    int drawTransfer(int start_y);

    static const int LEFT_MID_X = 20;
    static const int KEY_RADIUS = 7;
    static const int KEY_BORDER_WIDTH = 2;
    static const int KEY_TEXT_FONT_SIZE = 16;
    static const int MID_RADIUS = 3;
    static const int TEXT_OFFSET = 15;
    static const int LINE_OFFSET = 20;
    static const int LINE_WIDTH = 10;
    static const int TRS_RADIUS = 5;
    static const int TRS_NUM = 3;
    static const int TRS_LINE_OFFSET = 10;
    static const int RECT_RADIUS = 2;
    static const int RECT_OUTER_OFFSET = 3;

public:
    PathScene() = default;
    ~PathScene() = default;

    void setNet(Net *net);

    void drawPath(QList<Edge*> &path);
};


#endif //SUBWAY_SYSTEM_PATHSCENE_H
