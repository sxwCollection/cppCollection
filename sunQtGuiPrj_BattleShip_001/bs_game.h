#ifndef BS_GAME_H
#define BS_GAME_H
#include <QObject>
#include <settings.h>
#include <player.h>
#include <game_round.h>
#include <hmi_dpTemplate.h>

class bs_game : public QObject
{
    Q_OBJECT
public:
    bs_game(hmi_dpTemplate* pHmiDPInterface);
    ~bs_game();
    void initGame(hmi_dpTemplate* pHmiDPInterface);
    void deinitGame(void);
    void resetGame(hmi_dpTemplate* pHmiDPInterface);
    game_round* pubP_gameRound;
    hmi_dpTemplate* pubPHmi;

public slots:
    void handleReset(hmi_dpTemplate* pHmiDPInterface);
private:
    settings* prvPSettings;
    player* prvPPlayer;

};

#endif // BS_GAME_H
