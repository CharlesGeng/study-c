#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName  = TEXT("KeyView");
    TCHAR       *szTitle    = TEXT("View Keys");
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
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

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
    //char width, char height
    static int cxChar, cyChar;
    //Client area width and height
    static int cxClient, cyClient;
    //Used for save keystroke and char messages
    static PMSG pmsg;
    static int  cLineIndex;
    static RECT rectScroll;
    static int cyClientMax, cMaxLines;

    HDC         hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC  tm;
    int         i, iType;
    TCHAR       szBuffer[128], szKeyName[32];

    static TCHAR *szTitle       = TEXT("Message        Key      Char      Repeat Scan Ext ALT Prev Tran");
    static TCHAR *szUndLine     = TEXT("_______        ___      ____      ______ ____ ___ ___ ____ ____");
    static TCHAR *szMessage[]   = {TEXT("WM_KEYDOWN"), TEXT("WM_KEYUP"), TEXT("WM_CHAR"),
        TEXT("WM_DEADCHAR"), TEXT("WM_SYSKEYDOWN"), TEXT("WM_SYSKEYUP"),
        TEXT("WM_SYSCHAR"), TEXT("WM_SYSDEADCHAR")};
    static TCHAR * szFormat[2] = {TEXT ("%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
        TEXT ("%-13s            0x%04X%1s%c %6u %4d %3s %3s %4s %4s") } ;

    static TCHAR * szYes  = TEXT ("Yes") ;
    static TCHAR * szNo   = TEXT ("No") ;
    static TCHAR * szDown = TEXT ("Down") ;
    static TCHAR * szUp   = TEXT ("Up") ;



    switch(uMsg)
    {
    case WM_CREATE:
    case WM_DISPLAYCHANGE:
        {
            hdc = GetDC(hwnd);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hwnd, hdc);

            //Allocate memory space
            cyClientMax = GetSystemMetrics(SM_CYMAXIMIZED);
            cMaxLines   = cyClientMax / cyChar;
            if (pmsg != NULL)
            {
                free(pmsg);
            }
            pmsg = malloc(cMaxLines * sizeof(MSG));

            cLineIndex = 0;
            break;
        }
    case WM_SIZE:
        {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);

            rectScroll.top      = cyChar;
            rectScroll.left     = 0;
            rectScroll.bottom   = cyClient / cyChar * cyChar;
            rectScroll.right    = cxClient;

            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_SYSCHAR:
    case WM_SYSDEADCHAR:
    case WM_KEYUP:
    case WM_KEYDOWN:
    case WM_CHAR:
    case WM_DEADCHAR:
        {
            for (i = cMaxLines; i > 0; --i)
            {
                pmsg[i] = pmsg[i - 1];
            }

            cLineIndex = min(cMaxLines, cLineIndex + 1);
            pmsg[0].message    = uMsg;
            pmsg[0].hwnd       = hwnd;
            pmsg[0].wParam     = wParam;
            pmsg[0].lParam     = lParam;
            ScrollWindow(hwnd, 0, -cyChar, &rectScroll, &rectScroll);
            break;
        }
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
        SetBkMode(hdc, TRANSPARENT);

        //Show Title
        TextOut(hdc, 0, 0, szTitle, lstrlen(szTitle));
        TextOut(hdc, 0, 0, szUndLine, lstrlen(szUndLine));

        //Show Messages
        for (i = 0 ; i < min (cLineIndex, cyClient / cyChar - 1) ; i++)
        {
            iType = pmsg[i].message == WM_CHAR ||
                pmsg[i].message == WM_SYSCHAR ||
                pmsg[i].message == WM_DEADCHAR ||
                pmsg[i].message == WM_SYSDEADCHAR ;

            GetKeyNameText (pmsg[i].lParam, szKeyName, 
                sizeof (szKeyName) / sizeof (TCHAR)) ;

            TextOut (hdc, 0, (cyClient / cyChar - 1 - i) * cyChar, szBuffer,
                wsprintf (szBuffer, szFormat [iType],
                szMessage [pmsg[i].message - WM_KEYFIRST],                   
                pmsg[i].wParam,
                (PTSTR) (iType ? TEXT (" ") : szKeyName),
                (TCHAR) (iType ? pmsg[i].wParam : ' '),
                LOWORD (pmsg[i].lParam),
                HIWORD (pmsg[i].lParam) & 0xFF,
                0x01000000 & pmsg[i].lParam ? szYes  : szNo,
                0x20000000 & pmsg[i].lParam ? szYes  : szNo,
                0x40000000 & pmsg[i].lParam ? szDown : szUp,
                0x80000000 & pmsg[i].lParam ? szUp   : szDown)) ;
        }
        EndPaint(hwnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
