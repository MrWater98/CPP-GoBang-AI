#ifndef AIPLAYER4_H
#define AIPLAYER4_H
#include "AIPlayer2.h"
#include <vector>
class AIPlayer4 : public AIPlayer2
{
    public:
        AIPlayer4();
        AIPlayer4(ChessType Color);
        vector<int> MonteCarlo(vector<int> bestPlace,char cloneChessBoard[][15]);
        char [][15][15] getVector(char cloneChessBoard[][15],int num);
        void playChess();
        virtual ~AIPlayer4();

    protected:

    private:
};

#endif // AIPLAYER4_H
