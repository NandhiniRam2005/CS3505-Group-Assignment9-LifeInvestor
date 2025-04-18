#include <QMessageBox>
#include "mainwindow.h"
#include <QMovie>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "iostream"
#include "ui_mainwindow.h"

/*
The source file for MainWindow.

This class represents the main window for the LifeInvesting application. It consistenly asks the model for information
to display and displays the information to the user. The view is an interactive location for the user to interact with
our game.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/
MainWindow::MainWindow(MainModel *model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->Start);
    generalUISetup();

    setUpGifs();

    setupAudio();

    enableQuizSubmission();

    quizConnections(model);

    phoneConnections();

    nextYearConnections(model);

    depositingConnectionWindowToModel(model);

    withdrawingConnectionsWindowToModel(model);

    mainWindowValueUpdateConnections(model);

    buyingStockUIConnections();

    sellingStockUIConnections();

    visualIUpdatesStockConnections(model);

    cdPageConnections(model);

    savingsPageConnections(model);

    loansPageConnections(model);

    casinoPageConnections(model);

    extraQuizesPageConnections(model);

    lifeEventsConnections(model);

    shopItemsConnections(model);

    databaseConnections(model);

    connect(model, &MainModel::displayWarning, this, &MainWindow::showWarning);


    //UNORGANIZED CONNECTION  I COULD NOT GROUP THESE WITH ANYTHING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    connect(ui->continueButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
        ui->cashBalance->show();
        ui->creditLabel->show();
        ui->networthLabel->show();
    });

    connect(model, &MainModel::netWorthChanged, this, &MainWindow::updateNetWorth);

    connect(ui->App1, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->Stocks);
    });
    connect(model, &MainModel::returnToGame, this, &MainWindow::returnToGame);

    connect(ui->startButton, &QPushButton::pressed, [=]() {
        ui->startButton->setIcon(QIcon(":///icons/icons/startClick.png"));
        ui->startButton->setIconSize(QSize(200, 250));
    });

    connect(model, &MainModel::gameEnded, this, &MainWindow::gameEnded);

    connect(model, &MainModel::updateBalance, this, &MainWindow::updateBalance);

    // connection for showing error messages
    connect(model, &MainModel::showErrorMessage, this, &MainWindow::showErrorMessage);

    // Start button connections for pressed
    connect(ui->startButton, &QPushButton::pressed, [=]() {
        ui->startButton->setIcon(QIcon(":///icons/icons/startClick.png"));
        ui->startButton->setIconSize(QSize(200, 250));
    });

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showQuizData(Question question)
{
    ui->resultLabel->setText("");

    ui->choice1->setEnabled(true);
    ui->choice2->setEnabled(true);
    ui->choice3->setEnabled(true);
    ui->choice4->setEnabled(true);

    if (buttonGroup->checkedButton()) {
        buttonGroup->setExclusive(
            false); // Temporarily allow no selection so that we can unselect the prev radio button.
        buttonGroup->checkedButton()->setChecked(false);
        buttonGroup->setExclusive(true);
    }

    ui->submitButton->setEnabled(false);
    ui->nextButton->setEnabled(false);

    ui->labelQuestion->setText(QString::fromStdString(question.text));

    ui->choice1->setText(QString::fromStdString(question.choices[0]));
    ui->choice2->setText(QString::fromStdString(question.choices[1]));
    ui->choice3->setText(QString::fromStdString(question.choices[2]));
    ui->choice4->setText(QString::fromStdString(question.choices[3]));

    ui->choice1Label->setText(QString::fromStdString(question.choices[0]));
    ui->choice2Label->setText(QString::fromStdString(question.choices[1]));
    ui->choice3Label->setText(QString::fromStdString(question.choices[2]));
    ui->choice4Label->setText(QString::fromStdString(question.choices[3]));

    ui->labelReward->setText("Reward: " + QString::number(question.reward));
}

void MainWindow::updateQuizInfo(QuizInfo qI)
{
    qDebug() << qI.info << qI.category << qI.imageName;
    ui->categoryLabel->setText(QString::fromStdString(qI.category));
    ui->categoryLabel->adjustSize();
    ui->categoryInfo->setAlignment(Qt::AlignHCenter);

    ui->categoryInfo->setText(QString::fromStdString(qI.info));
    QPixmap pixmap(":///icons/icons/" + QString::fromStdString(qI.imageName));
    ui->infoImage->setPixmap(pixmap);

}

void MainWindow::displayPhone()
{
    ui->openPhoneButton->hide();
    ui->Phone->show();
    ui->closePhoneButton->show();
    ui->Apps->show();
}

void MainWindow::hidePhone()
{
    ui->Phone->hide();
    ui->closePhoneButton->hide();
    ui->Apps->hide();
    ui->openPhoneButton->show();
}

void MainWindow::returnToGame(QWidget *currentWidget)
{
    QString returnPage = currentWidget->objectName();
    if (returnPage == "Start") {
        ui->stackedWidget->setCurrentWidget(ui->Start);
    } else if (returnPage == "Quiz") {
        ui->stackedWidget->setCurrentWidget(ui->Quiz);
    } else if (returnPage == "quizEnd") {
        ui->stackedWidget->setCurrentWidget(ui->quizEnd);
    } else if (returnPage == "mainGame") {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    } else if (returnPage == "Stocks") {
        ui->stackedWidget->setCurrentWidget(ui->Stocks);
    } else if (returnPage == "Bank") {
        ui->stackedWidget->setCurrentWidget(ui->Bank);
    } else if (returnPage == "CD") {
        ui->stackedWidget->setCurrentWidget(ui->CD);
    } else if (returnPage == "Loans") {
        ui->stackedWidget->setCurrentWidget(ui->Loans);
    } else if (returnPage == "gameEnd") {
        ui->stackedWidget->setCurrentWidget(ui->gameEnd);
    } else if (returnPage == "quizInfo") {
        ui->stackedWidget->setCurrentWidget(ui->quizInfo);
    } else if (returnPage == "Casino") {
        ui->stackedWidget->setCurrentWidget(ui->Casino);
    } else {
        throw std::runtime_error("return page could not be found.");
    }
    if (returnPage != "Start" && returnPage != "quizEnd"){
        ui->cashBalance->show();
        ui->creditLabel->show();
        ui->networthLabel->show();
    }
}

void MainWindow::onStartClicked()
{
    hidePhone();
    ui->cashBalance->show();
    ui->creditLabel->show();
    ui->networthLabel->show();
    if(firstStart){
        emit requestQuiz(quizCategory, 1);
        firstStart = false;
    }
    ui->stackedWidget->setCurrentWidget(ui->quizInfo);
}

void MainWindow::submitHelper()
{
    QAbstractButton *selected = buttonGroup->checkedButton();
    std::string selectedText = (selected->text()).toStdString();
    emit sendAnswer(selectedText);

    ui->choice1->setEnabled(false);
    ui->choice2->setEnabled(false);
    ui->choice3->setEnabled(false);
    ui->choice4->setEnabled(false);

    ui->submitButton->setEnabled(false);
    ui->nextButton->setEnabled(true);
}

void MainWindow::displayResult(bool result, std::string explanation)
{
    if (result) {
        ui->resultLabel->setText(
            "<span style='color: #4ea912; font-weight: bold;'>CORRECT!!</span>");
        animationView->startConfettiAnimation();
        levelPassSound->play();
    } else {
        QString formattedText
            = "<span style='color: #d34e32; font-weight: bold;'>Incorrect!!!</span><br>"
              "<span style='color: black;'>Explanation: "
              + QString::fromStdString(explanation) + "</span>";
        ui->resultLabel->setText(formattedText);
        animationView->startRainAnimation();
        levelFailSound->play();
    }
}

void MainWindow::updateProgress(uint progress)
{
    ui->quizProgress->setValue(progress);
}

void MainWindow::updateBalance(double newAmount)
{
    currentMoney = newAmount;
    QString balanceText;
    if (currentMoney == std::floor(currentMoney))
        balanceText = "Checking: $" + QString::number(currentMoney, 'f', 0);
    else
        balanceText = "Checking: $" + QString::number(currentMoney, 'f', 2);

    ui->cashBalance->setText(balanceText);
    ui->checkingAccountAmount->setText(balanceText);
    ui->checkingAccountAmount->adjustSize();

    if(currentMoney >= 0){
        ui->cashBalance->setStyleSheet("QLabel {  color: #85bb65;  font-weight: bold;	font-size: 30px;}");
    }
    else{
        ui->cashBalance->setStyleSheet("QLabel {  color: red;  font-weight: bold;	font-size: 30px;}");
    }


}

void MainWindow::updateSavings(double newBalance, double interestRate)
{
    ui->savingsAccountAmount->setText("Balance: $" + QString::number(newBalance, 'f', 2));
    ui->savingsAccountAmount->adjustSize();
}

void MainWindow::updateNetWorth(double netWorth)
{
    ui->networthLabel->setText("Net Worth: $" + QString::number(netWorth, 'f', 2));
    ui->networthLabel->setStyleSheet(netWorth < 0 ? "color: red; font-weight: bold; font-size: 30px;" : "color: #85bb65; font-weight: bold; font-size: 30px;");
}

/*void MainWindow::updateChecking(double newBalance)
{
    ui->checkingAccountAmount->setText("Balance: $" + QString::number(newBalance, 'f', 2));
*/

