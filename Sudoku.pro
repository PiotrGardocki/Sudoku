#-------------------------------------------------
#
# Project created by QtCreator 2019-06-10T16:16:17
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Sudoku
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += src/

SOURCES += \
    src/LayoutWithSquaredWidget.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/SudokuBoard.cpp \
    src/SudokuIndex.cpp \
    src/IndexError.cpp \
    src/vendor/RandomNumbersLibrary/RandomGeneratorBase.cpp \
    src/SudokuBoardModel.cpp \
    src/unit_tests/IndexErrorTest.cpp \
    src/unit_tests/SudokuIndexTest.cpp \
    src/unit_tests/SudokuBoardTest.cpp \
    src/unit_tests/SudokuBoardModelTest.cpp

HEADERS += \
    src/LayoutWithSquaredWidget.hpp \
    src/MainWindow.hpp \
    src/SudokuBoard.hpp \
    src/SudokuIndex.hpp \
    src/IndexError.hpp \
    src/vendor/RandomNumbersLibrary/RandomGeneratorBase.hpp \
    src/vendor/RandomNumbersLibrary/RandomIntegerGenerator.hpp \
    src/vendor/RandomNumbersLibrary/RandomIntegerGenerator.inl \
    src/vendor/RandomNumbersLibrary/RandomRealNumberGenerator.hpp \
    src/vendor/RandomNumbersLibrary/RandomRealNumberGenerator.inl \
    src/SudokuBoardModel.hpp \
    src/vendor/catch.hpp \
    src/unit_tests/catch.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
