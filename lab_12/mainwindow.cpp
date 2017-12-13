#include "mainwindow.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QVector>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGridLayout *main_layout = new QGridLayout;

    text_edit_ = new QTextEdit;
    line_edit_ = new QLineEdit;
    label_ = new QLabel(tr("&Pattern"));
    label_->setBuddy(line_edit_);
    push_button_ = new QPushButton(tr("&Search"));

    main_layout->addWidget(text_edit_, 0, 0, 1, 2);
    main_layout->addWidget(label_, 1, 0, 1, 1);
    main_layout->addWidget(line_edit_, 1, 1, 1, 1);
    main_layout->addWidget(push_button_, 2, 0, 1, 2);

    QWidget *main_widget = new QWidget;
    main_widget->setLayout(main_layout);
    this->setCentralWidget(main_widget);

    connect(push_button_, &QPushButton::clicked,
            this, &MainWindow::do_stuff);
}

MainWindow::~MainWindow()
{
}

#include <QDebug>
void MainWindow::do_stuff()
{
    QString text = text_edit_->toPlainText(),
            pattern = line_edit_->text();
    int pattern_size = pattern.size(),
            text_size = text.size();
    QVector<int> suffix_shift, z_vector, occurances_vector;
    suffix_shift.resize(pattern_size + 1);
    suffix_shift.fill(pattern_size);
    z_vector.resize(pattern_size);
    z_vector.fill(0);

    for (int j = 1, max_z_idx = 0, max_z = 0; j < pattern_size; ++j)
    {
        if (j <= max_z)
            z_vector[j] = MIN(max_z - j + 1, z_vector.at(j - max_z_idx));

        while (j + z_vector.at(j) < pattern_size &&
               pattern.at(pattern_size - 1 - z_vector.at(j)) ==
               pattern.at(pattern_size - 1 - (j + z_vector.at(j))))
        {
               z_vector[j]++;
        }

        if (j + z_vector.at(j) - 1 > max_z)
        {
            max_z_idx = j;
            max_z = j + z_vector.at(j) - 1;
        }
    }

    qDebug() << "Z-function";
    for (int i = 0; i < z_vector.size(); i++)
        qDebug() << z_vector.at(i);

    for (int j = pattern_size - 1; j > 0; j--)
        suffix_shift[pattern_size - z_vector.at(j)] = j;

    for (int j = 1, r = 0; j <= pattern_size - 1; j++)
    {
        if (j + z_vector.at(j) == pattern_size)
        {
            for (; r <= j; r++)
            {
                if (suffix_shift.at(r) == pattern_size)
                    suffix_shift[r] = j;
            }
        }
    }

    qDebug() << "Suffix shift vector";
    for (int i = 0; i < suffix_shift.size(); i++)
        qDebug() << suffix_shift.at(i);

    for (int i = 0, j = 0; i <= text_size - pattern_size &&
         j >= 0; i += suffix_shift.at(j+1))
    {
        for (j = pattern_size - 1; j >= 0 && pattern.at(j) == text.at(i + j); j--);

        if (j < 0)
            occurances_vector.append(i);
    }

    if (occurances_vector.isEmpty())
    {
        QMessageBox::information(this, tr("Search finished"),
                                 tr("No hits were found"));
    }
    else
    {
        QMessageBox::information(this, tr("Search finished"),
                                 tr(">=1 hits were found, first of them:\n%1")
                                 .arg(occurances_vector.at(0)));
        select_text(occurances_vector.at(0), pattern_size);
    }
}

void MainWindow::select_text(int start, int length)
{
    QTextCursor cursor = text_edit_->textCursor();
    cursor.setPosition(start);
    cursor.setPosition(start + length, QTextCursor::KeepAnchor);
    text_edit_->setTextCursor(cursor);
}
