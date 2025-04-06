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

    void checkAnswer(std::string selectedChoice);

    void getNextQuestion();

signals:
    /**
     * Sends a question out for the view to display
     *
     * @param q - The question to be displayed
     */
    void sendQuestion(Question q);

    /**
     * Alerts the view as to whether the quiz question is correct.
     *
     * @param correct
     */
    void sendResult(bool correct);

    /**
     * Alerts the view that the quiz has been completed as well as how many were answered correctly
     *
     * @param numberCorrect - The number of correctly answered quizQuestions.
     */
    void quizFinished(uint numberCorrect);

    void quizProgress(uint progess);
private:
    QuizHandler* quizHandler;
};

#endif // MAINMODEL_H
