#include "AIPlayer2.h"
#include "ChessBoard.h"
#include<iostream>
#include<map>
#include<string>
#include<float.h>
#include<limits.h>
using namespace std;

AIPlayer2::AIPlayer2(ChessType Color)
{
    chessColor = Color;

    toScore.clear();
    toScore["aa___"]=100;
    toScore["a_a__"]=90;
    toScore["___aa"]=90;
    toScore["__a_a"]=90;
    toScore["a__a_"]=90;
    toScore["_a__a"]=90;
    toScore["a___a"]=90;


    toScore["__aa__"]=500;
    toScore["_a_a_"]=400;
    toScore["_a__a_"]=400;

    toScore["_aa__"]=500;
    toScore["__aa_"]=500;


    toScore["a_a_a"]=900;
    toScore["aa__a"]=800;
    toScore["_aa_a"]=1100;
    toScore["a_aa_"]=1100;
    toScore["_a_aa"]=1100;
    toScore["aa_a_"]=1100;
    toScore["aaa__"]=1200;

    toScore["_aa_a_"]=9000;
    toScore["_a_aa_"]=9000;

    toScore["_aaa_"]=10000;


    toScore["a_aaa"]=49000;
    toScore["aaa_a"]=49000;
    toScore["_aaaa"]=50000;
    toScore["aaaa_"]=50000;
    toScore["aa_aa"]=49000;


    toScore["_aaaa_"]=100000;

    toScore["aaaaa"]=1000000;

    stateMap[BLACK] = 'x';
    stateMap[WHITE] = 'o';
}
AIPlayer2::AIPlayer2()
{
    //ctor
}

AIPlayer2::~AIPlayer2()
{
    //dtor
}
float AIPlayer2::getLineScore(pair<short,short> p,pair<short,short> offset,ChessType myChessColor)
{
    string str = "a";
    HideCursor();
    for(int i = offset.first,j = offset.second,k=0; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15&&k<5; i+=offset.first,j+=offset.second,k++)
    {
        if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]==stateMap[myChessColor])
        {
            str += "a";
        }
        else if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]=='.')
        {
            str+="_";
        }
        else
        {
            break;
        }
    }

    for(int i = -offset.first,j = -offset.second,k=0; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15&&k<5; i-=offset.first,j-=offset.second,k++)
    {
        if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]==stateMap[myChessColor])
        {
            str="a"+str;
        }
        else if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]=='.')
        {
            str="_"+str;
        }
        else
        {
            break;
        }
    }
    string cmpStr = "";
    for(auto &i : toScore)
    {
        if(str.find(i.first)!=string::npos)
        {
            if (cmpStr != "")
            {
                if(toScore[i.first]>toScore[cmpStr])
                {
                    cmpStr = i.first;
                }
            }
            else
            {
                cmpStr = i.first;
            }
        }
    }
    return toScore[cmpStr];
}
