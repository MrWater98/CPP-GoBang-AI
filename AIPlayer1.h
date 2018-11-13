#ifndef AIPLAYER1_H
#define AIPLAYER1_H
#include "Player.h"
#include<map>
#include<cfloat>
using namespace std;
class AIPlayer1 : public Player
{
public:
    float Score[15][15];
    map<string,float> toScore;
    virtual ~AIPlayer1();
protected:
private:
};

#endif // AIPLAYER1_H
