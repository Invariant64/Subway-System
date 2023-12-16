//
// Created by Noah on 2023/12/16.
//

#include <qgridlayout.h>
#include <QButtonGroup>
#include <QMessageBox>
#include "SubwayTicketWidget.h"

SubwayTicketWidget::SubwayTicketWidget(QWidget *parent) {
    initUI();
    initConnect();
}

SubwayTicketWidget::~SubwayTicketWidget() {

}

void SubwayTicketWidget::initUI() {
    QLabel *label_start = new QLabel("起点: ");
    QLabel *label_end = new QLabel("终点: ");
    QLabel *label_price = new QLabel("票价: ");
    QLabel *label_ticket_type = new QLabel("票种: ");


    line_edit_start_ = new QLineEdit;
    line_edit_end_ = new QLineEdit;
    line_edit_price_ = new QLineEdit;

    line_edit_start_->setReadOnly(true);
    line_edit_end_->setReadOnly(true);
    line_edit_price_->setReadOnly(true);
    line_edit_start_->setAlignment(Qt::AlignCenter);
    line_edit_end_->setAlignment(Qt::AlignCenter);
    line_edit_price_->setAlignment(Qt::AlignCenter);

    radio_button_normal_ = new QRadioButton("普通票（原价）");
    radio_button_student_ = new QRadioButton("学生票（9折优惠）");
    radio_button_old_ = new QRadioButton("老年票（免费乘坐）");
    radio_button_child_ = new QRadioButton("儿童票（五折优惠）");
    radio_button_travel_1_ = new QRadioButton("1日旅游票（15元）");
    radio_button_travel_3_ = new QRadioButton("3日旅游票（30元）");
    radio_button_travel_5_ = new QRadioButton("5日旅游票（50元）");
    radio_button_travel_7_ = new QRadioButton("7日旅游票（70元）");

    button_group_ticket_type_ = new QButtonGroup;
    button_group_ticket_type_->addButton(radio_button_normal_, 0);
    button_group_ticket_type_->addButton(radio_button_student_, 1);
    button_group_ticket_type_->addButton(radio_button_old_, 2);
    button_group_ticket_type_->addButton(radio_button_child_, 3);
    button_group_ticket_type_->addButton(radio_button_travel_1_, 4);
    button_group_ticket_type_->addButton(radio_button_travel_3_, 5);
    button_group_ticket_type_->addButton(radio_button_travel_5_, 6);
    button_group_ticket_type_->addButton(radio_button_travel_7_, 7);
    radio_button_normal_->setChecked(true);

    button_buy_ = new QPushButton("购买");

    auto *layout = new QGridLayout;
    layout->addWidget(label_start, 0, 0);
    layout->addWidget(label_end, 1, 0);
    layout->addWidget(label_price, 2, 0);
    layout->addWidget(line_edit_start_, 0, 1);
    layout->addWidget(line_edit_end_, 1, 1);
    layout->addWidget(line_edit_price_, 2, 1);
    layout->addWidget(label_ticket_type, 3, 0, 1, 2);
    layout->addWidget(radio_button_normal_, 4, 0);
    layout->addWidget(radio_button_student_, 4, 1);
    layout->addWidget(radio_button_old_, 5, 0);
    layout->addWidget(radio_button_child_, 5, 1);
    layout->addWidget(radio_button_travel_1_, 6, 0);
    layout->addWidget(radio_button_travel_3_, 6, 1);
    layout->addWidget(radio_button_travel_5_, 7, 0);
    layout->addWidget(radio_button_travel_7_, 7, 1);
    layout->addWidget(button_buy_, 8, 0, 1, 2);

    setLayout(layout);
}

void SubwayTicketWidget::initConnect() {
    connect(button_buy_, &QPushButton::clicked, this, [=]() {
        if (line_edit_start_->text().isEmpty()) {
            QMessageBox::warning(this, "购买失败", "请先选择起点站和终点站！");
            return;
        }
        if (line_edit_start_->text() == line_edit_end_->text() && button_group_ticket_type_->checkedId() < 4) {
            QMessageBox::warning(this, "购买失败", "起点站和终点站不能相同！");
            return;
        }
        QMessageBox::information(this, "购买成功", "购买成功！\n花费" + QString::number(line_edit_price_->text().toDouble(), 'f', 2) + "元。");
    });

    connect(button_group_ticket_type_, &QButtonGroup::idClicked, this, [=](int id) {
        if (line_edit_price_->text().isEmpty()) {
            return;
        }

        switch (id) {
            case 0:
                line_edit_price_->setText(QString::number(price_, 'f', 2));
                break;
            case 1:
                line_edit_price_->setText(QString::number(price_ * 0.8, 'f', 2));
                break;
            case 2:
                line_edit_price_->setText(QString::number(0, 'f', 2));
                break;
            case 3:
                line_edit_price_->setText(QString::number(price_ * 0.5, 'f', 2));
                break;
            case 4:
                line_edit_price_->setText(QString::number(15, 'f', 2));
                break;
            case 5:
                line_edit_price_->setText(QString::number(30, 'f', 2));
                break;
            case 6:
                line_edit_price_->setText(QString::number(50, 'f', 2));
                break;
            case 7:
                line_edit_price_->setText(QString::number(70, 'f', 2));
                break;
            default:
                break;
        }
    });
}

void SubwayTicketWidget::setAll(const QString& start, const QString& end, double price) {
    line_edit_start_->setText(start);
    line_edit_end_->setText(end);
    line_edit_price_->setText(QString::number(price, 'f', 2));
    price_ = price;
}
