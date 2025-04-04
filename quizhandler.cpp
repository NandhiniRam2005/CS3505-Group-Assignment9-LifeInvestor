#include "quizhandler.h"
#include <cpptoml.h>

QuizHandler::QuizHandler(QObject *parent)
    : QObject{parent}
{}

void ParsingExample(){
    auto file = cpptoml::parse_file("example.toml");
    auto questions = file->get_table_array("questions");

    for (auto& q : *questions) {
        std::string text = *q->get_as<std::string>("question");
        std::string answer = *q->get_as<std::string>("answer");

        auto choices_raw = q->get_array_of<std::string>("choices");
        std::vector<std::string> choices;
        if (choices_raw) {
            choices = *choices_raw;
        }

        auto diff = q->get_as<std::string>("difficulty");
        auto tags = q->get_array_of<std::string>("tags");
    }
}
