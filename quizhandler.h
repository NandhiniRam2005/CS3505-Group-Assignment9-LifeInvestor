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

    /**
     * Parses a quiz toml file for usage when a quiz is started
     *
     * @param quizName - The name of the quiz.
     */
    void parseQuizFile(std::string quizName);

    /**
     * Gets the next quiz question or completes the quiz depending on if the quiz has been
     * completed
     */
    Question getNextQuestion();

    /**
     * Checks the user selected answer.
     *
     * @param selectedChoice - The answer selected by the user.
     * @return - If the user was correct or not.
     */
    bool checkAnswer(std::string selectedChoice);

    /**
     * Checks to see if the quiz has any more questions
     *
     * @return - if the quiz has any more questions
     */
    bool hasMoreQuestions();

    /**
     * Once the quiz is completed the number answered correctly should be returned.
     *
     * @return - The number of quiz questions answered correctly
     */
    uint getQuestionsAnsweredCorrectly();

    /**
     * The current progress of the quiz as an unsigned int percentage.
     *
     * @return - The quiz progress as an unsigned int percentage (1-100)
     */
    uint quizProgress();

private:
    /**
     * A collection of all the quizQuestions parsed.
     */
    std::vector<Question> quizQuestions;

    /**
     * Index for the quiz currently is.
     */
    uint currentQuestion;

    /**
     * Tracker for how many quizQuestions have been answered correctly so far.
     */
    uint numberCorrect;

};

#endif // QUIZHANDLER_H
