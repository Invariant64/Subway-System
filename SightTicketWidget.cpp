//
// Created by Noah on 2023/12/16.
//

#include <QMessageBox>
#include <qgridlayout.h>
#include <QGraphicsProxyWidget>
#include "SightTicketWidget.h"

SightTicketWidget::SightTicketWidget(QWidget *parent) {
    sight_blocks_ = new QList<QGraphicsProxyWidget*>;
    next_block_y_ = 0;

    initUI();
    initConnect();
}

SightTicketWidget::~SightTicketWidget() {

}

void SightTicketWidget::initUI() {
    combo_box_sight_ = new QComboBox(this);
    combo_box_sight_->setEditable(true);
    combo_box_sight_->lineEdit()->setAlignment(Qt::AlignCenter);
    button_search_ = new QPushButton("查询", this);

    QLabel *label_sight_name = new QLabel("景点名称: ", this);
    line_edit_sight_name_ = new QLineEdit(this);
    line_edit_sight_name_->setPlaceholderText("未找到景点");
    line_edit_sight_name_->setAlignment(Qt::AlignCenter);
    line_edit_sight_name_->setReadOnly(true);
    line_edit_sight_name_->setFocusPolicy(Qt::NoFocus);

    QLabel *label_station_name = new QLabel("站点名称: ", this);
    line_edit_station_name_ = new QLineEdit(this);
    line_edit_station_name_->setPlaceholderText("未找到站点");
    line_edit_station_name_->setAlignment(Qt::AlignCenter);
    line_edit_station_name_->setReadOnly(true);
    line_edit_station_name_->setFocusPolicy(Qt::NoFocus);

    QLabel *label_sight_price = new QLabel("景点价格: ", this);
    line_edit_sight_price_ = new QLineEdit(this);
    line_edit_sight_price_->setAlignment(Qt::AlignCenter);
    line_edit_sight_price_->setReadOnly(true);
    line_edit_sight_price_->setFocusPolicy(Qt::NoFocus);

    QLabel *label_sight_description = new QLabel("备注: ", this);
    line_edit_sight_description_ = new QLineEdit(this);
    line_edit_sight_description_->setAlignment(Qt::AlignCenter);
    line_edit_sight_description_->setReadOnly(true);
    line_edit_sight_description_->setFocusPolicy(Qt::NoFocus);

    button_add_ = new QPushButton("添加", this);

    graphics_view_ = new QGraphicsView(this);
    QGraphicsScene *scene = new QGraphicsScene;
    graphics_view_->setScene(scene);
    graphics_view_->setFixedSize(650, 300);

    QLabel *label_start = new QLabel("起点地铁站: ", this);
    line_edit_start_ = new QLineEdit(this);
    line_edit_start_->setAlignment(Qt::AlignCenter);
    line_edit_start_->setReadOnly(true);
    line_edit_start_->setFocusPolicy(Qt::NoFocus);

    QLabel *label_end = new QLabel("终点地铁站: ", this);
    line_edit_end_ = new QLineEdit(this);
    line_edit_end_->setAlignment(Qt::AlignCenter);
    line_edit_end_->setReadOnly(true);
    line_edit_end_->setFocusPolicy(Qt::NoFocus);

    button_search_path_ = new QPushButton("规划最佳出行路线", this);

    QLabel *label_time = new QLabel("出行耗时: ", this);
    line_edit_time_ = new QLineEdit(this);
    line_edit_time_->setAlignment(Qt::AlignCenter);
    line_edit_time_->setReadOnly(true);
    line_edit_time_->setFocusPolicy(Qt::NoFocus);
    QLabel *label_time_unit = new QLabel("分钟", this);

    QLabel *label_cost = new QLabel("景点花费: ", this);
    line_edit_cost_ = new QLineEdit(this);
    line_edit_cost_->setAlignment(Qt::AlignCenter);
    line_edit_cost_->setReadOnly(true);
    line_edit_cost_->setFocusPolicy(Qt::NoFocus);
    QLabel *label_cost_unit = new QLabel("元", this);

    auto *layout_search = new QHBoxLayout;
    layout_search->addWidget(combo_box_sight_);
    layout_search->addWidget(button_search_);

    auto *layout_sight_add = new QHBoxLayout;
    layout_sight_add->addWidget(label_sight_name);
    layout_sight_add->addWidget(line_edit_sight_name_);
    layout_sight_add->addWidget(label_station_name);
    layout_sight_add->addWidget(line_edit_station_name_);
    layout_sight_add->addWidget(label_sight_price);
    layout_sight_add->addWidget(line_edit_sight_price_);
    layout_sight_add->addWidget(button_add_);

    auto *layout_sight_description = new QHBoxLayout;
    layout_sight_description->addWidget(label_sight_description);
    layout_sight_description->addWidget(line_edit_sight_description_);

    auto *layout_start_end = new QHBoxLayout;
    layout_start_end->addWidget(label_start);
    layout_start_end->addWidget(line_edit_start_);
    layout_start_end->addWidget(label_end);
    layout_start_end->addWidget(line_edit_end_);
    layout_start_end->addWidget(button_search_path_);

    auto *layout_time_cost = new QHBoxLayout;
    layout_time_cost->addWidget(label_time);
    layout_time_cost->addWidget(line_edit_time_);
    layout_time_cost->addWidget(label_time_unit);
    layout_time_cost->addWidget(label_cost);
    layout_time_cost->addWidget(line_edit_cost_);
    layout_time_cost->addWidget(label_cost_unit);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(layout_search);
    layout->addLayout(layout_sight_add);
    layout->addLayout(layout_sight_description);
    layout->addLayout(layout_start_end);
    layout->addWidget(graphics_view_);
    layout->addLayout(layout_time_cost);

    setLayout(layout);
}

