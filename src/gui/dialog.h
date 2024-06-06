#ifndef DIALOG_H_
#define DIALOG_H_

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class InputDialog : public QDialog {
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    QString getText() const;

private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    QLineEdit *lineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};
#endif // DIALOG_H_