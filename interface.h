#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QVariantList>
namespace Ui {
class InterFace;
}

class InterFace : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterFace(const QString& username, QWidget *parent = nullptr);
    ~InterFace();
    QVariantList mylist;

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_fuel_suplied_amount_spinBox_valueChanged(double arg1);

    void on_fuel_suplied_amount_spinBox_editingFinished();

    void on_process_completed_button_clicked();

    void on_exit_button_clicked();

private:
    Ui::InterFace *ui;
};

#endif // INTERFACE_H
