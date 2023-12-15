//
// Created by Noah on 2023/12/15.
//

#include "TicketWindow.h"

TicketWindow::TicketWindow(QWidget *parent) : QWidget(parent) {}

TicketWindow::~TicketWindow() {

}

void TicketWindow::setNet(Net *net) {
    this->net_ = net;
}
