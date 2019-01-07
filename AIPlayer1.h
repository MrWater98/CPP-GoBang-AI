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
    float getTotalScore(pair<short,short> p);//Get total Score
    virtual float getLineScore(pair<short,short> p,pair<short,short> offset,ChessType myChessColor);//Get the line score
    map<ChessType,char> stateMap;
    map<string,float> toScore;// heuristic function
    float Score[15][15];//The chessboard score matirx
    virtual void playChess();
    virtual ~AIPlayer1();
protected:
private:
};

#endif // AIPLAYER1_H
