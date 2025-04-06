#include "quizhandler.h"
#include <cpptoml.h>
#include <iostream>

QuizHandler::QuizHandler(QObject *parent)
    : QObject{parent}
{
    //parsingExample();
    parseQuizFile("example");
}

void QuizHandler::parsingExample()
{
    std::string filepath = PROJECT_PATH "QuestionBanks/example.toml";
    auto file = cpptoml::parse_file(filepath);
    auto questions = file->get_table_array("questions");

    for (auto &q : *questions) {
        std::string text = *q->get_as<std::string>("question");
        std::string answer = *q->get_as<std::string>("answer");

        auto choices_raw = q->get_array_of<std::string>("choices");
        std::vector<std::string> choices;
        if (choices_raw) {
            choices = *choices_raw;
        }

        std::string diff = *q->get_as<std::string>("difficulty");
        int reward = *q->get_as<int>("reward");
        std::cout << text << std::endl;
        for (auto &choice : choices) {
            std::cout << choice << std::endl;
        }
        std::cout << reward << std::endl;
    }
}
void QuizHandler::parseQuizFile(std::string quizName)
{
    std::string filepath = PROJECT_PATH "QuestionBanks/" + quizName + ".toml";
    auto file = cpptoml::parse_file(filepath);
    auto questions = file->get_table_array("questions");

    for (auto &q : *questions) {
        std::string text = *q->get_as<std::string>("question");
        std::string answer = *q->get_as<std::string>("answer");

        auto choices_raw = q->get_array_of<std::string>("choices");
        std::vector<std::string> choices;
        if (choices_raw) {
            choices = *choices_raw;
        }

        std::string diff = *q->get_as<std::string>("difficulty");
        int reward = *q->get_as<int>("reward");
        std::cout << text << std::endl;
        for (auto &choice : choices) {
            std::cout << choice << std::endl;
        }
        std::cout << reward << std::endl;

        emit questionParsed(text, choices, answer, reward);
    }
}
