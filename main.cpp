#include <QApplication>
#include <iostream>
#include "Net.h"
#include "MainWindow.h"

#define Station_File_Path "/Users/noah/Projects/Subway-System/net-data/data.station"
#define Edge_File_Path "/Users/noah/Projects/Subway-System/net-data/data.edge"
#define Line_File_Path "/Users/noah/Projects/Subway-System/net-data/data.line"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow main_window;

    Net *net = new Net(Station_File_Path, Edge_File_Path, Line_File_Path);
    main_window.init(net);

    main_window.show();

    return QApplication::exec();
}


