#ifndef SHIP_2D_H
#define SHIP_2D_H
#include <QObject>
#include <unordered_map>
#include <unordered_set>
#include <QDebug>
#include <witness.h>
using namespace std;

class ship_2d : public QObject
{
    Q_OBJECT
public:
    explicit ship_2d( int shipLength_in );
    ~ship_2d();
    int pubI_maxHits;
    int setPositions(int id1_in, int id2_in, int mode_in);
    unordered_map<int,bool> getShipStates(void);
    unordered_set<int> getShipPositions(void);
    void setHeadPositions(int id1_in, int id2_in);
    bool isIDInShipPositions(int id1_in, int id2_in);
    bool hitAtPosition(int id1_in, int id2_in);
    int length(void);
    bool checkSunk(void);

private:
    int prvLength, prvHeadPosition1, prvHeadPosition2, prvHitCounter;
    bool prvBSunk;
    unordered_map <int, bool> prvShipPositions;
};

#endif // SHIP_2D_H
