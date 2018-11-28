#include "AIPlayer4.h"
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
AIPlayer4::AIPlayer4()
{
    //ctor
}

AIPlayer4::~AIPlayer4()
{
    //dtor
}
AIPlayer4::AIPlayer4(ChessType Color)
{
    chessColor = Color;


    toScore["aa___"]=100;                      //眠二
    toScore["a_a__"]=100;
    toScore["___aa"]=100;
    toScore["__a_a"]=100;
    toScore["a__a_"]=100;
    toScore["_a__a"]=100;
    toScore["a___a"]=100;


    toScore["__aa__"]=500;                     //活二
    toScore["_a_a_"]=500;
    toScore["_a__a_"]=500;

    toScore["_aa__"]=500;
    toScore["__aa_"]=500;


    toScore["a_a_a"]=1000;
    toScore["aa__a"]=1000;
    toScore["_aa_a"]=1000;
    toScore["a_aa_"]=1000;
    toScore["_a_aa"]=1000;
    toScore["aa_a_"]=1000;
    toScore["aaa__"]=1000;                     //眠三

    toScore["_aa_a_"]=9000;                    //跳活三
    toScore["_a_aa_"]=9000;

    toScore["_aaa_"]=10000;                    //活三


    toScore["a_aaa"]=15000;                    //冲四
    toScore["aaa_a"]=15000;                    //冲四
    toScore["_aaaa"]=15000;                    //冲四
    toScore["aaaa_"]=15000;                    //冲四
    toScore["aa_aa"]=15000;                    //冲四


    toScore["_aaaa_"]=1000000;                 //活四

    toScore["aaaaa"]=FLT_MAX;           //连五

    stateMap[BLACK] = 'x';
    stateMap[WHITE] = 'o';
}
void AIPlayer4::playChess()
{
    if(ChessBoard::getInstance()->st.size()==0)
    {
        ChessBoard::getInstance()->PlayChess(make_pair(7,7));
        return ;
    }

    char cloneChessBoard[15][15];
    memcpy(cloneChessBoard,ChessBoard::getInstance()->myChessBoard,
           sizeof(ChessBoard::getInstance()->myChessBoard));
           /*
    for(int i = 0;i < 15;i++)
        for(int j = 0;j < 15;j++)
            cloneChessBoard[i][j] = ChessBoard::getInstance()->myChessBoard[i][j];
            */

    char[4][15][15] bestCurStep = getVector(cloneChessBoard,4);


}
char[][15][15] AIPlayer4::getVector(char cloneChessBoard[][15],int num)
{
    map<float,pair<short,short> > scoreToPos;
    for(int i = 0;i < 15;i++)
    {
        for(int j = 0;j < 15;j++)
        {
            scoreToPos[getTotalScore(pair<short,short>(i,j))] = pair<short,short>(i,j);
        }
    }
    char bestPlace[num][15][15];
    char temp[15][15];
    int j = 0;
    for(auto i = scoreToPos.end();i!=scoreToPos.begin(),j<num;i--,j++)
    {
        memcpy(temp,cloneChessBoard,sizeof(cloneChessBoard));
        temp[i->second.first][i->second.second] = stateMap[chessColor];
        memcpy(bestPlace[j],temp,sizeof(temp));
    }

}
