//
// Created by Noah on 2023/11/8.
//

#ifndef SUBWAY_SYSTEM_SELECTIONWIDGET_H
#define SUBWAY_SYSTEM_SELECTIONWIDGET_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>

class SelectionWidget : public QWidget{
    Q_OBJECT

public:
    SelectionWidget(QWidget *parent = nullptr);
    ~SelectionWidget();

    void setCurrentStationName(QString name);
    QString getCurrentStationName() const;

    QPushButton *set_start_button_;
    QPushButton *set_end_button_;
    QPushButton *cancel_button_;

    QLabel *label_;


private:
    void initUI();
    void initConnect();

    QString current_station_name_;
};


#endif //SUBWAY_SYSTEM_SELECTIONWIDGET_H
