#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <ctime>
#include <QProgressDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QTime>
#include <cmath>
#include <typeinfo>

#define AUTO_SORT_SIZE int(100000)

#ifdef _WIN32
#define ENDL ("\r\n")
#else
#define ENDL ("\n")
#endif // _WIN32

#include <QProgressDialog>
#include <QApplication>

class QPushButton;
class QComboBox;
class QProgressDialog;
class QSpinBox;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    typedef int DefaultType;

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void manualDataSort();
    void autoDataSort();

private:
    QPushButton *manual_data_sort_;
    QPushButton *auto_data_sort_;
    QLabel *auto_num_label_;
    QSpinBox *auto_num_spinbox_;

    void sort(QVector<int> &values);
    template<typename T>
    void bubbleSort(QVector<T> values, QProgressDialog &dialog);
    template<typename T>
    void selectionSort(QVector<T> values, QProgressDialog &dialog);
    template<typename T>
    void shellSort(QVector<T> values, QProgressDialog &dialog);
    template<typename T>
    void mergeSort(QVector<T> values, QProgressDialog &dialog);
    template<typename T>
    void quick_Sort(QVector<T> values, int leftmost, int rightmost, QProgressDialog &dialog);

    void counting_Sort(QVector<int> values, int lower_limit, int upper_limit, QProgressDialog &dialog);
};

template<typename T>
void MainWindow::bubbleSort(QVector<T> values, QProgressDialog &dialog)
{
    bool is_sorted = false;
    for(int i = 0; i < values.size() - 1 && !is_sorted && !dialog.wasCanceled(); ++i)
    {
        is_sorted = true;
        for(int j = 0; j < values.size() - i - 1 && !dialog.wasCanceled(); ++j)
        {
            QApplication::processEvents();
            if(values.at(j) > values.at(j + 1))
            {
               qSwap(values[j], values[j + 1]);
               is_sorted = false;
            }
        }
    }
}

template<typename T>
void MainWindow::selectionSort(QVector<T> values, QProgressDialog &dialog)
{
    for(int i = 0; i < values.size() - 1 && !dialog.wasCanceled(); ++i)
    {
        uint max_value_index = 0;
        for(int j = 1; j < values.size() - i && !dialog.wasCanceled(); ++j)
        {
            QApplication::processEvents();
            if(values[max_value_index] < values[j])
                max_value_index = j;
        }
        qSwap(values[max_value_index], values[values.size() - i - 1]);
    }
}

template<typename T>
void MainWindow::shellSort(QVector<T> values, QProgressDialog &dialog)
{
    int steps = 0;
    for(int step = values.size() / 2; step > 0; step /= 2)
        steps += values.size() - step;

    for(int step = values.size() / 2; step > 0 && !dialog.wasCanceled(); step /= 2)
        for(int i = step; i < values.size() && !dialog.wasCanceled(); ++i)
        {
            dialog.setValue(dialog.value() + 1);
            T temp = values[i];
            int j;

            for(j = i; j >= step && values[j - step] > temp; j -= step)
                values[j] = values[j - step];

            values[j] = temp;
        }
}

template<typename T>
void MainWindow::mergeSort(QVector<T> values, QProgressDialog &dialog)
{
    dialog.setMaximum(0);
    if(values.size() > 1)
    {
        QVector<T> left_vector = values.mid(0, values.size()/2);
        QVector<T> right_vector = values.mid(values.size()/2, values.size()/2 + values.size() % 2);

        mergeSort(left_vector, dialog);
        mergeSort(right_vector, dialog);

        QApplication::processEvents();
        for(int i = 0, left_index = 0, right_index = 0; i < values.size(); ++i)
        {
            if(left_index < left_vector.size() && (right_index >= right_vector.size()  || left_vector.at(left_index) < right_vector.at(right_index)))
            {
                values[i] = left_vector.at(left_index++);
            }
            else
            {
                values[i] = right_vector.at(right_index++);
            }
        }
    }
}

template<typename T>
void MainWindow::quick_Sort(QVector<T> values, int leftmost, int rightmost, QProgressDialog &dialog)
{
    int i = leftmost, j = rightmost;
    double pivot = values.at((leftmost + rightmost) / 2);
    
    while (i <= j) {
        for(;values.at(i) < pivot; ++i);
        for(;values.at(j) > pivot; --j);
        QApplication::processEvents();
        if(dialog.wasCanceled())
            return;
        if (i <= j) {
                qSwap(values[j], values[i]);
                ++i;
                --j;
        }
    }
    
    if (leftmost < j)
        quick_Sort(values, leftmost, j, dialog);
    if (rightmost > i)
        quick_Sort(values, i, rightmost, dialog);
}

#endif // MAINWINDOW_H
