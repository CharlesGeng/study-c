#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName  = TEXT("STOCKFONT");
    TCHAR       *szTitle    = TEXT("Stock Fonts");
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
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,
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
    static struct
    {
        int idStockFont;
        TCHAR *szStockFont;
    }
    stockfont[] = { OEM_FIXED_FONT,      TEXT ("OEM_FIXED_FONT"),
        ANSI_FIXED_FONT,     TEXT ("ANSI_FIXED_FONT"),
        ANSI_VAR_FONT,       TEXT ("ANSI_VAR_FONT"),
        SYSTEM_FONT,         TEXT ("SYSTEM_FONT"),
        DEVICE_DEFAULT_FONT, TEXT ("DEVICE_DEFAULT_FONT"),
        SYSTEM_FIXED_FONT,   TEXT ("SYSTEM_FIXED_FONT"),
        DEFAULT_GUI_FONT,    TEXT ("DEFAULT_GUI_FONT") };

    HDC         hdc;
    PAINTSTRUCT ps;
    TCHAR       szBuffer[128];
    TEXTMETRIC  tm;
    static int  iFont, iFontCount;
    TCHAR       szFace[LF_FACESIZE];
    int         xGrid, yGrid;
    int         x, y;
    SCROLLINFO  si;
    int         iCurScrollPos;

    switch (uMsg)
    {
    case WM_CREATE:
        {
            iFontCount = sizeof(stockfont) / sizeof(stockfont[0]);
            iFont = 0;
            SetScrollRange(hwnd, SB_VERT, 0, iFontCount - 1, TRUE);
            break;
        }
        //处理垂直滚动条滚动消息
    case WM_VSCROLL:
        {
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);
            iCurScrollPos = si.nPos;

            switch(LOWORD(wParam))
            {
            case SB_LINEDOWN:
            case SB_PAGEDOWN:
                iFont++;
                break;
            case SB_PAGEUP:
            case SB_LINEUP:
                iFont--;
                break;
            case SB_TOP:
                iFont = 0;
                break;
            case SB_BOTTOM:
                iFont = iFontCount -1;
                break;
            }

            iFont = max(0, iFont);
            iFont = min(iFontCount - 1, iFont);

            if (iCurScrollPos != iFont)
            {
                SetScrollPos(hwnd, SB_VERT, iFont, TRUE);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        }
    case WM_KEYDOWN:
        {
            switch (wParam)
            {
            case VK_HOME:
                SendMessage(hwnd, WM_VSCROLL, SB_TOP, 0);
                break;
            case VK_END:
                SendMessage(hwnd, WM_VSCROLL, SB_BOTTOM, 0);
                break;
            case VK_PRIOR:
            case VK_UP:
            case VK_LEFT:
                SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0);
                break;
            case VK_NEXT:
            case VK_DOWN:
            case VK_RIGHT:
                SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0);
                break;
            }
        break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            SelectObject(hdc, GetStockObject(stockfont[iFont].idStockFont));
            GetTextMetrics(hdc, &tm);
            xGrid = max(3*tm.tmAveCharWidth, 2*tm.tmMaxCharWidth);
            yGrid = tm.tmHeight + 3;
            SetBkMode(hdc, TRANSPARENT);


            //显示标题头
            GetTextFace(hdc, LF_FACESIZE, szFace);
            TextOut(hdc, 0, 0, szBuffer, wsprintf(szBuffer, TEXT(" %s: Face Name = %s, CharSet = %i"), stockfont[iFont].szStockFont, szFace, tm.tmCharSet));

            //Draw Grid
            for(x = 0; x< 17; ++x)
            {
                //Draw vertical lines
                MoveToEx(hdc, (2 + x) * xGrid, 2 * yGrid, NULL);
                LineTo(hdc, (2 + x) * xGrid, 19 * yGrid);
                //Draw horizontal lines
                MoveToEx(hdc, xGrid, (x + 3) * yGrid, NULL);
                LineTo(hdc, 18 * xGrid, (x + 3) * yGrid);
            }

            SetTextAlign(hdc, TA_TOP | TA_CENTER);
            //Show Titles & charactors
            for(x = 0; x< 16; ++x)
            {
                //Show horizontal lines
                TextOut(hdc, (5 + 2 * x) * xGrid / 2, 2 * yGrid, szBuffer, wsprintf(szBuffer, TEXT("%X-"), x));
                //Show vertical lines
                TextOut(hdc, 3 * xGrid/2 , (x + 3) * yGrid, szBuffer, wsprintf(szBuffer, TEXT("-%X"), x));
                //Show Chars
                for (y = 0; y < 16; ++y)
                {
                    TextOut(hdc, (5 + 2 * x) * xGrid / 2, (3 + y)* yGrid, szBuffer, wsprintf(szBuffer, TEXT("%c"), x * 16 + y));
                }
            }

            EndPaint(hwnd, &ps);
            break;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
