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
    void handleQuestion(Question q);

    //TEMPORARY SLOT ADDED FOR TESTING.
    void requestQuiz();

signals:
    void newQuizData(Question q);
private:
    QuizHandler* quizHandler;
};

#endif // MAINMODEL_H
