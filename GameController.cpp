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

void GameController::Start()//开始界面
{
    SetWindowSize(41, 32);//设置窗口大小
    SetColor(2);//设置开始动画颜色
    StartInterface *start = new StartInterface();//动态分配一个StartInterface类start
    start->Action();//开始动画
    delete start;//释放内存空间

    /*设置关标位置，并输出提示语，等待任意键输入结束*/
    SetCursorPosition(13, 26);
    std::cout << "Press any key to start... " ;
    SetCursorPosition(13, 27);
    system("pause");
}
void GameController::SelectPlayer()//选择和人打还是和AI打
{
    /*初始化界面选项*/
    SetColor(3);
    SetCursorPosition(13, 26);
    std::cout << "                          " ;
    SetCursorPosition(13, 27);
    std::cout << "                          " ;
    SetColor(11);
    SetCursorPosition(2, 21);
    std::cout << "Chose to Play Game!" ;
    SetCursorPosition(2, 22);
    std::cout << "(UP/DOWN move, Enter determine.\"r\" to regret)" ;
    SetCursorPosition(2, 24);
    std::cout << "Press \"b\" then press Enter can back to last level" ;
    SetCursorPosition(27, 22);
    SetBackColor();//第一个选项设置背景色以表示当前选中
    std::cout << "Player VS Player" ;

    SetCursorPosition(27, 26);
    SetColor(3);
    std::cout << "Player VS   AI" ;

    SetCursorPosition(0, 31);

    /*上下方向键选择模块*/
    int ch;//记录键入值
    key = 1;//记录选中项，初始选择第一个
    bool flag = false;//记录是否键入Enter键标记，初始置为否
    while ((ch = getch()))
    {
        switch (ch)//检测输入键
        {
        case 72://UP上方向键
            if (key = 2)//当此时选中项为第一项时，UP上方向键无效
            {
                SetCursorPosition(27, 22);//给待选中项设置背景色
                SetBackColor();
                std::cout << "Player VS Player" ;

                SetCursorPosition(27, 26);//将已选中项取消我背景色
                SetColor(3);
                std::cout << "Player VS     AI" ;
                --key;
            }
            break;

        case 80://DOWN下方向键
            if (key = 1)
            {
                SetCursorPosition(27, 26);//给待选中项设置背景色
                SetBackColor();
                std::cout << "Player VS     AI" ;

                SetCursorPosition(27, 22);//将已选中项取消我背景色
                SetColor(3);
                std::cout << "Player VS Player" ;
                key++;
            }
            break;

        case 13://Enter回车键
            flag = true;
            break;
        default://无效按键
            break;
        }
        if (flag)
            break;//输入Enter回车键确认，退出检查输入循环

        SetCursorPosition(0, 31);//将光标置于左下角，避免关标闪烁影响游戏体验
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
    SetBackColor();//第一个选项设置背景色以表示当前选中
    std::cout << "You First" ;
    SetCursorPosition(27, 26);
    SetColor(3);
    cout<<"                                          ";
    SetColor(3);
    SetCursorPosition(27, 26);
    std::cout << "AI  First" ;

    SetCursorPosition(0, 31);

    /*上下方向键选择模块*/
    int ch;//记录键入值
    key = 1;//记录选中项，初始选择第一个
    bool flag = false;//记录是否键入Enter键标记，初始置为否
    while ((ch = getch()))
    {
        switch (ch)//检测输入键
        {
        case 'b':{
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
        case 72://UP上方向键
            if (key = 2)//当此时选中项为第一项时，UP上方向键无效
            {
                SetCursorPosition(27, 22);//给待选中项设置背景色
                SetBackColor();
                std::cout << "You First" ;

                SetCursorPosition(27, 26);//将已选中项取消我背景色
                SetColor(3);
                std::cout << "AI  First" ;
                --key;
            }
            break;

        case 80://DOWN下方向键
            if (key = 1)
            {
                SetCursorPosition(27, 26);//给待选中项设置背景色
                SetBackColor();
                std::cout << "AI  First" ;

                SetCursorPosition(27, 22);//将已选中项取消我背景色
                SetColor(3);
                std::cout << "You First" ;
                key++;
            }
            break;

        case 13://Enter回车键
            flag = true;
            break;
        default://无效按键
            break;
        }
        if (flag)
            break;//输入Enter回车键确认，退出检查输入循环

        SetCursorPosition(0, 31);//将光标置于左下角，避免关标闪烁影响游戏体验
    }
    switch (key)
    {
    case 1:
        //人类先下棋
        SelectDifficulty(false);
        break;
    case 2:
        SelectDifficulty(true);
        //AI先下棋
        break;
    }
}
void GameController::SelectDifficulty(bool AIFirst)//选择界面
{
    SetColor(3);
    SetCursorPosition(13, 26);
    std::cout << "                          " ;
    SetCursorPosition(13, 27);
    std::cout << "                          " ;
    SetColor(11);
    SetCursorPosition(2, 21);
    std::cout << "Chose to Play Game!" ;
    SetCursorPosition(2, 22);
    std::cout << "(UP/DOWN move, Enter determine.\"r\" to regret)" ;
    SetCursorPosition(2, 24);
    std::cout << "Press \"b\" then press Enter can back to last level" ;
    SetCursorPosition(27, 22);
    SetBackColor();//第一个选项设置背景色以表示当前选中
    std::cout << "Easy   Mode" ;
    SetCursorPosition(27, 24);
    SetColor(3);
    std::cout << "Normal Mode" ;
    SetCursorPosition(27, 26);
    cout<<"                                          ";
    SetCursorPosition(27, 26);
    std::cout << "Hard   Mode" ;
    SetCursorPosition(27, 28);
    std::cout << "Purgatory!!" ;
    SetCursorPosition(0, 31);

    /*上下方向键选择模块*/
    int ch;//记录键入值
    key = 1;//记录选中项，初始选择第一个
    bool flag = false;//记录是否键入Enter键标记，初始置为否
    while ((ch = getch()))
    {
        switch (ch)//检测输入键
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
        case 72://UP上方向键
            if (key > 1)//当此时选中项为第一项时，UP上方向键无效
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22);//给待选中项设置背景色
                    SetBackColor();
                    std::cout << "Easy   Mode" ;

                    SetCursorPosition(27, 24);//将已选中项取消我背景色
                    SetColor(3);
                    std::cout << "Normal Mode" ;

                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "Normal Mode" ;

                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "Hard   Mode" ;

                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "Hard   Mode" ;

                    SetCursorPosition(27, 28);
                    SetColor(3);
                    std::cout << "Purgatory!!" ;

                    --key;
                    break;
                }
            }
            break;

        case 80://DOWN下方向键
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "Normal Mode" ;
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    std::cout << "Easy   Mode" ;

                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "Hard   Mode" ;
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    std::cout << "Normal Mode" ;

                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    std::cout << "Purgatory!!" ;
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "Hard   Mode" ;

                    ++key;
                    break;
                }
            }
            break;

        case 13://Enter回车键
            flag = true;
            break;
        default://无效按键
            break;
        }
        if (flag)
            break;//输入Enter回车键确认，退出检查输入循环

        SetCursorPosition(0, 31);//将光标置于左下角，避免关标闪烁影响游戏体验
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
}
int GameController::PlayGame()//游戏二级循环
{
    HideCursor();
    Player BlackPlayer(BLACK);//创建Player类，并使用默认构造方法，生成黑子选手
    Player WhitePlayer(WHITE);
    while(true)
    {

    }
}

void GameController::Game()//游戏一级循环
{
    Start();//开始界面
    while (true)//游戏可视为一个死循环，直到退出游戏时循环结束
    {
        SelectPlayer();//选择界面
        //PlayGame();
    }
}

