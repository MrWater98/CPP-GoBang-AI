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
void copyArray(char cloneChessboard[15][15],char temp[15][15]);
void SetColor(int colorID);//Set the color
class WinRandom//Copy from internet, to generate a real random number
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


#endif // TOOLS_H
