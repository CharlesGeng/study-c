#include <windows.h>

#define ROWCOUNT        8
#define COLUMNCOUNT     8

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR *szAppName  = TEXT("Checker3");
    static TCHAR *szTitle    = TEXT("Checker3 Mouse hit");

    MSG         msg;
    WNDCLASS    wc;
    HWND        hwnd;

    //Register Parent window class
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = GetStockObject(WHITE_BRUSH);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Register window class error!"), TEXT("ERROR"), MB_ICONERROR);
        return 0;
    }

    //Register child window class
    wc.cbWndExtra       = sizeof(long);
    wc.hIcon            = NULL;
    wc.lpfnWndProc      = WndProcChild;
    wc.lpszClassName    = TEXT("Checker3_Child");
    RegisterClass(&wc);

    hwnd = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND         hwndChild[ROWCOUNT][COLUMNCOUNT];
    int                 x, y, cxGrid, cyGrid;
    switch(uMsg)
    {
    case WM_CREATE:
        {
            for(y = 0; y < COLUMNCOUNT; ++y)
            {
                for (x = 0; x < ROWCOUNT; ++x)
                {
                    hwndChild[x][y] = CreateWindow(TEXT("Checker3_Child"), NULL, WS_CHILDWINDOW | WS_VISIBLE,
                        0, 0, 0, 0, hwnd, (HMENU)(y << 8 | x), (HINSTANCE)GetWindowWord(hwnd, GWL_HINSTANCE), NULL);
                }
            }
            break;
        }
    case WM_SIZE:
        {
            cxGrid = LOWORD(lParam) / COLUMNCOUNT;
            cyGrid = HIWORD(lParam) / ROWCOUNT;

            for(y = 0; y < COLUMNCOUNT; ++y)
            {
                for (x = 0; x < ROWCOUNT; ++x)
                {
                    MoveWindow(hwndChild[x][y], x * cxGrid, y * cyGrid, cxGrid, cyGrid, TRUE);
                }
            }
            break;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcChild(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT     ps;
    HDC             hdc;
    RECT            rect;

    switch(uMsg)
    {
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);
            Rectangle(hdc, 0, 0, rect.right, rect.bottom);
            if (GetWindowLong(hwnd, 0))
            {
                MoveToEx(hdc, 0, 0, NULL);
                LineTo(hdc, rect.right, rect.bottom);
                MoveToEx(hdc, rect.right, 0, NULL);
                LineTo(hdc, 0, rect.bottom);
            }
            EndPaint(hwnd, &ps);
            break;
        }
    case WM_LBUTTONDOWN:
        {
            SetWindowLong(hwnd, 0, 1 ^ GetWindowLong(hwnd, 0));
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}