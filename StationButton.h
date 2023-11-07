//
// Created by Noah on 2023/11/3.
//

#ifndef SUBWAY_SYSTEM_STATIONBUTTON_H
#define SUBWAY_SYSTEM_STATIONBUTTON_H


#include <QPushButton>
#include "Station.h"

class StationButton : public QPushButton {
private:
    int id_;
    QString name_;
    QPoint position_;

    const int RADIUS = 20;

    const QString normal_style = QString("background-color: white;"
                                         "border-radius: %1px;"
                                         "border: %2px solid rgb(0, 0, 0);")
                                                 .arg(RADIUS).arg(RADIUS / 10);
    const QString pressed_style = QString("background-color: grey;"
                                          "border-radius: %1px;"
                                          "border: %2px solid rgb(0, 0, 0);")
                                                  .arg(RADIUS).arg(RADIUS / 10);

    void initUI();
    void initConnect();

public:
    StationButton() = default;
    ~StationButton() = default;
    explicit StationButton(Station *station, QWidget *parent = nullptr);
};


#endif //SUBWAY_SYSTEM_STATIONBUTTON_H
