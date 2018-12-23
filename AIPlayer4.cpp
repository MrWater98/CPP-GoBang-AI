#include "AIPlayer4.h"
#include<iostream>
#include<ctime>
#include<limits.h>
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
int GAMENUM = 15000;
int BESTPOSNUM = 3;
AIPlayer4::AIPlayer4(ChessType Color)
{
    chessColor = Color;

   toScore["aa___"]=100;                      //眠二
    toScore["a_a__"]=80;
    toScore["___aa"]=100;
    toScore["__a_a"]=80;
    toScore["a__a_"]=80;
    toScore["_a__a"]=80;
    toScore["a___a"]=60;


    toScore["__aa__"]=300;                     //活二
    toScore["_a_a_"]=230;
    toScore["_a__a_"]=230;

    toScore["_aa__"]=300;
    toScore["__aa_"]=300;


    toScore["a_a_a"]=600;
    toScore["aa__a"]=600;
    toScore["_aa_a"]=600;
    toScore["a_aa_"]=600;
    toScore["_a_aa"]=600;
    toScore["aa_a_"]=600;
    toScore["aaa__"]=600;                     //眠三

    toScore["_aa_a_"]=1200;                    //跳活三
    toScore["_a_aa_"]=1200;

    toScore["_aaa_"]=1800;                    //活三


    toScore["a_aaa"]=2100;                    //冲四
    toScore["aaa_a"]=2100;                    //冲四
    toScore["_aaaa"]=2100;                    //冲四
    toScore["aaaa_"]=2100;                    //冲四
    toScore["aa_aa"]=2100;                    //冲四


    toScore["_aaaa_"]=5000;                 //活四

    toScore["aaaaa"]=INT_MAX;           //连五
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
        BESTPOSNUM = 2;
        GAMENUM = 50000;
    }
    else if(ChessBoard::getInstance()->st.size()>9&&ChessBoard::getInstance()->st.size()<=20)
    {
        BESTPOSNUM = 3;
        GAMENUM = 50000;
    }
    else if(ChessBoard::getInstance()->st.size()>20)
    {
        BESTPOSNUM = 3;
        GAMENUM = 20000;
    }
    //SetCursorPos(pair<short,short>(0,16));
    //cout<<ChessBoard::getInstance()->st.size()<<endl;

    char cloneChessBoard[15][15];
    copyArray(ChessBoard::getInstance()->myChessBoard,cloneChessBoard);
    vector<pair<short,short> > bestPos;
    vector<nextState> vec;
    //方案1：启发蒙特卡洛(Monte Carlo Based on Human Chess Spectrum)
    if(ChessBoard::getInstance()->st.size()<=225)
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
    ChessType myColor = ChessType(3-chessColor);//获得我的颜色
    vector<pair<short,short> > p;
    /*完全随机法
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
    //不完全随机法
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
            int w = R.randUnsigned()%tempPos.size();//在可下位置中获取随机位置
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
            /*显示蒙特卡洛过程*/
            for(int i = 0; i < 15; i++)
            {
                for(int j = 0; j < 15; j++)
                {
                    SetCursorPos(pair<short,short>(i+20,j));
                    cout<<tempBoard[i][j];
                }
            }

            //getchar();
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
    //ÓÒ±ß
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
    //×ó±ß
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
