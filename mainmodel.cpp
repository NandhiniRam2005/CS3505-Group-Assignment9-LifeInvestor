#include "mainmodel.h"
#include "quizhandler.h"
MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    QuizHandler q;
}
