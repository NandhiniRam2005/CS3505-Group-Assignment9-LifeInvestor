#include "mainmodel.h"
#include "quizhandler.h"

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    QuizHandler *quizHandler = new QuizHandler(this);
    connect(quizHandler, &QuizHandler::questionParsed, this, &MainModel::handleQuestion);
}

void MainModel::handleQuestion(const std::string &question, const  std::vector<std::string> &choices, const std::string &answer, int reward) {
    emit newQuizData(question, choices, answer, reward);
}

