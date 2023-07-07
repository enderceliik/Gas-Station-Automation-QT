// https://github.com/Enderceliik
// Ender CELIK

#include "interface.h"
#include "ui_interface.h"
#include "database.h"
#include "mainwindow.h"
#include "QMap"
InterFace::InterFace(const QString& username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterFace)
{
    ui->setupUi(this);
    database db;
    interfaceInfoMap = db.interface_constructor_fetch(username);
    ui->stationName_label->setText(interfaceInfoMap.value("stationName").toString());
    ui->sale_price_spinBox->setValue(interfaceInfoMap.value("lpg").toDouble());
    int pump_counter = 0;
    for(pump_counter=0; pump_counter<interfaceInfoMap.value("pumpSize").toInt();pump_counter++)
    {
        ui->pump_no_comboBox->addItem(QString::number(pump_counter+1));
    }
}

InterFace::~InterFace()
{
    delete ui;
}

void InterFace::on_comboBox_currentIndexChanged(int index)
{
    double feeReceived;
    if(index == 0)
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value() * interfaceInfoMap.value("lpg").toDouble();
        ui->sale_price_spinBox->setValue(interfaceInfoMap.value("lpg").toDouble());
    }
    else if(index == 1)
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value() * interfaceInfoMap.value("diesel").toDouble();
        ui->sale_price_spinBox->setValue(interfaceInfoMap.value("diesel").toDouble());
    }
    else
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value() * interfaceInfoMap.value("gasoline").toDouble();
        ui->sale_price_spinBox->setValue(interfaceInfoMap.value("gasoline").toDouble());
    }
    ui->fee_received_label->setText(QString::number(feeReceived));
}


void InterFace::on_fuel_suplied_amount_spinBox_valueChanged(double arg1)
{
    double feeReceived;
    if(ui->comboBox->currentText() == "LPG")
    {
        feeReceived = arg1*interfaceInfoMap.value("lpg").toDouble();
    }
    else if(ui->comboBox->currentText() == "Diesel")
    {
        feeReceived = arg1*interfaceInfoMap.value("diesel").toDouble();
    }
    else
    {
        feeReceived = arg1*interfaceInfoMap.value("gasoline").toDouble();
    }
    ui->fee_received_label->setText(QString::number(feeReceived));
}


void InterFace::on_fuel_suplied_amount_spinBox_editingFinished()
{
    double feeReceived;
    if(ui->comboBox->currentText() == "LPG")
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value()*interfaceInfoMap.value("lpg").toDouble();
    }
    else if(ui->comboBox->currentText() == "Diesel")
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value()*interfaceInfoMap.value("diesel").toDouble();
    }
    else
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value()*interfaceInfoMap.value("gasoline").toDouble();
    }
    ui->fee_received_label->setText(QString::number(feeReceived));
}

void InterFace::on_process_completed_button_clicked()
{
    if(ui->fuel_suplied_amount_spinBox->value() != 0)
    {
        QMap<QString, QVariant> saleDatabaseMap;
        saleDatabaseMap.insert("fuelType", ui->comboBox->currentText());
        saleDatabaseMap.insert("salePrice", ui->sale_price_spinBox->value());
        saleDatabaseMap.insert("fuelSupplied", ui->fuel_suplied_amount_spinBox->value());
        saleDatabaseMap.insert("feeReceived", ui->fee_received_label->text().toDouble());
        saleDatabaseMap.insert("pumpNumber", ui->pump_no_comboBox->currentText().toInt());
        saleDatabaseMap.insert("userID", interfaceInfoMap.value("userID"));
        saleDatabaseMap.insert("stationID", interfaceInfoMap.value("stationID"));
        saleDatabaseMap.insert("stationName", interfaceInfoMap.value("stationName"));
        ui->statusbar->showMessage("Processing...");
        ui->comboBox->setEnabled(false);
        ui->sale_price_spinBox->setEnabled(false);
        ui->fuel_suplied_amount_spinBox->setEnabled(false);
        ui->fee_received_label->setEnabled(false);
        ui->pump_no_comboBox->setEnabled(false);
        database db;
        db.process_completed_button_function(saleDatabaseMap);
        ui->comboBox->setEnabled(true);
        ui->sale_price_spinBox->setEnabled(true);
        ui->fuel_suplied_amount_spinBox->setEnabled(true);
        ui->fee_received_label->setEnabled(true);
        ui->pump_no_comboBox->setEnabled(true);
        ui->statusbar->clearMessage();
    }
}


void InterFace::on_exit_button_clicked()
{
    MainWindow *mainwindow = new MainWindow();
    close();
    mainwindow->show();
}

