#pragma once


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>


class CProgress
{
public:
    CProgress();
    ~CProgress();

    bool Open(HWND hOwner = NULL, const TCHAR* header = NULL);
    bool IsCancelled() const;
    void SetPercent(unsigned percent) const;
    void Close();

private:
    static const TCHAR cClassName[];
    static const TCHAR cDefaultHeader[];
    static const int cBackgroundColor;
    static const int cPBwidth;
    static const int cPBheight;
    static const int cBTNwidth;
    static const int cBTNheight;

    static volatile LONG RefCount;
    static HINSTANCE HInst;

    static DWORD threadFunc(LPVOID data);
    static LRESULT APIENTRY wndProc(HWND hwnd, UINT umsg,
            WPARAM wparam, LPARAM lparam);

    // Disable copy construction and operator=
    CProgress(const CProgress&);
    const CProgress& operator=(const CProgress&);

    int thread();
    bool createProgressWindow();
    RECT adjustSizeAndPos(int width, int height);

    volatile bool _isInit;
    HWND _hOwner;
    TCHAR _header[128];
    HANDLE _hThread;
    HANDLE _hActiveState;
    HWND _hwnd;
    HWND _hPBar;
    HWND _hBtn;
};
