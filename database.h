#ifndef DATABASE_H
#define DATABASE_H
#include "QString"

class database
{
public:
    database();

    QString database_connection(QString username, QString password);
    QVariantList interface_constructor_fetch(QString username);
    void process_completed_button_function(QString fuelType, double salePrice, double fuelSupplied, double feeReceived, int pumpNumber, int adminID, int stationID, QString stationName);
    void initial_database_definition();
};

#endif // DATABASE_H
