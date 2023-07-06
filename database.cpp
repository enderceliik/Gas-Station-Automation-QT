// https://github.com/Enderceliik
// Ender CELIK

#include "database.h"
#include <QtSql>
#include "QString"
database::database()
{

}

QString database::database_connection(QString username, QString password)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("my_database.sqlite");
    if (!database.open()) {
        return "Veri tabanına bağlanılamadı";
    }
    else
    {
        QSqlQuery query;
        query.prepare("select password, userType from users where username = :username");
        query.bindValue(":username", username);
        if(query.exec())
        {
            qDebug() << "Sorgu gerçekleştirildi";
        }
        else
        {
            qDebug() << query.lastError().text()  + " giriş hatası";
        }
        query.next();
        if(password == query.value(0).toString())
        {
            return query.value(1).toString();
        }
        else
        {
            return "Şifre hatalı";
        }
    }

}

QVariantList database::interface_constructor_fetch(QString username)
{
    QVariantList mylist;
    QSqlQuery query;
    query.prepare("select adminID, stationID from users where username = :username");
    query.bindValue(":username", username);
    if(query.exec())
    {
        qDebug() << "Sorgu gerçekleştirildi";
    }
    else
    {
        qDebug() << query.lastError().text()  + " username sorgu hatası";
    }
    query.next();
    int adminID = query.value(0).toInt();
    int stationID = query.value(1).toInt();
    qDebug() << QString::number(stationID) + " STATION ";
    mylist.append(adminID);
    mylist.append(stationID);
    query.prepare("select stationName, pumpSize from stations where stationID = :stationID");
    query.bindValue(":stationID",stationID);
    if(query.exec())
    {
        qDebug() << "Sorgu gerçekleştirildi";
    }
    else
    {
        qDebug() << query.lastError().text()  + " stationID sorgu hatası";
    }
    query.next();
    QString stationName = query.value(0).toString();
    int pumpSize = query.value(1).toInt();
    mylist.append(stationName);
    mylist.append(pumpSize);

    query.prepare("select * from fuel_prices");
    if(query.exec())
    {
        qDebug() << "Sorgu gerçekleştirildi";
    }
    else
    {
        qDebug() << query.lastError().text()  + " stationID sorgu hatası";
    }
    query.next();
    double lpg = query.value(0).toDouble();
    double diesel = query.value(1).toDouble();
    double gasoline = query.value(2).toDouble();
    mylist.append(lpg);
    mylist.append(diesel);
    mylist.append(gasoline);
    return mylist;
}

void database::process_completed_button_function(QString fuelType, double salePrice, double fuelSupplied, double feeReceived, int pumpNumber, int adminID, int stationID, QString stationName)
{
    qDebug() << QString::number(stationID) + " ------ ";
    QSqlQuery query;
    query.prepare("insert into sales (stationName, feeReceived, fuelSupplied, pumpNumber, fuelType, salePrice, officerID, stationID) values (:stationName, :feeReceived, :fuelSupplied, :pumpNumber,:fuelType, :salePrice, :adminID, :stationID)");
    query.bindValue(":stationName", stationName);
    query.bindValue(":feeReceived", feeReceived);
    query.bindValue(":fuelSupplied", fuelSupplied);
    query.bindValue(":pumpNumber", pumpNumber);
    query.bindValue(":fuelType", fuelType);
    query.bindValue(":salePrice", salePrice);
    query.bindValue(":stationID", stationID);
    query.bindValue(":adminID", adminID);

    if(query.exec())
    {
        qDebug() << "insert stations table!";
    }
    else
    {
        qDebug() << query.lastError().text()  + "insert sales error";
    }

    query.prepare("update stations set totalSales = totalSales + :feeReceived where stationID = :stationID");
    query.bindValue(":stationID", stationID);
    query.bindValue(":feeReceived", feeReceived);
    if(query.exec())
    {
        qDebug() << "UPDATE stations table!";
    }
    else
    {
        qDebug() << query.lastError().text()  + "update totalSales error";
    }
    qDebug() << fuelType;
    if(fuelType == "LPG")
    {
        query.prepare("update stations set totalFuelSuppliedLPG = totalFuelSuppliedLPG + :fuelSupplied where stationID = :stationID");
    }
    else if(fuelType == "Diesel")
    {
        query.prepare("update stations set totalFuelSuppliedDiesel = totalFuelSuppliedDiesel + :fuelSupplied where stationID = :stationID");
    }
    else
    {
        query.prepare("update stations set totalFuelSuppliedGasoline = totalFuelSuppliedGasoline + :fuelSupplied where stationID = :stationID");

    }
    query.bindValue(":stationID", stationID);
    query.bindValue(":fuelSupplied", fuelSupplied);
    if(query.exec())
    {
        qDebug() << "UPDATE stations table!";
    }
    else
    {
        qDebug() << query.lastError().text()  + "update totalFuelSupplied error";
    }
}

