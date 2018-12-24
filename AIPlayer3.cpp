#include "AIPlayer3.h"
#include<iostream>
#include<vector>
#include<float.h>
#include<limits.h>
#include<ctime>
#include<unordered_map>
using namespace std;
AIPlayer3::AIPlayer3(ChessType Color)
{
    chessColor = Color;

    pointModel["Five"] = INT_MAX;
    pointModel["LiveFour"] = 1000000;
    pointModel["SleepFour"] = 15000;
    pointModel["LiveThree"] = 10000;
    pointModel["SleepThree"] = 1000;
    pointModel["LiveTwo"] = 500;
    pointModel["SleepTwo"] = 50;
    pointModel["LiveOne"] = 10;

    toScore["_a___"] = pointModel["LiveOne"];
    toScore["__a__"] = pointModel["LiveOne"];
    toScore["___a_"] = pointModel["LiveOne"];
    toScore["___a_"] = pointModel["LiveOne"];

    toScore["aa___"]=pointModel["SleepTwo"];                      //眠二
    toScore["a_a__"]=pointModel["SleepTwo"];
    toScore["___aa"]=pointModel["SleepTwo"];
    toScore["__a_a"]=pointModel["SleepTwo"];
    toScore["a__a_"]=pointModel["SleepTwo"];
    toScore["_a__a"]=pointModel["SleepTwo"];
    toScore["a___a"]=pointModel["SleepTwo"];


    toScore["__aa__"]=pointModel["LiveTwo"]+1;                     //活二
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
    toScore["aaa__"]=pointModel["SleepThree"]+1;                     //眠三

    toScore["_aa_a_"]=pointModel["LiveThree"]-100;                    //跳活三
    toScore["_a_aa_"]=pointModel["LiveThree"]-100;

    toScore["_aaa_"]=pointModel["LiveThree"]+1;                    //活三


    toScore["a_aaa"]=pointModel["SleepFour"];                    //冲四
    toScore["aaa_a"]=pointModel["SleepFour"];                    //冲四
    toScore["_aaaa"]=pointModel["SleepFour"]+1;                    //冲四
    toScore["aaaa_"]=pointModel["SleepFour"]+1;                    //冲四
    toScore["aa_aa"]=pointModel["SleepFour"];                    //冲四


    toScore["_aaaa_"]=pointModel["LiveFour"];                 //活四

    toScore["aaaaa"]=pointModel["Five"];           //连五

    stateMap[BLACK] = 'x';
    stateMap[WHITE] = 'o';
}
AIPlayer3::AIPlayer3()
{
    //ctor
}

AIPlayer3::~AIPlayer3()
{
    //dtor
}

void AIPlayer3::playChess()
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

    MiniMaxNode1 node;
    node.value = -INT_MAX;
    int Count = 0;
    char cloneChessBoard[15][15];
    copyArray(ChessBoard::getInstance()->myChessBoard,cloneChessBoard);
    //for(int i = 0;i < 15;i++)
    //for(int j = 0;j < 15;j++)
    //cloneChessBoard[i][j] = ChessBoard::getInstance()->myChessBoard[i][j];


    vector<MiniMaxNode1> Mnn = GetVector(cloneChessBoard,chessColor,true);
    for(auto &item : Mnn)
    {
        copyArray(ChessBoard::getInstance()->myChessBoard,cloneChessBoard);
        createTree(item,cloneChessBoard,3,false);

        float a = INT_MIN;
        float b = INT_MAX;
        item.value += AlphaBeta(item,3,false,a,b);
        //挑最大的
        if(node.value<item.value)
        {
            node = item;
        }
    }
    ChessBoard::getInstance()->PlayChess(node.pos);
}

float AIPlayer3::AlphaBeta(MiniMaxNode1 node,int depth,bool myself,float alpha,float beta)
{

    if(depth==0||node.value>=INT_MAX||node.value<=-INT_MAX)
        return node.value;
    if(myself)
    {
        for(auto &child : node.child)
        {
            alpha = max(alpha,AlphaBeta(child,depth-1,!myself,alpha,beta));

            //alpha剪枝
            if(alpha>=beta)
                return alpha;
        }
        return alpha;
    }
    else
    {
        for(auto &child : node.child)
        {
            beta = min(beta,AlphaBeta(child,depth-1,!myself,alpha,beta));

            //beta剪枝
            if(alpha>=beta)
                return beta;
        }
        return beta;
    }
}

