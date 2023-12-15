//
// Created by Noah on 2023/12/15.
//

#ifndef SUBWAY_SYSTEM_SIGHTSEARCHBOX_H
#define SUBWAY_SYSTEM_SIGHTSEARCHBOX_H


#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include "Net.h"

class SightSearchBox : public QGroupBox {
    Q_OBJECT

private:
    Net *net_;

    QComboBox *combo_box_sight_;
    QCompleter *completer_;
    QLineEdit *line_edit_station_name_;
    QPushButton *button_search_;
    QPushButton *button_clear_;

    void initUI();
    void initConnect();

public:
    QPushButton *button_set_as_start_;
    QPushButton *button_set_as_end_;

    SightSearchBox(QWidget *parent = nullptr);
    ~SightSearchBox();

    void setNet(Net *net);

    QString getStationName() const;
};


#endif //SUBWAY_SYSTEM_SIGHTSEARCHBOX_H
