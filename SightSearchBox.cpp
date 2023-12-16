//
// Created by Noah on 2023/12/15.
//

#include <QLabel>
#include <qgridlayout.h>
#include <QStringListModel>
#include <QCompleter>
#include <QMessageBox>
#include <QComboBox>

#include "SightSearchBox.h"

SightSearchBox::SightSearchBox(QWidget *parent) : QGroupBox(parent) {
    initUI();
    initConnect();
}

SightSearchBox::~SightSearchBox() = default;

void SightSearchBox::initUI() {
    setTitle("景点查询");

    auto *label_sight = new QLabel("景点名称: ", this);
    auto *label_station_name = new QLabel("站点名称: ", this);

    combo_box_sight_ = new QComboBox(this);
    combo_box_sight_->setEditable(true);
    combo_box_sight_->lineEdit()->setAlignment(Qt::AlignCenter);
    line_edit_station_name_ = new QLineEdit(this);
    line_edit_station_name_->setPlaceholderText("未找到站点");
    line_edit_station_name_->setAlignment(Qt::AlignCenter);
    line_edit_station_name_->setReadOnly(true);
    line_edit_station_name_->setFocusPolicy(Qt::NoFocus);
    button_search_ = new QPushButton("查询", this);
    button_clear_ = new QPushButton("清空", this);

    button_set_as_start_ = new QPushButton("设为起点", this);
    button_set_as_end_ = new QPushButton("设为终点", this);

    button_set_as_start_->setEnabled(false);
    button_set_as_end_->setEnabled(false);

    auto *layout = new QGridLayout(this);
    layout->addWidget(label_sight, 0, 0);
    layout->addWidget(combo_box_sight_, 0, 1);
    layout->addWidget(button_search_, 0, 2);
    layout->addWidget(button_clear_, 0, 3);
    layout->addWidget(label_station_name, 1, 0);
    layout->addWidget(line_edit_station_name_, 1, 1);
    layout->addWidget(button_set_as_start_, 1, 2);
    layout->addWidget(button_set_as_end_, 1, 3);

    setLayout(layout);
}

void SightSearchBox::initConnect() {
    connect(button_search_, &QPushButton::clicked, this, [=]() {
        if (combo_box_sight_->currentText().isEmpty()) {
            QMessageBox::warning(this, "搜索失败", "请输入景点名称");
            return;
        }
        auto station = net_->getStationBySightName(combo_box_sight_->currentText());
        if (station == nullptr) {
            QMessageBox::warning(this, "搜索失败", "未找到该景点");
            return;
        }
        line_edit_station_name_->setText(station->getName());
    });

    connect(button_clear_, &QPushButton::clicked, this, [=]() {
        combo_box_sight_->clearEditText();
    });

    connect(combo_box_sight_->lineEdit(), &QLineEdit::returnPressed, this, [=]() {
        button_search_->click();
    });

    connect(combo_box_sight_->lineEdit(), &QLineEdit::textChanged, this, [=]() {
        if (combo_box_sight_->lineEdit()->text().isEmpty()) {
            line_edit_station_name_->clear();
        }
    });

    connect(line_edit_station_name_, &QLineEdit::textChanged, this, [=]() {
        if (line_edit_station_name_->text().isEmpty()) {
            button_set_as_start_->setEnabled(false);
            button_set_as_end_->setEnabled(false);
        } else {
            button_set_as_start_->setEnabled(true);
            button_set_as_end_->setEnabled(true);
        }
    });
}

void SightSearchBox::setNet(Net *net) {
    net_ = net;

    auto sights = net_->getSights();
    QStringList sight_list;
    for (const auto &sight : *sights) {
        sight_list << sight->getName();
        combo_box_sight_->addItem(sight->getName());
    }
    completer_ = new QCompleter(sight_list, this);
    completer_->setMaxVisibleItems(7);
    completer_->setFilterMode(Qt::MatchContains);
    combo_box_sight_->setCompleter(completer_);
    combo_box_sight_->lineEdit()->setPlaceholderText("请输入景点名称");

    combo_box_sight_->clearEditText();
}

QString SightSearchBox::getStationName() const {
    return line_edit_station_name_->text();
}
