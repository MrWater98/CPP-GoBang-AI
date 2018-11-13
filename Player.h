#ifndef PLAYER_H
#define PLAYER_H
#include "ChessBoard.h"
#include<map>
class Player
{
    public:

        Player(ChessType Color);
        ChessType chessColor;
        virtual ~Player();
        float Score[15][15];
        void Start();
        void AIStart();
        void AIPlayChess();
        virtual void playChess();
    protected:

    private:
};

#endif // PLAYER_H
