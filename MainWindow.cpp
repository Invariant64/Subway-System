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
    button_clear_ = new QPushButton("重置", this);

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
    h_layout_scale->addWidget(button_clear_);

    h_layout_view->addWidget(view_);

    auto v_layout_window = new QVBoxLayout();
    auto v_layout_tab =  new QVBoxLayout();

    v_layout_window->addLayout(h_layout_start);
    v_layout_window->addLayout(h_layout_end);
    v_layout_window->addLayout(h_layout_button);
    v_layout_window->addLayout(h_layout_scale);
    v_layout_window->addLayout(h_layout_view);

    path_info_box_ = new PathInfoBox();
    path_tab_widget_ = new PathTabWidget();
    ticket_group_box_ = new TicketGroupBox();

    v_layout_tab->addWidget(path_info_box_);
    v_layout_tab->addWidget(path_tab_widget_);
    v_layout_tab->addWidget(ticket_group_box_);

    auto main_layout = new QHBoxLayout();

    main_layout->addLayout(v_layout_window);
    main_layout->addLayout(v_layout_tab);

    setLayout(main_layout);
}

void MainWindow::initConnect() {
    connect(combo_box_start_line_, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxStartLineIndexChanged(int)));
    connect(combo_box_end_line_, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxEndLineIndexChanged(int)));

    connect(button_search_time_, &QPushButton::clicked, this, [=](){
        if (combo_box_start_->currentText() == combo_box_end_->currentText()) {
            QMessageBox::warning(this, "查询失败", "起点站和终点站不能相同！");
            return;
        }
        onTabWidgetCurrentChanged(0);
    });

    connect(button_search_distance_, &QPushButton::clicked, this, [=](){
        if (combo_box_start_->currentText() == combo_box_end_->currentText()) {
            QMessageBox::warning(this, "查询失败", "起点站和终点站不能相同！");
            return;
        }
        onTabWidgetCurrentChanged(1);
    });

    connect(button_search_transfer_, &QPushButton::clicked, this, [=](){
        if (combo_box_start_->currentText() == combo_box_end_->currentText()) {
            QMessageBox::warning(this, "查询失败", "起点站和终点站不能相同！");
            return;
        }
        onTabWidgetCurrentChanged(2);
    });

    connect(net_scene_->selection_widget_->set_start_button_, &QPushButton::clicked, this, [=](){
        net_scene_->selection_widget_->hide();
        Line *start_line = net_->getFirstLineByStationName(net_scene_->selection_widget_->getCurrentStationName());
        combo_box_start_line_->setCurrentIndex(combo_box_start_line_->findText(start_line->getName()));
        onComboBoxStartLineIndexChanged(combo_box_start_line_->currentIndex());
        combo_box_start_->setCurrentIndex(combo_box_start_->findText(net_scene_->selection_widget_->getCurrentStationName()));
    });
    connect(net_scene_->selection_widget_->set_end_button_, &QPushButton::clicked, this, [=](){
        net_scene_->selection_widget_->hide();
        Line *end_line = net_->getFirstLineByStationName(net_scene_->selection_widget_->getCurrentStationName());
        combo_box_end_line_->setCurrentIndex(combo_box_end_line_->findText(end_line->getName()));
        onComboBoxEndLineIndexChanged(combo_box_end_line_->currentIndex());
        combo_box_end_->setCurrentIndex(combo_box_end_->findText(net_scene_->selection_widget_->getCurrentStationName()));
    });

    connect(path_tab_widget_, SIGNAL(currentChanged(int)), this, SLOT(onTabWidgetCurrentChanged(int)));

    connect(button_clear_, &QPushButton::clicked, this, [=](){
        net_scene_->clearHighlight();
        path_tab_widget_->clear();
        path_info_box_->clear();
    });
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
    path_info_box_->setAll(time, distance, transfer_num, station_num);

    ticket_group_box_->setAll(combo_box_start_->currentText(), combo_box_end_->currentText(), net_->getPriceByDistance(distance));
}







