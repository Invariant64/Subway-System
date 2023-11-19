//
// Created by Noah on 2023/11/19.
//

#include <qgridlayout.h>
#include "PathInfoBox.h"

void PathInfoBox::initUI() {
    label_time_ = new QLabel("时间：", this);
    label_distance_ = new QLabel("距离：", this);
    label_transfer_ = new QLabel("换乘：", this);
    label_station_num_ = new QLabel("途径：", this);

    label_time_unit_ = new QLabel("分钟", this);
    label_distance_unit_ = new QLabel("公里", this);
    label_transfer_unit_ = new QLabel("次", this);
    label_station_num_unit_ = new QLabel("站", this);

    label_time_value_ = new QLineEdit(this);
    label_distance_value_ = new QLineEdit(this);
    label_transfer_value_ = new QLineEdit(this);
    label_station_num_value_ = new QLineEdit(this);
    label_time_value_->setReadOnly(true);
    label_distance_value_->setReadOnly(true);
    label_transfer_value_->setReadOnly(true);
    label_station_num_value_->setReadOnly(true);
    label_time_value_->setAlignment(Qt::AlignCenter);
    label_distance_value_->setAlignment(Qt::AlignCenter);
    label_transfer_value_->setAlignment(Qt::AlignCenter);
    label_station_num_value_->setAlignment(Qt::AlignCenter);

    auto grid_layout = new QGridLayout();

    grid_layout->addWidget(label_time_, 0, 0);
    grid_layout->addWidget(label_distance_, 1, 0);
    grid_layout->addWidget(label_transfer_, 2, 0);
    grid_layout->addWidget(label_station_num_, 3, 0);
    grid_layout->addWidget(label_time_value_, 0, 1);
    grid_layout->addWidget(label_distance_value_, 1, 1);
    grid_layout->addWidget(label_transfer_value_, 2, 1);
    grid_layout->addWidget(label_station_num_value_, 3, 1);
    grid_layout->addWidget(label_time_unit_, 0, 2);
    grid_layout->addWidget(label_distance_unit_, 1, 2);
    grid_layout->addWidget(label_transfer_unit_, 2, 2);
    grid_layout->addWidget(label_station_num_unit_, 3, 2);

    setLayout(grid_layout);
}

PathInfoBox::PathInfoBox() {
    initUI();
}

PathInfoBox::~PathInfoBox() = default;

void PathInfoBox::setAll(double time, double distance, int transfer, int station_num) {
    label_time_value_->setText(QString::number(time / 60, 'f', 2));
    label_distance_value_->setText(QString::number(distance / 1000, 'f', 2));
    label_transfer_value_->setText(QString::number(transfer));
    label_station_num_value_->setText(QString::number(station_num));
}

void PathInfoBox::clear() {
    label_time_value_->clear();
    label_distance_value_->clear();
    label_transfer_value_->clear();
    label_station_num_value_->clear();
}
