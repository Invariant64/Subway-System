//
// Created by Noah on 2023/9/14.
//

#include <QApplication>
#include <QMessageBox>
#include <QGraphicsScene>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    initUI();
    initConnect();
}

MainWindow::~MainWindow() {
    delete combo_box_start_line_;
    delete combo_box_start_;
    delete combo_box_end_line_;
    delete combo_box_end_;
    delete button_search_time_;
    delete button_search_distance_;
    delete button_search_transfer_;
    delete net_scene_;
    delete view_;
}

void MainWindow::setNet(Net *net) {
    this->net_ = net;
    net_scene_->setNet(net);
    path_tab_widget_->setNet(net);
}

void MainWindow::initUI() {
    setWindowTitle("地铁查询系统");

    QLabel *label_start = new QLabel("起点: ", this);
    QLabel *label_end = new QLabel("终点: ", this);

    label_start->setMaximumWidth(40);
    label_end->setMaximumWidth(40);

    combo_box_start_line_ = new QComboBox(this);
    combo_box_start_ = new QComboBox(this);
    combo_box_end_line_ = new QComboBox(this);
    combo_box_end_ = new QComboBox(this);

    button_search_time_ = new QPushButton("查询最短时间", this);
    button_search_distance_ = new QPushButton("查询最短路", this);
    button_search_transfer_ = new QPushButton("查询最少换乘", this);

    net_scene_ = new NetScene();
    net_scene_->setSceneRect(0, 0, 15000, 10000);
    view_ = new ScaleView();
    view_->setScene(net_scene_);
    view_->setRenderHint(QPainter::Antialiasing);

    scale_button_group_ = new ScaleButtonGroup(QPointF(2, 2), QPointF(0.5, 0.5), QPointF(4, 4), QPointF(0.0625, 0.0625), view_, this);

    auto h_layout_start = new QHBoxLayout();
    auto h_layout_end = new QHBoxLayout();
    auto h_layout_button = new QHBoxLayout();
    auto h_layout_scale = new QHBoxLayout();
    auto h_layout_view = new QHBoxLayout();

    h_layout_start->addWidget(label_start);
    h_layout_start->addWidget(combo_box_start_line_);
    h_layout_start->addWidget(combo_box_start_);

    h_layout_end->addWidget(label_end);
    h_layout_end->addWidget(combo_box_end_line_);
    h_layout_end->addWidget(combo_box_end_);

    h_layout_button->addWidget(button_search_time_);
    h_layout_button->addWidget(button_search_distance_);
    h_layout_button->addWidget(button_search_transfer_);

    h_layout_scale->addWidget(scale_button_group_);

    h_layout_view->addWidget(view_);

    auto v_layout_window = new QVBoxLayout();
    auto v_layout_tab =  new QVBoxLayout();

    v_layout_window->addLayout(h_layout_start);
    v_layout_window->addLayout(h_layout_end);
    v_layout_window->addLayout(h_layout_button);
    v_layout_window->addLayout(h_layout_scale);
    v_layout_window->addLayout(h_layout_view);

    label_start_ = new QLabel("起点: ", this);
    label_end_ = new QLabel("终点: ", this);
    label_station_ = new QLabel("途径站个数：", this);
    label_time_ = new QLabel("总耗时：", this);
    label_distance_ = new QLabel("总路程：", this);
    label_transfer_ = new QLabel("换乘次数：", this);
    path_tab_widget_ = new PathTabWidget();

    v_layout_tab->addWidget(label_start_);
    v_layout_tab->addWidget(label_end_);
    v_layout_tab->addWidget(label_station_);
    v_layout_tab->addWidget(label_time_);
    v_layout_tab->addWidget(label_distance_);
    v_layout_tab->addWidget(label_transfer_);
    v_layout_tab->addWidget(path_tab_widget_);

    auto main_layout = new QHBoxLayout();

    main_layout->addLayout(v_layout_window);
    main_layout->addLayout(v_layout_tab);

    setLayout(main_layout);
}

void MainWindow::initConnect() {
    connect(combo_box_start_line_, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxStartLineIndexChanged(int)));
    connect(combo_box_end_line_, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxEndLineIndexChanged(int)));

    connect(button_search_time_, SIGNAL(clicked()), this, SLOT(onButtonSearchTimeClicked()));
    connect(button_search_distance_, SIGNAL(clicked()), this, SLOT(onButtonSearchDistanceClicked()));
    connect(button_search_transfer_, SIGNAL(clicked()), this, SLOT(onButtonSearchTransferClicked()));

    connect(net_scene_->selection_widget_->setStartButton, &QPushButton::clicked, this, [=](){
        net_scene_->selection_widget_->hide();
        Line *start_line = net_->getFirstLineByStationName(net_scene_->selection_widget_->getCurrentStationName());
        combo_box_start_line_->setCurrentIndex(combo_box_start_line_->findText(start_line->getName()));
        onComboBoxStartLineIndexChanged(combo_box_start_line_->currentIndex());
        combo_box_start_->setCurrentIndex(combo_box_start_->findText(net_scene_->selection_widget_->getCurrentStationName()));
    });
    connect(net_scene_->selection_widget_->setEndButton, &QPushButton::clicked, this, [=](){
        net_scene_->selection_widget_->hide();
        Line *end_line = net_->getFirstLineByStationName(net_scene_->selection_widget_->getCurrentStationName());
        combo_box_end_line_->setCurrentIndex(combo_box_end_line_->findText(end_line->getName()));
        onComboBoxEndLineIndexChanged(combo_box_end_line_->currentIndex());
        combo_box_end_->setCurrentIndex(combo_box_end_->findText(net_scene_->selection_widget_->getCurrentStationName()));
    });

    connect(path_tab_widget_, SIGNAL(currentChanged(int)), this, SLOT(onTabWidgetCurrentChanged(int)));
}

