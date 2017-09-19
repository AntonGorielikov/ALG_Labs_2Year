#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#ifdef WIN32
#define ENDL "\r\n"
#else
#define ENDL "\n"
#endif

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
        ARRAY_SIZE = 15,

        SHELL_SORT = 0,
        MERGE_SORT
    };
    const QString OUTPUT_FILE = "output.txt";

    void shellSort();
    void mergeSort(QVector<double> &array);
    void uselessActionLab3();
    void uselessActionLab4();

    QVector<double> array_;
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
