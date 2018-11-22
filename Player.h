#ifndef PLAYER_H
#define PLAYER_H
#include "ChessBoard.h"
#include<map>
class Player
{
    public:
        Player();
        virtual ~Player();
        Player(ChessType Color);
        ChessType chessColor;
        //float Score[15][15];
        void Start();
        virtual void playChess();
    protected:

    private:
};

#endif // PLAYER_H
