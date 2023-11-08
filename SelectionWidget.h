//
// Created by Noah on 2023/11/8.
//

#ifndef SUBWAY_SYSTEM_SELECTIONWIDGET_H
#define SUBWAY_SYSTEM_SELECTIONWIDGET_H


#include <QWidget>
#include <QPushButton>

class SelectionWidget : public QWidget{
    Q_OBJECT

public:
    SelectionWidget(QWidget *parent = nullptr);
    ~SelectionWidget();

    void setCurrentStationName(QString name);
    QString getCurrentStationName() const;

    QPushButton *setStartButton;
    QPushButton *setEndButton;
    QPushButton *cancelButton;

private:
    void initUI();
    void initConnect();

    QString current_station_name_;
};


#endif //SUBWAY_SYSTEM_SELECTIONWIDGET_H
