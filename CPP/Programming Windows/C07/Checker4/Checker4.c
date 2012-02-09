#include <windows.h>

#define ROWCOUNT        2 
#define COLUMNCOUNT     2

//Used in child window's attribute
#define FOCUSBIT        1   //The child window has the focus
#define CHECKBIT        0   //The child window has been checked

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild(HWND, UINT, WPARAM, LPARAM);

int     iFocus = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR *szAppName  = TEXT("Checker4");
    static TCHAR *szTitle    = TEXT("Checker4 Mouse hit");

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
    static int          xFocus, yFocus;
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
    case WM_SETFOCUS:
        {
            SetFocus(GetDlgItem(hwnd, iFocus));
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
    case WM_KEYDOWN:
        {
            x = iFocus & 0xFF;
            y = iFocus >> 8;

            switch(wParam)
            {
            case VK_UP:
                {
                    --y; 
                    break;
                }
            case VK_DOWN:
                {
                    ++y;
                    break;
                }
            case VK_LEFT:
                {
                    --x;
                    break;
                }
            case VK_RIGHT:
                {
                    ++x;
                    break;
                }
            case VK_HOME:
                {
                    x = 0;
                    y = 0;
                    break;
                }
            case VK_END:
                {
                    x = COLUMNCOUNT - 1;
                    y = ROWCOUNT - 1;
                    break;
                }
            default:
                return 0;
            }
            x = (x + COLUMNCOUNT) % COLUMNCOUNT;
            y = (y + ROWCOUNT) % ROWCOUNT;

            iFocus = y << 8 | x;
            SetFocus(GetDlgItem(hwnd, iFocus));
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
    int      cFocusLeft, cFocusRight, cFocusTop, cFocusBottom;
    PAINTSTRUCT     ps;
    HDC             hdc;
    RECT            rect;

    switch(uMsg)
    {
    case WM_KEYDOWN:
        {
            if (wParam != VK_SPACE && wParam != VK_RETURN)
            {
                SendMessage(GetParent(hwnd), uMsg, wParam, lParam);
                return 0;
            }
        }
    case WM_LBUTTONDOWN:
        {
            SetWindowLong(hwnd, CHECKBIT, 1 ^ GetWindowLong(hwnd, CHECKBIT));
            SetFocus(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_CREATE:
        {
            SetWindowLong(hwnd, 0, 0);
            break;
        }
    case WM_SETFOCUS:
        {
            iFocus = GetWindowLong (hwnd, GWL_ID);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_KILLFOCUS:
        {
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);
            Rectangle(hdc, 0, 0, rect.right, rect.bottom);
            cFocusLeft      = rect.right / 4;
            cFocusRight     = rect.right * 3 / 4;
            cFocusTop       = rect.bottom / 4;
            cFocusBottom    = rect.bottom * 3 / 4;

            //Draw focus rectangle
            if (hwnd == GetFocus())
            {
                SelectObject(hdc, GetStockObject(NULL_BRUSH));
                SelectObject(hdc, CreatePen(PS_DASH, 0, RGB(0x0, 0x0, 0x0)));
                Rectangle(hdc, cFocusLeft, cFocusTop, cFocusRight, cFocusBottom);
                DeleteObject(SelectObject(hdc, GetStockObject(BLACK_PEN)));
            }

            //Draw cross lines
            if (GetWindowLong(hwnd, CHECKBIT))
            {
                MoveToEx(hdc, 0, 0, NULL);
                LineTo(hdc, rect.right, rect.bottom);
                MoveToEx(hdc, rect.right, 0, NULL);
                LineTo(hdc, 0, rect.bottom);
            }

            EndPaint(hwnd, &ps);
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