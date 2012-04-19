#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR szCmdLine, int nCmdShow)
{
    TCHAR       szAppName[16], szCaption[64];
    MSG         msg;
    HWND        hwnd;
    WNDCLASS    wc;

    LoadString(hInstance, IDS_APPNAME, szAppName, sizeof(szAppName) / sizeof(TCHAR));
    LoadString(hInstance, IDS_CAPTION, szCaption, sizeof(szCaption) / sizeof(TCHAR));
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(hInstance, szAppName);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Register"), TEXT("adf"), MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, szCaption, WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int          nLineCount;
    static HGLOBAL      hResource;

    CHAR       *szText;
    HINSTANCE   hInstance;

    switch(msg)
    {
    case WM_CREATE:
        hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
        hResource = LoadResource(hInstance, FindResource(hInstance, TEXT("ANNABELLEE"), TEXT("TEXT")));
        szText = (CHAR *)LockResource(hResource);
        while(*szText != '\0' && *szText != '\\')
        {
            if (*szText == '\n')
                ++nLineCount;
            szText = AnsiNext(szText);
        }
        break;
    case WM_DESTROY:
        {
            FreeResource(hResource);
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}