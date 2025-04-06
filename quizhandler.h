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

    void parseQuizFile(std::string quizName);
signals:
    void questionParsed(const std::string &question, const  std::vector<std::string> &choices, const std::string &answer, int reward);
};

#endif // QUIZHANDLER_H
