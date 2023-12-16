//
// Created by Noah on 2023/11/19.
//

#include <qgridlayout.h>
#include <QMessageBox>
#include "TicketGroupBox.h"

void TicketGroupBox::initUI() {
    setTitle("购买地铁票");

    label_start_ = new QLabel("起点站：", this);
    label_end_ = new QLabel("终点站：", this);
    label_price_ = new QLabel("票价：", this);

    line_edit_start_ = new QLineEdit(this);
    line_edit_end_ = new QLineEdit(this);
    line_edit_price_ = new QLineEdit(this);
    line_edit_start_->setReadOnly(true);
    line_edit_end_->setReadOnly(true);
    line_edit_price_->setReadOnly(true);
    line_edit_start_->setAlignment(Qt::AlignCenter);
    line_edit_end_->setAlignment(Qt::AlignCenter);
    line_edit_price_->setAlignment(Qt::AlignCenter);

    button_open_ticket_window_ = new QPushButton("购买", this);

    auto grid_layout = new QGridLayout();
    grid_layout->addWidget(label_start_, 0, 0);
    grid_layout->addWidget(label_end_, 1, 0);
    grid_layout->addWidget(label_price_, 2, 0);
    grid_layout->addWidget(line_edit_start_, 0, 1);
    grid_layout->addWidget(line_edit_end_, 1, 1);
    grid_layout->addWidget(line_edit_price_, 2, 1);
    grid_layout->addWidget(button_open_ticket_window_, 3, 0, 1, 2);

    setLayout(grid_layout);
}

void TicketGroupBox::initConnect() {
//    connect(button_buy_, &QPushButton::clicked, this, [=](){
//        if (line_edit_start_->text().isEmpty() || line_edit_end_->text().isEmpty()) {
//            QMessageBox::warning(this, "购买失败", "请先选择起点站和终点站！");
//            return;
//        }
//        QMessageBox::information(this, "购买成功", "购买成功！\n花费" + QString::number(price_, 'f', 2) + "元。");
//    });
}

TicketGroupBox::TicketGroupBox() {
    price_ = 0;

    initUI();
    initConnect();
}

TicketGroupBox::~TicketGroupBox() = default;

void TicketGroupBox::setAll(QString start, QString end, double price) {
    line_edit_start_->setText(start);
    line_edit_end_->setText(end);
    line_edit_price_->setText(QString::number(price, 'f', 2));
    price_ = price;
}

bool TicketGroupBox::isEmpty() const {
    return line_edit_start_->text().isEmpty();
}

double TicketGroupBox::getPrice() const {
    return price_;
}
