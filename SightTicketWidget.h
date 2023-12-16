//
// Created by Noah on 2023/12/16.
//

#ifndef SUBWAY_SYSTEM_SIGHTTICKETWIDGET_H
#define SUBWAY_SYSTEM_SIGHTTICKETWIDGET_H


#include <QWidget>
#include <QLineEdit>
#include <QCompleter>
#include <QComboBox>
#include <QGraphicsView>
#include "SightBlock.h"
#include "Net.h"

class SightTicketWidget : public QWidget {
    Q_OBJECT

private:
    QComboBox *combo_box_sight_;
    QCompleter *completer_;
    QPushButton *button_search_;

    QLineEdit *line_edit_sight_name_;
    QLineEdit *line_edit_station_name_;
    QLineEdit *line_edit_sight_price_;
    QLineEdit *line_edit_sight_description_;
    QPushButton *button_add_;

    QGraphicsView *graphics_view_;

    QList<QGraphicsProxyWidget*> *sight_blocks_;

    QLineEdit *line_edit_start_;
    QLineEdit *line_edit_end_;
    QPushButton *button_search_path_;

    QLineEdit *line_edit_time_;
    QLineEdit *line_edit_cost_;

    Net *net_;

    int next_block_y_;

    void initUI();
    void initConnect();

    void repaintBlocks();

public:
    explicit SightTicketWidget(QWidget *parent = nullptr);
    ~SightTicketWidget() override;

    void setNet(Net *net);

    void setAll(const QString& start, const QString& end);

    void scheduleBestPath();
};


#endif //SUBWAY_SYSTEM_SIGHTTICKETWIDGET_H
