#include "mainmodel.h"
#include "quizhandler.h"
#include <iostream>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    quizHandler = new QuizHandler(this);

    currentBalance = 0;
    creditScore = 0;
    currentYear = 1;

    savingsAccount = new SavingsAccount(0);

    cdAccount = new CDAccount(0);

    stocks.push_back(Stock());
    stocks.push_back(Stock());
    stocks.push_back(Stock());
}

void MainModel::requestQuiz()
{
    this->quizHandler->parseQuizFile("example");
    getNextQuestion();
}

void MainModel::getNextQuestion()
{
    if (quizHandler->hasMoreQuestions()) {
        emit quizProgress(quizHandler->quizProgress());
        emit sendQuestion(quizHandler->getNextQuestion());
    } else {
        emit quizFinished(quizHandler->getQuestionsAnsweredCorrectly());
    }
}

void MainModel::checkAnswer(std::string selectedChoice)
{
    emit sendResult(quizHandler->checkAnswer(selectedChoice));
}

void MainModel::depositToSavings(double amount) {

}

void MainModel::depositToCD(double amount) {

}

void MainModel::buyStock(double amount, int stockNumber) {

}

void MainModel::depositToLoan(double amount, int loanNumber) {

}

void MainModel::withdrawFromSavings(double amount) {

}

void MainModel::withdrawFromCD(double amount) {

}

void MainModel::sellStock(double amount, int stockNumber) {

}

void MainModel::withdrawFromLoan(double amount, int loanNumber) {

}

void MainModel::nextYear() {

}

