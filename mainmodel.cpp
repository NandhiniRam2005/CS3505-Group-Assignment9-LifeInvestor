#include "mainmodel.h"
#include "quizhandler.h"
#include <iostream>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    QuizHandler *quizHandler = new QuizHandler(this);
    connect(quizHandler, &QuizHandler::questionParsed, this, &MainModel::handleQuestion);
}

void MainModel::handleQuestion(const std::string &question, const  std::vector<std::string> &choices, const std::string &answer, int reward) {
    std::cout << "In handleQuestion: " << question << std::endl;
    emit newQuizData(question, choices, answer, reward);
}

