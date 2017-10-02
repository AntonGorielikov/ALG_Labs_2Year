#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table_ = ui->tableWidget;

    arr_.resize(table_->columnCount());
    for(int i = 0; i < table_->columnCount(); ++i)
    {
        arr_[i].resize(table_->rowCount());
        for(int j = 0; j < table_->rowCount(); ++j)
        {
            arr_[i][j] = (rand()%100) + 0.01 * (rand()%100);
            table_->setItem(j, i, new QTableWidgetItem(QString::number(arr_[i][j])));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QDebug>
void MainWindow::on_pushButton_clicked()
{
    //quickSort(arr_, 0, arr_.size() - 1);
    QVector<QVector<double> > array;
    for(int i = 0; i < 5; ++i)
    {
        array.append(QVector<double>());
        array[i].append(i);
    }
    quickSort(array, 0, 4);
    dumpArray();
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i = 0; i < arr_[arr_.size() - 1].size(); ++i)
    {
        arr_[arr_.size() - 1][i] = qLn(qFabs(arr_[arr_.size() - 1][i]));
    }
    dumpArray();
}

void MainWindow::dumpArray()
{
    for(int i = 0; i < arr_.size(); ++i)
        for(int j = 0; j < arr_[i].size(); ++j)
            table_->setItem(j, i, new QTableWidgetItem(QString::number(arr_[i][j])));
}

#include <qDebug>
void MainWindow::quickSort(QVector<QVector<double> > &arr,
                           int leftmost,
                           int rightmost)
{
    int i = leftmost, j = rightmost;
    double pivot = arr[(leftmost + rightmost) / 2][0];

    while (i <= j) {
        for(;arr[i][0] < pivot; ++i);
        for(;arr[j][0] > pivot; --j);
        if (i <= j) {
            qSwap(arr[j], arr[i]);
            ++i;
            --j;
        }
    };

    if (leftmost < j)
        quickSort(arr, leftmost, j);
    if (rightmost > i)
        quickSort(arr, i, rightmost);
}
