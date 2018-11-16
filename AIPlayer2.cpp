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
    toScore["_a_"]=10;
    toScore["a_"]=5;
    toScore["_a"]=5;

    toScore["_aa_"]=100;
    toScore["aa_"]=50;
    toScore["_aa"]=50;

    toScore["_aaa_"]=1000;
    toScore["aaa_"]=500;
    toScore["_aaa"]=500;

    toScore["_aaaa_"]=10000;
    toScore["aaaa_"]=5000;
    toScore["_aaaa"]=5000;



    toScore["aa___"]=50;                      //眠二
    toScore["a_a__"]=50;
    toScore["___aa"]=50;
    toScore["__a_a"]=50;
    toScore["a__a_"]=50;
    toScore["_a__a"]=50;
    toScore["a___a"]=50;


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
    /*
    bool lfirst = true,lstop = false,rstop = false;
    int AllNum = 1;
    string str = "a";
    int ri = offset.first,rj = offset.second;
    int li = -offset.first,lj = -offset.second;
    while(AllNum<7&&(!lstop||!rstop))
    {
        if(lfirst)
        {
            //left
            if((p.first+li>=0&&p.first+li<15)&&
                    p.second+lj>=0&&p.second+lj<15&&!lstop)
            {

                if(ChessBoard::getInstance()->myChessBoard[p.first+li][p.second+lj]==stateMap[myChessColor])
                {
                    AllNum++;
                    str = "a"+str;
                }
                else if(ChessBoard::getInstance()->myChessBoard[p.first+ri][p.second+rj]=='.')
                {
                    AllNum++;
                    str = "_"+str;
                    if (!rstop)
                        lfirst = false;
                }
                else
                {
                    lstop = true;
                    if(!rstop)
                        lfirst = false;
                }
                li -= offset.first;
                lj -= offset.second;
            }
            else
            {
                lstop = true;
                if(!rstop)
                    lfirst = false;
            }
        }
        //右边
        else
        {
            if((p.first+ri>=0&&p.first+ri<15)&&
                    p.second+rj>=0&&p.second+rj<15&&!lfirst&&!rstop)
            {
                if(ChessBoard::getInstance()->myChessBoard[p.first+ri][p.second+rj]==stateMap[myChessColor])
                {
                    AllNum++;
                    str+="a";
                }
                else if(ChessBoard::getInstance()->myChessBoard[p.first+ri][p.second+rj]=='.')
                {
                    AllNum++;
                    str+="_";
                    if(!lstop)
                        lfirst = true;
                }
                else
                {
                    rstop = true;
                    if(!lstop)
                        lfirst = true;
                }
                ri+=offset.first;
                rj+=offset.second;
            }
            else
            {
                rstop = true;
                if(!lstop)
                    lfirst = true;
            }
        }
    }


    string cmpStr = "";
    */
    /*
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
    */
    /*
    for(int i = 0;i < 15;i++)
    {
        for(int j = 0;j < 15;j++)
        {
            SetCursorPos(pair<short,short>((10+i)*2,(10+j)*2));
            cout<<Score[i][j];
        }
    }
    */
    /*
    SetCursorPos(pair<short,short>(0,20));
    cout<<"      "<<endl;
    if(cmpStr=="")
        cout<<"None"<<endl;
    else
        cout<<cmpStr<<endl;
        */
    string str = "a";
    //右边
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
    //左边
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
