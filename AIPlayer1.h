#ifndef AIPLAYER1_H
#define AIPLAYER1_H
#include "Player.h"
#include<map>
#include<cfloat>
using namespace std;
class AIPlayer1 : public Player
{
public:
    AIPlayer1();
    AIPlayer1(ChessType Color);
    float getTotalScore(pair<short,short> p);
    virtual float getLineScore(pair<short,short> p,pair<short,short> offset,ChessType myChessColor);
    map<ChessType,char> stateMap;
    map<string,float> toScore;
    //ChessType temp;
    float Score[15][15];
    virtual void playChess();
    virtual ~AIPlayer1();
protected:
private:
};

#endif // AIPLAYER1_H
