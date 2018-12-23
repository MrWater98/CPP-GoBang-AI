#include "AIPlayer5.h"
#include<iostream>
#include<map>
#include<algorithm>
#include<limits.h>
#include<string.h>
#include<windows.h>
#include "ChessBoard.h"
#include "Zobrist.h"
using namespace std;
AIPlayer5::AIPlayer5(ChessType Color)
{

    chessColor = Color;
    stateMap[BLACK] = 'x';
    stateMap[WHITE] = 'o';
    chessModel["Five"] = 100000;
    chessModel["LiveFour"] = 10000;
    chessModel["SleepFour"] = 1000;
    chessModel["LiveThree"] = 1000;
    chessModel["SleepThree"] = 100;
    chessModel["LiveTwo"] = 100;
    chessModel["SleepTwo"] = 10;
    chessModel["LiveOne"] = 10;

    evaBoard["_a___"] = chessModel["LiveOne"];
    evaBoard["__a__"] = chessModel["LiveOne"];
    evaBoard["___a_"] = chessModel["LiveOne"];
    evaBoard["___a_"] = chessModel["LiveOne"];

    evaBoard["aa___"]=chessModel["SleepTwo"];                      //眠二
    evaBoard["a_a__"]=chessModel["SleepTwo"];
    evaBoard["___aa"]=chessModel["SleepTwo"];
    evaBoard["__a_a"]=chessModel["SleepTwo"];
    evaBoard["a__a_"]=chessModel["SleepTwo"];
    evaBoard["_a__a"]=chessModel["SleepTwo"];
    evaBoard["a___a"]=chessModel["SleepTwo"];


    evaBoard["__aa__"]=chessModel["LiveTwo"]+1;                     //活二
    evaBoard["_a_a_"]=chessModel["LiveTwo"];
    evaBoard["_a__a_"]=chessModel["LiveTwo"]-1;

    evaBoard["_aa__"]=chessModel["LiveTwo"]+1;
    evaBoard["__aa_"]=chessModel["LiveTwo"]+1;


    evaBoard["a_a_a"]=chessModel["SleepThree"]-1;
    evaBoard["aa__a"]=chessModel["SleepThree"];
    evaBoard["_aa_a"]=chessModel["SleepThree"];
    evaBoard["a_aa_"]=chessModel["SleepThree"];
    evaBoard["_a_aa"]=chessModel["SleepThree"];
    evaBoard["aa_a_"]=chessModel["SleepThree"];
    evaBoard["aaa__"]=chessModel["SleepThree"]+1;                     //眠三

    evaBoard["_aa_a_"]=chessModel["LiveThree"]-1;                    //跳活三
    evaBoard["_a_aa_"]=chessModel["LiveThree"]-1;

    evaBoard["_aaa_"]=chessModel["LiveThree"]+1;                    //活三


    evaBoard["a_aaa"]=chessModel["SleepFour"];                    //冲四
    evaBoard["aaa_a"]=chessModel["SleepFour"];                    //冲四
    evaBoard["_aaaa"]=chessModel["SleepFour"]+1;                    //冲四
    evaBoard["aaaa_"]=chessModel["SleepFour"]+1;                    //冲四
    evaBoard["aa_aa"]=chessModel["SleepFour"];                    //冲四


    evaBoard["_aaaa_"]=chessModel["LiveFour"];                 //活四

    evaBoard["aaaaa"]=chessModel["Five"];           //连五


}
AIPlayer5::AIPlayer5()
{
    //ctor
}

