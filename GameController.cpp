#include "GameController.h"
#include <iostream>
#include <time.h>
#include <conio.h>
#include "GameController.h"
#include "Player.h"
#include "GameController.h"
#include "Tools.h"
#include "startInterface.h"
#include <windows.h>
#include "AIPlayer1.h"
#include "AIPlayer2.h"
#include "AIPlayer3.h"
#include "AIPlayer4.h"
#include "AIPlayer5.h"
using namespace std;
void GameController::Start()//Start Interface
{
    SetWindowSize(41, 32);//Set the windows size
    SetColor(2);//set the color of the animation
    StartInterface *start = new StartInterface();
    start->Action();//Start animation
    delete start;//release the start

    /*Srt cursor pos and print the begin button*/
    SetCursorPosition(13, 26);
    cout << "Press any key to start... " ;
    //SetCursorPosition(13, 27);
    //system("pause");
}
void GameController::SelectPlayer()//select play with human or AI
{
    /*initial the interface*/
    SetColor(3);
    SetCursorPosition(13, 26);
    cout << "                          " ;
    SetCursorPosition(13, 27);
    cout << "                          " ;
    SetColor(11);
    SetCursorPosition(2, 21);
    cout << "Chose to Play Game!" ;
    SetCursorPosition(2, 22);
    cout << "(UP/DOWN move, Enter determine.\"r\" to regret)" ;
    SetCursorPosition(2, 24);
    cout << "Press \"b\" then press Enter can back to last level" ;
    if(!ChessBoard::getInstance()->show)
    {
        SetCursorPosition(2, 26);
        cout << "Show Mode: off(Press \"S\")" ;
    }else
    {
        SetCursorPosition(2, 26);
        cout << "Show Mode: on" ;
    }
    SetCursorPosition(27, 22);
    SetBackColor();//第一个选项设置背景色以表示当前选中
    cout << "Player VS Player" ;

    SetCursorPosition(27, 26);
    SetColor(3);
    cout << "Player VS   AI" ;

    SetCursorPosition(0, 31);

    /*Up and down button*/
    int ch;
    key = 1;//record the choice, the default is the first one
    bool flag = false;//record whether Enter
    while ((ch = getch()))
    {
        switch (ch)//check the input
        {
        case 's':
        {
            ChessBoard::getInstance()->show = true;
            SetCursorPosition(2, 26);
            cout << "                                    " ;
            SetCursorPosition(2, 26);
            cout << "Show Mode: on" ;

        }
        case 72://if Up
            if (key = 2)//when it is first one, the up not work
            {
                SetCursorPosition(27, 22);
                SetBackColor();
                cout << "Player VS Player" ;

                SetCursorPosition(27, 26);
                SetColor(3);
                cout << "Player VS   AI" ;
                --key;
            }
            break;

        case 80://DOWN
            if (key = 1)
            {
                SetCursorPosition(27, 26);
                SetBackColor();
                cout << "Player VS   AI" ;

                SetCursorPosition(27, 22);//将已选中项取消我背景色
                SetColor(3);
                cout << "Player VS Player" ;
                key++;
            }
            break;

        case 13://Enter
            flag = true;
            break;
        default:
            break;
        }
        if (flag)
            break;

        SetCursorPosition(0, 31);
    }
    switch (key)
    {
    case 1:
    {
        //直接开始和人对打
        system("cls");
        HideCursor();//隐藏鼠标
        Player BlackPlayer(BLACK);
        Player WhitePlayer(WHITE);
        while(true)//游戏循环
        {
            BlackPlayer.Start();
            WhitePlayer.Start();
        }
        break;
    }
    case 2:
    {
        SelectFirstPlayer();
        break;
    }
    }
}
void GameController::SelectFirstPlayer()
{
    SetCursorPosition(27, 22);
    cout<<"                                          ";
    SetCursorPosition(27, 22);
    SetBackColor();
    cout << "You First" ;
    SetCursorPosition(27, 26);
    SetColor(3);
    cout<<"                                          ";
    SetColor(3);
    SetCursorPosition(27, 26);
    cout << "AI  First" ;

    SetCursorPosition(0, 31);


    int ch;
    key = 1;
    bool flag = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 'b':
        {
            SetCursorPosition(27, 22);
            cout<<"                                          ";
            SetCursorPosition(27, 24);
            cout<<"                                          ";
            SetCursorPosition(27, 26);
            cout<<"                                          ";
            SetCursorPosition(27, 28);
            cout<<"                                          ";
            SelectPlayer();
        }
        case 's':
        {
            ChessBoard::getInstance()->show = true;
            SetCursorPosition(2, 26);
            cout << "                                          " ;
            SetCursorPosition(2, 26);
            cout << "Show Mode: on" ;
        }
        case 72:
            if (key = 2)
            {
                SetCursorPosition(27, 22);
                SetBackColor();
                cout << "You First" ;

                SetCursorPosition(27, 26);
                SetColor(3);
                cout << "AI  First" ;
                --key;
            }
            break;

        case 80:
            if (key = 1)
            {
                SetCursorPosition(27, 26);
                SetBackColor();
                cout << "AI  First" ;

                SetCursorPosition(27, 22);
                SetColor(3);
                cout << "You First" ;
                key++;
            }
            break;

        case 13:
            flag = true;
            break;
        default:
            break;
        }
        if (flag)
            break;

        SetCursorPosition(0, 31);
    }
    switch (key)
    {
    case 1:
        SelectDifficulty(false);
        break;
    case 2:
        SelectDifficulty(true);
        break;
    }
}
void GameController::SelectDifficulty(bool AIFirst)
{
    SetColor(3);
    SetCursorPosition(13, 26);
    cout << "                          " ;
    SetCursorPosition(13, 27);
    cout << "                          " ;
    SetColor(11);
    SetCursorPosition(2, 21);
    cout << "Chose to Play Game!" ;
    SetCursorPosition(2, 22);
    cout << "(UP/DOWN move, Enter determine.\"r\" to regret)" ;
    SetCursorPosition(2, 24);
    cout << "Press \"b\" then press Enter can back to last level" ;
    if(!ChessBoard::getInstance()->show)
    {
        SetCursorPosition(2, 26);
        cout << "Show Mode: off" ;
    }else
    {
        SetCursorPosition(2, 26);
        cout << "Show Mode: on" ;
    }
    SetCursorPosition(27, 22);
    SetBackColor();
    cout << "Easy   Mode" ;
    SetCursorPosition(27, 24);
    SetColor(3);
    cout << "Normal Mode" ;
    SetCursorPosition(27, 26);
    cout<<"                                          ";
    SetCursorPosition(27, 26);
    cout << "Hard   Mode" ;
    SetCursorPosition(27, 28);
    cout << "Purgatory!!" ;
    SetCursorPosition(0, 31);

    int ch;
    key = 1;
    bool flag = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 'b':
            SetCursorPosition(27, 22);
            cout<<"                                          ";
            SetCursorPosition(27, 24);
            cout<<"                                          ";
            SetCursorPosition(27, 26);
            cout<<"                                          ";
            SetCursorPosition(27, 28);
            cout<<"                                          ";
            SelectFirstPlayer();
        case 's':
        {
            ChessBoard::getInstance()->show = true;
            SetCursorPosition(2, 26);
            cout << "                 " ;
            SetCursorPosition(2, 26);
            cout << "Show Mode: on" ;

        }
        case 72:
            if (key > 1)
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22);
                    SetBackColor();
                    cout << "Easy   Mode" ;

                    SetCursorPosition(27, 24);
                    SetColor(3);
                    cout << "Normal Mode" ;

                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    cout << "Normal Mode" ;

                    SetCursorPosition(27, 26);
                    SetColor(3);
                    cout << "Hard   Mode" ;

                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    cout << "Hard   Mode" ;

                    SetCursorPosition(27, 28);
                    SetColor(3);
                    cout << "Purgatory!!" ;

                    --key;
                    break;
                }
            }
            break;

        case 80:
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    cout << "Normal Mode" ;
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    cout << "Easy   Mode" ;

                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    cout << "Hard   Mode" ;
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    cout << "Normal Mode" ;

                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    cout << "Purgatory!!" ;
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    cout << "Hard   Mode" ;

                    ++key;
                    break;
                }
            }
            break;

        case 13:
            flag = true;
            break;
        default:
            break;
        }
        if (flag)
            break;

        SetCursorPosition(0, 31);
    }
    switch (key)
    {
    case 1:
        StartGame(AIFirst,key);
        break;
    case 2:
        StartGame(AIFirst,key);
        break;
    case 3:
        StartGame(AIFirst,key);
        break;
    case 4:
        StartGame(AIFirst,key);
        break;
    default:
        break;
    }
}
void GameController::StartGame(bool AIFirst,int key)
{
    system("cls");
    HideCursor();
    Player Human;
    if(!AIFirst)
        Human = Player(BLACK);
    else
        Human = Player(WHITE);
    if(key==1)
    {
        AIPlayer2 AIBlack = AIPlayer2(BLACK);
        AIPlayer2 AIWhite = AIPlayer2(WHITE);
        while(true)
        {
            if(AIFirst)
            {
                AIBlack.Start();
                Human.Start();
            }
            else
            {
                Human.Start();
                AIWhite.Start();
            }
        }
    }
    else if(key==2)
    {
        AIPlayer4 AIBlack = AIPlayer4(BLACK);
        AIPlayer4 AIWhite = AIPlayer4(WHITE);
        while(true)
        {
            if(AIFirst)
            {
                AIBlack.Start();
                Human.Start();
            }
            else
            {
                Human.Start();
                AIWhite.Start();
            }
        }
    }
    else if(key==3)
    {
        AIPlayer3 AIBlack = AIPlayer3(BLACK);
        AIPlayer3 AIWhite = AIPlayer3(WHITE);
        while(true)
        {
            if(AIFirst)
            {
                AIBlack.Start();
                Human.Start();
            }
            else
            {
                Human.Start();
                AIWhite.Start();
            }
        }
    }
    else if(key==4)
    {
        AIPlayer5 AIBlack = AIPlayer5(BLACK);
        AIPlayer5 AIWhite = AIPlayer5(WHITE);
        AIPlayer3 _AIBlack = AIPlayer3(BLACK);
        AIPlayer3 _AIWhite = AIPlayer3(WHITE);
        while(true)
        {
            if(AIFirst)
            {
                if(ChessBoard::getInstance()->st.size()<=18)
                {
                    AIBlack.Start();
                    Human.Start();
                }
                else
                {
                    _AIBlack.Start();
                    Human.Start();
                }
            }
            else
            {
                if(ChessBoard::getInstance()->st.size()<=18)
                {
                    Human.Start();
                    AIWhite.Start();
                }
                else
                {
                    Human.Start();
                    _AIWhite.Start();
                }
            }
        }
    }
}
int GameController::PlayGame()
{
    HideCursor();
    Player BlackPlayer(BLACK);
    Player WhitePlayer(WHITE);
    while(true)
    {

    }
}

void GameController::Game()
{
    Start();
    while (true)
    {
        SelectPlayer();
    }
}

