#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainmodel.h"
#include "quizhandler.h"
#include <QMainWindow>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainModel *model, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QButtonGroup *buttonGroup;
    Question currentQuestion;

public slots:
    void showQuizData(Question q);
    void onStartClicked();

signals:
    void startQuizRequested();

};
#endif // MAINWINDOW_H