void MainWindow::updateCD(int cdNumber,
                          double newBalance,
                          double interestRate,
                          int termlength,
                          double minimumDeposit,
                          int yearsLeft)
{
    switch (cdNumber) {
    case 0:
        ui->cd1BalanceLabel->setText("Balance: $" + QString::number(newBalance, 'f', 2));
        ui->cd1InterestLabel->setText("Interest: " + QString::number(interestRate * 100, 'f', 2)
                                      + "%");
        ui->cd1TermLabel->setText("Term: " + QString::number(termlength) + " yrs");
        ui->cd1YearsLeftLabel->setText("Years Left: " + QString::number(yearsLeft));
        ui->cd1MinDepositLabel->setText("Min Deposit: $" + QString::number(minimumDeposit, 'f', 2));
        ui->cd1WithdrawButton->setEnabled(yearsLeft == 0);
        break;
    case 1:
        ui->cd2BalanceLabel->setText("Balance: $" + QString::number(newBalance, 'f', 2));
        ui->cd2InterestLabel->setText("Interest: " + QString::number(interestRate * 100, 'f', 2)
                                      + "%");
        ui->cd2TermLabel->setText("Term: " + QString::number(termlength) + " yrs");
        ui->cd2YearsLeftLabel->setText("Years Left: " + QString::number(yearsLeft));
        ui->cd2MinDepositLabel->setText("Min Deposit: $" + QString::number(minimumDeposit, 'f', 2));
        ui->cd2WithdrawButton->setEnabled(yearsLeft == 0);
        break;
    case 2:
        ui->cd3BalanceLabel->setText("Balance: $" + QString::number(newBalance, 'f', 2));
        ui->cd3InterestLabel->setText("Interest: " + QString::number(interestRate * 100, 'f', 2)
                                      + "%");
        ui->cd3TermLabel->setText("Term: " + QString::number(termlength) + " yrs");
        ui->cd3YearsLeftLabel->setText("Years Left: " + QString::number(yearsLeft));
        ui->cd3MinDepositLabel->setText("Min Deposit: $" + QString::number(minimumDeposit, 'f', 2));
        ui->cd3WithdrawButton->setEnabled(yearsLeft == 0);
        break;
    }
}

void MainWindow::updateStock(int stockNumber, double newBalance) {}

