#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>

class MainModel : public QObject
{
    Q_OBJECT
public:
    explicit MainModel(QObject *parent = nullptr);

public slots:
    void handleQuestion(const std::string &question, const  std::vector<std::string> &choices, const std::string &answer, int reward);

signals:
    void newQuizData(const std::string &question, const  std::vector<std::string> &choices, const std::string &answer, int reward);
};

#endif // MAINMODEL_H
