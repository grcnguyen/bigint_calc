#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbigint.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _left_op = 0;
    _right_op = 0;
    _storage = 0;
    _left_op_str = "";
    _right_op_str = "";
    _storage_str = "";
    display();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display()
{
    ui -> left_op ->setText(QString::fromStdString(_left_op_str));
    ui -> memory ->setText(QString::fromStdString(_storage_str));
    ui -> right_op ->setText(QString::fromStdString(_right_op_str));
    update();
}

void MainWindow::on_add_clicked()
{
    _left_op = _left_op_str;
    _right_op = _right_op_str;
    _left_op += _right_op;
    _left_op_str = _left_op.toStdString();
    display();
}

void MainWindow::on_subtract_clicked()
{
    _left_op = _left_op_str;
    _right_op = _right_op_str;
    _left_op -= _right_op;
    _left_op_str = _left_op.toStdString();
    display();
}

void MainWindow::on_mult_clicked()
{
    _left_op = _left_op_str;
    _right_op = _right_op_str;
    _left_op *= _right_op;
    _left_op_str = _left_op.toStdString();
    display();
}

void MainWindow::on_store_clicked()
{
    _storage_str = _left_op_str;
    display();
}

void MainWindow::on_recall_clicked()
{
    _right_op_str = _storage_str;
    display();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox m;
    m.setText("This dynamic big integer calculator was created by Grace Nguyen, 2016.");
    m.exec();
}

void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}

void MainWindow::on_left_op_textEdited(const QString &arg1)
{
    _left_op_str = arg1.QString::toStdString();
    display();
}

void MainWindow::on_right_op_textEdited(const QString &arg1)
{
    _right_op_str = arg1.QString::toStdString();
    display();
}
