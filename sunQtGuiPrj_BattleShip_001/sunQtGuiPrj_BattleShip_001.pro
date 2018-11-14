#-------------------------------------------------
#
# Project created by QtCreator 2018-11-14T09:29:38
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sunQtGuiPrj_BattleShip_001
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


SOURCES += \
        main.cpp \
    boxbutton.cpp \
    battleship_gui.cpp \
    ship_2d.cpp \
    witness.cpp \
    hmi_dpTemplate.cpp \
    bs_game.cpp \
    game_round.cpp \
    fleet.cpp \
    player.cpp \
    settings.cpp \
    board2d.cpp \
    hmi_gui.cpp

HEADERS += \
    boxbutton.h \
    battleship_gui.h \
    ship_2d.h \
    witness.h \
    hmi_dpTemplate.h \
    game_round.h \
    player.h \
    settings.h \
    bs_game.h \
    fleet.h \
    board2d.h \
    hmi_gui.h

FORMS += \
    battleship.ui
