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
            lifeEvents.push_back(specificLifeEvent);
        }
    }
}

LifeEvent LifeEventHandler::getRandomLifeEvent() {
    int index = QRandomGenerator::global()->bounded(static_cast<int>(lifeEvents.size()));
    return lifeEvents[index];
}
