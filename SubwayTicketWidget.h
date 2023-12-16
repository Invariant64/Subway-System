//
// Created by Noah on 2023/12/16.
//

#ifndef SUBWAY_SYSTEM_SUBWAYTICKETWIDGET_H
#define SUBWAY_SYSTEM_SUBWAYTICKETWIDGET_H


#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include "PathInfoBox.h"
#include "TicketGroupBox.h"

class SubwayTicketWidget : public QWidget {
    Q_OBJECT

private:
    QLineEdit *line_edit_start_;
    QLineEdit *line_edit_end_;
    QRadioButton *radio_button_normal_;
    QRadioButton *radio_button_student_;
    QRadioButton *radio_button_old_;
    QRadioButton *radio_button_child_;
    QRadioButton *radio_button_travel_1_;
    QRadioButton *radio_button_travel_3_;
    QRadioButton *radio_button_travel_5_;
    QRadioButton *radio_button_travel_7_;
    QLineEdit *line_edit_price_;
    QPushButton *button_buy_;

    QButtonGroup *button_group_ticket_type_;

    double price_;

    void initUI();
    void initConnect();

public:
    explicit SubwayTicketWidget(QWidget *parent = nullptr);
    ~SubwayTicketWidget() override;

    void setAll(const QString& start, const QString& end, double price);
};


#endif //SUBWAY_SYSTEM_SUBWAYTICKETWIDGET_H
