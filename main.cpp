#include <QApplication>
#include <iostream>
#include "MainWindow.h"
#include "Net.h"

#define Test_Station_File_Path "/Users/noah/Projects/Subway-System/net-data/test.station"
#define Test_Edge_File_Path "/Users/noah/Projects/Subway-System/net-data/test.edge"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow main_window;
    main_window.show();

    Net net(Test_Station_File_Path, Test_Edge_File_Path);

    QMap<int, Station> *stations = net.getStations();
    for (const auto& station : *stations) {
        qDebug() << station.getId() << station.getName() << station.getPosition() << "\n";
    }

    QMap<int, Edge> *edges = net.getEdges();
    for (const auto& edge : *edges) {
        qDebug() << edge.getId() << edge.getLineId() << edge.getStationId() << edge.getNextStationId()
                 << edge.getWeightTime() << edge.getWeightDistance() << "\n";
    }

    QList<int> time_path;
    qDebug() << "time cost is " << net.getShortestPath(1, 4, time_path, 0) << "\n";

    for (const auto& station_id : time_path) {
        qDebug() << station_id << "\n";
    }

    QList<int> distance_path;
    qDebug() << "distance cost is " << net.getShortestPath(1, 4, distance_path, 1) << "\n";

    for (const auto& station_id : distance_path) {
        qDebug() << station_id << "\n";
    }

    return QApplication::exec();
}


