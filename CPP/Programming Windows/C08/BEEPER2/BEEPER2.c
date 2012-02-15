#include <windows.h>

#define MAINTIMER   1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName  = TEXT("Beeper2");
    TCHAR       *szTitle    = TEXT("Time Beeper 2");
    WNDCLASS    wc;
    HWND        hWnd;
    MSG         msg;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Register WNDCLASS failed!"), TEXT("ERROR"), MB_ICONERROR);
        return 0;
    }

    hWnd = CreateWindow(szAppName, szTitle, 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static BOOL bRed;
    PAINTSTRUCT ps;
    HDC         hdc;
    RECT        rectClient;
    LOGBRUSH    logBrush;
	HBRUSH		hbrush;
    

    switch(uMsg)
    {
    case WM_CREATE:
        {
            SetTimer(hwnd, MAINTIMER, 100, TimerProc);
            bRed = TRUE;
            return 0;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rectClient);

            logBrush.lbHatch    = HS_CROSS;
            logBrush.lbStyle    = BS_SOLID;
			logBrush.lbColor	= bRed ? RGB(0xFF, 0, 0) : RGB(0, 0xFF, 0);
			hbrush				= CreateBrushIndirect(&logBrush);
			FillRect(hdc, &rectClient, hbrush);
            bRed = !bRed;
			DeleteObject(hbrush);
            EndPaint(hwnd, &ps);
            return 0;
        }
    case WM_DESTROY:
        {
            KillTimer(hwnd, MAINTIMER);
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    if (uMsg == WM_TIMER)
    {
        if (idEvent == MAINTIMER)
        {
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
}