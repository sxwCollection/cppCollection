#include <battleship_gui.h>
#include <iostream>
#include <time.h>
#include <QMouseEvent>
#include <QtCore/QDir>
//#include <QGui/QSound>
#include <QtMultimedia/QSound>
#include <QtCore/QTimer>

// Constructor
Battleship_GUI::Battleship_GUI(int const & iCRef_boardSize, QWidget *parent) : QMainWindow(parent)
  , prvCi_boardSize(iCRef_boardSize)
{
    prvI_currentFocusId1=0;
    prvI_currentFocusId2=0;
	QApplication::setStyle("plastique");
	setupUi(this);
    sizePolicy().setHeightForWidth(true);
    labelStatus = new QLabel(QString::fromUtf8("enjoy the game"), statusbar);
	statusbar->setSizeGripEnabled(true);
	statusbar->addWidget(labelStatus, 3);
    connect(pushButtonResetGame, QPushButton::clicked, this, Battleship_GUI::slotResetGame);

    init_hmi();
    setupField();


}
void Battleship_GUI::handleStartGui()
{
    show();
}

void Battleship_GUI::init_hmi()
{
    pubP_hmiGui = new hmi_gui(prvCi_boardSize);
    connect(pubP_hmiGui, hmi_gui::sigStartGui, this, Battleship_GUI::handleStartGui);
    connect(pubP_hmiGui, hmi_gui::sigHitFire, this, Battleship_GUI::slotHitFire);
    connect(pubP_hmiGui, hmi_gui::sigFleetSunk, this, Battleship_GUI::slotFleetSunk);
    connect(pubP_hmiGui, hmi_gui::sigGameRoundeFinished, this, Battleship_GUI::slotGameRoundeFinished);
    connect(pubP_hmiGui, hmi_gui::sigMultipleFired, this, Battleship_GUI::slotMultipleFired);
    connect(pubP_hmiGui, hmi_gui::sigReportBoardState, this, Battleship_GUI::slotReportBoardState);
    connect(pubP_hmiGui, hmi_gui::sigSunkFire, this, Battleship_GUI::slotSunkFire);
}
void Battleship_GUI::deinit_hmi()
{
    disconnect(pubP_hmiGui, hmi_gui::sigStartGui, this, Battleship_GUI::handleStartGui);
    disconnect(pubP_hmiGui, hmi_gui::sigHitFire, this, Battleship_GUI::slotHitFire);
    disconnect(pubP_hmiGui, hmi_gui::sigFleetSunk, this, Battleship_GUI::slotFleetSunk);
    disconnect(pubP_hmiGui, hmi_gui::sigGameRoundeFinished, this, Battleship_GUI::slotGameRoundeFinished);
    disconnect(pubP_hmiGui, hmi_gui::sigMultipleFired, this, Battleship_GUI::slotMultipleFired);
    disconnect(pubP_hmiGui, hmi_gui::sigReportBoardState, this, Battleship_GUI::slotReportBoardState);
    disconnect(pubP_hmiGui, hmi_gui::sigSunkFire, this, Battleship_GUI::slotSunkFire);
    delete pubP_hmiGui;
}

// Destructor
Battleship_GUI::~Battleship_GUI()
{
    destroyField();
    delete pubP_hmiGui;
    disconnect(pubP_hmiGui, hmi_gui::sigStartGui, this, Battleship_GUI::handleStartGui);

}


void Battleship_GUI::setupField(void)
{
	// Create BoxButtons, assign them to the right "gridLayout" and save its coordinates
	int col, row;
	QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	sizePolicy.setHeightForWidth(true);
	sizePolicy.setHorizontalStretch(1);
	sizePolicy.setVerticalStretch(1);
    for (row=0; row<prvCi_boardSize; row++) {
        for (col=0; col<prvCi_boardSize; col++) {
            field[row][col] = new BoxButton(row, col);
            connect(field[row][col], BoxButton::sigRelayClick, this, Battleship_GUI::slotClickOnField);
            field[row][col]->setSizePolicy(sizePolicy);
            field[row][col]->setFocusPolicy(Qt::ClickFocus);
            field[row][col]->setMinimumSize(20,20);
            gridLayout_board->addWidget(field[row][col], row, col);
		}
	}
	return;
}
void Battleship_GUI::destroyField()
{
    int row, col;
    for (row=0; row<prvCi_boardSize; row++) {
        for (col=0; col<prvCi_boardSize; col++)
        {
            disconnect(field[row][col], BoxButton::sigRelayClick, this, Battleship_GUI::slotClickOnField);
            delete field[row][col];		// deleting the dynamically created BoxButtons
        }
    }
}

void Battleship_GUI::slotClickOnField( int row, int col)
{
    prvI_currentFocusId1=row;
    prvI_currentFocusId2=col;
    pubP_hmiGui->inputPosition(row, col);
	return;
}


void Battleship_GUI::slotHitFire(bool bGetHit)
{
    if(bGetHit)
    {
        field[prvI_currentFocusId1][prvI_currentFocusId2]->setStyleSheet("background-color:darkMagenta;");
    }
    else
    {
        field[prvI_currentFocusId1][prvI_currentFocusId2]->setStyleSheet("background-color:blue;");
    }
    update();
}

void Battleship_GUI::slotFleetSunk(int iScore_in)
{
    statusBar()->showMessage(QString("congratulations, you win, your score: %1").arg(iScore_in));
    blockBoxSignals(true);
    setCursor(QCursor(Qt::ForbiddenCursor));
    return;
}
void Battleship_GUI::slotGameRoundeFinished()
{

    blockBoxSignals(true);
    setCursor(QCursor(Qt::ForbiddenCursor));
    return;
}
void Battleship_GUI::slotMultipleFired()
{

}
void Battleship_GUI::slotReportBoardState(unordered_set<int> firedPositions, unordered_set<int> hitPositions, unordered_set<int> sunkPositions)
{

}
void Battleship_GUI::slotSunkFire(const ship_2d &cref_sunkShip)
{
    ship_2d& refShip = const_cast<ship_2d&>(cref_sunkShip);
    unordered_set<int> uSet_positions = refShip.getShipPositions();
    for(auto const & ai: uSet_positions)
    {
        field[(ai/10)][(ai%10)]->setStyleSheet("background-color:red;");
    }
    update();
    emit pubP_hmiGui->requestGameRoundState();
}
void Battleship_GUI::slotResetGame()
{
    // Reset game
    statusBar()->showMessage(QString("enjoy the game!"));
    destroyField();
    setupField();
    setCursor(QCursor(Qt::ArrowCursor));
    emit pubP_hmiGui->requestGameReset(pubP_hmiGui);
	return;
}

void Battleship_GUI::blockBoxSignals(bool block)
{
	int row, col;
	for (row=0; row<10; row++) {
		for (col=0; col<10; col++) {
            field[row][col]->blockSignals(block);
		}
	}
}


