/*

The header file for QuizHandler.

This class parses quizzes from the Question Bank toml files that they are stored in. It will randomly generate quizzes from
a given category and provide a list of possible answers, a reward for the question, difficulty, etc. It will also have the answer
to the question and an explanation for why the answer is correct. Instance methods can be called to progress through the quiz when needed.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#ifndef QUIZHANDLER_H
#define QUIZHANDLER_H

#include <QObject>

/**
 * @brief struct to hold information about a quiz question, including the question's text, answer choices, the answer,
 * why the answer is correct, the question's difficulty, and the reward for getting it correct.
 */
struct Question
{
    std::string text;
    std::vector<std::string> choices;
    std::string answer;
    std::string why;
    std::string difficulty;
    int reward;
};

/**
 * @brief struct to hold information about a quiz category including some financial info about the topic,
 * the name for the image used for that category, and the name of the category.
 */
struct QuizInfo{
    std::string info;
    std::string imageName;
    std::string category;
};

/**
 * @brief enum for the different categories of quizzes
 */
enum class QuizCategory {
    cds = 0,
    stocks = 1,
    gambling = 2,
    loans = 3,
    savings = 4,
    tutorial = 5,
    mixOfAll = 6,
};

Q_DECLARE_METATYPE(Question)
Q_DECLARE_METATYPE(QuizInfo)


class QuizHandler : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs the QuizHandler widget.
     * @param parent - the Parent widget.
     */
    explicit QuizHandler(QObject *parent = nullptr);

    /**
     * Creates a quiz given the category and the length of the quiz
     *
     * @param category - The category of the quiz
     * @param quizLength - The length of the quiz
     */
    void createQuiz(QuizCategory category, uint quizLength);

    /**
     * Finds and returns the info about a given Quiz Category
     * @param category the category to find
     * @return information about that Quiz Category
     */
    QuizInfo generateQuizInfo(QuizCategory category);
    /**
     * Gets the next quiz question or completes the quiz depending on if the quiz has been
     * completed
     */
    Question getNextQuestion();

    /**
     * Returns the QuizInfo about the quiz currently being taken
     * @return The QuizInfo for the quiz being taken
     */
    QuizInfo getQuizInfo();

    /**
     * @return the reason for why the quiz question's answer is correct.
     */
    std::string getCurrentQuestionWhy();

    /**
     * @return the reward for getting the current quiz question right.
     */
    int getCurrentQuestionReward();

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

    /**
     * @return the total amount that the user has made taking this quiz so far.
     */
    int getAmountEarned();

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
    /**
     * Tracker for how long the quiz should be i.e how many questions should be asked.
     */
    uint quizLength;

    /**
     * Tracks how much the user has made taking this quiz
     */
    int amountEarned;

    /**
     * Holds the file names for all the quizzes
     */
    static const std::array<std::string, 6> quizFileNames;

    /**
     * Holds the information for the current quiz being taken
     */
    QuizInfo information;

    /**
     * Scrambles the elements in a given vector into a random order.
     * @param vector the vector to scramble.
     */
    template<typename T>
    void scrambleVector(std::vector<T> &vector)
    {
        std::srand(std::time(nullptr));
        for (size_t i = 0; i < vector.size(); i++) {
            size_t swapIndex = std::rand() % vector.size();
            std::swap(vector[i], vector[swapIndex]);
        }
    }

    /**
     * Returns the filepath to the the quiz file of a given Quiz Category
     * @param category The QuizCategory to use
     * @return The filepath of that Quiz Category
     */
    std::string getFilePath(QuizCategory category);

    /**
     * Parses the files and returns all quiz questions in a given Quiz Category
     * @param category The QuizCategory to use
     * @return A vector of all Questions in that category.
     */
    std::vector<Question> getAllQuestionsFromCategory(QuizCategory category);
};

#endif
