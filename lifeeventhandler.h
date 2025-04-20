/*
The header file for LifeEventHandler.

This class represents a Handles life events. It will randomly generate a life event when requested and return it.
Life events have text information about the event, the amount of money the user's balance should change by, the type of the event
and the image to display when the event happens.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#ifndef LIFEEVENTHANDLER_H
#define LIFEEVENTHANDLER_H

#include <QObject>

/**
 * @brief struct holding information about a life event. Including: text representing the event, the price of the event,
 * the type of the event, and an image to display when the event ocurrs.
 */
struct LifeEvent
{
    std::string text;
    int price;
    std::string type;
    std::string image;
    std::string category;
};

class LifeEventHandler: public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs the LifeEventHandler widget.
     * @param parent - the Parent widget.
     */
    explicit LifeEventHandler(QObject *parent = nullptr);

    /**
     * Generates a random life event
     * @return A LifeEvent struct containing information about the event.
     */
    LifeEvent getRandomLifeEvent();

private:
    std::string filePath;
    std::vector<LifeEvent> lifeEvents;

    /**
     * Loads all life events into a vector so they can be randomly selected later.
     */
    void loadAllLifeEvents();

};

#endif
