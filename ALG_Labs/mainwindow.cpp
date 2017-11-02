#include "mainwindow.h"

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

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    manual_data_sort_ = new QPushButton();
    manual_data_sort_->setText(tr("&Test"));

    auto_num_label_ = new QLabel(tr("Array &size:"));
    auto_num_spinbox_ = new QSpinBox();
    auto_num_label_->setBuddy(auto_num_spinbox_);

    auto_num_spinbox_->setMinimum(0);
    auto_num_spinbox_->setMaximum(10000000);
    auto_num_spinbox_->setValue(10000);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(auto_num_label_, 0, 0, 1, 1);
    layout->addWidget(auto_num_spinbox_, 0, 1, 1, 2);
    layout->addWidget(manual_data_sort_, 2, 0, 1, 2);

    QWidget *main_widget = new QWidget();
    main_widget->setLayout(layout);
    this->setCentralWidget(main_widget);

    setFixedSize(minimumSizeHint());

    connect(manual_data_sort_, &QPushButton::clicked, this, &MainWindow::manualDataSort);
}

void MainWindow::manualDataSort()
{
    autoDataSort();
}

void MainWindow::autoDataSort()
{
    QVector<int> values(auto_num_spinbox_->value());
    srand(time(NULL));

    for(int i = 0; i < values.size(); ++i)
        values[i] = rand() % 100;

    sort(values);
}

void MainWindow::sort(QVector<int> &values)
{
    QFile file("output.txt");
    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream stream(&file);
    QProgressDialog dialog(this);
    dialog.setLabelText(tr("Sorting array..."));
    dialog.setCancelButtonText(tr("Cancel"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.show();

    stream << "Running tests with array size = " << values.size() << ENDL;
    if (dialog.wasCanceled())
    {
        stream << "Test was canceled, results may be invalid" << ENDL;
        return;
    }

    dialog.setLabelText(tr("Sorting array... (bubble)"));
    QTime time_before = QTime::currentTime();
    bubbleSort(values, dialog);
    QTime time_after = QTime::currentTime();
    stream << "Bubble sort: " << time_before.msecsTo(time_after) << " msec" << ENDL;

    if (dialog.wasCanceled())
    {
        stream << "Test was canceled, results may be invalid" << ENDL;
        return;
    }

    dialog.setLabelText(tr("Sorting array... (selection)"));
    time_before = QTime::currentTime();
    selectionSort(values, dialog);
    time_after = QTime::currentTime();
    stream << "Selection sort: " << time_before.msecsTo(time_after) << " msec" << ENDL;

    if (dialog.wasCanceled())
    {
        stream << "Test was canceled, results may be invalid" << ENDL;
        return;
    }


    dialog.setLabelText(tr("Sorting array... (shell)"));
    time_before = QTime::currentTime();
    shellSort(values, dialog);
    time_after = QTime::currentTime();
    stream << "Shell sort: " << time_before.msecsTo(time_after) << " msec" << ENDL;

    if (dialog.wasCanceled())
    {
        stream << "Test was canceled, results may be invalid" << ENDL;
        return;
    }


    dialog.setLabelText(tr("Sorting array... (merge)"));
    time_before = QTime::currentTime();
    mergeSort(values, dialog);
    time_after = QTime::currentTime();
    stream << "Merge sort: " << time_before.msecsTo(time_after) << " msec" << ENDL;

    if (dialog.wasCanceled())
    {
        stream << "Test was canceled, results may be invalid" << ENDL;
        return;
    }


    dialog.setLabelText(tr("Sorting array... (quick)"));
    time_before = QTime::currentTime();
    quick_Sort(values, 0, values.size() - 1, dialog);
    time_after = QTime::currentTime();
    stream << "Quick sort: " << time_before.msecsTo(time_after) << " msec" << ENDL;

    if (dialog.wasCanceled())
    {
        stream << "Test was canceled, results may be invalid" << ENDL;
        return;
    }


    dialog.setLabelText(tr("Sorting array... (counting)"));
    time_before = QTime::currentTime();
    counting_Sort(values, 0, 99, dialog);
    time_after = QTime::currentTime();
    stream << "Counting sort: " << time_before.msecsTo(time_after) << " msec" << ENDL;

    if (dialog.wasCanceled())
    {
        stream << "Test was canceled, results may be invalid" << ENDL;
        return;
    }

    dialog.hide();
    QMessageBox::information(this,tr("Sort tests completed"),
                                  tr("Output is in output.txt file in exe dir."));
}


void MainWindow::counting_Sort(QVector<int> values, int lower_limit, int upper_limit, QProgressDialog &dialog)
{
    if(upper_limit < lower_limit)
            return;

    QVector<int> key_occurances;
    key_occurances.resize(upper_limit - lower_limit + 1);

    for(int i = 0; i < key_occurances.size(); ++i)
        key_occurances[i] = 0;

    for(int i = 0; i < values.size(); ++i)
    {
        if (dialog.wasCanceled())
            return;
        QApplication::processEvents();
        key_occurances[values.at(i) - lower_limit] += 1;
    }

    values.clear();
    for(int i = 0; i < key_occurances.size(); ++i)
        for(int j = 0; j < key_occurances.at(i); ++j)
        {
            if (dialog.wasCanceled())
                return;
            QApplication::processEvents();
            values.append(i + lower_limit);
        }
}
