// https://github.com/Enderceliik
// Ender CELIK

#include "homepage.h"
#include "ui_homepage.h"
#include "QSqlRecord"
#include "mainwindow.h"
HomePage::HomePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
}

HomePage::~HomePage()
{
    delete ui;
}



void HomePage::on_query_button_clicked()
{
    QSqlQuery query;
    ui->tableWidget->clear();
    int rowCount = ui->tableWidget->rowCount();
    for (int i = rowCount - 1; i >= 0; --i) {
        ui->tableWidget->removeRow(i);
    }

    ui->tableWidget->clearContents();
    if(ui->comboBox->currentText() == "Stations")
    {
        query.prepare("select * from stations");
        if(query.exec())
        {
            qDebug() << "select stations table!";
        }
        else
        {
            qDebug() << query.lastError().text()  + "select stations error";
        }

        ui->tableWidget->setColumnCount(query.record().count());
        for (int i = 0; i < query.record().count(); ++i) {
            QTableWidgetItem* headerItem = new QTableWidgetItem(query.record().fieldName(i));
            ui->tableWidget->setHorizontalHeaderItem(i, headerItem);
        }

        int row = 0;
        while (query.next())
        {
            QString stationID = query.value(0).toString();
            QString stationName = query.value(1).toString();
            QString totalSales = query.value(2).toString();
            QString totalFuelSuppliedLPG = query.value(3).toString();
            QString totalFuelSuppliedDiesel = query.value(4).toString();
            QString totalFuelSuppliedGasoline = query.value(5).toString();
            QString pumpSize = query.value(6).toString();

            // Satır ekleme ve hücreleri doldurma
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(stationID));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(stationName));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(totalSales));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(totalFuelSuppliedLPG));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(totalFuelSuppliedDiesel));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(totalFuelSuppliedGasoline));
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(pumpSize));

            row++;
        }
    }
    else
    {
        query.prepare("select * from sales");
        if(query.exec())
        {
            qDebug() << "select sales table!";
        }
        else
        {
            qDebug() << query.lastError().text()  + "select sales error";
        }
        ui->tableWidget->setColumnCount(query.record().count());
        for (int i = 0; i < query.record().count(); ++i) {
            QTableWidgetItem* headerItem = new QTableWidgetItem(query.record().fieldName(i));
            ui->tableWidget->setHorizontalHeaderItem(i, headerItem);
        }
        int row = 0;
        while (query.next())
        {
            QString salesID = query.value(0).toString();
            QString saleDate = query.value(1).toString();
            QString stationName = query.value(2).toString();
            QString feeReceived = query.value(3).toString();
            QString fuelSupplied = query.value(4).toString();
            QString pumpNumber = query.value(5).toString();
            QString fueType = query.value(6).toString();
            QString salePrice = query.value(7).toString();
            QString officerID = query.value(8).toString();
            QString stationID = query.value(9).toString();

            // Satır ekleme ve hücreleri doldurma
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(salesID));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(saleDate));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(stationName));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(feeReceived));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(fuelSupplied));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(pumpNumber));
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(fueType));
            ui->tableWidget->setItem(row, 7, new QTableWidgetItem(salePrice));
            ui->tableWidget->setItem(row, 8, new QTableWidgetItem(officerID));
            ui->tableWidget->setItem(row, 9, new QTableWidgetItem(stationID));

            row++;
        }
    }
}


void HomePage::on_exit_button_clicked()
{
    MainWindow *mainwindow = new MainWindow();
    close();
    mainwindow->show();
}

