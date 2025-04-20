/*
The source file for LifeEventHandler.

This class represents a Handles life events. It will randomly generate a life event when requested and return it.
Life events have text information about the event, the amount of money the user's balance should change by, the type of the event
and the image to display when the event happens.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#include "lifeeventhandler.h"
#include <cpptoml.h>
#include <QRandomGenerator>

LifeEventHandler::LifeEventHandler(QObject *parent)
    : QObject{parent}
{
    filePath = PROJECT_PATH "QuestionBanks/lifeEvents.toml";
    loadAllLifeEvents();
}

void LifeEventHandler::loadAllLifeEvents() {
    std::vector<std::string> categories = { "goodEvents", "neutralEvents", "badEvents" };
    auto file = cpptoml::parse_file(filePath);

    for (std::string category : categories) {
        auto events = file->get_table_array(category);

        for (auto& event: *events) {
            LifeEvent specificLifeEvent;
            specificLifeEvent.text = *event->get_as<std::string>("eventDesc");
            specificLifeEvent.price = *event->get_as<int>("price");
            specificLifeEvent.type = *event->get_as<std::string>("type");
            specificLifeEvent.image = *event->get_as<std::string>("image");
            specificLifeEvent.category = *event->get_as<std::string>("category");

            lifeEvents.push_back(specificLifeEvent);
        }
    }
}

LifeEvent LifeEventHandler::getRandomLifeEvent() {
    int index = QRandomGenerator::global()->bounded(static_cast<int>(lifeEvents.size()));
    return lifeEvents[index];
}
