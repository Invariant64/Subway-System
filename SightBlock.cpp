//
// Created by Noah on 2023/12/16.
//

#include <QHBoxLayout>
#include "SightBlock.h"

SightBlock::SightBlock(QWidget *parent) {
    initUI();
}

SightBlock::~SightBlock() {

}

void SightBlock::initUI() {
    QLabel *label_name_ = new QLabel("景点: ");
    QLabel *label_station_ = new QLabel("站点: ");
    QLabel *label_price_ = new QLabel("价格: ");
    label_sight_name_ = new QLabel;
    label_station_name_ = new QLabel;
    label_sight_price_ = new QLabel;
    label_sight_name_->setAlignment(Qt::AlignCenter);
    label_station_name_->setAlignment(Qt::AlignCenter);
    label_sight_price_->setAlignment(Qt::AlignCenter);
    label_sight_name_->setFixedWidth(140);
    label_station_name_->setFixedWidth(80);
    label_sight_price_->setFixedWidth(40);

    button_up_ = new QPushButton("↑");
    button_down_ = new QPushButton("↓");
    button_delete_ = new QPushButton("×");

    QHBoxLayout *layout_label = new QHBoxLayout;
    layout_label->addWidget(label_name_);
    layout_label->addWidget(label_sight_name_);
    layout_label->addWidget(label_station_);
    layout_label->addWidget(label_station_name_);
    layout_label->addWidget(label_price_);
    layout_label->addWidget(label_sight_price_);

    QHBoxLayout *layout_button = new QHBoxLayout;
    layout_button->addWidget(button_up_);
    layout_button->addWidget(button_down_);
    layout_button->addWidget(button_delete_);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(0, 1);
    layout->addLayout(layout_label, 0, 0, 1, 2);
    layout->addLayout(layout_button, 0, 2, 1, 1);

    setLayout(layout);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QColor(0, 0, 0, 0)));
    setPalette(palette);
}

void SightBlock::setAll(const QString &name, const QString &station_name, double price) {
    label_sight_name_->setText(name);
    label_station_name_->setText(station_name);
    label_sight_price_->setText(QString::number(price, 'f', 2));
}

QString SightBlock::getSightName() const {
    return label_sight_name_->text();
}

QString SightBlock::getStationName() const {
    return label_station_name_->text();
}

double SightBlock::getPrice() const {
    return label_sight_price_->text().toDouble();
}
