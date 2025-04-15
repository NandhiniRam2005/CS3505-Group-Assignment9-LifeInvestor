#ifndef LIFEEVENTDISPLAY_H
#define LIFEEVENTDISPLAY_H

#include <QDialog>
#include "lifeeventhandler.h"

namespace Ui {
class LifeEventDisplay;
}

class LifeEventDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit LifeEventDisplay(QWidget *parent = nullptr);
    ~LifeEventDisplay();

public slots:
    void showLifeEvent(LifeEvent event);


private:
    Ui::LifeEventDisplay *ui;
};

#endif // LIFEEVENTDISPLAY_H
