#ifndef PLAYER_H
#define PLAYER_H
#include "ChessBoard.h"
#include<map>
class Player// represent the normal player
{
    public:
        Player();
        virtual ~Player();
        Player(ChessType Color);
        ChessType chessColor;
        void Start();
        virtual void playChess();
    protected:

    private:
};

#endif // PLAYER_H
