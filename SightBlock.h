//
// Created by Noah on 2023/12/16.
//

#ifndef SUBWAY_SYSTEM_SIGHTBLOCK_H
#define SUBWAY_SYSTEM_SIGHTBLOCK_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "Sight.h"

class SightBlock : public QWidget {
    Q_OBJECT

private:
    QLabel *label_sight_name_;
    QLabel *label_station_name_;
    QLabel *label_sight_price_;

    void initUI();

public:
    QPushButton *button_up_;
    QPushButton *button_down_;
    QPushButton *button_delete_;

    explicit SightBlock(QWidget *parent = nullptr);
    ~SightBlock() override;

    void setAll(const QString& name, const QString& station_name, double price);

    QString getSightName() const;
    QString getStationName() const;
    double getPrice() const;
};


#endif //SUBWAY_SYSTEM_SIGHTBLOCK_H
