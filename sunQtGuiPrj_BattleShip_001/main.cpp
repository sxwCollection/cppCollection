
#include <QApplication>
#include "battleship_gui.h"
#include <witness.h>
#include <bs_game.h>
#include <battleship_gui.h>

bool Witness::enable_Witness=false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Battleship_GUI* pBattleship_GUI = new Battleship_GUI(10);

    bs_game * pGame= new bs_game(pBattleship_GUI->pubP_hmiGui);

    pGame->pubP_gameRound->startRound();
    pBattleship_GUI->pubP_hmiGui->startService();

    return a.exec();
}
