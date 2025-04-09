#include "mainwindow.h"
#include <QMovie>
#include "iostream"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MainModel *model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->Start);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->choice1);
    buttonGroup->addButton(ui->choice2);
    buttonGroup->addButton(ui->choice3);
    buttonGroup->addButton(ui->choice4);
    ui->balance->hide();

    startScreenView = new StartScreenView(ui->Start);
    startScreenView->stackUnder(ui->startButton);
    startScreenView->setGeometry(this->rect());
    startScreenView->show();

    animationView = new AnimationView(ui->Quiz);
    animationView->stackUnder(ui->choicesLayout);
    animationView->setGeometry(this->rect());
    animationView->hide();

    ui->yearlyReportLabel->setText(generateReportString({0,0,0,0,0}, {0,0,0,0,0}));

    // Experimental gif stuff, not permanent
    QMovie *bankMovie = new QMovie(":/gifs/gifs/bank.gif");
    ui->bankGif->setMovie(bankMovie);
    bankMovie->setScaledSize(ui->bankGif->size());
    connect(bankMovie, &QMovie::finished, [bankMovie]() {
        bankMovie->setPaused(true); // Freeze on the last frame
    });
    bankMovie->start();

    // connections for buttons to enable submitting
    connect(ui->choice1, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice2, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice3, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice4, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);

    connect(model, &MainModel::sendQuestion, this, &MainWindow::showQuizData);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->startButton, &QPushButton::clicked, model, &MainModel::requestQuiz);
    connect(ui->nextButton, &QPushButton::clicked, model, &MainModel::getNextQuestion);
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::submitHelper);
    connect(ui->continueButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
        ui->balance->show();
    });
    connect(ui->App1, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->Stocks);
    });
    connect(ui->stocksBackButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    });
    connect(model, &MainModel::returnToGame, this, &MainWindow::returnToGame);
    connect(this, &MainWindow::settingsOpened, model, &MainModel::settingsOpened);
    connect(ui->settingsButton, &QPushButton::clicked, this, [this]() {
        ui->settingsButton->hide();
        ui->balance->hide();
        emit settingsOpened(ui->stackedWidget->currentWidget());
        ui->stackedWidget->setCurrentWidget(ui->Settings);
    });
    connect(ui->settingsBackButton, &QPushButton::clicked, model, &MainModel::settingsClosed);

    // phone connections
    connect(ui->openPhoneButton, &QPushButton::clicked, this, &MainWindow::displayPhone);
    connect(ui->closePhoneButton, &QPushButton::clicked, this, &MainWindow::hidePhone);

    connect(this, &MainWindow::sendAnswer, model, &MainModel::checkAnswer);
    connect(model, &MainModel::sendResult, this, &MainWindow::displayResult);
    connect(model, &MainModel::quizProgress, this, &MainWindow::updateProgress);

    connect(model, &MainModel::quizFinished, this, &MainWindow::showEndScreen);

    // connections for nextYear
    connect(ui->nextYearButton, &QPushButton::clicked, model, &MainModel::nextYear);
    connect(this, &MainWindow::nextYear, model, &MainModel::nextYear);
    connect(model, &MainModel::newYear, this, &MainWindow::newYear);

    // connections for depositing
    connect(this, &MainWindow::depositToSavings, model, &MainModel::depositToSavings);
    connect(this, &MainWindow::depositToCD, model, &MainModel::depositToCD);
    connect(this, &MainWindow::depositToLoan, model, &MainModel::depositToLoan);
    connect(this, &MainWindow::buyStock, model, &MainModel::buyStock);
    connect(model, &MainModel::updateBalance, this, &MainWindow::updateBalance);

    // connections for withdrawing
    connect(this, &MainWindow::withdrawFromSavings, model, &MainModel::withdrawFromSavings);
    connect(this, &MainWindow::withdrawFromCD, model, &MainModel::withdrawFromCD);
    connect(this, &MainWindow::sellStock, model, &MainModel::sellStock);
    connect(this, &MainWindow::activateLoan, model, &MainModel::activateLoan);

    // connections for updating MainWindow values
    connect(model, &MainModel::updateSavings, this, &MainWindow::updateSavings);
    connect(model, &MainModel::updateCD, this, &MainWindow::updateCD);
    connect(model, &MainModel::updateStock, this, &MainWindow::updateStock);
    connect(model, &MainModel::updateLoan, this, &MainWindow::updateLoan);

    // connection for showing error messages
    connect(model, &MainModel::showErrorMessage, this, &MainWindow::showErrorMessage);

    // connections for buying and selling stock

    // Buys stock
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

    connect(this,
            &MainWindow::revalidateStockDisplay,
            this,
            &MainWindow::revalidateAllStockDisplays);
    connect(this,
            &MainWindow::revalidateSpecificStockDisplay,
            this,
            &MainWindow::updateStockPriceDisplay);

    // Sell Stock
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
    // View protection of selling/buying is done in update price label...

    // Connect CD page signals

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

    //App 3 -savings

    connect(ui->App3, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->Bank);
    });

    // connect(ui->savingsDepositButton, &QPushButton::clicked, this, &MainWindow::displayDepositPage);

    connect(ui->bankBackButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    });

    connect(ui->savingsDepositButton, &QPushButton::clicked, this, &MainWindow::readSavingsAmount);
    connect(this, &MainWindow::amountRead, model, &MainModel::depositToSavings);
    connect(model, &MainModel::updateSavings, this, &MainWindow::updateSavings);

    // Start button connections for pressed
    connect(ui->startButton, &QPushButton::pressed, [=]() {
        ui->startButton->setIcon(QIcon(":///icons/icons/startClick.png"));
        ui->startButton->setIconSize(QSize(150, 200));
    });

    // Sounds
    levelPassSound = new QSoundEffect(this);
    levelPassSound->setSource(QUrl("qrc:/sounds/sounds/level-up-sound.wav"));
    levelFailSound = new QSoundEffect(this);
    levelFailSound->setSource(QUrl("qrc:/sounds/sounds/wrong.wav"));

    //App 4 - LOANS connecytions
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
        double amount = ui->loan1PaymentInput->text().toDouble();
        emit depositToLoan(amount, 0);
        ui->loan1PaymentInput->clear();
    });
    connect(ui->payLoan2Button, &QPushButton::clicked, this, [this]() {
        double amount = ui->loan2PaymentInput->text().toDouble();
        emit depositToLoan(amount, 1);
        ui->loan2PaymentInput->clear();
    });


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

    ui->labelReward->setText("Reward: " + QString::number(question.reward));
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
    } else {
        throw std::runtime_error("return page could not be found.");
    }
    ui->settingsButton->show();
    if (returnPage != "Start" && returnPage != "quizEnd")
        ui->balance->show();
}

