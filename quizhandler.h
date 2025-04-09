#ifndef QUIZHANDLER_H
#define QUIZHANDLER_H

#include <QObject>

struct Question
{
    std::string text;
    std::vector<std::string> choices;
    std::string answer;
    std::string why;
    std::string difficulty;
    int reward;
};
enum class QuizCategory{
    cds = 0,
    example = 1,
    gambling = 2,
    loans = 3,
    savings = 4,
    tutorial = 5,
    mixOfAll = 6
};

Q_DECLARE_METATYPE(Question)

class QuizHandler : public QObject
{
    Q_OBJECT
public:
    explicit QuizHandler(QObject *parent = nullptr);

    /**
     * Creates a quiz given the category and the length of the quiz
     *
     * @param category - The category of the quiz
     * @param quizLength - The length of the quiz
     */
    void createQuiz(QuizCategory category, uint quizLength);

    /**
     * Gets the next quiz question or completes the quiz depending on if the quiz has been
     * completed
     */
    Question getNextQuestion();

    std::string getCurrentQuestionWhy();

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

    static const std::array<std::string, 6> quizFileNames;


    /**
     * Scrambles the elements in a given vector into a random order.
     * @param vector the vector to scramble.
     */
    template <typename T>
    void scrambleVector(std::vector<T>& vector){
        std::srand(std::time(nullptr));
        for(size_t i = 0; i<vector.size(); i++){
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

#endif // QUIZHANDLER_H
