#include "mainwindow.h"

#include "vectormodel.h"
#include "algorithms.h"

#include <QPushButton>
#include <QListView>
#include <QComboBox>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QtMath>
#include <QTime>

static const int upper_limit = 99;
static const int lower_limit = 0;

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
    choose_method_->addItems(methods << tr("Counting Sort"));
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
        array_.append(rand()%100);
}

void MainWindow::sort()
{
    *stream_ << "Before sort:" << ENDL;
    for(int i = 0; i < array_.size(); ++i)
    {
        *stream_ << tr("array[") << i << tr("] = ") << array_.at(i) << ENDL;
    }
    QTime time_before = QTime::currentTime();
    switch(choose_method_->currentIndex())
    {
    case COUNTING_SORT:
        *stream_ << tr("Starting Shell Sort") << ENDL;
        Algorithms<int>::countingSort(array_, upper_limit, lower_limit, stream_);
        break;
    }
    QTime time_after = QTime::currentTime();
    *stream_ << tr("Time elapsed: ") << time_before.msecsTo(time_after) << tr(" msec") << ENDL;

    for(int i = 0; i < array_.size(); ++i)
    {
        *stream_ << tr("array[") << i << tr("] = ") << array_.at(i) << ENDL;
    }
    array_interf_->update();
}

void MainWindow::uselessAction()
{
    switch(choose_method_->currentIndex())
    {
    case COUNTING_SORT:
        uselessActionLab5();
        break;
    }
    array_interf_->update();
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

void MainWindow::uselessActionLab5()
{
}