void MainWindow::onStartClicked()
{
    hidePhone();
    ui->balance->show();
    ui->stackedWidget->setCurrentWidget(ui->Quiz);
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
    if (currentMoney == std::floor(currentMoney))
        ui->balance->setText("$" + QString::number(currentMoney, 'f', 0));
    else
        ui->balance->setText("$" + QString::number(currentMoney, 'f', 2));
}

void MainWindow::updateSavings(double newBalance, double interestRate)
{
    ui->savingsAccountAmount->setText("Balance: $" + QString::number(newBalance, 'f', 2));
}

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
    QString balanceText = QString::number(newBalance, 'f', 2);
    QString status;

    if(loanNumber == 0) {
        ui->loan1Balance->setText("$" + balanceText);
        ui->loan1InterestRate->setText(QString::number(interestRate*100, 'f', 1) + "%");
        ui->loan1YearsLeft->setText(QString::number(yearsLeft));

        if(available && !active) {
            ui->activateLoan1Button->setEnabled(true);
            status = "Available";
        } else if(active) {
            status = "Active";
            ui->activateLoan1Button->setEnabled(false);
        } else {
            status = "Unavailable";
            ui->activateLoan1Button->setEnabled(false);
        }
        ui->loan1AvailabilityStatus->setText(status);
    }
    else {
        ui->loan2Balance->setText("$" + balanceText);
        ui->loan2InterestRate->setText(QString::number(interestRate*100, 'f', 1) + "%");
        ui->loan2YearsLeft->setText(QString::number(yearsLeft));

        if(available && !active) {
            ui->activateLoan2Button->setEnabled(true);
            status = "Available";
        } else if(active) {
            status = "Active";
            ui->activateLoan2Button->setEnabled(false);
        } else {
            status = "Unavailable";
            ui->activateLoan2Button->setEnabled(false);
        }
        ui->loan2AvailabilityStatus->setText(status);
    }
}

void MainWindow::showErrorMessage(QString errorMessage) {}

void MainWindow::enableSubmitButton(bool checked)
{
    if (checked) {
        ui->submitButton->setEnabled(true);
    }
}

void MainWindow::showEndScreen()
{
    ui->balance->hide();
    ui->stackedWidget->setCurrentWidget(ui->quizEnd);
    ui->endLabel->setText("Quiz done! yay\n here is the recap (there is no recap)");
}

