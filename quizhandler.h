#ifndef QUIZHANDLER_H
#define QUIZHANDLER_H

#include <QObject>

class QuizHandler : public QObject
{
    Q_OBJECT
public:
    explicit QuizHandler(QObject *parent = nullptr);

private:
    void parsingExample();

signals:
};

#endif // QUIZHANDLER_H
