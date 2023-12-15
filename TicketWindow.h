//
// Created by Noah on 2023/12/15.
//

#ifndef SUBWAY_SYSTEM_TICKETWINDOW_H
#define SUBWAY_SYSTEM_TICKETWINDOW_H


#include <QWidget>
#include "Net.h"

class TicketWindow : public QWidget {
    Q_OBJECT
private:
    Net *net_;

public:
    explicit TicketWindow(QWidget *parent = nullptr);
    ~TicketWindow() override;

    void setNet(Net *net);
};


#endif //SUBWAY_SYSTEM_TICKETWINDOW_H
