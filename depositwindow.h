#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QWidget>

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DepositWindow(QWidget *parent = nullptr);
    ~DepositWindow();

signals:
    void depositRequested(double amount, int cdNumber);

private slots:
    void handleOkButton();
    void handleCancelButton();

private:
    Ui::DepositWindow *ui;
    int currentCdNumber;
};

#endif // DEPOSITWINDOW_H
