#include <windows.h>
#include "DEVCAPS1.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = (HCURSOR)LoadCursorW(NULL, IDC_ARROW);
    wc.hIcon            = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = TEXT("Test");
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Error"), TEXT("ERROR"), MB_ICONERROR);
    }

    hwnd = CreateWindowW(TEXT("Test"), TEXT("Test"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxChar, cyChar, cxCaps;
    int     nData;
    TCHAR   szBuffer[10];
    HDC     hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;
    int i;

    switch(uMsg)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);
        cxChar  = tm.tmAveCharWidth;
        cyChar  = tm.tmHeight + tm.tmInternalLeading;
        cxCaps  = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
        ReleaseDC(hwnd, hdc);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        for (i = 0; i < DevCapsNumber; ++i)
        {
            //±êÌâ
            TextOut(hdc, 0, cyChar * i, devcaps[i].szLabel, lstrlen(devcaps[i].szLabel));
            //ÃèÊö
            TextOut(hdc, cxCaps * 14, cyChar * i, devcaps[i].szDesc, lstrlen(devcaps[i].szDesc));
            SetTextAlign(hdc, TA_RIGHT);
            TextOut(hdc, cxCaps * 14 + cxChar * 35, cyChar * i, szBuffer , wsprintf(szBuffer, TEXT("%5d"), GetDeviceCaps(hdc, devcaps[i].INDEX)));
            SetTextAlign(hdc, TA_LEFT);
        }
        EndPaint(hwnd, &ps);
        break;
    case WM_NCPAINT:
        hdc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
