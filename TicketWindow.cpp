//
// Created by Noah on 2023/12/15.
//

#include <QHBoxLayout>
#include "TicketWindow.h"

TicketWindow::TicketWindow(QWidget *parent) : QWidget(parent) {
    initUI();
    initConnect();
}

TicketWindow::~TicketWindow() {

}

void TicketWindow::setNet(Net *net) {
    this->net_ = net;
    sight_ticket_widget_->setNet(net);
}

void TicketWindow::initUI() {
    tab_widget_ = new QTabWidget;
    subway_ticket_widget_ = new SubwayTicketWidget;
    sight_ticket_widget_ = new SightTicketWidget;

    tab_widget_->addTab(subway_ticket_widget_, "地铁票");
    tab_widget_->addTab(sight_ticket_widget_, "景点票");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tab_widget_);

    setLayout(layout);

    tab_widget_->widget(0)->adjustSize();
    tab_widget_->setFixedSize(tab_widget_->widget(0)->width() + 20, tab_widget_->widget(0)->height() + 20);
    setFixedSize(tab_widget_->width() + 40, tab_widget_->height() + 40);
}

void TicketWindow::initConnect() {
    connect(tab_widget_, &QTabWidget::currentChanged, this, [=](int index) {
        tab_widget_->widget(index)->adjustSize();
        tab_widget_->setFixedSize(tab_widget_->widget(index)->width() + 20, tab_widget_->widget(index)->height() + 20);
        setFixedSize(tab_widget_->width() + 40, tab_widget_->height() + 40);
    });
}

void TicketWindow::setAll(const QString &start, const QString &end, double price) {
    subway_ticket_widget_->setAll(start, end, price);
    sight_ticket_widget_->setAll(start, end);
}
