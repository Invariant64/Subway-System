//
// Created by Noah on 2023/11/19.
//

#ifndef SUBWAY_SYSTEM_PATHINFOBOX_H
#define SUBWAY_SYSTEM_PATHINFOBOX_H


#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

class PathInfoBox : public QGroupBox {
    Q_OBJECT

private:
    QLabel *label_time_;
    QLabel *label_distance_;
    QLabel *label_transfer_;
    QLabel *label_station_num_;
    QLabel *label_time_unit_;
    QLabel *label_distance_unit_;
    QLabel *label_transfer_unit_;
    QLabel *label_station_num_unit_;
    QLineEdit *label_time_value_;
    QLineEdit *label_distance_value_;
    QLineEdit *label_transfer_value_;
    QLineEdit *label_station_num_value_;

    void initUI();

public:
    PathInfoBox();
    ~PathInfoBox();

    void setAll(double time, double distance, int transfer, int station_num);
    void clear();
};


#endif //SUBWAY_SYSTEM_PATHINFOBOX_H
