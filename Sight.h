//
// Created by Noah on 2023/12/15.
//

#ifndef SUBWAY_SYSTEM_SIGHT_H
#define SUBWAY_SYSTEM_SIGHT_H


#include <QString>

class Sight {
private:
    int id_;
    QString name_;
    QString description_;
    double price_;

    int related_station_id_;

public:
    Sight(int id, const QString& name, const QString& description, double price, int related_station_id);

    int getId() const;
    const QString& getName() const;
    const QString& getDescription() const;
    double getPrice() const;
    int getRelatedStationId() const;
};


#endif //SUBWAY_SYSTEM_SIGHT_H
