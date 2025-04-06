#include "mainmodel.h"
#include "quizhandler.h"
#include <iostream>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    quizHandler = new QuizHandler(this);

    connect(quizHandler, &QuizHandler::sendQuestion, this, &MainModel::newQuizData);
    connect(quizHandler, &QuizHandler::sendResult, this, &MainModel::quizResult);
    connect(quizHandler, &QuizHandler::quizFinished, this, &MainModel::quizCompleted);
}

void MainModel::requestQuiz(){
    this->quizHandler->parseQuizFile("example");
    this->quizHandler->getNextQuestion();
}

void MainModel::submitAnswer(const std::string &answer) {
    quizHandler->checkAnswer(answer);
}

void MainModel::requestNextQuestion() {
    quizHandler->getNextQuestion();
}
