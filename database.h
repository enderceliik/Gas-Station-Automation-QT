#ifndef DATABASE_H
#define DATABASE_H
#include "QString"
#include <QSqlQueryModel>
#include <QVariantList>
#include <QMap>
class database
{
public:
    database();

    QString database_connection(QString username, QString password);
    QMap<QString, QVariant> interface_constructor_fetch(QString username);
    void process_completed_button_function(QMap<QString,QVariant> saleDatabaseMap);
    void initial_database_definition();
    QSqlQueryModel* database_query(QString);
};

#endif // DATABASE_H
