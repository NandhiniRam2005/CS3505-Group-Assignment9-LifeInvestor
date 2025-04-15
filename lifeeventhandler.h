#ifndef LIFEEVENTHANDLER_H
#define LIFEEVENTHANDLER_H

#include <QObject>

struct LifeEvent
{
    std::string text;
    int price;
    std::string type;
};

class LifeEventHandler: public QObject

{
    Q_OBJECT
public:
    explicit LifeEventHandler(QObject *parent = nullptr);

    LifeEvent getRandomLifeEvent();

private:
    std::string filePath;
    std::vector<LifeEvent> lifeEvents;
    void loadAllLifeEvents();

};

#endif // LIFEEVENTHANDLER_H
