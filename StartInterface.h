#ifndef STRATINTERFACE_H
#define STARTINTERFACE_H

#include <deque>
#include <vector>
#include "point.h"

class StartInterface
{
public:
    StartInterface() : speed(35) {
        startsnake.emplace_back(Point(0,14));
        startsnake.emplace_back(Point(1,14));
        startsnake.emplace_back(Point(2,15));
        startsnake.emplace_back(Point(3,16));
        startsnake.emplace_back(Point(4,17));
        startsnake.emplace_back(Point(5,18));
        startsnake.emplace_back(Point(6,17));
        startsnake.emplace_back(Point(7,16));
        startsnake.emplace_back(Point(8,15));
        startsnake.emplace_back(Point(9,14));

        textsnake.emplace_back(Point(-26, 14));//F
        textsnake.emplace_back(Point(-25, 14));
        textsnake.emplace_back(Point(-27, 14));
        textsnake.emplace_back(Point(-27, 15));
        textsnake.emplace_back(Point(-27, 16));
        textsnake.emplace_back(Point(-26, 16));
        textsnake.emplace_back(Point(-27, 17));
        textsnake.emplace_back(Point(-25, 16));
        textsnake.emplace_back(Point(-27, 18));

        textsnake.emplace_back(Point(-22, 14));//S
        textsnake.emplace_back(Point(-21, 14));
        textsnake.emplace_back(Point(-23, 15));
        textsnake.emplace_back(Point(-22, 16));
        textsnake.emplace_back(Point(-21, 17));
        textsnake.emplace_back(Point(-23, 18));
        textsnake.emplace_back(Point(-22, 18));

        textsnake.emplace_back(Point(-19, 14));//T
        textsnake.emplace_back(Point(-18, 14));
        textsnake.emplace_back(Point(-17, 14));
        textsnake.emplace_back(Point(-16, 14));
        textsnake.emplace_back(Point(-15, 14));
        textsnake.emplace_back(Point(-17, 14));
        textsnake.emplace_back(Point(-17, 15));
        textsnake.emplace_back(Point(-17, 16));
        textsnake.emplace_back(Point(-17, 17));
        textsnake.emplace_back(Point(-17, 18));

        textsnake.emplace_back(Point(-10, 18));
        textsnake.emplace_back(Point(-10, 14));
        textsnake.emplace_back(Point(-11, 18));
        textsnake.emplace_back(Point(-11, 14));
        textsnake.emplace_back(Point(-12, 18));
        textsnake.emplace_back(Point(-12, 14));
        textsnake.emplace_back(Point(-13, 18));
        textsnake.emplace_back(Point(-13, 14));
        textsnake.emplace_back(Point(-13, 15));
        textsnake.emplace_back(Point(-13, 16));
        textsnake.emplace_back(Point(-13, 17));
        textsnake.emplace_back(Point(-9, 14));
        textsnake.emplace_back(Point(-9, 15));
        textsnake.emplace_back(Point(-9, 16));
        textsnake.emplace_back(Point(-9, 17));
        textsnake.emplace_back(Point(-9, 18));

        textsnake.emplace_back(Point(-7, 14));//N
        textsnake.emplace_back(Point(-7, 15));
        textsnake.emplace_back(Point(-7, 16));
        textsnake.emplace_back(Point(-7, 17));
        textsnake.emplace_back(Point(-7, 18));
        textsnake.emplace_back(Point(-6, 15));
        textsnake.emplace_back(Point(-5, 16));
        textsnake.emplace_back(Point(-4, 17));
        textsnake.emplace_back(Point(-3, 14));
        textsnake.emplace_back(Point(-3, 15));
        textsnake.emplace_back(Point(-3, 16));
        textsnake.emplace_back(Point(-3, 17));
        textsnake.emplace_back(Point(-3, 18));

        textsnake.emplace_back(Point(-1, 14));//E
        textsnake.emplace_back(Point(-1, 15));
        textsnake.emplace_back(Point(-1, 16));
        textsnake.emplace_back(Point(-1, 17));
        textsnake.emplace_back(Point(-1, 18));
        textsnake.emplace_back(Point(0, 14));
        textsnake.emplace_back(Point(0, 16));
        textsnake.emplace_back(Point(0, 18));
        textsnake.emplace_back(Point(1, 14));
        textsnake.emplace_back(Point(1, 16));
        textsnake.emplace_back(Point(1, 18));
        textsnake.emplace_back(Point(2, 14));
        textsnake.emplace_back(Point(2, 16));
        textsnake.emplace_back(Point(2, 18));
    }
    void PrintFirst();
    void PrintSecond();
    void PrintThird();
    void PrintText();
    void ClearText();
    void Action();
private:
    std::deque<Point> startsnake;//开始动画中的蛇
    std::vector<Point> textsnake;//开始动画中的文字
    int speed;//动画的速度
};
#endif // STRATINTERFACE_H
