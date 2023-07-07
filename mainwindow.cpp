// https://github.com/Enderceliik
// Ender CELIK

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "homepage.h"
#include <QSqlError>
#include <interface.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_button_clicked()
{
    ui->username_line_edit->setEnabled(false);
    ui->password_line_edit->setEnabled(false);
    ui->login_button->setEnabled(false);
    ui->statusbar->showMessage("Checking...");
    if(ui->username_line_edit->text().isEmpty() || ui->password_line_edit->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Hata");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Bilgilerinizin tamamını girdiğinizden emin olun!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        ui->statusbar->clearMessage();
        ui->username_line_edit->setEnabled(true);
        ui->password_line_edit->setEnabled(true);
        ui->login_button->setEnabled(true);
        return;
    }
    else
    {
        ui->statusbar->showMessage("Try to connect database...");
        database db;
        QString response = db.database_connection(ui->username_line_edit->text(), ui->password_line_edit->text());
        if(response == "1")
        {
            qDebug() << "Bağlandı!";
            ui->statusbar->clearMessage();
            HomePage *homePage = new HomePage();
            close();
            homePage->show();
        }
        else if (response == "0")
        {
            qDebug() << "user mode";
            InterFace *interface = new InterFace(ui->username_line_edit->text());
            close();
            interface->show();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Hata");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Veritabanına bağlanılamadı!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            ui->statusbar->clearMessage();
            ui->username_line_edit->setEnabled(true);
            ui->password_line_edit->setEnabled(true);
            ui->login_button->setEnabled(true);
            return;
        }
    }

}

