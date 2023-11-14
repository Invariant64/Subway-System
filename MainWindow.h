//
// Created by Noah on 2023/9/14.
//

#ifndef SUBWAY_SYSTEM_MAINWINDOW_H
#define SUBWAY_SYSTEM_MAINWINDOW_H

#include <QPushButton>
#include <QCheckBox>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>

#include "Line.h"
#include "Station.h"
#include "Net.h"

#include "StationButton.h"
#include "SelectionWidget.h"
#include "NetScene.h"

class MainWindow : public QWidget {
    Q_OBJECT

private:
    QComboBox *combo_box_start_line_;
    QComboBox *combo_box_start_;
    QComboBox *combo_box_end_line_;
    QComboBox *combo_box_end_;
    QPushButton *button_search_1_;
    QPushButton *button_search_2_;

    NetScene *net_scene_;
    QGraphicsView *view_;

    void initUI();
    void initConnect();

    Net *net_;

private slots:
    void onComboBoxStartLineIndexChanged(int index); // 当起始线路下拉框的选项改变时
    void onComboBoxEndLineIndexChanged(int index); // 当终点线路下拉框的选项改变时
    void onButtonSearch1Clicked();
    void onButtonSearch2Clicked();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setNet(Net *net);

    void initComboBoxLine();

};


#endif //SUBWAY_SYSTEM_MAINWINDOW_H
