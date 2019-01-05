#ifndef AIPLAYER2_H
#define AIPLAYER2_H
#include "AIPlayer1.h"

class AIPlayer2 : public AIPlayer1//the improvement of AIPlayer1
{
    public:
        AIPlayer2();
        AIPlayer2(ChessType Color);
        float getLineScore(pair<short,short> p,pair<short,short> offset,ChessType myChessColor);
        virtual ~AIPlayer2();

    protected:

    private:
};

#endif // AIPLAYER2_H
