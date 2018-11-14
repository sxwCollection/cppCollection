#ifndef HMI_H
#define HMI_H
#include <QObject>
#include <string>
#include <iostream>
#include <regex>
#include <QDebug>
#include <ship_2d.h>

using namespace std;
class hmi_dpTemplate : public QObject
{
    Q_OBJECT
public:
    hmi_dpTemplate(int const & iCRef_HmiBoardSize);
    const int pubI_HmiBoardSize;
    virtual void startService(void)=0;

public slots:
    virtual void handleHitFire(bool bGetHit)=0;
    virtual void handleSunkFire(ship_2d const & cref_sunkShip)=0;
    virtual void handleMultipleFired(void)=0;
    virtual void handleFleetSunk(int iScore_in)=0;
    virtual void handleGameRoundeFinished(void)=0;
    virtual void handleReportBoardState(unordered_set<int> firedPositions, unordered_set<int> hitPositions, unordered_set<int> sunkPositions)=0;


signals:
    void inputPosition(int id1, int id2);
    void requestGameRoundState(void);
    void requestGameRoundBoardState(void);
    void requestGameReset(hmi_dpTemplate* pHmiDPInterface);

    void sigHitFire(bool bGetHit);
    void sigSunkFire(ship_2d const & cref_sunkShip);
    void sigMultipleFired(void);
    void sigFleetSunk(int iScore_in);
    void sigGameRoundeFinished(void);
    void sigReportBoardState(unordered_set<int> firedPositions, unordered_set<int> hitPositions, unordered_set<int> sunkPositions);



};

#endif // HMI_H
