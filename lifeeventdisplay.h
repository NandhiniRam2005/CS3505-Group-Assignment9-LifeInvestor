/*
The header file for LifeEventHandler.

This class represents the view for a life event. It will diplay a life event when requested.
Life events have text information about the event, the amount of money the user's balance should change by, the type of the event
and the image to display when the event happens.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

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
    /**
     * Constructs the LifeEventDisplay widget.
     * @param parent - the Parent widget.
     */
    explicit LifeEventDisplay(QWidget *parent = nullptr);

    /**
     * Deconstructor for the life event display
     */
    ~LifeEventDisplay();

public slots:
    /**
     * Sets this life event display to display the data of the input life event.
     * @param event - the life event to display the data of
     */
    void showLifeEvent(LifeEvent event);


private:

    /**
     * The life event display's ui as a pointer
     */
    Ui::LifeEventDisplay *ui;
};

#endif
