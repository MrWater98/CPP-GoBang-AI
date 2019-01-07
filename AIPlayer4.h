#ifndef AIPLAYER4_H
#define AIPLAYER4_H
#include "AIPlayer2.h"
#include "Tools.h"
#include <vector>
struct nextState
    {
        char nextBoard[15][15];
        nextState(char temp[][15])
        {
            copyArray(temp,nextBoard);
        }
    };
class AIPlayer4 : public AIPlayer2//Monte Carlo
{
    public:
        AIPlayer4();
        AIPlayer4(ChessType Color);
        int MonteCarlo(char bestPlace[][15],ChessType ChessColor);
        bool CheckWinner(char Board[][15],pair<short,short> pos);
        unordered_map<string,int> pointModel;
        bool CheckLine(char Board[][15],pair<short,short> pos,pair<short,short>offset);
        void addPos(vector<pair<short,short> > &p,int i,int j,char newBoard[][15]);
        void playChess();
        virtual ~AIPlayer4();

    protected:

    private:
};

#endif // AIPLAYER4_H