AIPlayer5::~AIPlayer5()
{
    //dtor
}
void AIPlayer5::playChess()
{
    hashValue = ChessBoard::getInstance()->zobrist.computeHash(ChessBoard::getInstance()->myChessBoard);
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

    MiniMaxNode2 node;
    node.value = -chessModel["Five"];
    char cloneChessBoard[15][15];
    copyArray(ChessBoard::getInstance()->myChessBoard,cloneChessBoard);
    vector<MiniMaxNode2> Mnn = GetVector(cloneChessBoard,chessColor,true);
    for(auto &item : Mnn)
    {
        SetCursorPos(pair<short,short>(item.pos.first,item.pos.second));
        SetColor(3);
        cout<<".";

        copyArray(ChessBoard::getInstance()->myChessBoard,cloneChessBoard);
        createTree(item,cloneChessBoard,3,false);

        float a = -chessModel["Five"];
        float b = chessModel["Five"];
        item.value += AlphaBeta(item,3,false,a,b);

        SetCursorPos(pair<short,short>(item.pos.first,item.pos.second));
        SetColor(10);
        cout<<".";

        SetCursorPos(pair<short,short>(0,18));
        cout<<"                                   ";
        SetCursorPos(pair<short,short>(0,18));
        cout<<"x:"<<item.pos.first<<" y:"<<item.pos.second<<" "<<item.value;

        //挑最大的
        if(node.value<item.value)
        {
            node = item;
        }
    }
    SetCursorPos(pair<short,short>(0,18));
    cout<<"                                   ";
    SetCursorPos(pair<short,short>(0,18));
    cout<<"nx:"<<node.pos.first<<" ny:"<<node.pos.second<<" "<<node.value;
    //getchar();
    ChessBoard::getInstance()->PlayChess(node.pos);

}
bool AIPlayer5::hasNeighbor(char chessBoard[][15],int i,int j)
{
    /*
    pair<short,short> po[4];
    po[0] = make_pair(1,1);
    po[1] = make_pair(1,-1);
    po[2] = make_pair(1,0);
    po[3] = make_pair(0,1);
    for(int k = 0;k<=3;k++)
    {
        int xEnd = i+po[k].first*2,yEnd = j+po[k].second*2;
        for(int x = i-po[k].first*2;x<=xEnd&&x>=0&&x<15;x++)
        {
            for(int y = j-po[k].second*2;y<=yEnd&&y>=0&&y<15;y++)
            {
                if(chessBoard[x][y]!='.')
                    return true;
            }
        }
    }
    return false;
    */


    int xBegin = i-2>=0?i-2:0;
    int yBegin = j-2>=0?j-2:0;
    int xEnd = i+2<=14?i+2:14;
    int yEnd = j+2<=14?j+2:14;

    for(int x = xBegin; x<=xEnd; x++)
    {
        for(int y = yBegin; y<=yEnd; y++)
        {
            if(chessBoard[x][y]!='.')
                return true;
        }
    }
    return false;

}
vector<MiniMaxNode2> AIPlayer5::GetVector(char chessboard[][15],ChessType myChessColor,bool myself)
{
    vector<MiniMaxNode2> nodeVector;
    MiniMaxNode2 node;
    int Count = 0;
    unsigned long long int curBoardHash = ChessBoard::getInstance()->zobrist.computeHash(chessboard);
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(chessboard[i][j]=='.'&&hasNeighbor(chessboard,i,j))
            {
                pair<short,short> p = pair<short,short>(i,j);
                node.pos = p;
                node.chess = myChessColor;
                char cloneChessBoard[15][15];
                copyArray(chessboard,cloneChessBoard);
                cloneChessBoard[i][j] = myself?stateMap[chessColor]:stateMap[ChessType(-chessColor+3)];

                unsigned long long int tempHash = curBoardHash^ChessBoard::getInstance()
                ->zobrist.ZobristTable[i][j][ChessBoard::getInstance()
                ->zobrist.indexOf(cloneChessBoard[i][j])];

                if(ChessBoard::getInstance()->zobrist.hashTable[to_string(tempHash)]==0){
                    node.value = getTotalValue(cloneChessBoard,myself);
                    ChessBoard::getInstance()->zobrist.hashTable[to_string(tempHash)] = node.value;
                }else
                {
                    node.value = ChessBoard::getInstance()->zobrist.hashTable[to_string(tempHash)];
                }

                //hashTable[chessboard] = node.value这时候就可以对已经打过分的点进行储存


                /*
                SetCursorPos(pair<short,short>(0,18));
                cout<<"                             "<<endl;
                SetCursorPos(pair<short,short>(0,18));
                cout<<"x:"<<p.first<<" y:"<<p.second<<endl;
                SetCursorPos(pair<short,short>(0,19));
                cout<<"                             "<<endl;
                SetCursorPos(pair<short,short>(0,19));
                cout<<node.value<<endl;
                */
                //getchar();
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
    }

    return nodeVector;
}
void AIPlayer5::createTree(MiniMaxNode2 &node,char chessboard[][15],int depth,bool myself)
{
    char cloneChessBoard[15][15];
    //SetCursorPos(pair<short,short>(0,18));
    //cout<<depth<<" "<<myself;
    if(depth==0||node.value>=chessModel["Five"]||node.value<=-chessModel["Five"])
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
float AIPlayer5::AlphaBeta(MiniMaxNode2 node,int depth,bool myself,float alpha,float beta)
{

    if(depth==0||node.value>=chessModel["Five"])
        return node.value;
    if(myself)
    {
        for(auto &child : node.child)
        {
            alpha = max(alpha,AlphaBeta(child,depth-1,!myself,alpha,beta));

            //alpha剪枝
            //if(alpha>=beta)
            //return alpha;
        }
        return alpha;
    }
    else
    {
        for(auto &child : node.child)
        {
            beta = min(beta,AlphaBeta(child,depth-1,!myself,alpha,beta));
            //beta剪枝
            //if(alpha>=beta)
            //return beta;
        }
        return beta;
    }
}
float AIPlayer5::getTotalValue(char chessboard[][15],bool myself)
{
    float ans1 = 0;
    float ans2 = 0;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(chessboard[i][j]!='.')
            {
                if(chessboard[i][j]==stateMap[chessColor])
                {
                    ans1 += getLineScore(chessboard,pair<short,short>(i,j),pair<short,short>(1,0),chessColor);
                    ans1 += getLineScore(chessboard,pair<short,short>(i,j),pair<short,short>(0,1),chessColor);
                    ans1 += getLineScore(chessboard,pair<short,short>(i,j),pair<short,short>(1,1),chessColor);
                    ans1 += getLineScore(chessboard,pair<short,short>(i,j),pair<short,short>(1,-1),chessColor);
                }
                else if(chessboard[i][j]==stateMap[ChessType(-chessColor+3)])
                {
                    ans2 += getLineScore(chessboard,pair<short,short>(i,j),pair<short,short>(1,0),ChessType(-chessColor+3))*1.01;
                    ans2 += getLineScore(chessboard,pair<short,short>(i,j),pair<short,short>(0,1),ChessType(-chessColor+3))*1.01;
                    ans2 += getLineScore(chessboard,pair<short,short>(i,j),pair<short,short>(1,1),ChessType(-chessColor+3))*1.01;
                    ans2 += getLineScore(chessboard,pair<short,short>(i,j),pair<short,short>(1,-1),ChessType(-chessColor+3))*1.01;
                }
            }
        }
    }

    if(myself)
        return ans1-ans2;
    else
        return ans2-ans1;
    return 0;
}
float AIPlayer5::getLineScore(char chessboard[][15],pair<short,short> p,pair<short,short> offset,ChessType myChessColor)
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
    for(auto &i : evaBoard)
    {
        if(str.find(i.first)!=string::npos)
        {
            if (cmpStr != "")
            {
                if(evaBoard[i.first]>evaBoard[cmpStr])
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
    return evaBoard[cmpStr];
}
