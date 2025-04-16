#include "quizhandler.h"
#include <cpptoml.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

const std::array<std::string, 6> QuizHandler::quizFileNames
    = {"cdQuiz", "stocks", "gamblingQuiz", "loansQuiz", "savingsQuiz", "tutorialQuiz"};

QuizHandler::QuizHandler(QObject *parent)
    : QObject{parent}
{
    currentQuestion = 0;
    numberCorrect = 0;
    amountEarned = 0;
}

void QuizHandler::createQuiz(QuizCategory category, uint length)
{
    quizLength = length;
    quizQuestions.clear();
    currentQuestion = 0;
    amountEarned = 0;
    numberCorrect= 0;
    quizQuestions = getAllQuestionsFromCategory(category);
    information = generateQuizInfo(category);
    scrambleVector(quizQuestions);
}

QuizInfo QuizHandler::generateQuizInfo(QuizCategory category){
    QuizInfo generatedInformation;
    if(category == QuizCategory::mixOfAll){
        generatedInformation.category = "All categories";
        generatedInformation.imageName = "moneyMan.png";
        generatedInformation.info = "This is a quiz containing a mixture questions from all of the other categories.";
        return generatedInformation;
    }
    auto file = cpptoml::parse_file(getFilePath(category));
    generatedInformation.category = *file->get_as<std::string>("category");
    generatedInformation.imageName = *file->get_as<std::string>("image");
    generatedInformation.info = *file->get_as<std::string>("categoryInfo");

    return generatedInformation;
}

std::vector<Question> QuizHandler::getAllQuestionsFromCategory(QuizCategory category)
{
    std::vector<std::string> filePathsToParse;
    std::vector<Question> questionList;
    if (category != QuizCategory::mixOfAll) {
        filePathsToParse.push_back(getFilePath(category));
    } else {
        for (std::string quizName : quizFileNames) {\
                if(quizName == "tutorialQuiz"){
                    continue;
                }
            filePathsToParse.push_back(PROJECT_PATH "QuestionBanks/" + quizName + ".toml");
        }
    }
    for (std::string &filepath : filePathsToParse) {
        auto file = cpptoml::parse_file(filepath);
        auto questions = file->get_table_array("questions");
        for (auto &q : *questions) {
            Question question;
            std::string text = *q->get_as<std::string>("question");
            std::string why = *q->get_as<std::string>("why");
            std::string answer = *q->get_as<std::string>("answer");
            question.text = text;
            question.why = why;
            question.answer = answer;
            auto choices_raw = q->get_array_of<std::string>("choices");
            std::vector<std::string> choices;
            if (choices_raw) {
                choices = *choices_raw;
                question.choices = choices;
            }
            scrambleVector(question.choices);

            std::string diff = *q->get_as<std::string>("difficulty");
            question.difficulty = diff;
            int reward = *q->get_as<int>("reward");
            question.reward = reward;

            questionList.push_back(question);
        }
    }
    return questionList;
}

Question QuizHandler::getNextQuestion()
{
    if (currentQuestion >= quizLength) {
        throw new std::runtime_error("No more questions to access");
    }
    currentQuestion++;
    return quizQuestions.at(currentQuestion - 1);
}

QuizInfo QuizHandler::getQuizInfo(){
    return information;
}

std::string QuizHandler::getCurrentQuestionWhy()
{
    return quizQuestions[currentQuestion - 1].why;
}

int QuizHandler::getCurrentQuestionReward()
{
    return quizQuestions[currentQuestion - 1].reward;
}

int QuizHandler::getAmountEarned(){
    return amountEarned;
}

bool QuizHandler::hasMoreQuestions()
{
    if (currentQuestion >= quizLength) {
        return false;
    }
    return true;
}

bool QuizHandler::checkAnswer(std::string selectedAnswer)
{
    if (selectedAnswer == quizQuestions.at(currentQuestion - 1).answer) {
        numberCorrect++;
        amountEarned+= getCurrentQuestionReward();
        return true;
    } else {
        return false;
    }
}

uint QuizHandler::getQuestionsAnsweredCorrectly()
{
    return numberCorrect;
}

uint QuizHandler::quizProgress()
{
    return (currentQuestion * 100) / quizLength;
}

std::string QuizHandler::getFilePath(QuizCategory category)
{
    if (category == QuizCategory::mixOfAll) {
        throw std::runtime_error("This category does not have a file");
    }
    return PROJECT_PATH "QuestionBanks/" + quizFileNames[static_cast<uint>(category)] + ".toml";
}