void MainWindow::updateLoan(int loanNumber, double newBalance, double interestRate, bool available, bool active, int yearsLeft){
    QString balanceText = QString::number(-newBalance, 'f', 2);
    QString status;

    if(loanNumber == 0) {
        ui->loan1InterestRate->setText("Interest: " + QString::number(interestRate*100, 'f', 1) + "%");

        if(available && !active) {
            ui->loan1Balance->setText("Loan Amount: $" + balanceText);
            ui->loan1YearsLeft->setText("Term Length: " + QString::number(yearsLeft));
            ui->activateLoan1Button->setEnabled(true);
            status = "Available";
        } else if(active) {
            ui->loan1Balance->setText("Outstanding Balance: $" + balanceText);
            ui->loan1YearsLeft->setText("Years Left: " + QString::number(yearsLeft));
            status = "Active";
            ui->activateLoan1Button->setEnabled(false);
        } else {
            ui->loan1Balance->setText("Loan Amount: $" + balanceText);
            ui->loan1YearsLeft->setText("Term Length: " + QString::number(yearsLeft));
            status = "Unavailable";
            ui->activateLoan1Button->setEnabled(false);
        }
        ui->loan1AvailabilityStatus->setText("Status: " + status);
    }
    else {
        ui->loan2InterestRate->setText("Interest: " + QString::number(interestRate*100, 'f', 1) + "%");

        if(available && !active) {
            ui->loan2Balance->setText("Loan Amount: $" + balanceText);
            ui->loan2YearsLeft->setText("Term Length: " + QString::number(yearsLeft));
            ui->activateLoan2Button->setEnabled(true);
            status = "Available";
        } else if(active) {
            ui->loan2Balance->setText("Outstanding Balance: $" + balanceText);
            ui->loan2YearsLeft->setText("Years Left: " + QString::number(yearsLeft));
            status = "Active";
            ui->activateLoan2Button->setEnabled(false);
        } else {
            ui->loan2Balance->setText("Loan Amount: $" + balanceText);
            ui->loan2YearsLeft->setText("Term Length: " + QString::number(yearsLeft));
            status = "Unavailable";
            ui->activateLoan2Button->setEnabled(false);
        }
        ui->loan2AvailabilityStatus->setText("Status: " + status);
    }
}
void MainWindow::startQuiz(QuizCategory category, uint questionAmount){
    emit requestQuiz(category, questionAmount);
    updateProgress(0);
    ui->stackedWidget->setCurrentWidget(ui->Quiz);
}


void MainWindow::showErrorMessage(QString errorMessage) {
    QMessageBox::warning(this, "Warning", errorMessage);
}

void MainWindow::enableSubmitButton(bool checked)
{
    if (checked) {
        ui->submitButton->setEnabled(true);
    }
}

void MainWindow::showEndScreen(uint questionsAnsweredCorrectly, int moneyEarned)
{
    ui->cashBalance->hide();
    ui->creditLabel->hide();
    ui->networthLabel->hide();
    ui->stackedWidget->setCurrentWidget(ui->quizEnd);
    double percentage = ((double)questionsAnsweredCorrectly / quizLength) * 100;
    ui->scoreLabel->setText(QString::number(questionsAnsweredCorrectly) + " / " +  QString::number(quizLength));
    ui->percentage->setText(QString::number(percentage, 'f', 2) + "%");
    if(percentage < 60){
        ui->scoreLabel->setStyleSheet("QLabel {color: red; font-weight: bold; font-size: 50px;}");
        ui->percentage->setStyleSheet("QLabel {color: red; font-weight: bold; font-size: 50px;}");
    }
    else{
        ui->scoreLabel->setStyleSheet("QLabel {color:  #85bb65; font-weight: bold; font-size: 50px;}");
        ui->percentage->setStyleSheet("QLabel {color: #85bb65; font-weight: bold; font-size: 50px;}");
    }
    ui->moneyEarned->setText("$" + QString::number(moneyEarned));
}

void MainWindow::updateStockPriceDisplay(double amount, int stockNumber)
{
    switch (stockNumber) {
    case 0: {
        ui->totalPriceStockOne->setText("$" + QString::number(amount, 'f', 2));
        if (amount > currentMoney) {
            ui->totalPriceStockOne->setStyleSheet("color: red; font-weight: bold; font-size: 20px;");
            ui->purchaseStockOneButton->setEnabled(false);
        } else {
            ui->totalPriceStockOne->setStyleSheet("QLabel {color: #85bb65; font-weight: bold; font-size: 20px;}");
            ui->purchaseStockOneButton->setEnabled(true);
        }
        ui->totalPriceStockOne->adjustSize();
        break;
    }
    case 1: {
        ui->totalPriceStockTwo->setText("$" + QString::number(amount, 'f', 2));
        if (amount > currentMoney) {
            ui->totalPriceStockTwo->setStyleSheet("color: red; font-weight: bold; font-size: 20px;");
            ui->purchaseStockTwoButton->setEnabled(false);
        } else {
            ui->totalPriceStockTwo->setStyleSheet("QLabel {color: #85bb65; font-weight: bold; font-size: 20px;}");
            ui->purchaseStockTwoButton->setEnabled(true);
        }
        ui->totalPriceStockTwo->adjustSize();
        break;
    }
    case 2: {
        ui->totalPriceStockThree->setText("$" + QString::number(amount, 'f', 2));
        if (amount > currentMoney) {
            ui->totalPriceStockThree->setStyleSheet("color: red; font-weight: bold; font-size: 20px;");
            ui->purchaseStockThreeButton->setEnabled(false);
        } else {
            ui->totalPriceStockThree->setStyleSheet("QLabel {color: #85bb65; font-weight: bold; font-size: 20px;}");
            ui->purchaseStockThreeButton->setEnabled(true);
        }
        ui->totalPriceStockTwo->adjustSize();
        break;
    }
    default: {
        break;
    }
    }
}

void MainWindow::updateSellingStockPriceDisplay(double amount, int stockNumber, bool tooMany)
{
    switch (stockNumber) {
    case 0: {
        ui->sellingTotalPriceStockOne->setText("$" + QString::number(amount, 'f', 2));
        if (tooMany) {
            ui->sellingTotalPriceStockOne->setStyleSheet("color: red; font-weight: bold; font-size: 20px;");
            ui->sellButtonStockOne->setEnabled(false);
        } else {
            ui->sellingTotalPriceStockOne->setStyleSheet("QLabel {color: #85bb65; font-weight: bold; font-size: 20px;};");
            ui->sellButtonStockOne->setEnabled(true);
        }
        ui->sellingTotalPriceStockOne->adjustSize();
        break;
    }
    case 1: {
        ui->sellingTotalPriceStockTwo->setText("$" + QString::number(amount, 'f', 2));
        if (tooMany) {
            ui->sellingTotalPriceStockTwo->setStyleSheet("color: red; font-weight: bold; font-size: 20px;");
            ui->sellButtonStockTwo->setEnabled(false);
        } else {
            ui->sellingTotalPriceStockTwo->setStyleSheet("QLabel {color: #85bb65; font-weight: bold; font-size: 20px;}");
            ui->sellButtonStockTwo->setEnabled(true);
        }
        ui->sellingTotalPriceStockTwo->adjustSize();
        break;
    }
    case 2: {
        ui->sellingTotalPriceStockThree->setText("$" + QString::number(amount, 'f', 2));
        if (tooMany) {
            ui->sellingTotalPriceStockThree->setStyleSheet("color: red; font-weight: bold; font-size: 20px;");
            ui->sellButtonStockThree->setEnabled(false);
        } else {
            ui->sellingTotalPriceStockThree->setStyleSheet("QLabel {color: #85bb65; font-weight: bold; font-size: 20px;}");
            ui->sellButtonStockThree->setEnabled(true);
        }
        ui->sellingTotalPriceStockThree->adjustSize();
        break;
    }
    default: {
        break;
    }
    }
}

