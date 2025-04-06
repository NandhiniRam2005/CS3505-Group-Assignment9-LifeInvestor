// quizpage.h
#ifndef QUIZPAGE_H
#define QUIZPAGE_H

#include <QWidget>
#include "quiz.h" // auto-generated from quiz.ui

class QuizPage : public QWidget
{
    Q_OBJECT

public:
    explicit QuizPage(QWidget *parent = nullptr);

    Ui::Quiz *ui;
};

#endif // QUIZPAGE_H