void SightTicketWidget::initConnect() {
    connect(button_search_, &QPushButton::clicked, this, [=]() {
        if (combo_box_sight_->currentText().isEmpty()) {
            QMessageBox::warning(this, "搜索失败", "请输入景点名称");
            return;
        }
        auto station = net_->getStationBySightName(combo_box_sight_->currentText());
        if (station == nullptr) {
            QMessageBox::warning(this, "搜索失败", "未找到该景点");
            return;
        }
        Sight *sight = net_->getSights()->value(combo_box_sight_->currentText());
        line_edit_sight_name_->setText(sight->getName());
        line_edit_station_name_->setText(station->getName());
        line_edit_sight_price_->setText(QString::number(sight->getPrice(), 'f', 2));
        line_edit_sight_description_->setText(sight->getDescription());
    });

    connect(button_add_, &QPushButton::clicked, this, [=]() {
        if (line_edit_sight_name_->text().isEmpty()) {
            QMessageBox::warning(this, "添加失败", "请先确定景点");
            return;
        }

        // 检测是否已经添加过该景点
        for (const auto &sight_block : *sight_blocks_) {
            if (((SightBlock*) sight_block->widget())->getSightName() == line_edit_sight_name_->text()) {
                QMessageBox::warning(this, "添加失败", "该景点已经添加过了");
                return;
            }
        }

        auto sight_block = new SightBlock;
        sight_block->setAll(line_edit_sight_name_->text(), line_edit_station_name_->text(), line_edit_sight_price_->text().toDouble());
        QGraphicsProxyWidget *proxy = graphics_view_->scene()->addWidget(sight_block);
        proxy->setPos(0, next_block_y_);
        sight_blocks_->append(proxy);
        repaintBlocks();

        connect(sight_block->button_up_, &QPushButton::clicked, this, [=]() {
            int index = sight_blocks_->indexOf(proxy);
            if (index == 0) {
                return;
            }
            sight_blocks_->move(index, index - 1);
            repaintBlocks();
        });

        connect(sight_block->button_down_, &QPushButton::clicked, this, [=]() {
            int index = sight_blocks_->indexOf(proxy);
            if (index == sight_blocks_->size() - 1) {
                return;
            }
            sight_blocks_->move(index, index + 1);
            repaintBlocks();
        });

        connect(sight_block->button_delete_, &QPushButton::clicked, this, [=]() {
            sight_blocks_->removeOne(proxy);
            graphics_view_->scene()->removeItem(proxy);
            repaintBlocks();
        });
    });

    connect(button_search_path_, &QPushButton::clicked, this, [=]() {
        if (line_edit_start_->text().isEmpty() || line_edit_end_->text().isEmpty()) {
            QMessageBox::warning(this, "规划失败", "请先选择起点站和终点站！");
            return;
        }
        scheduleBestPath();
        QMessageBox::information(this, "规划完毕", "规划完毕！");
    });
}

