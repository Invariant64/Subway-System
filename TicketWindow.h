//
// Created by Noah on 2023/12/15.
//

#ifndef SUBWAY_SYSTEM_TICKETWINDOW_H
#define SUBWAY_SYSTEM_TICKETWINDOW_H


#include <QWidget>
#include <qtabwidget.h>
#include "Net.h"
#include "SubwayTicketWidget.h"
#include "SightTicketWidget.h"

class TicketWindow : public QWidget {
    Q_OBJECT
private:
    Net *net_;

    QTabWidget *tab_widget_;

    void initUI();
    void initConnect();

public:
    SubwayTicketWidget *subway_ticket_widget_;
    SightTicketWidget *sight_ticket_widget_;

    explicit TicketWindow(QWidget *parent = nullptr);
    ~TicketWindow() override;

    void setNet(Net *net);

    void setAll(const QString& start, const QString& end, double price);
};


#endif //SUBWAY_SYSTEM_TICKETWINDOW_H
