#ifndef AIPLAYER3_H
#define AIPLAYER3_H
#include "Player.h"
#include<map>
#include<iostream>
#include<vector>
using namespace std;
class MiniMaxNode
{
    public:
    ChessType chess;
    pair<short,short> pos;
    vector<MiniMaxNode> child;
    float value;
};
class AIPlayer3 : public Player
{
    public:
        AIPlayer3();
        AIPlayer3(ChessType Color);
        virtual ~AIPlayer3();
        map<string,float> toScore;
        map<ChessType,char> stateMap;
        float getTotalScore(char chessboard[][15],pair<short,short> p);
        float getLineScore(char chessboard[][15],pair<short,short> p,pair<short,short> offset,ChessType myChessColor);
        float AlphaBeta(MiniMaxNode node,int depth,bool myself,float alpha,float beta);
        vector<MiniMaxNode> GetVector(char chessboard[][15],ChessType myChessColor,bool myself);
        void createTree(MiniMaxNode &node,char chessboard[][15],int depth,bool myself);
        void playChess();
    protected:

    private:
};

#endif // AIPLAYER3_H
