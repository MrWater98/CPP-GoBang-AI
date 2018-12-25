#ifndef TOOLS_H
#define TOOLS_H
#include<iostream>
#include<assert.h>
#include<windows.h>
#include <string>
#include <chrono>
#include <windows.h>
#include <wincrypt.h>
using namespace std;
void SetWindowSize(int cols, int lines);
void SetCursorPosition(const int x, const int y);
void SetColor(int colorID);
void SetBackColor();
void HideCursor();
void SetCursorPos(pair<short,short> pos);
float getTotalScore(pair<short,short> p);
float getLineScore(pair<short,short> p,pair<short,short> offset);
void copyArray(char cloneChessboard[15][15],char temp[15][15]);
void SetColor(int colorID);//ÉèÖÃÎÄ±¾ÑÕÉ«
class WinRandom
{
    HCRYPTPROV handle;
public:
    WinRandom()
    {
        handle = NULL;
        CryptAcquireContext(
            (HCRYPTPROV*)&handle,NULL,NULL,
            PROV_RSA_FULL,0
        );
    }
    ~WinRandom()
    {
        if (handle != NULL)
            CryptReleaseContext(handle, 0);
    }
    bool randBuf(void *dest, int len)
    {
        if (handle == NULL)
            return false;
        return CryptGenRandom(handle, len, (BYTE*)dest);
    }
#   define _(func, typ) \
    typ func() { \
        typ ret = 0; \
        assert(randBuf((void *)&ret, sizeof(ret))); \
        return ret; \
    }
    _(randInt, int)
    _(randLong, long long)
    _(randUnsigned, unsigned)
    _(randUnsignedLong, unsigned long long)
    _(randShort, short)
    _(randUnsignedShort, unsigned short)
    _(randChar, char)
    _(randUnsignedChar, unsigned char)
    _(randSignedChar, signed char)
};
class Timer
{
public:

    explicit Timer()
    {
        _name = "Time elapsed:";
        restart();
    }

    explicit Timer(const std::string &name)
    {
        _name = name + ":";
        restart();
    }

    /**
    * 启动计时
    */
    inline void restart()
    {
        _start_time = std::chrono::steady_clock::now();
    }

    /**
    * 结束计时
    * @return 返回ms数
    */
    inline double elapsed(bool restart = false)
    {
        _end_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = _end_time-_start_time;
        if(restart)
            this->restart();
        return diff.count()*1000;
    }

    /**
     * 打印时间并重启计时器
     * @param tip 提示
     */
    void rlog(const std::string &tip)
    {
        log(true,tip,true,false);
    }

    /**
    * 打印时间
    * @param reset 输出之后是否重启计时器，true重启，false不重启
    * @param unit_ms true是ms，false是s
    * @param tip 输出提示
    * @param kill 输出之后是否退出程序，true退出，false不退出
    */
    void log(bool reset = false, const std::string &tip = "",
             bool unit_ms = true, bool kill = false
            )
    {
        if (unit_ms)
        {
            if (tip.length() > 0)
                std::cout << tip+":" << elapsed() << "ms" << std::endl;
            else
                std::cout << _name << elapsed() << "ms" << std::endl;
        }
        else
        {
            if (tip.length() > 0)
                std::cout << tip+":" << elapsed() / 1000.0 << "s" << std::endl;
            else
                std::cout << _name << elapsed() / 1000.0 << "s" << std::endl;
        }

        if (reset)
            this->restart();

        if (kill)
            exit(5);
    }


private:
    std::chrono::steady_clock::time_point _start_time;
    std::chrono::steady_clock::time_point _end_time;
    std::string _name;
};

#endif // TOOLS_H
