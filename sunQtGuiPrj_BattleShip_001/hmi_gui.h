#ifndef HMI_GUI_H
#define HMI_GUI_H
#include <hmi_dpTemplate.h>
#include <unordered_set>

//#include <QObject>

class hmi_gui : public hmi_dpTemplate
{
    Q_OBJECT
public:
    hmi_gui(int const & iCRef_HmiBoardSize);
    ~hmi_gui();
    void startService(void);

public slots:
    void handleHitFire(bool bGetHit);
    void handleSunkFire(ship_2d const & cref_sunkShip);
    void handleMultipleFired(void);
    void handleFleetSunk(int iScore_in);
    void handleGameRoundeFinished(void);
    void handleReportBoardState(unordered_set<int> firedPositions, unordered_set<int> hitPositions, unordered_set<int> sunkPositions);
signals:
    void sigStartGui(void);
private:
    bool prvB_isServiceRunning;
};

#endif // HMI_GUI_H