void MainWindow::revalidateAllStockDisplays()
{
    emit requestPriceOfXStocks(ui->purchaseStockOneSpin->value(), 0);
    emit requestPriceOfXStocks(ui->purchaseStockTwoSpin->value(), 1);

    emit requestPriceOfXStocks(ui->purchaseStockThreeSpin->value(), 2);
}

void MainWindow::updateStockAmountOwned(uint amount, int stockNumber)
{
    switch (stockNumber) {
    case 0: {
        ui->ownedStockOne->setText("Amount Owned: " + QString::number(amount));
        break;
    }
    case 1: {
        ui->ownedStockTwo->setText("Amount Owned: " + QString::number(amount));
        break;
    }
    case 2: {
        ui->ownedStockThree->setText("Amount Owned: " + QString::number(amount));
        break;
    }
    default: {
        break;
    }
    }
}

void MainWindow::updateStockImage(bool stockOneUp, bool stockTwoUp, bool stockThreeUp){
    if(stockOneUp){
        QPixmap pixmap(":///icons/icons/stock.png");
        ui->stockImageOne->setPixmap(pixmap);
    }
    else{
        QPixmap pixmap(":///icons/icons/StockDown.png");
        ui->stockImageOne->setPixmap(pixmap);
    }

    if(stockTwoUp){
        QPixmap pixmap(":///icons/icons/stock.png");
        ui->stockImageTwo->setPixmap(pixmap);
    }
    else{
        QPixmap pixmap(":///icons/icons/StockDown.png");
        ui->stockImageTwo->setPixmap(pixmap);
    }

    if(stockThreeUp){
        QPixmap pixmap(":///icons/icons/stock.png");
        ui->stockImageThree->setPixmap(pixmap);
    }
    else{
        QPixmap pixmap(":///icons/icons/StockDown.png");
        ui->stockImageThree->setPixmap(pixmap);
    }
}



void MainWindow::newYear(QVector<double> newTotals, QVector<double> changes, int currentYear, double yearlyBills)
{
    switch(14 - currentYear){
        case 12:{
            quizCategory = QuizCategory::savings;
            break;
        }
        case 11:{
            quizCategory = QuizCategory::stocks;
            QPixmap pixmap(":///icons/icons/stockApp.png");
            ui->App1->setIcon(pixmap);
            ui->App1->setEnabled(true);
            break;
        }
        case 10:{
            quizCategory = QuizCategory::cds;
            QPixmap pixmap(":///icons/icons/cdApp.png");
            ui->App2->setIcon(pixmap);
            ui->App2->setEnabled(true);
            break;
        }
        case 9:{
            quizCategory = QuizCategory::loans;
            // QPixmap pixmap(":///icons/icons/loanIcon.png");
            // ui->App2->setIcon(pixmap);
            ui->App2->setEnabled(true);
            break;
        }
        case 8:{
            quizCategory = QuizCategory::gambling;
            // QPixmap pixmap(":///icons/icons/casinoIcon.png");
            // ui->App6->setIcon(pixmap);
            break;
        }
        default:{
            quizCategory = QuizCategory::mixOfAll;
            break;
        }
    }
    quizLength = 5;
    emit requestQuiz(quizCategory, quizLength);
    onStartClicked();
    ui->billbalance->setText("$"+ QString::number(yearlyBills));
    // Set current year label and button
    ui->currentYear->setText("YEARS REMAINING: " + QString::number(15 - currentYear));
    ui->nextYearButton->setText("End Year " + QString::number(currentYear));
    ui->continueButton->setText("Continute to Year " +  QString::number(currentYear));

    // Set yearly report
    ui->yearlyReportLabel->setText(generateReportString(newTotals, changes));

    lifeEventShown = false;
}

void MainWindow::gameEnded(QString reason, QString imageName) {
    ui->cashBalance->hide();
    ui->creditLabel->hide();
    ui->networthLabel->hide();

    ui->stackedWidget->setCurrentWidget(ui->gameEnd);
    ui->reasonLabel->setText(reason);
    ui->reasonLabel->adjustSize();
    ui->endCashBalance->setText("End " + ui->cashBalance->text());
    ui->endCashBalance->adjustSize();
    ui->endCredit->setText("End " + ui->creditLabel->text());
    ui->endCredit->adjustSize();
    ui->endNetWorth->setText("End " + ui->networthLabel->text());
    ui->endNetWorth->adjustSize();

    std::string networthString = ui->endNetWorth->text().toStdString();
    std::string networthNum = networthString.substr(16);
    double networth = std::stod(networthNum);

    std::string creditStr = ui->endCredit->text().toStdString();
    std::string creditNum = creditStr.substr(12);
    int credit = std::stoi(creditNum);

    if(currentMoney < 0){
        ui->endCashBalance->setStyleSheet("QLabel {color: red;   font-weight: bold; font-size: 30px;}");
    }

    if(networth < 0){
        ui->endNetWorth->setStyleSheet("QLabel {color: red;   font-weight: bold; font-size: 30px;}");
    }

    if(credit < 650){
        ui->endCredit->setStyleSheet("QLabel {color: red;   font-weight: bold; font-size: 30px;}");
    }

    if(credit >=850){
        rankToDisplay = "World Renowned Investing Expert";
        ui->rank->setText("RANK: World Renowned Investing Expert");
    }
    else if(credit > 800){
        rankToDisplay = "Investing Mogul";
        ui->rank->setText("RANK: Investing Mogul");
    }
    else if(credit > 775){
        rankToDisplay = "Investing Pro";
         ui->rank->setText("RANK: Investing Pro");
    }
    else if(credit > 739){
        rankToDisplay = "Responsible Citizen";
        ui->rank->setText("RANK: Responsible Citizen");
    }
    else if(credit > 670){
        rankToDisplay = "Average Citizen";
        ui->rank->setText("RANK: Average Citizen");
    }
    else if(credit > 630){
        rankToDisplay = "Bad Investor";
        ui->rank->setText("RANK: Bad Investor");
    }
    else if(credit > 300){
        rankToDisplay = "Gambler";
        ui->rank->setText("RANK: Gambler");
    }
    else{
        rankToDisplay = "Nandhini";
        ui->rank->setText("RANK: Nandhini");
    }

    ui->rank->adjustSize();
    QPixmap pixmap(":///icons/icons/" + imageName);
    ui->endImage->setPixmap(pixmap);
}

