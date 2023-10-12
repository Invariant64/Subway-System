#include <QApplication>
#include <iostream>
#include "MainWindow.h"
#include "Net.h"

#define Test_Station_File_Path "/Users/noah/Projects/Subway-System/net-data/test.station"
#define Test_Edge_File_Path "/Users/noah/Projects/Subway-System/net-data/test.edge"

#define Station_File_Path "/Users/noah/Projects/Subway-System/net-data/data.station"
#define Edge_File_Path "/Users/noah/Projects/Subway-System/net-data/data.edge"
#define Line_File_Path "/Users/noah/Projects/Subway-System/net-data/data.line"

void printPath(Net *net, const QList<int>& path) {
    if (path.size() <= 1) {
        return;
    }

    int last_line_id = -1;
    int line_id = net->getEdgeByStationId(path[0], path[1]).getLineId();

    for (int i = 0; i < path.size(); i++) {
        std::cout << net->getStationById(path[i]).getName().toStdString() << " ";
        if (i == 0) {
            std::cout << "(" << net->getLineById(line_id).getName().toStdString() << ") -> ";
            last_line_id = line_id;
        }
        else if (i != path.size() - 1) {
            line_id = net->getEdgeByStationId(path[i], path[i + 1]).getLineId();
            if (last_line_id != line_id && last_line_id != -1) {
                std::cout << "(从 " << net->getLineById(last_line_id).getName().toStdString()
                          << " 转乘至 " << net->getLineById(line_id).getName().toStdString() << ") ";
                last_line_id = line_id;
            }
            std::cout << "-> ";
        }
    }
}

int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);
//
//    MainWindow main_window;
//    main_window.show();

    Net net(Station_File_Path, Edge_File_Path, Line_File_Path);

    std::string from, to;
    std::cin >> from >> to;

    QList<int> time_path;
    std::cout << "time cost is " << net.getShortestPath(
            net.getStationIdByName(QString::fromStdString(from)),
            net.getStationIdByName(QString::fromStdString(to)),
            time_path, 1) << std::endl;

    printPath(&net, time_path);

//    return QApplication::exec();
    return 0;
}


