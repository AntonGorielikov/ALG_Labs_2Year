#include "mainwindow.h"

#include "vectormodel.h"

#include <QPushButton>
#include <QListView>
#include <QComboBox>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QtMath>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), output_file_(OUTPUT_FILE)
{
    reset_button_ = new QPushButton(tr("&Reset"));
    useless_stuff_button_ = new QPushButton(tr("&Useless"));
    sort_button_ = new QPushButton(tr("&Sort"));

    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(reset_button_);
    buttons_layout->addStretch();
    buttons_layout->addWidget(useless_stuff_button_);
    buttons_layout->addWidget(sort_button_);

    array_interf_ = new QListView;
    model_ = new VectorModel;
    model_->setVector(array_);
    array_interf_->setModel(model_);

    choose_method_ = new QComboBox;
    QStringList methods;
    choose_method_->addItems(methods << tr("Shell Sort")
                                     << tr("Merge Sort"));
    choose_method_->setCurrentIndex(0);

    QVBoxLayout *vert_layout = new QVBoxLayout;
    vert_layout->addWidget(array_interf_);
    vert_layout->addWidget(choose_method_);
    vert_layout->addLayout(buttons_layout);

    QWidget *main_window = new QWidget;
    main_window->setLayout(vert_layout);
    setCentralWidget(main_window);

    output_file_.open(QIODevice::WriteOnly);
    stream_ = new QTextStream(&output_file_);

    connect(useless_stuff_button_, &QPushButton::clicked,
            this, &MainWindow::uselessAction);
    connect(sort_button_, &QPushButton::clicked,
            this, &MainWindow::sort);
    connect(reset_button_, &QPushButton::clicked,
            this, &MainWindow::reset);

    reset();
}

MainWindow::~MainWindow()
{
    output_file_.close();
    delete stream_;
}

void MainWindow::reset()
{
    array_.clear();
    for(int i = 0; i < ARRAY_SIZE; ++i)
    {
        array_.append(100.0 - (rand() % 200 + 0.01 * (rand() % 100)));
    }
}

void MainWindow::sort()
{
    QTime time_before = QTime::currentTime();
    switch(choose_method_->currentIndex())
    {
    case SHELL_SORT:
        *stream_ << tr("Starting Shell Sort") << ENDL;
        shellSort();
        break;
    case MERGE_SORT:
        *stream_ << tr("Starting Merge Sort") << ENDL;
        mergeSort(array_);
        break;
    }
    QTime time_after = QTime::currentTime();
    *stream_ << tr("Time elapsed: ") << time_before.msecsTo(time_after) << tr(" msec") << ENDL;

    for(int i = 0; i < array_.size(); ++i)
    {
        *stream_ << tr("array[") << i << tr("] = ") << array_.at(i) << ENDL;
    }
}

void MainWindow::uselessAction()
{
    switch(choose_method_->currentIndex())
    {
    case SHELL_SORT:
        uselessActionLab3();
        break;
    case MERGE_SORT:
        uselessActionLab4();
        break;
    }
}

void MainWindow::shellSort()
{
    for(int step = array_.size() / 2; step > 0; step /= 2)
    {
        *stream_ << tr("Step = ") << step << ENDL;
        for(int i = step; i < array_.size(); ++i)
        {
            *stream_ << tr("Holding element array[") << i << tr("] = ") << array_.at(i) << ENDL;
            double temp = array_.at(i);
            int j;
            for(j = i; j >= step && array_.at(j - step) > temp; j -= step)
            {
                *stream_ << tr("Shifting elements array[") << j << tr("] and array[")<< j - step << tr("]") << ENDL;
                array_[j] = array_[j - step];
            }

            *stream_ << tr("Placing array[") << i << ("] element on its place at array[") << j << tr("]") << ENDL;
            array_[j] = temp;
        }
    }
    *stream_ << tr("Array sorted") << ENDL;
}

void MainWindow::mergeSort(QVector<double> &array)
{
    if(array.size() > 1)
    {
        *stream_ << tr("Dividing array with size=") << array.size() << tr(" to vectors with size=")
                 << array.size() / 2 << tr(" and size=") << array.size() / 2 + array.size() % 2 << ENDL;;

        QVector<double> left_vector = array.mid(0, array.size() / 2);
        mergeSort(left_vector);
        QVector<double> right_vector = array.mid(array.size() / 2,
                                                 array.size() / 2 + array.size() % 2);
        mergeSort(right_vector);

        *stream_ << tr("Merging vectors with size=") << left_vector.size() << tr(" and size=") << right_vector.size() << ENDL;
        for(int i = 0, left_index = 0, right_index = 0; i < array.size(); ++i)
        {
            array[i] = (left_index < left_vector.size()
                                && (right_index >= right_vector.size()
                                    || left_vector.at(left_index) < right_vector.at(right_index))
                                ? left_vector.at(left_index++) : right_vector.at(right_index++));
        }
    }
}

void MainWindow::uselessActionLab3()
{
    QMap<double, int> mode_map;
    double mode_value;
    int occurances = 0;
    for(int i = 0; i < array_.size(); ++i)
    {
        if(mode_map.contains(array_.at(i)))
            mode_map[array_.at(i)] += 1;
        else
            mode_map[array_.at(i)] = 1;

        if(mode_map.value(array_.at(i)) > occurances)
        {
            mode_value = array_.at(i);
            occurances = mode_map.value(mode_value);
        }
    }

    for(int i = 0; i < array_.size();)
    {
        if(array_.at(i) == mode_value)
            array_.removeAt(i);
        else
            ++i;
    }
}

void MainWindow::uselessActionLab4()
{
    for(int i = 0; i < array_.size(); ++i)
        if(array_.at(i) < 0)
            array_[i] = qSin(array_.at(i));
}
