#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void do_stuff();

private:
    QTextEdit *text_edit_;
    QLineEdit *line_edit_;
    QLabel *label_;
    QPushButton *push_button_;

    void select_text(int start, int length);
};

#endif // MAINWINDOW_H
