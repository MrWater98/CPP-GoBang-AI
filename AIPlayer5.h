#ifndef AIPLAYER5_H
#define AIPLAYER5_H
#include<iostream>
#include<unordered_map>
#include<algorithm>
#include "Player.h"
#include "Tools.h"
using namespace std;
struct MiniMaxNode2
{
    public:
    ChessType chess;
    pair<short,short> pos;
    vector<MiniMaxNode2> child;
    float value;//得到下了这步后局面的分数
    float point;//得到这步棋的分数
    unsigned long long int nodeHashVal;
};
class AIPlayer5 : public Player
{
    public:
        AIPlayer5(ChessType Color);
        AIPlayer5();
        unsigned long long int hashValue;
        unordered_map<string,int> evaBoard;
        unordered_map<string,int> pointModel;
        unordered_map<string,int> chessModel;
        unordered_map<ChessType,char> stateMap;
        void setModel(int i);
        bool hasNeighbor(char chessBoard[][15],int i,int j);
        float getTotalValue(char chessBoard[][15],bool myself);
        float getLineScore(char chessboard[][15],pair<short,short> p,pair<short,short> offset,ChessType myChessColor);
        float getPointScore(char chessboard[][15],pair<short,short> p,pair<short,short> offset,ChessType myChessColor);
        float AlphaBeta(MiniMaxNode2 node,int depth,bool myself,float alpha,float beta);
        vector<MiniMaxNode2> GetVector(char chessboard[][15],ChessType myChessColor,bool myself);
        void createTree(MiniMaxNode2 &node,char chessboard[][15],int depth,bool myself);
        void playChess();
        virtual ~AIPlayer5();

    protected:

    private:
};

#endif // AIPLAYER5_H