void MainWindow::initComboBoxLine() {
    QMap<int, Line*> *lines = net_->getLines();
    for (auto line : *lines) {
        combo_box_start_line_->addItem(line->getName());
        combo_box_end_line_->addItem(line->getName());
    }
    combo_box_start_line_->addItem("所有线路");
    combo_box_end_line_->addItem("所有线路");
    net_scene_->init();
}

void MainWindow::onComboBoxStartLineIndexChanged(int index) {
    combo_box_start_->clear();
    if (index == net_->getLines()->size()) {
        for (const auto& station : *net_->getStations()) {
            combo_box_start_->addItem(station->getName());
        }
        return;
    }
    auto stationsId = net_->getLines()->value(index)->getStationsId();
    for (int & it : *stationsId) {
        combo_box_start_->addItem(net_->getStationById(it)->getName());
    }
}

void MainWindow::onComboBoxEndLineIndexChanged(int index) {
    combo_box_end_->clear();
    if (index == net_->getLines()->size()) {
        for (const auto& station : *net_->getStations()) {
            combo_box_end_->addItem(station->getName());
        }
        return;
    }
    auto stationsId = net_->getLines()->value(index)->getStationsId();
    for (int & it : *stationsId) {
        combo_box_end_->addItem(net_->getStationById(it)->getName());
    }
}

void MainWindow::onButtonSearchTimeClicked() {
    if (combo_box_start_->currentText() == combo_box_end_->currentText()) {
        QMessageBox::information(this, "错误", "起点和终点相同");
        return;
    }

    QList<Edge*> path;
    double time = net_->getShortestPath(combo_box_start_->currentText(), combo_box_end_->currentText(), path, 0);
    net_scene_->highlightPath(path);
    QString result = "最短时间为" + QString::number(int((time + 60) / 60.0)) + "分钟\n" + net_->getPathString(path);
    QMessageBox::information(this, "最短时间", result);

    path_tab_widget_->drawPath(path, 0);
}

void MainWindow::onButtonSearchDistanceClicked() {
    if (combo_box_start_->currentText() == combo_box_end_->currentText()) {
        QMessageBox::information(this, "错误", "起点和终点相同");
        return;
    }

    QList<Edge*> path;
    double distance = net_->getShortestPath(combo_box_start_->currentText(), combo_box_end_->currentText(), path, 1);
    net_scene_->highlightPath(path);
    QString result = "最短路程为" + QString::number(distance / 1000) + "千米\n" + net_->getPathString(path);
    QMessageBox::information(this, "最短路程", result);

    path_tab_widget_->drawPath(path, 1);
}

void MainWindow::onButtonSearchTransferClicked() {
    if (combo_box_start_->currentText() == combo_box_end_->currentText()) {
        QMessageBox::information(this, "错误", "起点和终点相同");
        return;
    }

    QList<Edge*> path;
    int transfer = net_->getShortestPath(combo_box_start_->currentText(), combo_box_end_->currentText(), path, 2);
    net_scene_->highlightPath(path);
    QString result = "最少换乘" + QString::number(transfer) + "次\n" + net_->getPathString(path);
    QMessageBox::information(this, "最少换乘", result);

    path_tab_widget_->drawPath(path, 2);
}

void MainWindow::onTabWidgetCurrentChanged(int index) {
    if (combo_box_start_->currentText() == combo_box_end_->currentText()) {
        return;
    }

    QList<Edge*> path;
    net_->getShortestPath(combo_box_start_->currentText(), combo_box_end_->currentText(), path, index);
    net_scene_->highlightPath(path);
    path_tab_widget_->drawPath(path, index);

    int station_num, transfer_num;
    double time, distance;
    net_->statPath(path, station_num, transfer_num, time, distance);
    label_start_->setText("起点: " + combo_box_start_->currentText());
    label_end_->setText("终点: " + combo_box_end_->currentText());
    label_station_->setText("途径站个数：" + QString::number(station_num));
    label_time_->setText("总耗时：" + QString::number(int((time + 60) / 60.0)) + "分钟");
    label_distance_->setText("总路程：" + QString::number(distance / 1000) + "千米");
    label_transfer_->setText("换乘次数：" + QString::number(transfer_num));
}







