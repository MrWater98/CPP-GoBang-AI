#include "Player.h"
#include "ChessBoard.h"
#include"GameController.h"
#include<algorithm>
#include<iostream>
#include<map>
#include<limits>
#include<float.h>
#include<string.h>
#include "AIPlayer1.h"
#include"conio.h"
using namespace std;
Player::Player()
{

}
Player::~Player()
{
    //dtor
}
Player::Player(ChessType Color)
{
    chessColor = Color;
}

void Player::Start()
{
    if(chessColor==ChessBoard::getInstance()->turn)
    {
        playChess();
    }
}
//map<string,float> toScore;
//map<ChessType,char> stateMap;
//ChessType temp;
/*
void Player::AIStart()
{
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

    toScore["aaaaa"]=FLT_MAX;
    toScore["aaaaa_"]=FLT_MAX;
    toScore["_aaaaa"]=FLT_MAX;
    toScore["_aaaaa_"]=FLT_MAX;


    if(chessColor==ChessBoard::getInstance()->turn)
    {
        SetCursorPos(pair<short,short>(0,17));
        //cout<<"??"<<endl;
        AIPlayChess();
    }
}
*/
pair<short,short> p(6,6);
void Player::playChess()
{
    while(true)
    {
        int ind;
        if(kbhit())
        {
            ind = getch();
        }
        switch(ind)
        {
        case 75:
            if(p.first-1>=0)
                p.first -= 1;
            break;
        case 77:
            if(p.first+1<15)
                p.first += 1;
            break;
        case 72:
            if(p.second-1>=0)
                p.second -= 1;
            break;
        case 80:
            if(p.second+1<15)
                p.second += 1;
            break;
        case 'r':
            ChessBoard::getInstance()->Retract();
            break;
        case 13:
            if(ChessBoard::getInstance()->PlayChess(p))
                return ;
            else
                break;
        }
        SetCursorPos(pair<short,short>(0,17));
        cout<<"Your Local Position:"<<p.first<<"  "<<p.second<<endl;
        ChessBoard::getInstance()->print(p);
    }
}
/*
float getLineScore(pair<short,short> p,pair<short,short> offset,ChessType chessColor)
{
    string str = "a";
    char localChess = stateMap[chessColor];
    //×ó±ß
    for(int i = offset.first,j = offset.second; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15; i+=offset.first,j+=offset.second)
    {
        if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]==localChess)
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
        if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]==localChess)
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
    return toScore[str];

}

float getTotalScore(pair<short,short> p)
{
    float ans = 0;
    ans += getLineScore(p,pair<short,short>(1,0),temp);
    ans += getLineScore(p,pair<short,short>(0,1),temp);
    ans += getLineScore(p,pair<short,short>(1,1),temp);
    ans += getLineScore(p,pair<short,short>(1,-1),temp);

    ans += getLineScore(p,pair<short,short>(1,0),ChessType(-temp+3));
    ans += getLineScore(p,pair<short,short>(0,1),ChessType(-temp+3));
    ans += getLineScore(p,pair<short,short>(1,1),ChessType(-temp+3));
    ans += getLineScore(p,pair<short,short>(1,-1),ChessType(-temp+3));

    return ans;
}


void Player::AIPlayChess()
{
    temp = chessColor;
    stateMap[BLACK] = 'x';
    stateMap[WHITE] = 'o';
    if(ChessBoard::getInstance()->st.size()==0)
    {
        ChessBoard::getInstance()->st.push(pair<short,short>(7,7));
        ChessBoard::getInstance()->myChessBoard[7][7] = stateMap[temp];
        ChessBoard::getInstance()->turn = ChessType(-temp+3);
        return ;
    }
    memset(Score,0,sizeof(Score));//first step set all the zero
    float Max = -1;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(ChessBoard::getInstance()->myChessBoard[i][j]=='.')
            {
                Score[i][j] = getTotalScore(pair<short,short>(i,j));
                Max = max(Max,Score[i][j]);
            }
        }
    }
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(Max==Score[i][j])
            {
                ChessBoard::getInstance()->myChessBoard[i][j] = stateMap[temp];
                ChessBoard::getInstance()->st.push(pair<short,short>(i,j));
                if(ChessBoard::getInstance()->CheckWinner(pair<short,short>(i,j)))
                {
                    SetCursorPos(pair<short,short>(0,16));
                    cout<<"win->Press any key to stop"<<endl;
                    ChessBoard::getInstance()->print(pair<short,short>(i,j));
                    getchar();
                }
                ChessBoard::getInstance()->turn = ChessType(-temp+3);
                return ;
            }
        }
    }

}
*/

