#include "dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

InputDialog::InputDialog(QWidget *parent)
    : QDialog(parent),
      lineEdit(new QLineEdit(this)),
      okButton(new QPushButton("OK", this)),
      cancelButton(new QPushButton("Cancel", this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(lineEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &InputDialog::onOkButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &InputDialog::onCancelButtonClicked);
}

QString InputDialog::getText() const {
    return lineEdit->text();
}

void InputDialog::onOkButtonClicked() {
    accept();
}

void InputDialog::onCancelButtonClicked() {
    reject();
}
