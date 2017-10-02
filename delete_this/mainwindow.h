#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    void dumpArray();

    void quickSort(QVector<QVector<double>> &arr, int leftmost, int rightmost);

    Ui::MainWindow *ui;
    QTableWidget *table_;
    QVector<QVector<double>> arr_;
};

#endif // MAINWINDOW_H
