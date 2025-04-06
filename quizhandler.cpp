#include "quizhandler.h"
#include <cpptoml.h>
#include <iostream>
#include <stdexcept>


QuizHandler::QuizHandler(QObject *parent)
    : QObject{parent}
{
    currentQuestion = 0;
    numberCorrect = 0;
    // parsingExample();
    // parseQuizFile("example");
    // getNextQuestion();
}

void QuizHandler::parseQuizFile(std::string quizName)
{

    quizQuestions.clear();
    currentQuestion = 0;
    std::string filepath = PROJECT_PATH "QuestionBanks/" + quizName + ".toml";
    auto file = cpptoml::parse_file(filepath);
    auto questions = file->get_table_array("questions");

    for (auto &q : *questions) {
        Question question;
        std::string text = *q->get_as<std::string>("question");
        std::string why = *q->get_as<std::string>("why");
        std::string answer = *q->get_as<std::string>("answer");
        question.text = text;
        question.why = why;
        question.answer = answer;
        auto choices_raw = q->get_array_of<std::string>("choices");
        std::vector<std::string> choices;
        if (choices_raw) {
            choices = *choices_raw;
            question.choices = choices;
        }

        std::string diff = *q->get_as<std::string>("difficulty");
        question.difficulty = diff;
        int reward = *q->get_as<int>("reward");
        question.reward = reward;

        quizQuestions.push_back(question);
    }

}
Question QuizHandler::getNextQuestion(){
    if(currentQuestion >= quizQuestions.size()){
        throw new std::runtime_error("No more questions to access");
    }
    currentQuestion++;
    return quizQuestions.at(currentQuestion - 1);
}

bool QuizHandler::hasMoreQuestions(){
    if (currentQuestion >= quizQuestions.size()){
        return false;
    }
    return true;
}


bool QuizHandler::checkAnswer(std::string selectedAnswer){
    if(selectedAnswer == quizQuestions.at(currentQuestion - 1).answer){
        numberCorrect++;
        return true;
    }
    else{
        return false;
    }
}

uint QuizHandler::getQuestionsAnsweredCorrectly(){
    return numberCorrect;
}

uint QuizHandler::quizProgress(){
    return (currentQuestion * 100) / quizQuestions.size();
}
