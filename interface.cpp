// https://github.com/Enderceliik
// Ender CELIK

#include "interface.h"
#include "ui_interface.h"
#include "database.h"
#include "mainwindow.h"
InterFace::InterFace(const QString& username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterFace)
{
    ui->setupUi(this);
    database db;
    mylist = db.interface_constructor_fetch(username);
    qDebug() << mylist.at(1).toString() + "  ENDER ";
    ui->stationName_label->setText(mylist.at(2).toString());
    ui->sale_price_spinBox->setValue(mylist.at(4).toDouble());
    int pump_counter = 0;
    for(pump_counter=0; pump_counter<mylist.at(3).toInt();pump_counter++)
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
        feeReceived = ui->fuel_suplied_amount_spinBox->value() * mylist.at(4).toDouble();
        ui->sale_price_spinBox->setValue(mylist.at(4).toDouble());
    }
    else if(index == 1)
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value() * mylist.at(5).toDouble();
        qDebug() << ui->comboBox->currentText() + QString::number(mylist.at(5).toDouble());
        ui->sale_price_spinBox->setValue(mylist.at(5).toDouble());
    }
    else
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value() * mylist.at(6).toDouble();
        qDebug() << ui->comboBox->currentText() + QString::number(mylist.at(6).toDouble());
        ui->sale_price_spinBox->setValue(mylist.at(6).toDouble());
    }
    ui->fee_received_label->setText(QString::number(feeReceived));
}


void InterFace::on_fuel_suplied_amount_spinBox_valueChanged(double arg1)
{
    double feeReceived;
    if(ui->comboBox->currentText() == "LPG")
    {
        feeReceived = arg1*mylist.at(4).toDouble();
    }
    else if(ui->comboBox->currentText() == "Diesel")
    {
        feeReceived = arg1*mylist.at(5).toDouble();
    }
    else
    {
        feeReceived = arg1*mylist.at(6).toDouble();
    }
    ui->fee_received_label->setText(QString::number(feeReceived));
}


void InterFace::on_fuel_suplied_amount_spinBox_editingFinished()
{
    double feeReceived;
    if(ui->comboBox->currentText() == "LPG")
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value()*mylist.at(4).toDouble();
    }
    else if(ui->comboBox->currentText() == "Diesel")
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value()*mylist.at(5).toDouble();
    }
    else
    {
        feeReceived = ui->fuel_suplied_amount_spinBox->value()*mylist.at(6).toDouble();
    }
    ui->fee_received_label->setText(QString::number(feeReceived));
}

void InterFace::on_process_completed_button_clicked()
{
    if(ui->fuel_suplied_amount_spinBox->value() != 0)
    {
        ui->statusbar->showMessage("Processing...");
        ui->comboBox->setEnabled(false);
        ui->sale_price_spinBox->setEnabled(false);
        ui->fuel_suplied_amount_spinBox->setEnabled(false);
        ui->fee_received_label->setEnabled(false);
        ui->pump_no_comboBox->setEnabled(false);
        database db;

        db.process_completed_button_function(ui->comboBox->currentText(), ui->sale_price_spinBox->value(),ui->fuel_suplied_amount_spinBox->value(),ui->fee_received_label->text().toDouble(),ui->pump_no_comboBox->currentText().toInt(),mylist.at(0).toInt(),mylist.at(1).toInt(), mylist.at(2).toString());
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

