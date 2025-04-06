QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"

SOURCES += \
    cdaccount.cpp \
    loan.cpp \
    main.cpp \
    mainmodel.cpp \
    mainwindow.cpp \
    moneycontainer.cpp \
    quizhandler.cpp \
    savingsaccount.cpp \
    stock.cpp

HEADERS += \
    cdaccount.h \
    cpptoml.h \
    loan.h \
    mainmodel.h \
    mainwindow.h \
    moneycontainer.h \
    quizhandler.h \
    savingsaccount.h \
    stock.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QuestionBanks/example.toml
