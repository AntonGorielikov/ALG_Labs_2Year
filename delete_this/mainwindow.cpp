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
    quickSort(arr_, 0, arr_.size() - 1);
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

#include <qDebug>
void MainWindow::dumpArray()
{
    for(int i = 0; i < arr_.size(); ++i)
        for(int j = 0; j < arr_[i].size(); ++j)
            table_->setItem(j, i, new QTableWidgetItem(QString::number(arr_[i][j])));
}

void MainWindow::quickSort(QVector<QVector<double> > &arr,
                           int leftmost,
                           int rightmost)
{
    qDebug() << "Quick sort from leftmost=" << leftmost << " to rightmost=" << rightmost;
    qDebug() << "Elements is:";
    for(int s = leftmost; s < rightmost + 1; ++s)
        qDebug() << arr[s][0];
    int i = leftmost, j = rightmost;
    double pivot = arr[(leftmost + rightmost) / 2][0];
    qDebug() << "Pivot element is arr[" << (leftmost + rightmost) / 2 << "]=" << pivot;

    qDebug() << "Starting partition";
    while (i <= j) {
        for(;arr[i][0] < pivot; ++i);
        for(;arr[j][0] > pivot; --j);
        qDebug() << "Found i=" << i << "=" << arr[i][0] << " and j=" << j << "=" << arr[j][0];
        if (i <= j) {
            qDebug() << "Swapping them";
            qSwap(arr[j], arr[i]);
            ++i;
            --j;
        }
    };
    qDebug() << "Ending partition";

    if (leftmost < j)
        quickSort(arr, leftmost, j);
    if (rightmost > i)
        quickSort(arr, i, rightmost);
}