QString MainWindow::generateReportString(QVector<double> newTotals, QVector<double> changes) {
    QString reportString;

    reportString.append("<p style='line-height:1.4'><font size='4'><u>Yearly Report: </u></font>");

    reportString.append("<table cellpadding='2'>");

    // Add savings account
    reportString.append("</td></tr><tr><td>Savings Account:</td><td> $" + QString::number(newTotals[0], 'f', 2));
    if (changes[0] > 0)
        reportString.append("<font color=#85bb65>+$" + QString::number(changes[0], 'f', 2));

    // Add cd accounts
    reportString.append("</font></td></tr><tr><td>CDs Total:</td><td> $" + QString::number(newTotals[1], 'f', 2));
    if (changes[1] > 0)
        reportString.append("<font color=#85bb65> +$" + QString::number(changes[1], 'f', 2));

    // Add stocks
    reportString.append("</font></td></tr><tr><td>Stocks Total:</td><td> $" + QString::number(newTotals[2], 'f', 2));
    if (changes[2] > 0)
        reportString.append("<font color=#85bb65> +$" + QString::number(changes[2], 'f', 2));
    else if (changes[2] < 0)
        reportString.append("<font color='red'> -$" + QString::number(-changes[2], 'f', 2));

    // Add loans
    if (newTotals[3] < 0)
        reportString.append("</font></td></tr><tr><td>Loans Total:</td><td> -$" + QString::number(-newTotals[3], 'f', 2));
    else
        reportString.append("</font></td></tr><tr><td>Loans Total:</td><td> $" + QString::number(newTotals[3], 'f', 2));
    if (changes[3] < 0)
        reportString.append("<font color='red'> -$" + QString::number(-changes[3], 'f', 2));
    reportString.append("</font></td></tr></p>");

    return reportString;
}

void MainWindow::updateCreditScore(int score) {
    ui->creditLabel->setText("Credit: " + QString::number(score));
    if (score < 580) {
        ui->creditLabel->setStyleSheet("color: red; font-weight: bold; font-size: 30px;");
    } else if (score < 670) {
        ui->creditLabel->setStyleSheet("color: orange; font-weight: bold; font-size: 30px;");
    } else {
        ui->creditLabel->setStyleSheet("color: #85bb65; font-weight: bold; font-size: 30px;");
    }
}

void MainWindow::showLifeEvent(LifeEvent lifeEvent) {
    lifeEventDisplay.showLifeEvent(lifeEvent);
}

void MainWindow::showWarning(QString warning, QString image){
    warningDisplay.setModal(true);
    warningDisplay.show();
    warningDisplay.showWarning(warning, image);
}

void MainWindow::saveClicked(){
    emit sendName(ui->nameBox->toPlainText(), rankToDisplay);
}

void MainWindow::displayLeaderboard(QVector<QString> names, QVector<QString> credit, QVector<QString> rank){
    QString textToDisplay;
    foreach (QString row, names) {
        textToDisplay.append(row + "\n");
    }
    ui->leaderBoardNames->setText(textToDisplay);
    textToDisplay = "";
    foreach (QString row, credit) {
        textToDisplay.append(row + "\n");
    }
    ui->leaderBoardCredits->setText(textToDisplay);
    textToDisplay = "";
    foreach (QString row, rank) {
        textToDisplay.append(row + "\n");
    }
    ui->leaderBoardRanks->setText(textToDisplay);
    ui->stackedWidget->setCurrentWidget(ui->leaderBoardPage);
}

void MainWindow::displayInvalidName(){
    ui->nameBox->setText("");
    ui->nameBox->setPlaceholderText("Name is invalid try again");
}

void MainWindow::displaySaveSuccess(){
    ui->nameBox->setPlaceholderText("Saved Successfully!");
    ui->nameBox->setText("");
    ui->nameBox->setReadOnly(true);
    ui->saveButton->setEnabled(false);
}

void MainWindow::leaderBoardBack(){
    ui->stackedWidget->setCurrentWidget(ui->Start);
}

// CONNECTIONS ----------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::generalUISetup()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->choice1);
    buttonGroup->addButton(ui->choice2);
    buttonGroup->addButton(ui->choice3);
    buttonGroup->addButton(ui->choice4);
    ui->cashBalance->hide();
    ui->creditLabel->hide();
    ui->networthLabel->hide();

    startScreenView = new StartScreenView(ui->Start);
    startScreenView->stackUnder(ui->startButton);
    startScreenView->setGeometry(this->rect());
    startScreenView->show();

    animationView = new AnimationView(ui->Quiz);
    animationView->stackUnder(ui->choicesLayout);
    animationView->setGeometry(this->rect());
    animationView->hide();

    ui->yearlyReportLabel->setText(generateReportString({0,0,0,0,0,0}, {0,0,0,0,0,0}));

    quizCategory = QuizCategory::tutorial;
    quizLength = 1;
    firstStart = true;

    QDoubleValidator* decimalValidator = new QDoubleValidator(0, 1000000000000, 2);

    ui->cd1DepositInput->setValidator(decimalValidator);
    ui->cd2DepositInput->setValidator(decimalValidator);
    ui->cd3DepositInput->setValidator(decimalValidator);

    ui->savingsDepositInput->setValidator(decimalValidator);
    ui->savingsWithdrawInput->setValidator(decimalValidator);

    ui->loan1PaymentInput->setValidator(decimalValidator);
    ui->loan2PaymentInput->setValidator(decimalValidator);

    lifeEventShown = true;
    rankToDisplay = "";
}

