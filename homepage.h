#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
namespace Ui {
class HomePage;
}

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private slots:

    void on_query_button_clicked();

    void on_exit_button_clicked();

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
