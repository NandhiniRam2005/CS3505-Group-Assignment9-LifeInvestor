#ifndef WARNINGDISPLAY_H
#define WARNINGDISPLAY_H

#include <QDialog>

namespace Ui {
class warningdisplay;
}

class warningdisplay : public QDialog
{
    Q_OBJECT

public:
    explicit warningdisplay(QWidget *parent = nullptr);
    ~warningdisplay();
    void showWarning(QString warning, QString image);

private:
    Ui::warningdisplay *ui;
};

#endif // WARNINGDISPLAY_H
