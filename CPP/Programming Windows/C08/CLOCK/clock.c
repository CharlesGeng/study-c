#include <windows.h>
#include <math.h>

#define IDTIMER		1
#define CXWINDOW	128
#define CYWINDOW    128
#define M_PI		3.14159265358979323846


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName  = TEXT("CLOCK");
    TCHAR       *szTitle    = TEXT("CLOCK");
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

void DisplayTime(HDC hdc)
{
    int		i;
    double	x, y;
    int		xPoint, yPoint;
    SYSTEMTIME  st;

    GetLocalTime(&st);
    for (i = 0; i < 60; ++i)
    {
        x = cos(M_PI * 3 /2 + i * 2 * M_PI / 60);
        y = sin(M_PI * 3 /2  + i * 2 * M_PI / 60);
        xPoint = (int)((1 + x) * CXWINDOW / 2.0);
        yPoint = (int)((1 + y) * (CYWINDOW) / 2.0);

        // Draw big points
        if ((i % 5) == 0)
        {
            Ellipse(hdc, xPoint -2, yPoint-2, xPoint + 2, yPoint + 2);
        }
        // Draw little points
        else
        {
            Ellipse(hdc, xPoint -1, yPoint-1, xPoint + 1, yPoint + 1);
        }

        // draw second pin
        if (i == st.wSecond)
        {
            MoveToEx(hdc, CXWINDOW/2, CYWINDOW/2, NULL);
            LineTo(hdc, xPoint, yPoint);
        }
    }
    // draw minute pin
    x = cos( M_PI * 3 / 2 + st.wMinute * 2 * M_PI / 60);
    y = sin( M_PI * 3 / 2 + st.wMinute * 2 * M_PI / 60);
    xPoint = (int)((1 + x) * CXWINDOW / 2.0);
    yPoint = (int)((1 + y) * (CYWINDOW) / 2.0);
    MoveToEx(hdc, CXWINDOW/2, CYWINDOW/2, NULL);
    LineTo(hdc, xPoint, yPoint);

    // draw hour pin
    x = cos( M_PI * 3 / 2 + (st.wHour + st.wMinute / 60.0) * 2 * M_PI / 12 );
    y = sin( M_PI * 3 / 2 + (st.wHour+ st.wMinute / 60.0) * 2 * M_PI / 12 );
    xPoint = (int)((1 + x) * CXWINDOW / 2.0 );
    yPoint = (int)((1 + y) * (CYWINDOW) / 2.0 );
    MoveToEx(hdc, CXWINDOW/2, CYWINDOW/2, NULL);
    LineTo(hdc, xPoint, yPoint);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static BOOL		b24Hour, bLeadingZero;
    static int		cxClient, cyClient;
    static HBRUSH	brush;

    HDC				hdc;
    PAINTSTRUCT		ps;
    TCHAR			szBuffer[2];

    switch(uMsg)
    {
    case WM_CREATE:
        SetTimer(hwnd, IDTIMER, 1000, NULL);
        break;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        break;
    case WM_TIMER:
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        //Set up map mode
        SetMapMode(hdc, MM_ISOTROPIC);
        SetWindowExtEx(hdc, CXWINDOW, CYWINDOW, NULL);
        SetViewportExtEx(hdc, cxClient * 9 / 10, cyClient * 9 / 10, NULL);
        SetWindowOrgEx(hdc, CXWINDOW / 2, CYWINDOW / 2, NULL);
        SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);

        //Display time
        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        DisplayTime(hdc);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        KillTimer(hwnd, IDTIMER);
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
