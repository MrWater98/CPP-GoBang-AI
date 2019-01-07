#include "AIPlayer4.h"
#include<iostream>
#include <conio.h>
#include<ctime>
#include<limits.h>
#include<string.h>
#include<vector>
using namespace std;
#define ITERATION1 100
#define ITERATION2 40000  //the iteration time of MonteCarlo
#define JNUM1 4
#define JNUM2 3 // the number you want to judge
int BESTPOSNUM,GAMENUM;
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

    pointModel["Five"] = INT_MAX;
    pointModel["LiveFour"] = 1000000;
    pointModel["SleepFour"] = 30000;
    pointModel["LiveThree"] = 10000;
    pointModel["SleepThree"] = 1000;
    pointModel["LiveTwo"] = 500;
    pointModel["SleepTwo"] = 50;
    pointModel["LiveOne"] = 10;

    toScore["_a___"] = pointModel["LiveOne"];
    toScore["__a__"] = pointModel["LiveOne"];
    toScore["___a_"] = pointModel["LiveOne"];
    toScore["___a_"] = pointModel["LiveOne"];

    toScore["aa___"]=pointModel["SleepTwo"];
    toScore["a_a__"]=pointModel["SleepTwo"];
    toScore["___aa"]=pointModel["SleepTwo"];
    toScore["__a_a"]=pointModel["SleepTwo"];
    toScore["a__a_"]=pointModel["SleepTwo"];
    toScore["_a__a"]=pointModel["SleepTwo"];
    toScore["a___a"]=pointModel["SleepTwo"];


    toScore["__aa__"]=pointModel["LiveTwo"]+1;
    toScore["_a_a_"]=pointModel["LiveTwo"];
    toScore["_a__a_"]=pointModel["LiveTwo"]-1;

    toScore["_aa__"]=pointModel["LiveTwo"]+1;
    toScore["__aa_"]=pointModel["LiveTwo"]+1;


    toScore["a_a_a"]=pointModel["SleepThree"]-1;
    toScore["aa__a"]=pointModel["SleepThree"];
    toScore["_aa_a"]=pointModel["SleepThree"];
    toScore["a_aa_"]=pointModel["SleepThree"];
    toScore["_a_aa"]=pointModel["SleepThree"];
    toScore["aa_a_"]=pointModel["SleepThree"];
    toScore["aaa__"]=pointModel["SleepThree"]+1;

    toScore["_aa_a_"]=pointModel["LiveThree"]-100;
    toScore["_a_aa_"]=pointModel["LiveThree"]-100;

    toScore["_aaa_"]=pointModel["LiveThree"]+1;


    toScore["a_aaa"]=pointModel["SleepFour"];
    toScore["aaa_a"]=pointModel["SleepFour"];
    toScore["_aaaa"]=pointModel["SleepFour"]+1;
    toScore["aaaa_"]=pointModel["SleepFour"]+1;
    toScore["aa_aa"]=pointModel["SleepFour"];


    toScore["_aaaa_"]=pointModel["LiveFour"];

    toScore["aaaaa"]=pointModel["Five"];
    stateMap[BLACK] = 'x';
    stateMap[WHITE] = 'o';

}
pair<short,short> showPoint;
void AIPlayer4::playChess()
{
    if(ChessBoard::getInstance()->st.size()==0)
    {
        ChessBoard::getInstance()->PlayChess(make_pair(7,7));
        return ;
    }
    else if(ChessBoard::getInstance()->st.size()==1)
    {
        for(int i = 0; i < 15; i++)
            for(int j = 0; j < 15; j++)
            {
                if(ChessBoard::getInstance()->myChessBoard[i][j] == ChessBoard::getInstance()->m[int(-chessColor+3)])
                {
                    srand((unsigned)time(NULL));
                    int a=1,b=1;
                    while(a==0&&b==0)
                        a = rand()%3-1;
                    b = rand()%3-1;
                    ChessBoard::getInstance()->myChessBoard[i+a][j+b] = ChessBoard::getInstance()->m[int(chessColor)];
                    ChessBoard::getInstance()->turn = ChessType(-chessColor+3);
                    ChessBoard::getInstance()->st.push(pair<short,short>(i+a,j+b));
                    return ;
                }
            }
    }
    else if(ChessBoard::getInstance()->st.size()<=9)
    {
        BESTPOSNUM = JNUM1;
        GAMENUM = ITERATION1;
    }
    else if(ChessBoard::getInstance()->st.size()>9&&ChessBoard::getInstance()->st.size()<=20)
    {
        BESTPOSNUM = JNUM1;
        GAMENUM = ITERATION1;
    }
    else if(ChessBoard::getInstance()->st.size()>20)
    {
        BESTPOSNUM = JNUM2;
        GAMENUM = ITERATION2;
    }
    //SetCursorPos(pair<short,short>(0,16));
    //cout<<ChessBoard::getInstance()->st.size()<<endl;

    char cloneChessBoard[15][15];
    copyArray(ChessBoard::getInstance()->myChessBoard,cloneChessBoard);
    vector<pair<short,short> > bestPos;
    vector<nextState> vec;
    //方案1：启发蒙特卡洛(Monte Carlo Based on Human Chess Spectrum)
    if(ChessBoard::getInstance()->st.size()<=225)//now all use heuristic monte-carlo
    {
        map<float,pair<short,short> > scoreToPoint;
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                if(cloneChessBoard[i][j]=='.')
                {
                    float TScore = getTotalScore(pair<short,short>(i,j));
                    if(TScore>=INT_MAX)
                    {
                        ChessBoard::getInstance()->PlayChess(pair<short,short>(i,j));
                        return ;
                    }
                    scoreToPoint[TScore] = pair<short,short>(i,j);
                }
            }
        }
        int j = 0;
        for(auto i = scoreToPoint.rbegin(); i!=scoreToPoint.rend()&&j<BESTPOSNUM; i++,j++)
        {
            char temp[15][15];
            copyArray(cloneChessBoard,temp);
            //SetCursorPos(pair<short,short>(0,16));
            temp[i->second.first][i->second.second] = stateMap[chessColor];
            bestPos.push_back(i->second);
            vec.push_back(nextState(temp));
        }
    }
    else
    {
        GAMENUM = 1000;
        //方案2：朴素蒙特卡洛(pure MonteCarlo)
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                if(cloneChessBoard[i][j]=='.')
                {
                    char temp[15][15];
                    copyArray(cloneChessBoard,temp);
                    temp[i][j] = stateMap[chessColor];
                    vec.push_back(nextState(temp));
                    bestPos.push_back(pair<short,short>(i,j));
                }
            }
        }
    }

    int index = 0,scoreTemp,score = -1;

    for(int i = 0; i < vec.size(); i++)
    {
        showPoint = bestPos[i];
        scoreTemp = MonteCarlo(vec[i].nextBoard,ChessType(3-chessColor));


        //SetCursorPos(pair<short,short>(0,17));
        //cout<<"                       ";
        //SetCursorPos(pair<short,short>(0,17));
        //cout<<bestPos[i].first<<" "<<bestPos[i].second<<" "<<scoreTemp<<endl;
        //getchar();
        if(scoreTemp>score)
        {
            score = scoreTemp;
            index = i;
        }
    }
    ChessBoard::getInstance()->PlayChess(bestPos[index]);
    return ;
}
void AIPlayer4::addPos(vector<pair<short,short> > &p,int i,int j,char newBoard[][15])
{
    if(i-1>=0&&newBoard[i-1][j]=='.')
        p.push_back(pair<short,short>(i-1,j));
    if(i+1<15&&newBoard[i+1][j]=='.')
        p.push_back(pair<short,short>(i+1,j));
    if(j-1>=0&&newBoard[i][j-1]=='.')
        p.push_back(pair<short,short>(i,j-1));
    if(j+1<15&&newBoard[i][j+1]=='.')
        p.push_back(pair<short,short>(i,j+1));
    if(i-1>=0&&j-1>=0&&newBoard[i-1][j-1]=='.')
        p.push_back(pair<short,short>(i-1,j-1));
    if(i+1<15&&j+1<15&&newBoard[i+1][j+1]=='.')
        p.push_back(pair<short,short>(i+1,j+1));
    if(j-1>=0&&i+1<15&&newBoard[i+1][j-1]=='.')
        p.push_back(pair<short,short>(i+1,j-1));
    if(j+1<15&&i-1>=0&&newBoard[i-1][j+1]=='.')
        p.push_back(pair<short,short>(i-1,j+1));
    /*
    if(i-2>=0&&newBoard[i-2][j]=='.')
        p.push_back(pair<short,short>(i-2,j));
    if(i+2<15&&newBoard[i+2][j]=='.')
        p.push_back(pair<short,short>(i+2,j));
    if(j-2>=0&&newBoard[i][j-2]=='.')
        p.push_back(pair<short,short>(i,j-2));
    if(j+2<15&&newBoard[i][j+2]=='.')
        p.push_back(pair<short,short>(i,j+2));
    if(i-2>=0&&j-2>=0&&newBoard[i-2][j-2]=='.')
        p.push_back(pair<short,short>(i-2,j-2));
    if(i+2<15&&j+2<15&&newBoard[i+2][j+2]=='.')
        p.push_back(pair<short,short>(i+2,j+2));
    if(j-2>=0&&i+2<15&&newBoard[i+2][j-2]=='.')
        p.push_back(pair<short,short>(i+2,j-2));
    if(j+2<15&&i-2>=0&&newBoard[i-2][j+2]=='.')
        p.push_back(pair<short,short>(i-2,j+2));
        */
}
int AIPlayer4::MonteCarlo(char bestPlace[][15],ChessType ChessColor)
{
    WinRandom R;
    int finalScore = 0;
    ChessType myColor = ChessType(3-chessColor);//Get my color
    vector<pair<short,short> > p;
    /*Pure MonteCarlo
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(bestPlace[i][j]=='.')
                p.push_back(pair<short,short>(pair<short,short>(i,j)));
        }
    }
    for(int i = 0; i < GAMENUM; i++)
    {
        vector<pair<short,short> > tempPos = p;
        ChessType tempColor = ChessColor;
        char tempBoard[15][15];
        copyArray(bestPlace,tempBoard);
        while(true)
        {
            if(tempPos.size()==0)
            {
                break;
            }
            int w = R.randUnsigned()%tempPos.size();//在可下位置中获取随机位置
            if(CheckWinner(tempBoard,tempPos[w]))
            {
                if(tempColor==myColor)
                {
                    finalScore+=1;
                    break;
                }
                else
                {
                    break;
                }
            }
            else
            {
                tempBoard[tempPos[w].first][tempPos[w].second] = stateMap[tempColor];
                tempColor = ChessType(3-tempColor);
                tempPos.erase(tempPos.begin()+w);
            }
            for(int i = 0;i < 15;i++)
            {
                for(int j = 0;j < 15;j++)
                {
                    SetCursorPos(pair<short,short>(i+20,j));
                    cout<<tempBoard[i][j];
                }
            }
            getchar();

        }
    }
    */
    //Heuristic MonteCarlo
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(bestPlace[i][j]!='.')
            {
                addPos(p,i,j,bestPlace);
            }
        }
    }
    for(int i = 0; i < GAMENUM; i++)
    {
        vector<pair<short,short> > tempPos = p;
        ChessType tempColor = ChessColor;
        char tempBoard[15][15];
        copyArray(bestPlace,tempBoard);
        while(true)
        {
            if(tempPos.size()==0)
            {
                break;
            }
            int w = R.randUnsigned()%tempPos.size();//get the random place
            if(tempBoard[tempPos[w].first][tempPos[w].second] !='.')
            {
                tempPos.erase(tempPos.begin()+w);
                continue;
            }
            if(CheckWinner(tempBoard,tempPos[w]))
            {
                if(tempColor==myColor)
                {
                    finalScore+=1;
                    break;
                }
                else
                {
                    finalScore-=1;
                    break;
                }
            }
            else
            {
                tempBoard[tempPos[w].first][tempPos[w].second] = stateMap[tempColor];
                addPos(tempPos,tempPos[w].first,tempPos[w].second,tempBoard);
                tempColor = ChessType(3-tempColor);
                tempPos.erase(tempPos.begin()+w);
            }

            /*Show the Mento Carlo process*/
            if(ChessBoard::getInstance()->show)
            {
                for(int i = 0; i < 15; i++)
                {
                    for(int j = 0; j < 15; j++)
                    {
                        SetCursorPos(pair<short,short>(i+20,j));
                        cout<<tempBoard[i][j];
                    }
                }

                SetCursorPos(pair<short,short>(0,17));
                cout<<"               "<<endl;
                SetCursorPos(pair<short,short>(0,17));
                cout<<"Score:"<<finalScore<<endl;

                SetCursorPos(pair<short,short>(0,16));
                cout<<"               "<<endl;
                SetCursorPos(pair<short,short>(0,16));
                cout<<"Point:"<<showPoint.first<<" "<<showPoint.second<<endl;

                SetCursorPos(pair<short,short>(0,18));
                cout<<"                   ";
                SetCursorPos(pair<short,short>(0,18));
                cout<<"iterate times:"<<i<<endl;
            }


        }
    }


    return finalScore;
}
bool AIPlayer4::CheckWinner(char Board[15][15],pair<short,short> pos)
{
    if(CheckLine(Board,pos,pair<short,short>(1,0)))
        return 1;
    if(CheckLine(Board,pos,pair<short,short>(0,1)))
        return 1;
    if(CheckLine(Board,pos,pair<short,short>(1,1)))
        return 1;
    if(CheckLine(Board,pos,pair<short,short>(1,-1)))
        return 1;

    return 0;
}
bool AIPlayer4::CheckLine(char Board[15][15],pair<short,short> pos,pair<short,short>offset)
{
    int linkNum = 1;
    int Count = 0;
    //Left
    for(int i = offset.first,j = offset.second; (pos.first+i>=0&&pos.first+i<15)&&
            (pos.second+j>=0&&pos.second+j<15); i+=offset.first,j+=offset.second)
    {
        if(Board[pos.first+i][pos.second+j]==stateMap[chessColor])
        {
            linkNum++;
        }
        else
        {
            break;
        }
    }
    //right
    for(int i = -offset.first,j = -offset.second; (pos.first+i>=0&&pos.first+i<15)&&
            (pos.second+j>=0&&pos.second+j<15); i-=offset.first,j-=offset.second)
    {
        if(Board[pos.first+i][pos.second+j]==stateMap[chessColor])
        {
            linkNum++;
        }
        else
        {
            break;
        }
    }
    if (linkNum > 4)
        return true;
    return false;
}
