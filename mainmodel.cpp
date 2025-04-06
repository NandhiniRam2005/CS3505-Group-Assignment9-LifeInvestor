#include "mainmodel.h"
#include "quizhandler.h"
#include <iostream>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    quizHandler = new QuizHandler(this);
    connect(quizHandler, &QuizHandler::sendQuestion, this, &MainModel::handleQuestion);

}

void MainModel::handleQuestion(Question question) {
    std::cout << "In handleQuestion: " << std::endl;
    emit newQuizData(question);
}
void MainModel::requestQuiz(){
    this->quizHandler->parseQuizFile("example");
    this->quizHandler->getNextQuestion();
}

