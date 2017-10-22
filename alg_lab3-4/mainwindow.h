#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QListView;
class QComboBox;
class VectorModel;

#include <QFile>
#include <QTextStream>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void reset();
    void sort();
    void uselessAction();

private:
    enum
    {
        ARRAY_SIZE = 100,

        COUNTING_SORT = 0
    };
    const QString OUTPUT_FILE = "output.txt";

    void uselessActionLab3();
    void uselessActionLab4();
    void uselessActionLab5();

    QVector<int> array_;
    VectorModel *model_;
    QComboBox *choose_method_;
    QListView *array_interf_;
    QPushButton *useless_stuff_button_;
    QPushButton *reset_button_;
    QPushButton *sort_button_;

    QFile output_file_;
    QTextStream *stream_;
};

#endif // MAINWINDOW_H
