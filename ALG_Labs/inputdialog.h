#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QLabel;

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    InputDialog(QWidget *parent = nullptr);

    QString getResult()const;

private slots:
    void enableOkButton(const QString &text);
    void onOkButtonClicked();

private:
    QLabel *label_;
    QLineEdit *edit_;
    QPushButton *ok_;
    QPushButton *cancel_;

    QString result_;

    const QString ABOUT_TITLE = tr("About");
    const QString ABOUT_TEXT = tr("Enter values");
};

#endif // INPUTDIALOG_H