void SightTicketWidget::setNet(Net *net) {
    net_ = net;

    auto sights = net_->getSights();
    QStringList sight_list;
    for (const auto &sight : *sights) {
        sight_list << sight->getName();
        combo_box_sight_->addItem(sight->getName());
    }
    completer_ = new QCompleter(sight_list, this);
    completer_->setMaxVisibleItems(7);
    completer_->setFilterMode(Qt::MatchContains);
    combo_box_sight_->setCompleter(completer_);
    combo_box_sight_->lineEdit()->setPlaceholderText("请输入景点名称");

    combo_box_sight_->clearEditText();
}

void SightTicketWidget::repaintBlocks() {
    next_block_y_ = 0;
    for (const auto &sight_block : *sight_blocks_) {
        sight_block->setPos(0, next_block_y_);
        next_block_y_ += sight_block->widget()->height() - 40;
    }

    double time = 0;
    double cost = 0;
    QList<Edge*> temp_path;
    time += net_->getShortestPath(line_edit_start_->text(), ((SightBlock*) sight_blocks_->first()->widget())->getStationName(), temp_path, 0);
    for (int i = 0; i < sight_blocks_->size() - 1; i++) {
        time += net_->getShortestPath(((SightBlock*) sight_blocks_->at(i)->widget())->getStationName(),
                                      ((SightBlock*) sight_blocks_->at(i + 1)->widget())->getStationName(),
                                      temp_path, 0);
        cost += ((SightBlock*) sight_blocks_->at(i)->widget())->getPrice();
    }
    time += net_->getShortestPath(((SightBlock*) sight_blocks_->last()->widget())->getStationName(), line_edit_end_->text(), temp_path, 0);
    cost += ((SightBlock*) sight_blocks_->last()->widget())->getPrice();

    line_edit_time_->setText(QString::number(time / 60, 'f', 2));
    line_edit_cost_->setText(QString::number(cost, 'f', 2));
}

void SightTicketWidget::setAll(const QString &start, const QString &end) {
    line_edit_start_->setText(start);
    line_edit_end_->setText(end);
}

void SightTicketWidget::scheduleBestPath() {
    QString start = line_edit_start_->text();
    QString end = line_edit_end_->text();

    QList<QString> sights_station;
    for (const auto &sight_block : *sight_blocks_) {
        sights_station.append(((SightBlock*) sight_block->widget())->getStationName());
    }

    // 遍历所有可能的路径，从全排列找出最佳路径
    double min_weight = 100000000;
    QList<QString> min_path;

    std::vector<int> arr;
    for (int i = 0; i < sights_station.size(); i++) {
        arr.push_back(i);
    }

    do {
        QList<QString> temp;
        temp.append(start);
        for (int i : arr) {
            temp.append(sights_station[i]);
        }
        temp.append(end);
        QList<Edge*> temp_path;
        double weight = 0;
        for (int j = 0; j < temp.size() - 1; j++) {
            weight += net_->getShortestPath(temp[j], temp[j + 1], temp_path, 0);
        }
        if (weight < min_weight) {
            min_weight = weight;
            min_path = temp;
        }
    } while (std::next_permutation(arr.begin(), arr.end()));

    for (int i = 1; i < min_path.size() - 1; i++) {
        for (const auto &sight_block : *sight_blocks_) {
            if (((SightBlock*) sight_block->widget())->getStationName() == min_path[i]) {
                sight_blocks_->swapItemsAt(i - 1, sight_blocks_->indexOf(sight_block));
                break;
            }
        }
    }

    repaintBlocks();
}
