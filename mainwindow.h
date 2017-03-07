#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbigint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_add_clicked();

    void on_subtract_clicked();

    void on_mult_clicked();

    void on_store_clicked();

    void on_recall_clicked();

    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

    void on_left_op_textEdited(const QString &arg1);

    void on_right_op_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

    dbigint _right_op, _left_op, _storage;
    std::string _right_op_str, _left_op_str, _storage_str;

    //pre: none
    //post: displays current values of _left_op_str, _right_op_str, and _storage_str
    void display();
};

#endif // MAINWINDOW_H
