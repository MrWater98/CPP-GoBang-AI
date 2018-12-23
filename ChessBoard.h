#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include<map>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<memory.h>
#include<stack>
#include "Tools.h"
using namespace std;

enum ChessType
    {
        WATCH,
        BLACK,
        WHITE
    };
class ChessBoard
{
public:
    ChessBoard();
    virtual ~ChessBoard();
    char myChessBoard[15][15];
    bool PlayChess(pair<short,short> pos);
    static ChessBoard *getInstance();
    bool CheckWinner(pair<short,short> pos);
    bool CheckLine(pair<short,short> pos,pair<short,short>offset);
    stack<pair<short,short>> st;
    map<int,char> m;
    void Retract();
    void print(pair<short,short> twinkle);
    ChessType turn = BLACK;
        protected:
        private:
    static ChessBoard* instance;
};
#endif // CHESSBOARD_H
