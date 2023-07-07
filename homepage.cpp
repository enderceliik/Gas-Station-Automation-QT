// https://github.com/Enderceliik
// Ender CELIK

#include "homepage.h"
#include "ui_homepage.h"
#include "QSqlRecord"
#include "mainwindow.h"
#include "database.h"
HomePage::HomePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

HomePage::~HomePage()
{
    delete ui;
}



void HomePage::on_query_button_clicked()
{
    database db;
    QSqlQueryModel *model = db.database_query(ui->comboBox->currentText());
    ui->tableView->setModel(model);
    ui->tableView->show();
    ui->tableView->update();
}


void HomePage::on_exit_button_clicked()
{
    MainWindow *mainwindow = new MainWindow();
    close();
    mainwindow->show();
}

