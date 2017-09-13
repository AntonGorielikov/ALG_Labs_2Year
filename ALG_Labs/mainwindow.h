#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    enum SortingMethods
    {
        BubbleSort = 0,
        SelectionSort,
        ShellSort,
        MergeSort
    };

    enum ValueType
    {
        INTEGER = 0,
        FLOATING_POINT,
        STRING
    };

    QPushButton *manual_data_sort_;
    QPushButton *auto_data_sort_;
    QLabel *sort_selection_label_;
    QComboBox *sort_selection_combobox_;
    QLabel *auto_num_label_;
    QSpinBox *auto_num_spinbox_;

    template<typename T>
    void sort(QVector<T> &values);
    template<typename T>
    void bubbleSort(QVector<T> &values, QProgressDialog &dialog);
    template<typename T>
    void selectionSort(QVector<T> &values, QProgressDialog &dialog);
    template<typename T>
    void shellSort(QVector<T> &values, QProgressDialog &dialog);
    template<typename T>
    void mergeSort(QVector<T> &values, QProgressDialog &dialog);
};

template<typename T>
void MainWindow::sort(QVector<T> &values)
{
    QProgressDialog dialog(this);
    dialog.setLabelText(tr("Sorting array..."));
    dialog.setCancelButtonText(tr("Cancel"));
    dialog.setMinimum(0);
    dialog.setMaximum(values.size());
    dialog.setWindowModality(Qt::WindowModal);
    dialog.show();

    QTime time_before = QTime::currentTime();

    switch(sort_selection_combobox_->currentIndex())
    {
    case SortingMethods::BubbleSort:
        bubbleSort(values, dialog);
        break;
    case SortingMethods::SelectionSort:
        selectionSort(values, dialog);
        break;
    case SortingMethods::ShellSort:
        shellSort(values, dialog);
        break;
    case SortingMethods::MergeSort:
        mergeSort(values, dialog);
        break;
    }

    QTime time_after = QTime::currentTime();
    dialog.hide();

    QFile file("output.txt");
    if(file.open(QIODevice::WriteOnly) && !dialog.wasCanceled())
    {
        QTextStream stream(&file);
        stream << "Elapsed time: " << time_before.msecsTo(time_after) << " msec" << ENDL;
        for(decltype(values[0]) value : values)
        {
            stream << value << ENDL;
        }

        QMessageBox::information(this,
                                 tr("Sort completed"),
                                 tr("Time elapsed : %1 msec\n"
                                    "Output is in output.txt file in exe dir.")
                                    .arg(time_before.msecsTo(time_after)));

        file.close();
    }
}

template<typename T>
void MainWindow::bubbleSort(QVector<T> &values, QProgressDialog &dialog)
{
    bool is_sorted = false;
    dialog.setMaximum(values.size() - 1);
    for(int i = 0; i < values.size() - 1 && !is_sorted && !dialog.wasCanceled(); ++i)
    {
        is_sorted = true;
        dialog.setValue(i);
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
    dialog.setValue(values.size() - 1);
}

template<typename T>
void MainWindow::selectionSort(QVector<T> &values, QProgressDialog &dialog)
{
    for(int i = 0; i < values.size() - 1 && !dialog.wasCanceled(); ++i)
    {
        dialog.setValue(i);
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
void MainWindow::shellSort(QVector<T> &values, QProgressDialog &dialog)
{
    int steps = 0;
    for(int step = values.size() / 2; step > 0; step /= 2)
        steps += values.size() - step;

    dialog.setMaximum(steps);
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

    dialog.setValue(dialog.maximum());
}

template<typename T>
void MainWindow::mergeSort(QVector<T> &values, QProgressDialog &dialog)
{
    dialog.setMaximum(0);
    if(values.size() > 1)
    {
        QVector<T> *left_vector = new QVector<T>;
        *left_vector = values.mid(0, values.size()/2);
        QVector<T> *right_vector = new QVector<T>;
        *right_vector = values.mid(values.size()/2, values.size()/2 + values.size() % 2);

        mergeSort(*left_vector, dialog);
        mergeSort(*right_vector, dialog);

        QApplication::processEvents();
        QVector<T> merged_values(values.size());
        for(int i = 0, left_index = 0, right_index = 0; i < merged_values.size(); ++i)
        {
            if(left_index < left_vector->size() && (right_index >= right_vector->size()  || left_vector->at(left_index) < right_vector->at(right_index)))
            {
                merged_values[i] = left_vector->at(left_index++);
            }
            else
            {
                merged_values[i] = right_vector->at(right_index++);
            }
        }

        values = merged_values;

        delete left_vector;
        delete right_vector;
    }
}

#endif // MAINWINDOW_H
