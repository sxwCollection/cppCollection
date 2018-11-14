#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "boxbutton.h"
#include "ui_battleship.h"
#include <QObject>
#include <hmi_gui.h>
#include <unordered_set>

class Battleship_GUI : public QMainWindow, private Ui::Battleship
{
    Q_OBJECT

public:
    Battleship_GUI(int const & iCRef_boardSize, QWidget *parent = NULL);	// constructor
    ~Battleship_GUI();		// destructor

    hmi_gui* pubP_hmiGui;
    BoxButton *field[10][10];

    void setupField(void);
    void destroyField(void);
    void init_hmi(void);
    void deinit_hmi(void);

public slots:
    void slotClickOnField( int row, int col);	//FROM: User_>click->Box.sigRelayClick
    void slotHitFire(bool bGetHit);
    void slotSunkFire(ship_2d const & cref_sunkShip);
    void slotMultipleFired(void);
    void slotFleetSunk(int iScore_in);
    void slotGameRoundeFinished(void);
    void slotReportBoardState(unordered_set<int> firedPositions, unordered_set<int> hitPositions, unordered_set<int> sunkPositions);
    void slotResetGame();
    void handleStartGui(void);

protected:
    QLabel *labelStatus;
	void blockBoxSignals(bool block);
private:
    int prvI_currentFocusId1, prvI_currentFocusId2;
    const int prvCi_boardSize;
    int round;
};

#endif
