#include "AIPlayer1.h"
#include<iostream>
#include<iomanip>
#include<ctime>
#include<map>
#include<fstream>
#include"Tools.h"
using namespace std;

AIPlayer1::AIPlayer1(ChessType Color)
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

    toScore["aaaaa"]=100000;
    toScore["aaaaa_"]=100000;
    toScore["_aaaaa"]=100000;
    toScore["_aaaaa_"]=100000;
    stateMap[BLACK] = 'x';stateMap[WHITE] = 'o';
}
AIPlayer1::AIPlayer1()
{

}
AIPlayer1::~AIPlayer1()
{

}
void AIPlayer1::playChess()
{
    HideCursor();
    //temp = chessColor;
    if(ChessBoard::getInstance()->st.size()==0)
    {
        ChessBoard::getInstance()->st.push(pair<short,short>(7,7));
        ChessBoard::getInstance()->myChessBoard[7][7] = stateMap[chessColor];
        ChessBoard::getInstance()->turn = ChessType(-chessColor+3);
        return ;
    }
    else if(ChessBoard::getInstance()->st.size()==1)
    {
        for(int i = 0;i < 15;i++)
            for(int j = 0;j < 15;j++){
                if(ChessBoard::getInstance()->myChessBoard[i][j] == ChessBoard::getInstance()->m[int(-chessColor+3)])
                {
                    srand((unsigned)time(NULL));
                    int a,b;
                    a = rand()%3-1;b = rand()%3-1;
                    while(a==0&&b==0)
                        a = rand()%3-1;b = rand()%3-1;
                    ChessBoard::getInstance()->myChessBoard[i+a][j+b] = ChessBoard::getInstance()->m[int(chessColor)];
                    ChessBoard::getInstance()->turn = ChessType(-chessColor+3);
                    ChessBoard::getInstance()->st.push(pair<short,short>(i+a,j+b));
                    return ;
                }
            }
    }

    memset(Score,0,sizeof(Score));//first step set all the zero
    float Max = -1;
    ofstream myCout;
    myCout.open("ChessBoard.txt");
    myCout.setf(std::ios::left);
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(ChessBoard::getInstance()->myChessBoard[i][j]=='.')
            {
                Score[i][j] = getTotalScore(pair<short,short>(i,j));
                //SetCursorPos(pair<short,short>((i+10)*2,j));
                //print all the score
                //cout<<"   ";
                //Sleep(1);
                //SetCursorPos(pair<short,short>((i+10)*2,j));
                //cout<<Score[i][j];
                Max = max(Max,Score[i][j]);
            }
            myCout.width(15);
            if(Score[i][j]!=0)
                myCout<<fixed<<setprecision(1)<<Score[i][j];
            else
                myCout<<-1000;
        }
        myCout<<"\n";
    }
    myCout<<"\n";
    myCout.close();
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(Max==Score[i][j])
            {
                //PlayChess is a function that encapsulated in ChessBoard, which can finish the PlayChess operation
                ChessBoard::getInstance()->PlayChess(pair<short,short>(i,j));
                return ;
            }
        }
    }
}
//get score from all direction
float AIPlayer1::getTotalScore(pair<short,short> p)
{
    float ans = 0;
    ans += getLineScore(p,pair<short,short>(1,0),chessColor)/*1.05*/;
    ans += getLineScore(p,pair<short,short>(0,1),chessColor)/*1.05*/;
    ans += getLineScore(p,pair<short,short>(1,1),chessColor)/*1.1*/;
    ans += getLineScore(p,pair<short,short>(1,-1),chessColor)/*1.1*/;

    ans += getLineScore(p,pair<short,short>(1,0),ChessType(-chessColor+3));
    ans += getLineScore(p,pair<short,short>(0,1),ChessType(-chessColor+3));
    ans += getLineScore(p,pair<short,short>(1,1),ChessType(-chessColor+3));
    ans += getLineScore(p,pair<short,short>(1,-1),ChessType(-chessColor+3));

    return ans;
}
//get score from one direction
float AIPlayer1::getLineScore(pair<short,short> p,pair<short,short> offset,ChessType myChessColor)
{
    string str = "a";
    for(int i = offset.first,j = offset.second; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15; i+=offset.first,j+=offset.second)
    {
        if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]==stateMap[myChessColor])
        {
            str+="a";
        }
        else if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]=='.')
        {
            str+="_";
            break;
        }
        else
        {
            break;
        }
    }
    for(int i = -offset.first,j = -offset.second; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15; i-=offset.first,j-=offset.second)
    {
        if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]==stateMap[myChessColor])
        {
            str="a"+str;
        }
        else if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]=='.')
        {
            str="_"+str;
            break;
        }
        else
        {
            break;
        }
    }

    //Sleep(1);
    return toScore[str];
}
