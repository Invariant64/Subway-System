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
    delete button_search_1_;
    delete button_search_2_;
    delete net_scene_;
    delete view_;
}

void MainWindow::setNet(Net *net) {
    this->net_ = net;
    net_scene_->setNet(net);
}

void MainWindow::initUI() {
    combo_box_start_line_ = new QComboBox(this);
    combo_box_start_ = new QComboBox(this);
    combo_box_end_line_ = new QComboBox(this);
    combo_box_end_ = new QComboBox(this);

    button_search_1_ = new QPushButton("查询最短路", this);
    button_search_2_ = new QPushButton("查询最少换乘", this);

    net_scene_ = new NetScene();
    net_scene_->setSceneRect(0, 0, 15000, 10000);
    view_ = new QGraphicsView();
    view_->setScene(net_scene_);
    view_->setRenderHint(QPainter::Antialiasing);

    auto h_layout_start = new QHBoxLayout();
    auto h_layout_end = new QHBoxLayout();
    auto h_layout_button = new QHBoxLayout();
    auto h_layout_view = new QHBoxLayout();

    h_layout_start->addWidget(combo_box_start_line_);
    h_layout_start->addWidget(combo_box_start_);
    h_layout_end->addWidget(combo_box_end_line_);
    h_layout_end->addWidget(combo_box_end_);
    h_layout_button->addWidget(button_search_1_);
    h_layout_button->addWidget(button_search_2_);
    h_layout_view->addWidget(view_);

    auto main_layout = new QVBoxLayout();

    main_layout->addLayout(h_layout_start);
    main_layout->addLayout(h_layout_end);
    main_layout->addLayout(h_layout_button);
    main_layout->addLayout(h_layout_view);

    setLayout(main_layout);
}

void MainWindow::initConnect() {
    connect(combo_box_start_line_, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxStartLineIndexChanged(int)));
    connect(combo_box_end_line_, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxEndLineIndexChanged(int)));
    connect(button_search_1_, SIGNAL(clicked()), this, SLOT(onButtonSearch1Clicked()));
    connect(button_search_2_, SIGNAL(clicked()), this, SLOT(onButtonSearch2Clicked()));

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
}

void MainWindow::initComboBoxLine() {
    QMap<int, Line*> *lines = net_->getLines();
    for (auto line : *lines) {
        combo_box_start_line_->addItem(line->getName());
        combo_box_end_line_->addItem(line->getName());
    }
    net_scene_->init();
}

void MainWindow::onComboBoxStartLineIndexChanged(int index) {
    combo_box_start_->clear();
    auto stationsId = net_->getLines()->value(index)->getStationsId();
    for (int & it : *stationsId) {
        combo_box_start_->addItem(net_->getStationById(it).getName());
    }
}

void MainWindow::onComboBoxEndLineIndexChanged(int index) {
    combo_box_end_->clear();
    auto stationsId = net_->getLines()->value(index)->getStationsId();
    for (int & it : *stationsId) {
        combo_box_end_->addItem(net_->getStationById(it).getName());
    }
}

void MainWindow::onButtonSearch1Clicked() {
    view_->scale(0.5, 0.5);

    QString result = net_->getShortestPathString(combo_box_start_->currentText(), combo_box_end_->currentText(), 1);

    QMessageBox::information(this, "最短路径", result);
}

void MainWindow::onButtonSearch2Clicked() {
    view_->scale(2, 2);

    QString result = net_->getShortestPathString(combo_box_start_->currentText(), combo_box_end_->currentText(), 2);

    QMessageBox::information(this, "最少换乘", result);
}







