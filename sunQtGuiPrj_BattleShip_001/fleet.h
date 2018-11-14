#ifndef FLEET_H
#define FLEET_H
#include <QObject>
#include <ship_2d.h>
#include <QDebug>
#include <board2d.h>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <tuple>
#include <witness.h>



using namespace std;

class fleet : public QObject
{
    Q_OBJECT
public:
    explicit fleet(board2D & board2d_in);
    ~fleet();
    bool placeShipInFleet(ship_2d* p_ship_inOut);
    bool clearShips(void);
    vector<ship_2d *> getPlacedShips(void);
    board2D* getBoard2D(void);
    vector<ship_2d *> pubVSunkShips;
    bool isFleetSunk();
    tuple<bool, ship_2d*> hitAtPosition(int id1_in, int id2_in);
private:
    vector<ship_2d *> prvVShips;
    board2D* prvBoard2d;
};

#endif // FLEET_H