void database::initial_database_definition()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("my_database.sqlite");
    if (!database.open()) {
        return;
    }
    else
    {
        QSqlQuery query;
        query.prepare(
            "create table fuel_prices(lpg DOUBLE, diesel DOUBLE, gasoline DOUBLE)");
        if(query.exec())
        {
            qDebug() << "fuel_prices created succesfully!";
        }
        else
        {
            qDebug() << query.lastError().text() + " users table";
        }
        query.prepare(
            "insert into fuel_prices(lpg, diesel, gasoline) values (11.73, 23.95, 26.19)");
        if(query.exec())
        {
            qDebug() << "fuel_prices insert succesfully!";
        }
        else
        {
            qDebug() << query.lastError().text() + " users table";
        }
        query.prepare(
            "create table users ("
            "adminID INTEGER PRIMARY KEY AUTOINCREMENT,"
            "username VARCHAR(50),"
            "password VARCHAR(16),"
            "userType INT,"
            "stationID INTEGER"
            ")");
        if(query.exec())
        {
            qDebug() << "admins created succesfully!";
        }
        else
        {
            qDebug() << query.lastError().text() + " users table";
        }
        query.prepare(
            "create table stations ("
            "stationID INTEGER PRIMARY KEY AUTOINCREMENT,"
            "stationName VARCHAR(50),"
            "totalSales DOUBLE,"
            "totalFuelSuppliedLPG DOUBLE,"
            "totalFuelSuppliedDiesel DOUBLE,"
            "totalFuelSuppliedGasoline DOUBLE,"
            "pumpSize INT"
            ")");
        if(query.exec())
        {
            qDebug() << "stations created succesfully!";
        }
        else
        {
            qDebug() << query.lastError().text()  + "admins table";
        }

        query.prepare(
            "CREATE TABLE sales ("
            "salesID INTEGER PRIMARY KEY AUTOINCREMENT,"
            "saleDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
            "stationName VARCHAR(50),"
            "feeReceived DOUBLE,"
            "fuelSupplied DOUBLE,"
            "pumpNumber INT," // dzlt
            "fuelType VARCHAR(3),"
            "salePrice DOUBLE,"
            "officerID INT,"
            "stationID INT,"
            "FOREIGN KEY(stationID) REFERENCES stations(stationID)"
            ")");
        if(query.exec())
        {
            qDebug() << "sales created succesfully!";
        }
        else
        {
            qDebug() << query.lastError().text()  + "sales table";
        }
        query.prepare("insert into users (username, password, userType, stationID) values ('ecelik', '123*', 1, 0)");
        if(query.exec())
        {
            qDebug() << "user insert succesfully!";
        }
        else
        {
            qDebug() << query.lastError().text()  + " user insert";
        }
        query.prepare("insert into users (username, password, userType, stationID) values ('celik1', '321*', 0, 1)");
        if(query.exec())
        {
            qDebug() << "user insert succesfully! 2";
        }
        else
        {
            qDebug() << query.lastError().text()  + " user insert";
        }
        query.prepare("insert into users (username, password, userType, stationID) values ('celik2', '654*', 0, 1)");
        if(query.exec())
        {
            qDebug() << "user insert succesfully! 2";
        }
        else
        {
            qDebug() << query.lastError().text()  + " user insert";
        }
        query.prepare("insert into stations (stationName, totalSales, totalFuelSuppliedLPG, totalFuelSuppliedDiesel ,totalFuelSuppliedGasoline ,pumpSize) values ('CelikGas', 0.0, 0.0, 0.0, 0.0, 6);");
        if(query.exec())
        {
            qDebug() << "insert stations table!";
        }
        else
        {
            qDebug() << query.lastError().text()  + "insert station error";
        }
        query.prepare("insert into stations (stationName, totalSales, totalFuelSuppliedLPG, totalFuelSuppliedDiesel ,totalFuelSuppliedGasoline ,pumpSize) values ('tp', 0.0, 0.0, 0.0, 0.0, 4);");
        if(query.exec())
        {
            qDebug() << "insert stations table!";
        }
        else
        {
            qDebug() << query.lastError().text()  + "insert station error";
        }
        query.prepare("insert into users (username, password, userType, stationID) values ('tp1', '321*', 0, 2)");
        if(query.exec())
        {
            qDebug() << "user insert succesfully! 2";
        }
        else
        {
            qDebug() << query.lastError().text()  + " user insert";
        }
    }
}