void MainWindow::updateStockPriceDisplay(double amount, int stockNumber)
{
    switch (stockNumber) {
    case 0: {
        ui->totalPriceStockOne->setText("$" + QString::number(amount, 'f', 2));
        if (amount > currentMoney) {
            ui->totalPriceStockOne->setStyleSheet("color: red; font-weight: bold;");
            ui->purchaseStockOneButton->setEnabled(false);
        } else {
            ui->totalPriceStockOne->setStyleSheet("color: green; font-weight: bold;");
            ui->purchaseStockOneButton->setEnabled(true);
        }
        ui->totalPriceStockOne->adjustSize();
        break;
    }
    case 1: {
        ui->totalPriceStockTwo->setText("$" + QString::number(amount, 'f', 2));
        if (amount > currentMoney) {
            ui->totalPriceStockTwo->setStyleSheet("color: red; font-weight: bold;");
            ui->purchaseStockTwoButton->setEnabled(false);
        } else {
            ui->totalPriceStockTwo->setStyleSheet("color: green; font-weight: bold;");
            ui->purchaseStockTwoButton->setEnabled(true);
        }
        ui->totalPriceStockTwo->adjustSize();
        break;
    }
    case 2: {
        ui->totalPriceStockThree->setText("$" + QString::number(amount, 'f', 2));
        if (amount > currentMoney) {
            ui->totalPriceStockThree->setStyleSheet("color: red; font-weight: bold;");
            ui->purchaseStockThreeButton->setEnabled(false);
        } else {
            ui->totalPriceStockThree->setStyleSheet("color: green; font-weight: bold;");
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
            ui->sellingTotalPriceStockOne->setStyleSheet("color: red; font-weight: bold;");
            ui->sellButtonStockOne->setEnabled(false);
        } else {
            ui->sellingTotalPriceStockOne->setStyleSheet("color: green; font-weight: bold;");
            ui->sellButtonStockOne->setEnabled(true);
        }
        ui->sellingTotalPriceStockOne->adjustSize();
        break;
    }
    case 1: {
        ui->sellingTotalPriceStockTwo->setText("$" + QString::number(amount, 'f', 2));
        if (tooMany) {
            ui->sellingTotalPriceStockTwo->setStyleSheet("color: red; font-weight: bold;");
            ui->sellButtonStockTwo->setEnabled(false);
        } else {
            ui->sellingTotalPriceStockTwo->setStyleSheet("color: green; font-weight: bold;");
            ui->sellButtonStockTwo->setEnabled(true);
        }
        ui->sellingTotalPriceStockTwo->adjustSize();
        break;
    }
    case 2: {
        ui->sellingTotalPriceStockThree->setText("$" + QString::number(amount, 'f', 2));
        if (tooMany) {
            ui->sellingTotalPriceStockThree->setStyleSheet("color: red; font-weight: bold;");
            ui->sellButtonStockThree->setEnabled(false);
        } else {
            ui->sellingTotalPriceStockThree->setStyleSheet("color: green; font-weight: bold;");
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
    qDebug() << "updating Amount owned to: " << amount;
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

void MainWindow::displayDepositPage()
{
    depositWindow.show();
}

void MainWindow::readSavingsAmount()
{
    double updatedSavings = ui->savingsDepositInput->text().toDouble();
    emit amountRead(updatedSavings);
}

void MainWindow::newYear(QVector<double> newTotals, QVector<double> changes, int currentYear)
{
    // Set current year label and button
    ui->currentYear->setText("YEAR " + QString::number(currentYear));
    ui->nextYearButton->setText("End Year " + QString::number(currentYear));

    // Set yearly report
    ui->yearlyReportLabel->setText(generateReportString(newTotals, changes));
}

QString MainWindow::generateReportString(QVector<double> newTotals, QVector<double> changes) {
    QString reportString;

    reportString.append("<font size='4'><b>Yearly Report: </b></font>");

    reportString.append("<table>");

    // Add net worth to the string
    reportString.append("<tr><td><b>Net Worth:   </b></td><td> $" + QString::number(newTotals[4], 'f', 2));
    if (changes[4] > 0)
        reportString.append("<font color='green'> +$" + QString::number(changes[4], 'f', 2));
    else if (changes[4] < 0)
        reportString.append("<font color='red'> $" + QString::number(changes[4], 'f', 2));

    // Add savings account
    reportString.append("</font></td></tr><tr><td><b>Savings Account: </b></td><td> $" + QString::number(newTotals[0], 'f', 2));
    if (changes[0] > 0)
        reportString.append("<font color='green'>+$" + QString::number(changes[0], 'f', 2));

    // Add cd accounts
    reportString.append("</font></td></tr><tr><td><b>CDs Total: </b></td><td> $" + QString::number(newTotals[1], 'f', 2));
    if (changes[1] > 0)
        reportString.append("<font color='green'> +$" + QString::number(changes[1], 'f', 2));

    // Add stocks
    reportString.append("</font></td></tr><tr><td><b>Stocks Total: </b></td><td> $" + QString::number(newTotals[2], 'f', 2));
    if (changes[2] > 0)
        reportString.append("<font color='green'> +$" + QString::number(changes[2], 'f', 2));
    else if (changes[2] < 0)
        reportString.append("<font color='red'> $" + QString::number(changes[2], 'f', 2));

    // Add loans
    reportString.append("</font></td></tr><tr><td><b>Loans Total: </b></td><td> $" + QString::number(newTotals[3], 'f', 2));
    if (changes[3] < 0)
        reportString.append("<font color='red'> $" + QString::number(changes[3], 'f', 2));
    reportString.append("</font></td></tr>");

    return reportString;
}

