#ifndef QUIZHANDLER_H
#define QUIZHANDLER_H

#include <QObject>

struct Question {
    std::string text;
    std::vector<std::string> choices;
    std::string answer;
    std::string why;
    std::string difficulty;
    int reward;
};

Q_DECLARE_METATYPE(Question)

class QuizHandler : public QObject
{
    Q_OBJECT
public:
    explicit QuizHandler(QObject *parent = nullptr);

public slots:
    void parseQuizFile(std::string quizName);

    void getNextQuestion();

    void checkAnswer(std::string selectedChoice);
private:
    //void parsingExample();
    std::vector<Question> quizQuestions;
    uint currentQuestion;

signals:
    void questionParsed(const std::string &question, const  std::vector<std::string> &choices, const std::string &answer, int reward);
    void sendQuestion(Question q);
    void sendResult(bool correct);
};

#endif // QUIZHANDLER_H
