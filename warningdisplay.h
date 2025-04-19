/*
The header file for WarningDisplay.

This class represents a pop-up warning dialog that displays
a warning message to the user.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/

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
    /**
     * Constructs the warningdisplay dialog.
     * @param parent - The parent widget
     */
    explicit warningdisplay(QWidget *parent = nullptr);

    /**
     * Destructor for warningdisplay.
     */
    ~warningdisplay();

    /**
     * Displays the warning dialog with a given message.
     * @param warning - The warning text to show.
     * @param image - The file path (resource) of the image to display.
     */
    void showWarning(QString warning, QString image);

private:
    Ui::warningdisplay *ui;
};

#endif
