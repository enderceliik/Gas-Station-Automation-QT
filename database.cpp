// https://github.com/Enderceliik
// Ender CELIK

#include "database.h"
#include <QtSql>
#include "QString"
#include <QSqlQueryModel>

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
            query.next();
            qDebug() << "Sorgu gerçekleştirildi";
        }
        else
        {
            qDebug() << query.lastError().text()  + " giriş hatası";
            return "Bağlanılamadı";
        } 
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

QMap<QString, QVariant> database::interface_constructor_fetch(QString username)
{
    QMap <QString, QVariant> interfaceInfoMap;
    QSqlQuery query;
    query.prepare("select userID, stationID from users where username = :username");
    query.bindValue(":username", username);
    if(query.exec())
    {
        query.next();
        interfaceInfoMap.insert("userID", query.value(0).toInt());
        interfaceInfoMap.insert("stationID", query.value(1).toInt());
        qDebug() << "Sorgu gerçekleştirildi";
    }
    else
    {
        qDebug() << query.lastError().text()  + " username sorgu hatası";
    }
    query.prepare("select stationName, pumpSize from stations where stationID = :stationID");
    query.bindValue(":stationID", interfaceInfoMap.value("stationID"));
    if(query.exec())
    {
        query.next();
        interfaceInfoMap.insert("stationName", query.value(0).toString());
        interfaceInfoMap.insert("pumpSize", query.value(1).toInt());
        qDebug() << "Sorgu gerçekleştirildi";
    }
    else
    {
        qDebug() << query.lastError().text()  + " stationID sorgu hatası";
    }
    query.prepare("select * from fuel_prices");
    if(query.exec())
    {
        query.next();
        interfaceInfoMap.insert("lpg", query.value(0).toDouble());
        interfaceInfoMap.insert("diesel", query.value(1).toDouble());
        interfaceInfoMap.insert("gasoline", query.value(2).toDouble());
        qDebug() << "Sorgu gerçekleştirildi";
    }
    else
    {
        qDebug() << query.lastError().text()  + " stationID sorgu hatası";
    }
    return interfaceInfoMap;
}

void database::process_completed_button_function(QMap<QString,QVariant> saleDatabaseMap)
{
    QSqlQuery query;
    query.prepare("insert into sales (stationName, feeReceived, fuelSupplied, pumpNumber, fuelType, salePrice, userID, stationID) values (:stationName, :feeReceived, :fuelSupplied, :pumpNumber,:fuelType, :salePrice, :userID, :stationID)");
    query.bindValue(":stationName", saleDatabaseMap.value("stationName"));
    query.bindValue(":feeReceived", saleDatabaseMap.value("feeReceived"));
    query.bindValue(":fuelSupplied", saleDatabaseMap.value("fuelSupplied"));
    query.bindValue(":pumpNumber", saleDatabaseMap.value("pumpNumber"));
    query.bindValue(":fuelType", saleDatabaseMap.value("fuelType"));
    query.bindValue(":salePrice", saleDatabaseMap.value("salePrice"));
    query.bindValue(":stationID", saleDatabaseMap.value("stationID"));
    query.bindValue(":userID", saleDatabaseMap.value("userID"));
    if(query.exec())
    {
        qDebug() << "insert stations table!";
    }
    else
    {
        qDebug() << query.lastError().text()  + "insert sales error";
    }

    query.prepare("update stations set totalSales = totalSales + :feeReceived where stationID = :stationID");
    query.bindValue(":stationID", saleDatabaseMap.value("stationID"));
    query.bindValue(":feeReceived", saleDatabaseMap.value("feeReceived"));
    if(query.exec())
    {
        qDebug() << "UPDATE stations table!";
    }
    else
    {
        qDebug() << query.lastError().text()  + "update totalSales error";
    }
    if(saleDatabaseMap.value("fuelType") == "LPG")
    {
        query.prepare("update stations set totalFuelSuppliedLPG = totalFuelSuppliedLPG + :fuelSupplied where stationID = :stationID");
    }
    else if(saleDatabaseMap.value("fuelType") == "Diesel")
    {
        query.prepare("update stations set totalFuelSuppliedDiesel = totalFuelSuppliedDiesel + :fuelSupplied where stationID = :stationID");
    }
    else
    {
        query.prepare("update stations set totalFuelSuppliedGasoline = totalFuelSuppliedGasoline + :fuelSupplied where stationID = :stationID");

    }
    query.bindValue(":stationID", saleDatabaseMap.value("stationID"));
    query.bindValue(":fuelSupplied", saleDatabaseMap.value("fuelSupplied"));
    if(query.exec())
    {
        qDebug() << "UPDATE stations table!";
    }
    else
    {
        qDebug() << query.lastError().text()  + "update totalFuelSupplied error";
    }
}

QSqlQueryModel* database::database_query(QString parameter)
{
    QString query = QString("SELECT * FROM '%1'").arg(parameter);
    QSqlQueryModel *model  = new QSqlQueryModel();
    model->setQuery(query);
    return model;
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
            "userID INTEGER PRIMARY KEY AUTOINCREMENT,"
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
            "saleID INTEGER PRIMARY KEY AUTOINCREMENT,"
            "saleDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
            "stationName VARCHAR(50),"
            "feeReceived DOUBLE,"
            "fuelSupplied DOUBLE,"
            "pumpNumber INT,"
            "fuelType VARCHAR(3),"
            "salePrice DOUBLE,"
            "userID INT,"
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