void MainWindow::setUpGifs()
{
    QMovie *bankMovie = new QMovie(":/gifs/gifs/bank.gif");
    ui->bankGif->setMovie(bankMovie);
    bankMovie->setScaledSize(ui->bankGif->size());
    connect(bankMovie, &QMovie::finished, [bankMovie]() {
        bankMovie->setPaused(true); // Freeze on the last frame
    });
    bankMovie->start();

    QMovie *stocksMovie = new QMovie(":/gifs/gifs/bank.gif");
    ui->stockGif->setMovie(stocksMovie);
    stocksMovie->setScaledSize(ui->stockGif->size());
    connect(stocksMovie, &QMovie::finished, [stocksMovie]() {
        stocksMovie->setPaused(true); // freeze on the last frame
    });
    stocksMovie->start();

    QMovie *pigMovie = new QMovie(":/gifs/gifs/piggy.gif");
    ui->pigGif->setMovie(pigMovie);
    pigMovie->setScaledSize(ui->pigGif->size());
    pigMovie->start();

    QMovie *sharkMovie = new QMovie(":/gifs/gifs/shark.gif");
    ui->sharkGif->setMovie(sharkMovie);
    sharkMovie->setScaledSize(ui->sharkGif->size());
    sharkMovie->start();

    cupMovie = new QMovie(":/gifs/gifs/cupSwap.gif");
    ui->shuffleSpot->setMovie(cupMovie);
    // ensure we're at frame 0 initially
    cupMovie->jumpToFrame(0);
}

void MainWindow::setupAudio()
{
    levelPassSound = new QSoundEffect(this);
    levelPassSound->setSource(QUrl("qrc:/sounds/sounds/level-up-sound.wav"));
    levelFailSound = new QSoundEffect(this);
    levelFailSound->setSource(QUrl("qrc:/sounds/sounds/wrong.wav"));
    depositSound = new QSoundEffect(this);
    depositSound->setSource(QUrl("qrc:/sounds/sounds/cash-register.wav"));

    //Experimental Music stuff
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;

    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.25);

    player->setSource(QUrl("qrc:/sounds/sounds/ElvisHerod-Clutterbuck.mp3"));
    player->setLoops(QMediaPlayer::Infinite);

    player->play();
}

void MainWindow::enableQuizSubmission()
{
    connect(ui->choice1, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice2, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice3, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice4, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
}

void MainWindow::quizConnections(MainModel *model)
{
    connect(model, &MainModel::sendQuestion, this, &MainWindow::showQuizData);
    connect(model, &MainModel::sendQuizInfo, this, &MainWindow::updateQuizInfo);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);

    //make a show quiz info, then make that button on page start quiz
    connect(ui->startQuizButton, &QPushButton::clicked, this, [this]() {
        startQuiz(quizCategory, quizLength);
    });
    connect(this, &MainWindow::requestQuiz, model, &MainModel::quizRequested);
    connect(ui->nextButton, &QPushButton::clicked, model, &MainModel::getNextQuestion);
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::submitHelper);

    connect(this, &MainWindow::sendAnswer, model, &MainModel::checkAnswer);
    connect(model, &MainModel::sendResult, this, &MainWindow::displayResult);
    connect(model, &MainModel::quizProgress, this, &MainWindow::updateProgress);
    connect(model, &MainModel::quizFinished, this, &MainWindow::showEndScreen);

    //DEVELOPMENT CONNECTION
    connect(ui->skipQuizButton, &QPushButton::clicked, this, [&] ()->void{
        showEndScreen(0,0);
    });
}

void MainWindow::depositingConnectionWindowToModel(MainModel *model)
{
    connect(this, &MainWindow::depositToSavings, model, &MainModel::depositToSavings);
    //connect(this, &MainWindow::depositToChecking, model, &MainModel::depositToChecking);
    connect(this, &MainWindow::depositToCD, model, &MainModel::depositToCD);
    connect(this, &MainWindow::depositToLoan, model, &MainModel::depositToLoan);
    connect(this, &MainWindow::buyStock, model, &MainModel::buyStock);
}

void MainWindow::withdrawingConnectionsWindowToModel(MainModel *model)
{
    connect(this, &MainWindow::withdrawFromSavings, model, &MainModel::withdrawFromSavings);
    //connect(this, &MainWindow::withdrawFromChecking, model, &MainModel::withdrawFromChecking);
    connect(this, &MainWindow::withdrawFromCD, model, &MainModel::withdrawFromCD);
    connect(this, &MainWindow::sellStock, model, &MainModel::sellStock);
    connect(this, &MainWindow::activateLoan, model, &MainModel::activateLoan);
}

void MainWindow::mainWindowValueUpdateConnections(MainModel *model)
{
    connect(model, &MainModel::updateSavings, this, &MainWindow::updateSavings);
    //connect(model, &MainModel::updateChecking, this, &MainWindow::updateChecking);
    connect(model, &MainModel::updateCD, this, &MainWindow::updateCD);
    connect(model, &MainModel::updateStock, this, &MainWindow::updateStock);
    connect(model, &MainModel::updateLoan, this, &MainWindow::updateLoan);
    connect(model, &MainModel::creditScoreChanged, this, &MainWindow::updateCreditScore);
}

void MainWindow::buyingStockUIConnections()
{
    connect(ui->purchaseStockOneButton, &QPushButton::clicked, this, [&]() -> void {
        emit buyStock(ui->purchaseStockOneSpin->value(), 0);
        ui->purchaseStockOneSpin->setValue(0);
        emit revalidateStockDisplay();
    });
    connect(ui->purchaseStockTwoButton, &QPushButton::clicked, this, [&]() -> void {
        emit buyStock(ui->purchaseStockTwoSpin->value(), 1);
        ui->purchaseStockTwoSpin->setValue(0);
        emit revalidateStockDisplay();
    });
    connect(ui->purchaseStockThreeButton, &QPushButton::clicked, this, [&]() -> void {
        emit buyStock(ui->purchaseStockThreeSpin->value(), 2);
        ui->purchaseStockThreeSpin->setValue(0);
        emit revalidateStockDisplay();
    });
}

void MainWindow::sellingStockUIConnections()
{
    connect(ui->sellButtonStockOne, &QPushButton::clicked, this, [&]() -> void {
        emit sellStock(ui->sellSpinStockOne->value(), 0);
        ui->sellSpinStockOne->setValue(0);
    });
    connect(ui->sellButtonStockTwo, &QPushButton::clicked, this, [&]() -> void {
        emit sellStock(ui->sellSpinStockTwo->value(), 1);
        ui->sellSpinStockTwo->setValue(0);
    });
    connect(ui->sellButtonStockThree, &QPushButton::clicked, this, [&]() -> void {
        emit sellStock(ui->sellSpinStockThree->value(), 2);
        ui->sellSpinStockThree->setValue(0);
    });
}

