// https://github.com/Enderceliik
// Ender CELIK

#include "mainwindow.h"
#include <QApplication>
#include <QTSql>
#include "database.h"

int main(int argc, char *argv[])
{
    // For the username and passwords you can use;
    // for admin account:
    //    username: 'ecelik'
    //    password: '123*'
    // for officier account:
    //    username: 'celik2'
    //    password: '321*'
    // for definitions of other accounts: database.cpp -> initial_database_definition()
    // User&station registration system will be added later... Thx.

    // Uncomment the this part from being a comment when it is run for the first time for creating the database:
//    database db;
//    db.initial_database_definition();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
