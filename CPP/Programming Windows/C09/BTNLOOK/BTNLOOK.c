#include <windows.h>

struct
{
    int     BtnStyle;
    TCHAR   *BtnDescription;
}
Buttons[] = {
    BS_PUSHBUTTON,      TEXT("Push Buton"),
    BS_DEFPUSHBUTTON,   TEXT("BS_DEFPUSHBUTTON"),
    BS_CHECKBOX ,       TEXT("BS_CHECKBOX"),
    BS_3STATE ,         TEXT("BS_3STATE"),
    BS_AUTO3STATE ,     TEXT("BS_AUTO3STATE"),
    BS_AUTOCHECKBOX ,   TEXT("BS_AUTOCHECKBOX"),
    BS_RADIOBUTTON ,    TEXT("BS_RADIOBUTTON"),
    BS_AUTORADIOBUTTON , TEXT("BS_AUTORADIOBUTTON"),
    BS_GROUPBOX ,       TEXT("BS_GROUPBOX"),
    BS_OWNERDRAW ,      TEXT("BS_OWNERDRAW"),
};

#define BUTTONCOUNT     sizeof(Buttons) / sizeof(Buttons[0])

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    TCHAR szAppName[] = TEXT ("BTNLOOK") ;
    TCHAR szAppTitle[] = TEXT ("Buttons Look") ;
    HWND         hwnd ;
    MSG          msg ;
    WNDCLASS     wndclass ;

    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = WndProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hInstance ;
    wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = szAppName ;

    if (!RegisterClass (&wndclass))
    {
        MessageBox (NULL, TEXT ("Program requires Windows NT!"),
            szAppName, MB_ICONERROR) ;
        return 0 ;
    }

    hwnd = CreateWindow (szAppName, szAppTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL) ;

    ShowWindow (hwnd, iCmdShow) ;
    UpdateWindow (hwnd) ;

    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }
    return msg.wParam ;
}




LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND     hwndButtons[BUTTONCOUNT];
    static int      cxChar, cyChar;
    static RECT     rectClient;
    static TCHAR    *szTitle = TEXT("message            wParam          lParam");
    static TCHAR    *szUnd   = TEXT("_______            ______          ______");

    HDC         hdc ;
    PAINTSTRUCT ps ;
    int         i;
    long        data;
    TCHAR       szBuffer[50];


    switch (message)
    {
    case WM_CREATE:
        {
            // Create buttons
            data = GetDialogBaseUnits();
            cxChar = LOWORD(data);
            cyChar = HIWORD(data);
            for (i = 0; i < BUTTONCOUNT; ++i)
            {
                hwndButtons[i] = CreateWindow(TEXT("Button"), Buttons[i].BtnDescription, 
                    Buttons[i].BtnStyle | WS_VISIBLE | WS_CHILD, 
                    cxChar, i * cyChar * 2 + cyChar, cxChar * 20, cyChar * 7 / 4, hwnd, (HMENU)i, ((LPCREATESTRUCT)lParam)->hInstance, NULL); 
            }
            break;
        }
    case WM_SIZE:
        {
            rectClient.left     = 24 * cxChar;
            rectClient.right    = LOWORD(lParam);
            rectClient.top      = cyChar * 2;
            rectClient.bottom   = HIWORD(lParam);
            break;
        }
    case WM_COMMAND:
        {
            hdc = GetDC(hwnd);
            ScrollWindow(hwnd, 0, -cyChar, &rectClient, &rectClient);
            TextOut(hdc, rectClient.left + cxChar, rectClient.bottom - cyChar, szBuffer, wsprintf(szBuffer, TEXT("%s    %04X-%04X %08X"), TEXT("WM_COMMAND"),HIWORD(wParam), LOWORD(wParam), lParam));
            ValidateRect(hwnd, &rectClient);
            ReleaseDC(hwnd, hdc);
            break;
        }
    case WM_PAINT :
        {
            hdc = BeginPaint (hwnd, &ps) ;
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            SetBkMode(hdc, TRANSPARENT);
            TextOut(hdc, rectClient.left, cyChar, szTitle, lstrlen(szTitle));
            TextOut(hdc, rectClient.left, cyChar, szUnd, lstrlen(szUnd));
            EndPaint (hwnd, &ps);
            return 0 ;
        }
    case WM_DESTROY :
        {
            PostQuitMessage (0) ;
            return 0 ;
        }
    }
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}
