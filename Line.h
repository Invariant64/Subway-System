//
// Created by Noah on 2023/10/10.
//

#ifndef SUBWAY_SYSTEM_LINE_H
#define SUBWAY_SYSTEM_LINE_H


#include <QString>

class Line {
private:
    int id_;
    QString name_;

public:
    Line() = default;
    ~Line() = default;
    Line(int id, QString name);

    int getId() const;
    QString getName() const;
};


#endif //SUBWAY_SYSTEM_LINE_H
