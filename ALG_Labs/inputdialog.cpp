#include "inputdialog.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QRegExpValidator>

InputDialog::InputDialog(QWidget *parent)
{
    label_ = new QLabel(tr("&Numbers:"));

    edit_ = new QLineEdit;
    edit_->setWhatsThis(tr("Enter integer values separated by spaces.\n"
                           "Invalid values will be ignored"));
    label_->setBuddy(edit_);

    ok_ = new QPushButton(tr("&OK"));
    ok_->setDefault(true);
    ok_->setEnabled(false);

    cancel_ = new QPushButton(tr("&Canpel"));

    connect(edit_, &QLineEdit::textChanged, this, &InputDialog::enableOkButton);
    connect(ok_, &QPushButton::clicked, this, &InputDialog::onOkButtonClicked);
    connect(cancel_, &QPushButton::clicked, this, &InputDialog::reject);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label_, 0, 0, 1, 1);
    layout->addWidget(edit_, 0, 1, 1, 2);
    layout->addWidget(ok_, 1, 1, 1, 1);
    layout->addWidget(cancel_, 1, 2, 1, 1);

    setLayout(layout);
    setWindowTitle(tr("Enter values"));
    setFixedHeight(sizeHint().height());
}

QString InputDialog::getResult() const
{
    return result_;
}

void InputDialog::enableOkButton(const QString &text)
{
    ok_->setEnabled(!text.isEmpty());
}

void InputDialog::onOkButtonClicked()
{
    result_ = edit_->text();
    accept();
}
