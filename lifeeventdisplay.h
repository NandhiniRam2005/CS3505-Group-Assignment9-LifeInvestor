#ifndef LIFEEVENTDISPLAY_H
#define LIFEEVENTDISPLAY_H

#include <QDialog>

namespace Ui {
class LifeEventDisplay;
}

class LifeEventDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit LifeEventDisplay(QWidget *parent = nullptr);
    ~LifeEventDisplay();

private:
    Ui::LifeEventDisplay *ui;
};

#endif // LIFEEVENTDISPLAY_H
