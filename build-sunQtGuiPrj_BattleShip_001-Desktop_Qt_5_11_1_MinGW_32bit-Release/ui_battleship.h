/********************************************************************************
** Form generated from reading UI file 'battleship.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATTLESHIP_H
#define UI_BATTLESHIP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Battleship
{
public:
    QAction *actionHost_network_game;
    QAction *actionQuit;
    QAction *actionLicense;
    QAction *actionJoin_network_game;
    QAction *actionStart_local_game;
    QAction *actionAbout;
    QAction *actionManual;
    QAction *actionSound_on;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButtonQuit;
    QPushButton *pushButtonResetGame;
    QSpacerItem *spacerItem;
    QFrame *frame;
    QGridLayout *gridLayout1;
    QLabel *label;
    QGridLayout *gridLayout_board;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Battleship)
    {
        if (Battleship->objectName().isEmpty())
            Battleship->setObjectName(QStringLiteral("Battleship"));
        Battleship->resize(651, 684);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Battleship->sizePolicy().hasHeightForWidth());
        Battleship->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral("pictures/hi48-app-battleship.png"), QSize(), QIcon::Normal, QIcon::Off);
        Battleship->setWindowIcon(icon);
        actionHost_network_game = new QAction(Battleship);
        actionHost_network_game->setObjectName(QStringLiteral("actionHost_network_game"));
        actionHost_network_game->setEnabled(false);
        actionQuit = new QAction(Battleship);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionLicense = new QAction(Battleship);
        actionLicense->setObjectName(QStringLiteral("actionLicense"));
        actionJoin_network_game = new QAction(Battleship);
        actionJoin_network_game->setObjectName(QStringLiteral("actionJoin_network_game"));
        actionJoin_network_game->setEnabled(false);
        actionStart_local_game = new QAction(Battleship);
        actionStart_local_game->setObjectName(QStringLiteral("actionStart_local_game"));
        actionAbout = new QAction(Battleship);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionManual = new QAction(Battleship);
        actionManual->setObjectName(QStringLiteral("actionManual"));
        actionSound_on = new QAction(Battleship);
        actionSound_on->setObjectName(QStringLiteral("actionSound_on"));
        actionSound_on->setCheckable(true);
        actionSound_on->setChecked(true);
        centralwidget = new QWidget(Battleship);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonQuit = new QPushButton(centralwidget);
        pushButtonQuit->setObjectName(QStringLiteral("pushButtonQuit"));

        gridLayout->addWidget(pushButtonQuit, 0, 2, 1, 1);

        pushButtonResetGame = new QPushButton(centralwidget);
        pushButtonResetGame->setObjectName(QStringLiteral("pushButtonResetGame"));

        gridLayout->addWidget(pushButtonResetGame, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 1, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(631, 350));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout1 = new QGridLayout(frame);
        gridLayout1->setSpacing(6);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Sans Serif"));
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout1->addWidget(label, 0, 0, 1, 1);

        gridLayout_board = new QGridLayout();
        gridLayout_board->setSpacing(0);
        gridLayout_board->setObjectName(QStringLiteral("gridLayout_board"));
        gridLayout_board->setContentsMargins(0, 0, 0, 0);

        gridLayout1->addLayout(gridLayout_board, 1, 0, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 3);


        vboxLayout->addLayout(gridLayout);

        Battleship->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Battleship);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Battleship->setStatusBar(statusbar);

        retranslateUi(Battleship);
        QObject::connect(actionQuit, SIGNAL(triggered()), Battleship, SLOT(close()));
        QObject::connect(pushButtonQuit, SIGNAL(clicked()), Battleship, SLOT(close()));
        QObject::connect(actionStart_local_game, SIGNAL(triggered()), pushButtonResetGame, SLOT(click()));

        QMetaObject::connectSlotsByName(Battleship);
    } // setupUi

    void retranslateUi(QMainWindow *Battleship)
    {
        Battleship->setWindowTitle(QApplication::translate("Battleship", "Battleship", nullptr));
        actionHost_network_game->setText(QApplication::translate("Battleship", "Host network game", nullptr));
        actionQuit->setText(QApplication::translate("Battleship", "Quit", nullptr));
        actionLicense->setText(QApplication::translate("Battleship", "License", nullptr));
        actionJoin_network_game->setText(QApplication::translate("Battleship", "Join network game", nullptr));
        actionStart_local_game->setText(QApplication::translate("Battleship", "Single Player", nullptr));
#ifndef QT_NO_SHORTCUT
        actionStart_local_game->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        actionAbout->setText(QApplication::translate("Battleship", "About", nullptr));
        actionManual->setText(QApplication::translate("Battleship", "Manual", nullptr));
        actionSound_on->setText(QApplication::translate("Battleship", "Sound on", nullptr));
        pushButtonQuit->setText(QApplication::translate("Battleship", "Quit", nullptr));
        pushButtonResetGame->setText(QApplication::translate("Battleship", "Reset Game", nullptr));
        label->setText(QApplication::translate("Battleship", "Battle Field", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Battleship: public Ui_Battleship {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLESHIP_H
