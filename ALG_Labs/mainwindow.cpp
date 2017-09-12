#include "mainwindow.h"
#include "inputdialog.h"

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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    manual_data_sort_ = new QPushButton();
    manual_data_sort_->setText(tr("&Manual"));

    auto_data_sort_ = new QPushButton();
    auto_data_sort_->setText(tr("&Auto"));

    sort_selection_label_ = new QLabel(tr("&Methods:"));
    sort_selection_combobox_ = new QComboBox();
    sort_selection_label_->setBuddy(sort_selection_combobox_);
    QStringList options;
    sort_selection_combobox_->addItems(options << tr("Bubble Sort")
                                               << tr("Selection Sort"));
    sort_selection_combobox_->setCurrentIndex(0);

    auto_num_label_ = new QLabel(tr("Auto array &size:"));
    auto_num_spinbox_ = new QSpinBox();
    auto_num_label_->setBuddy(auto_num_spinbox_);

    auto_num_spinbox_->setMinimum(0);
    auto_num_spinbox_->setMaximum(1000000);
    auto_num_spinbox_->setValue(AUTO_SORT_SIZE);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(auto_num_label_, 0, 0, 1, 1);
    layout->addWidget(auto_num_spinbox_, 0, 1, 1, 2);
    layout->addWidget(sort_selection_label_, 1, 0, 1, 1);
    layout->addWidget(sort_selection_combobox_, 1, 1, 1, 1);
    layout->addWidget(manual_data_sort_, 2, 0, 1, 1);
    layout->addWidget(auto_data_sort_, 2, 1, 1, 1);

    QWidget *main_widget = new QWidget();
    main_widget->setLayout(layout);
    this->setCentralWidget(main_widget);

    setFixedSize(minimumSizeHint());

    connect(manual_data_sort_, &QPushButton::clicked, this, &MainWindow::manualDataSort);
    connect(auto_data_sort_, &QPushButton::clicked, this, &MainWindow::autoDataSort);
}

void MainWindow::manualDataSort()
{
    InputDialog input;
    input.exec();

    if(input.result() == QDialog::Accepted)
    {
        QStringList strings = input.getResult().split(" ");
        QVector<qint32> int_vector;
        bool conversion_result = true;
        int temp_value;
        for(uint i = 0; i < strings.size(); ++i)
        {
            temp_value = QString(strings.at(i)).toInt(&conversion_result);
            if(conversion_result)
                int_vector.append(temp_value);
        }

        if(int_vector.size() > 0)
            sort(int_vector);
    }
}

void MainWindow::autoDataSort()
{
    QVector<int> int_vector(auto_num_spinbox_->value());
    srand(time(NULL));

    for(int i = 0; i < int_vector.size(); ++i)
        int_vector[i] = rand();

    sort(int_vector);
}

void MainWindow::sort(QVector<int> &values)
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
    }

    QTime time_after = QTime::currentTime();

    QFile file("output.txt");
    if(file.open(QIODevice::WriteOnly) && !dialog.wasCanceled())
    {
        QTextStream stream(&file);
        for(int value : values)
        {
            stream << value << ENDL;
        }

        QMessageBox::information(this,
                                 tr("Sort completed"),
                                 tr("Time elapsed : %1 msec\n"
                                    "Output is in output.txt file in exe dir.")
                                    .arg(time_before.msecsTo(time_after)));
    }

    file.close();
    dialog.hide();
}

void MainWindow::bubbleSort(QVector<int> &values, QProgressDialog &dialog)
{
    bool is_sorted = false;
    dialog.setMaximum(values.size() - 1);
    for(uint i = 0; i < values.size() - 1 && !is_sorted && !dialog.wasCanceled(); ++i)
    {
        is_sorted = true;
        dialog.setValue(i);
        QApplication::processEvents();
        for(uint j = 0; j < values.size() - i - 1; ++j)
        {
            if(values.at(j) > values.at(j + 1))
            {
               qSwap(values[j], values[j + 1]);
               is_sorted = false;
            }
        }
    }
    dialog.setValue(values.size() - 1);
}

void MainWindow::selectionSort(QVector<int> &values, QProgressDialog &dialog)
{
    for(uint i = 0; i < values.size() - 1; ++i)
    {
        dialog.setValue(i);
        uint max_value_index = 0;
        for(uint j = 1; j < values.size() - i; ++j)
        {
            if(values[max_value_index] < values[j])
                max_value_index = j;
        }
        qSwap(values[max_value_index], values[values.size() - i - 1]);
    }
}