void MainWindow::visualIUpdatesStockConnections(MainModel *model)
{
    connect(this, &MainWindow::revalidateStockDisplay,this, &MainWindow::revalidateAllStockDisplays);
    connect(this, &MainWindow::revalidateSpecificStockDisplay,this, &MainWindow::updateStockPriceDisplay);
    connect(model, &MainModel::numberOfStocksOwned, this, &MainWindow::updateStockAmountOwned);

    // Update price buying
    connect(ui->purchaseStockOneSpin, &QSpinBox::valueChanged, this, [&]() -> void {
        emit requestPriceOfXStocks(ui->purchaseStockOneSpin->value(), 0);
    });
    connect(ui->purchaseStockTwoSpin, &QSpinBox::valueChanged, this, [&]() -> void {
        emit requestPriceOfXStocks(ui->purchaseStockTwoSpin->value(), 1);
    });
    connect(ui->purchaseStockThreeSpin, &QSpinBox::valueChanged, this, [&]() -> void {
        emit requestPriceOfXStocks(ui->purchaseStockThreeSpin->value(), 2);
    });
    connect(this, &MainWindow::requestPriceOfXStocks, model, &MainModel::sendPriceOfXStocks);
    connect(model, &MainModel::sendPriceOfStocks, this, &MainWindow::updateStockPriceDisplay);

    //Update price selling
    connect(ui->sellSpinStockOne, &QSpinBox::valueChanged, this, [&]() -> void {
        emit requestSellingPriceOfXStocks(ui->sellSpinStockOne->value(), 0);
    });
    connect(ui->sellSpinStockTwo, &QSpinBox::valueChanged, this, [&]() -> void {
        emit requestSellingPriceOfXStocks(ui->sellSpinStockTwo->value(), 1);
    });
    connect(ui->sellSpinStockThree, &QSpinBox::valueChanged, this, [&]() -> void {
        emit requestSellingPriceOfXStocks(ui->sellSpinStockThree->value(), 2);
    });

    connect(this,
            &MainWindow::requestSellingPriceOfXStocks,
            model,
            &MainModel::sendSellingPriceOfXStocks);
    connect(model,
            &MainModel::sendSellingPriceOfStocks,
            this,
            &MainWindow::updateSellingStockPriceDisplay);

    //UPDATE STOCK IMAGE
    connect(model, &MainModel::stockChange, this, &MainWindow::updateStockImage);

    //Stocks go back button
    connect(ui->stocksBackButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    });
}

void MainWindow::cdPageConnections(MainModel *model)
{
    connect(ui->App2, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->CD);
        for (int i = 0; i < 3; ++i) {
            emit requestCDInfo(i);
        }
    });

    connect(this, &MainWindow::requestCDInfo, model, &MainModel::updateCDInformation);

    connect(ui->cdBackButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    });

    connect(ui->cd1WithdrawButton, &QPushButton::clicked, this, [this]() {
        emit withdrawFromCD(0);
    });
    connect(ui->cd2WithdrawButton, &QPushButton::clicked, this, [this]() {
        emit withdrawFromCD(1);
    });
    connect(ui->cd3WithdrawButton, &QPushButton::clicked, this, [this]() {
        emit withdrawFromCD(2);
    });

    // connect(ui->cd1DepositButton, &QPushButton::clicked, this, &MainWindow::displayDepositPage);
    // connect(ui->cd2DepositButton, &QPushButton::clicked, this, &MainWindow::displayDepositPage);
    // connect(ui->cd3DepositButton, &QPushButton::clicked, this, &MainWindow::displayDepositPage);

    connect(ui->cd1DepositButton, &QPushButton::clicked, this, [this]() {
        double amount = ui->cd1DepositInput->text().toDouble();
        emit depositToCD(amount, 0);
        ui->cd1DepositInput->clear();
    });
    connect(ui->cd2DepositButton, &QPushButton::clicked, this, [this]() {
        double amount = ui->cd2DepositInput->text().toDouble();
        emit depositToCD(amount, 1);
        ui->cd2DepositInput->clear();
    });
    connect(ui->cd3DepositButton, &QPushButton::clicked, this, [this]() {
        double amount = ui->cd3DepositInput->text().toDouble();
        emit depositToCD(amount, 2);
        ui->cd3DepositInput->clear();
    });
}

void MainWindow::savingsPageConnections(MainModel *model)
{
    connect(ui->App3, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->Bank);
    });

    connect(ui->bankBackButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    });

    connect(ui->savingsDepositButton, &QPushButton::clicked, this, [this]() {
        double updatedSavings = ui->savingsDepositInput->text().toDouble();
        emit savingsDepositAmountRead(updatedSavings);
        ui->savingsDepositInput->clear();
        depositSound->play();

    });
    connect(this, &MainWindow::savingsDepositAmountRead, model, &MainModel::depositToSavings);
    connect(model, &MainModel::updateSavings, this, &MainWindow::updateSavings);

    connect(ui->savingsWithdrawButton, &QPushButton::clicked, this, [this]() {
        double updatedSavings = ui->savingsWithdrawInput->text().toDouble();
        emit savingsWithdrawAmountRead(updatedSavings);
        ui->savingsWithdrawInput->clear();
    });

    //connect(this, &MainWindow::checkingWithdrawAmountRead, model, &MainModel::withdrawFromChecking);

    connect(this, &MainWindow::savingsWithdrawAmountRead, model, &MainModel::withdrawFromSavings);
}

