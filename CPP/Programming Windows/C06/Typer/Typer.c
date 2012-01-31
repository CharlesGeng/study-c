#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName  = TEXT("Typer");
    TCHAR       *szTitle    = TEXT("Typer");
    WNDCLASS    wc;
    HWND        hwnd;
    MSG         msg;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = (HCURSOR)LoadCursorW(NULL, IDC_ARROW);
    wc.hIcon            = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Error"), TEXT("Register Window Class Error"), MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName, szTitle,
        WS_OVERLAPPEDWINDOW,
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
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxChar, cyChar;
    static int xCaret, yCaret;
    static int cxClient, cyClient;
    static int cxBuffer, cyBuffer;
    static DWORD dwCharSet = DEFAULT_CHARSET;
    static TCHAR    *szBuffer;

    HDC         hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC  tm;
    int         x, y;


    switch(uMsg)
    {
    case WM_INPUTLANGCHANGE:
    case WM_CREATE:
        if(uMsg == WM_INPUTLANGCHANGE)
        {
            dwCharSet = wParam ;
        }

        hdc = GetDC (hwnd) ;
        SelectObject (hdc, CreateFont (0, 0, 0, 0, 0, 0, 0, 0,
            dwCharSet, 0, 0, 0, FIXED_PITCH, NULL)) ;

        GetTextMetrics (hdc, &tm) ;
        cxChar = tm.tmAveCharWidth ;
        cyChar = tm.tmHeight ;

        DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;
        ReleaseDC (hwnd, hdc) ;

        for (x = 0; x < cxBuffer; ++x)
            for(y=0; y < cyBuffer; ++y)
                szBuffer[x][y] = ' ';
        xCaret = 0;
        yCaret = 0;
        if (hwnd == GetFocus())
        {
            SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        cxBuffer = cxClient / cxChar;
        cyBuffer = cyClient / cyChar;

        if (szBuffer != NULL)
        {
            free(szBuffer);
        }
        szBuffer = (TCHAR *)malloc(cxBuffer * cyBuffer * sizeof(TCHAR));

        xCaret = 0;
        yCaret = 0;
        if (hwnd == GetFocus())
        {
            SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_SETFOCUS:
        {
            CreateCaret (hwnd, NULL, cxChar, cyChar) ;
            SetCaretPos (xCaret * cxChar, yCaret * cyChar) ;
            ShowCaret (hwnd) ;
            return 0 ;
        }
    case WM_KILLFOCUS:
        {
            HideCaret (hwnd) ;
            DestroyCaret () ;
            return 0 ;
        }

    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    default:
        {
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
