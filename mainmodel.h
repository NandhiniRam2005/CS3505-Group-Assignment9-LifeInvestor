#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "quizhandler.h"

class MainModel : public QObject
{
    Q_OBJECT
public:
    explicit MainModel(QObject *parent = nullptr);

public slots:
    //TEMPORARY SLOT ADDED FOR TESTING.
    void requestQuiz();

    void submitAnswer(const std::string &answer);
    void requestNextQuestion();

signals:
    void newQuizData(Question q);
    void quizResult(bool correct);
    void quizCompleted();

private:
    QuizHandler* quizHandler;
};

#endif // MAINMODEL_H


