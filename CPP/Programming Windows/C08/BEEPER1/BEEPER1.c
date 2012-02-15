#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName = TEXT("Beeper1");
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
        return 0;
    }

    hWnd = CreateWindow(szAppName, TEXT("Beeper 1"), 
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC         hdc;
    RECT        rect;
    static LOGBRUSH    logbrush;
    static BOOL        flag;

    switch (uMsg)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 1000, NULL);
        flag = TRUE;
        logbrush.lbColor = RGB(255, 0,0);
        logbrush.lbStyle = BS_SOLID;
        break;
    case WM_TIMER:
        flag = !flag;
        logbrush.lbColor = flag ? RGB(255, 0,0) : RGB(0, 0, 255);
        logbrush.lbStyle = BS_SOLID;
        logbrush.lbHatch = NULL;
        GetClientRect(hWnd, &rect);
        MessageBeep(-1);
        InvalidateRect(hWnd, &rect ,TRUE);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, CreateBrushIndirect(&logbrush));
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}