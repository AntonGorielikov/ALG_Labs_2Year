#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define AUTO_SORT_SIZE int(100000)

#ifdef _WIN32
#define ENDL ("\r\n")
#else
#define ENDL ("\n")
#endif // _WIN32

class QPushButton;
class QComboBox;
class QProgressDialog;
class QSpinBox;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void manualDataSort();
    void autoDataSort();

private:
    enum SortingMethods
    {
        BubbleSort = 0,
        SelectionSort
    };

    QPushButton *manual_data_sort_;
    QPushButton *auto_data_sort_;
    QLabel *sort_selection_label_;
    QComboBox *sort_selection_combobox_;
    QLabel *auto_num_label_;
    QSpinBox *auto_num_spinbox_;

    void sort(QVector<int> &values);
    void bubbleSort(QVector<int> &values, QProgressDialog &dialog);
    void selectionSort(QVector<int> &values, QProgressDialog &dialog);
};

#endif // MAINWINDOW_H
