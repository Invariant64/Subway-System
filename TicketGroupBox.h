//
// Created by Noah on 2023/11/19.
//

#ifndef SUBWAY_SYSTEM_TICKETGROUPBOX_H
#define SUBWAY_SYSTEM_TICKETGROUPBOX_H


#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class TicketGroupBox : public QGroupBox {
    Q_OBJECT

private:
    QLabel *label_start_;
    QLabel *label_end_;
    QLabel *label_price_;
    QLineEdit *line_edit_start_;
    QLineEdit *line_edit_end_;
    QLineEdit *line_edit_price_;

    double price_;

    void initUI();
    void initConnect();

public:
    QPushButton *button_open_ticket_window_;

    TicketGroupBox();
    ~TicketGroupBox();

    void setAll(QString start, QString end, double price);

    bool isEmpty() const;

    double getPrice() const;
};


#endif //SUBWAY_SYSTEM_TICKETGROUPBOX_H
