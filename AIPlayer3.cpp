#include "AIPlayer3.h"
#include<iostream>
#include<vector>
#include<float.h>
#include<limits.h>
#include<ctime>
#include<map>
using namespace std;
AIPlayer3::AIPlayer3(ChessType Color)
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
    toScore["_a_a_"]=499;
    toScore["_a__a_"]=499;

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

    toScore["aaaaa"]=INT_MAX;           //连五

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
    /*
    else if(ChessBoard::getInstance()->st.size()==1)
    {
        for(int i = 0;i < 15;i++)
            for(int j = 0;j < 15;j++){
                if(ChessBoard::getInstance()->myChessBoard[i][j] == ChessBoard::getInstance()->m[int(-chessColor+3)])
                {
                    srand((unsigned)time(NULL));
                    int a=1,b=1;
                    while(a==0&&b==0)
                        a = rand()%3-1;b = rand()%3-1;
                    ChessBoard::getInstance()->myChessBoard[i+a][j+b] = ChessBoard::getInstance()->m[int(chessColor)];
                    ChessBoard::getInstance()->turn = ChessType(-chessColor+3);
                    ChessBoard::getInstance()->st.push(pair<short,short>(i+a,j+b));
                    return ;
                }
            }
    }
    */
    MiniMaxNode node;
    node.value = -INT_MAX;
    int Count = 0;
    char cloneChessBoard[15][15];
    for(int i = 0;i < 15;i++)
        for(int j = 0;j < 15;j++)
            cloneChessBoard[i][j] = ChessBoard::getInstance()->myChessBoard[i][j];

    vector<MiniMaxNode> Mnn = GetVector(cloneChessBoard,chessColor,true);
    for(auto &item : Mnn)
    {
        createTree(item,cloneChessBoard,8,false);

        float a = INT_MAX;
        float b = INT_MAX;
        item.value += AlphaBeta(item,8,false,a,b);
        //挑最大的
        if(node.value<item.value){
            node = item;
        }
    }
    ChessBoard::getInstance()->PlayChess(node.pos);
}

float AIPlayer3::AlphaBeta(MiniMaxNode node,int depth,bool myself,float alpha,float beta)
{

    if(depth==0||node.value>=INT_MAX||node.value>=INT_MAX)
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

vector<MiniMaxNode> AIPlayer3::GetVector(char chessboard[][15],ChessType myChessColor,bool myself)
{
    vector<MiniMaxNode> nodeVector;
    MiniMaxNode node;
    for(int i = 0;i < 15;i++)
    {
        for(int j = 0;j < 15;j++)
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
            if(nodeVector.size()<4)
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

void AIPlayer3::createTree(MiniMaxNode &node,char chessboard[][15],int depth,bool myself)
{
    if(depth==0||node.value>=INT_MAX)
        return ;
    chessboard[node.pos.first][node.pos.second] = stateMap[node.chess];
    node.child = GetVector(chessboard,node.chess,!myself);

    for(auto &item : node.child)
    {
        createTree(item,chessboard,depth-1,!myself);
    }
}
float AIPlayer3::getTotalScore(char chessboard[][15],pair<short,short> p)
{
    float ans = 0;
    ans += getLineScore(chessboard,p,pair<short,short>(1,0),chessColor)*1.2;
    ans += getLineScore(chessboard,p,pair<short,short>(0,1),chessColor)*1.2;
    ans += getLineScore(chessboard,p,pair<short,short>(1,1),chessColor)*1.2;
    ans += getLineScore(chessboard,p,pair<short,short>(1,-1),chessColor)*1.2;

    ans += getLineScore(chessboard,p,pair<short,short>(1,0),ChessType(-chessColor+3))*0.9;
    ans += getLineScore(chessboard,p,pair<short,short>(0,1),ChessType(-chessColor+3))*0.9;
    ans += getLineScore(chessboard,p,pair<short,short>(1,1),ChessType(-chessColor+3))*0.9;
    ans += getLineScore(chessboard,p,pair<short,short>(1,-1),ChessType(-chessColor+3))*0.9;

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