vector<MiniMaxNode1> AIPlayer3::GetVector(char chessboard[][15],ChessType myChessColor,bool myself)
{
    vector<MiniMaxNode1> nodeVector;
    MiniMaxNode1 node;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            pair<short,short> p = pair<short,short>(i,j);
            if(chessboard[i][j]!='.')
                continue;

            node.pos = p;
            node.chess = myChessColor;
            if(myself)
                node.value = getTotalScore(chessboard,p);
            else
                node.value = -getTotalScore(chessboard,p);
            if(nodeVector.size()<=3)
                nodeVector.push_back(node);
            else
            {
                int Count = 0;
                for(auto &item : nodeVector)
                {
                    if(myself)
                    {
                        if(node.value>item.value)
                        {
                            nodeVector.erase(nodeVector.begin()+Count);
                            nodeVector.push_back(node);
                            break;
                        }
                    }
                    else
                    {
                        if(node.value<item.value)
                        {
                            nodeVector.erase(nodeVector.begin()+Count);
                            nodeVector.push_back(node);
                            break;
                        }
                    }
                    ++Count;
                }
            }
        }
    }
    return nodeVector;
}

void AIPlayer3::createTree(MiniMaxNode1 &node,char chessboard[][15],int depth,bool myself)
{
    char cloneChessBoard[15][15];
    //SetCursorPos(pair<short,short>(0,18));
    //cout<<depth<<" "<<myself;
    if(depth==0||node.value>=INT_MAX)
        return ;
    if(!myself)
        chessboard[node.pos.first][node.pos.second] = stateMap[chessColor];
    else
        chessboard[node.pos.first][node.pos.second] = stateMap[ChessType(-chessColor+3)];
    node.child = GetVector(chessboard,ChessType(-node.chess+3),!myself);

    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            SetCursorPos(pair<short,short>(i+20,j));
            cout<<"   ";
        }
    }
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {

            SetCursorPos(pair<short,short>(i+20,j));
            cout<<chessboard[i][j];
        }
    }
    //getchar();


    for(auto &item : node.child)
    {
        copyArray(chessboard,cloneChessBoard);
        createTree(item,cloneChessBoard,depth-1,!myself);
    }
}
float AIPlayer3::getTotalScore(char chessboard[][15],pair<short,short> p)
{
    float ans = 0;
    ans += getLineScore(chessboard,p,pair<short,short>(1,0),chessColor);
    ans += getLineScore(chessboard,p,pair<short,short>(0,1),chessColor);
    ans += getLineScore(chessboard,p,pair<short,short>(1,1),chessColor);
    ans += getLineScore(chessboard,p,pair<short,short>(1,-1),chessColor);

    ans += getLineScore(chessboard,p,pair<short,short>(1,0),ChessType(-chessColor+3));
    ans += getLineScore(chessboard,p,pair<short,short>(0,1),ChessType(-chessColor+3));
    ans += getLineScore(chessboard,p,pair<short,short>(1,1),ChessType(-chessColor+3));
    ans += getLineScore(chessboard,p,pair<short,short>(1,-1),ChessType(-chessColor+3));

    return ans;
}
float AIPlayer3::getLineScore(char chessboard[][15],pair<short,short> p,pair<short,short> offset,ChessType myChessColor)
{
    string str = "a";
    //右边
    HideCursor();
    for(int i = offset.first,j = offset.second,k=0; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15&&k<4; i+=offset.first,j+=offset.second,k++)
    {
        if(chessboard[p.first+i][p.second+j]==stateMap[myChessColor])
        {
            str += "a";
        }
        else if(chessboard[p.first+i][p.second+j]=='.')
        {
            str +="_";
        }
        else
        {
            break;
        }
    }
    //左边
    for(int i = -offset.first,j = -offset.second,k=0; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15&&k<4; i-=offset.first,j-=offset.second,k++)
    {
        if(chessboard[p.first+i][p.second+j]==stateMap[myChessColor])
        {
            str="a"+str;
        }
        else if(chessboard[p.first+i][p.second+j]=='.')
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