void MainWindow::loansPageConnections(MainModel *model)
{
    connect(ui->App4, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->Loans);
        emit requestLoanInfo(0);
        emit requestLoanInfo(1);
    });

    connect(this, &MainWindow::requestLoanInfo, model, &MainModel::handleLoanInfoRequest);

    connect(ui->loanBackButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    });

    connect(ui->activateLoan1Button, &QPushButton::clicked, this, [this]() {
        emit activateLoan(0);
    });
    connect(ui->activateLoan2Button, &QPushButton::clicked, this, [this]() {
        emit activateLoan(1);
    });

    connect(ui->payLoan1Button, &QPushButton::clicked, this, [this]() {
        QString input = ui->loan1PaymentInput->text();
        bool ok;
        double amount = input.toDouble(&ok);

        if (input.isEmpty() || !ok || amount <= 0) {
            showErrorMessage("Invalid loan amount!");
            return;
        }

        emit depositToLoan(amount, 0);
        ui->loan1PaymentInput->clear();
    });

    connect(ui->payLoan2Button, &QPushButton::clicked, this, [this]() {
        QString input = ui->loan2PaymentInput->text().trimmed();
        bool ok;
        double amount = input.toDouble(&ok);

        if (input.isEmpty() || !ok || amount <= 0) {
            showErrorMessage("Invalid loan amount!");
            return;
        }

        emit depositToLoan(amount, 1);
        ui->loan2PaymentInput->clear();
    });
}

void MainWindow::casinoPageConnections(MainModel *model)
{
    connect(ui->App6, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->Casino);
    });

    connect(ui->casinoBackButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    });

    connect(ui->gambleButton, &QPushButton::clicked, model, &MainModel::startGamble);

    connect(model, &MainModel::shuffleStarted, this, [this]() {
        if (cupMovie) {
            cupMovie->stop();
            cupMovie->deleteLater(); // schedule for deletion
            cupMovie = nullptr;
        }

        cupMovie = new QMovie(":/gifs/gifs/cupSwap.gif");
        ui->shuffleSpot->setMovie(cupMovie);
        // freeze on last frame and enable buttons
        connect(cupMovie, &QMovie::finished, this, [this]() {
            cupMovie->setPaused(true);
            ui->cup1->setEnabled(true);
            ui->cup2->setEnabled(true);
            ui->cup3->setEnabled(true);
            ui->gambleButton->setText("Pick a cup");
        });
        // play gif
        cupMovie->start();
        ui->gambleButton->setText("Shuffling...");
        // disable buttons during shuffle
        ui->gambleButton->setDisabled(true);
        ui->cup1->setDisabled(true);
        ui->cup2->setDisabled(true);
        ui->cup3->setDisabled(true);
    });

    connect(ui->cup1, &QPushButton::clicked, model, [model]() { model->checkCup(0); });
    connect(ui->cup2, &QPushButton::clicked, model, [model]() { model->checkCup(1); });
    connect(ui->cup3, &QPushButton::clicked, model, [model]() { model->checkCup(2); });

    connect(model, &MainModel::gambleResult, this, [this](bool won, int amount) {
        ui->gambleButton->setEnabled(true);
        ui->gambleButton->setText("$1000");
        // disable cup buttons
        ui->cup1->setEnabled(false);
        ui->cup2->setEnabled(false);
        ui->cup3->setEnabled(false);
        if(won) {
            QMessageBox::information(this, "Winner!", QString("+$%1!").arg(amount));
        } else {
            QMessageBox::information(this, "Loser!", "Wrong Cup, Keep Gambling!!!");
        }
    });
}

void MainWindow::nextYearConnections(MainModel *model)
{
    connect(ui->nextYearButton, &QPushButton::clicked, model, &MainModel::nextYear);
    connect(this, &MainWindow::nextYear, model, &MainModel::nextYear);
    connect(model, &MainModel::newYear, this, &MainWindow::newYear);
}

void MainWindow::phoneConnections()
{
    connect(ui->openPhoneButton, &QPushButton::clicked, this, &MainWindow::displayPhone);
    connect(ui->closePhoneButton, &QPushButton::clicked, this, &MainWindow::hidePhone);
}

void MainWindow::extraQuizesPageConnections(MainModel *model)
{
    connect(ui->App5, &QPushButton::clicked, model, &MainModel::handleExtraQuizRequest);

    connect(model, &MainModel::quizzesRemainingChanged, this, [this](int remaining) {
        ui->quizRemains->setText("Extra Quizzes Remaining: " + QString::number(remaining));
    });

    connect(model, &MainModel::quizStarted, this, [this]() {
        quizCategory = QuizCategory::mixOfAll;
        quizLength = 5;
        ui->stackedWidget->setCurrentWidget(ui->quizInfo);
    });
}

void MainWindow::lifeEventsConnections(MainModel *model)
{
    connect(ui->continueButton, &QPushButton::clicked, this, [this]() {
        if (!lifeEventShown) {
            emit requestLifeEvent();
            lifeEventShown = true;
            lifeEventDisplay.setModal(true);
            lifeEventDisplay.show();
        }
    });

    connect(this, &MainWindow::requestLifeEvent, model, &MainModel::randomLifeEvent);
    connect(model, &MainModel::displayLifeEvent, this, &MainWindow::showLifeEvent);
}

void MainWindow::shopItemsConnections(MainModel *model)
{
    connect(ui->autoInsurance, &QPushButton::clicked, this, [=]() {
        emit shopItemClicked(0);
    });

    connect(ui->healthInsurance, &QPushButton::clicked, this, [=]() {
        emit shopItemClicked(1);
    });

    connect(ui->petInsurance, &QPushButton::clicked, this, [=]() {
        emit shopItemClicked(2);
    });

    connect(ui->homeInsurance, &QPushButton::clicked, this, [=]() {
        emit shopItemClicked(3);
    });

    connect(this, &MainWindow::shopItemClicked, model, &MainModel::purchaseShopItem);

    connect(model, &MainModel::shopItemPurchased, this, [=](int index) {
        if (index == 0) {
            ui->autoInsurance->setEnabled(false);
        } else if (index == 1) {
            ui->healthInsurance->setEnabled(false);
        } else if (index == 2) {
            ui->petInsurance->setEnabled(false);
        } else {
            ui->homeInsurance->setEnabled(false);
        }
    });
}

void MainWindow::databaseConnections(MainModel *model){

    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveClicked);
    connect(ui->leaderBoardButton, &QPushButton::clicked, model, &MainModel::getLeaderboard);
    connect(model, &MainModel::showLeaderBoard, this, &MainWindow::displayLeaderboard);
    connect(model, &MainModel::invalidName, this, &MainWindow::displayInvalidName);
    connect(model, &MainModel::saved, this, &MainWindow::displaySaveSuccess);
    connect(this, &MainWindow::sendName, model, &MainModel::saveGame);
    connect(ui->leaderBoardBackButton, &QPushButton::clicked, this, &MainWindow::leaderBoardBack);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

