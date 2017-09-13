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
#include <cmath>
#include <typeinfo>

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
                                               << tr("Selection Sort")
                                               << tr("Shell Sort")
                                               << tr("Merge Sort"));
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
        ValueType type;
        bool conversion_result = true;
        QVariant data;
        if(QString(strings.at(0)).contains('.'))
        {
            data = QString(strings.at(0)).toDouble(&conversion_result);
            if(conversion_result)
            {
                type = ValueType::FLOATING_POINT;
            }
        }
        else if(!QString(strings.at(0)).contains('.'))
        {
            data = QString(strings.at(0)).toInt(&conversion_result);
            if(conversion_result)
            {
                type = ValueType::INTEGER;
            }
            else
            {
                type = ValueType::STRING;
            }
        }

        void *vector;
        switch(type)
        {
        case ValueType::INTEGER:
            vector = new QVector<int>;
            break;
        case ValueType::STRING:
            vector = new QVector<QString>;
            break;
        case ValueType::FLOATING_POINT:
            vector = new QVector<double>;
            break;
        }

        QVariant temp_value;
        for(int i = 0; i < strings.size(); ++i)
        {
            switch(type)
            {
            case ValueType::INTEGER:
                temp_value = QString(strings.at(i)).toInt(&conversion_result);
                if(conversion_result)
                    ((QVector<int>*)vector)->append(temp_value.toInt());
                break;

            case ValueType::FLOATING_POINT:
                temp_value = QString(strings.at(i)).toDouble(&conversion_result);
                if(conversion_result)
                    ((QVector<double>*)vector)->append(temp_value.toDouble());
                break;

            case ValueType::STRING:
                ((QVector<QString>*)vector)->append(QString(strings.at(i)));
                break;
            }
        }

        switch(type)
        {
        case ValueType::INTEGER:
            sort(*(QVector<int>*)vector);
            break;
        case ValueType::FLOATING_POINT:
            sort(*(QVector<double>*)vector);
            break;
        case ValueType::STRING:
            sort(*(QVector<QString>*)vector);
        }
    }
}

void MainWindow::autoDataSort()
{
    QVector<DefaultType> values(auto_num_spinbox_->value());
    srand(time(NULL));

    for(int i = 0; i < values.size(); ++i)
        values[i] = DefaultType(rand());

    sort(values);
}
