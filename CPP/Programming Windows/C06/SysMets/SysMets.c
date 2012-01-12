#include <windows.h>
#include "SysMets.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName  = TEXT("SysMets");
    TCHAR       *szTitle    = TEXT("Show System Metrics");
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
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
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
    static int cxFont, cyFont, cxCaps;
    static int cxClient, cyClient, iMaxWidth;
    int iVertPos, iHorzPos;
    int iPaintBgn, iPaintEnd;
    int x, y;
    TEXTMETRIC tm;
    HDC     hdc;
    PAINTSTRUCT ps;
    TCHAR   szBuffer[16];
    SCROLLINFO si;
    int i;

    switch(uMsg)
    {
    case WM_CREATE:
        {
            //Get Font information of width and height
            hdc = GetDC(hwnd);

            GetTextMetrics(hdc,&tm);
            cxFont  = tm.tmAveCharWidth;
            cyFont  = tm.tmHeight + tm.tmExternalLeading;
            cxCaps  = (tm.tmPitchAndFamily & TMPF_FIXED_PITCH ? 3 : 2)  * cxFont / 2;

            iMaxWidth = 22 * cxCaps + 40 * cxCaps;
            ReleaseDC(hwnd, hdc);
            return 0;
        }
    case WM_SIZE:
        {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);

            //Set vertical scroll bar
            si.cbSize   = sizeof(si);
            si.fMask    = SIF_RANGE | SIF_PAGE;
            si.nMin     = 0;
            si.nMax     = METRICSCOUNT;
            si.nPage    = cyClient / cyFont;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            //Set horizontal scroll bar
            si.cbSize   = sizeof(si);
            si.fMask    = SIF_RANGE | SIF_PAGE;
            si.nMin     = 0;
            si.nMax     = 2 + iMaxWidth / cxFont;
            si.nPage    = cxClient / cxFont;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
            return 0;
        }
    case WM_KEYDOWN:
        {
            switch (wParam)
            {
            case VK_DOWN:
                uMsg    = WM_VSCROLL;
                wParam  = SB_LINEDOWN;
                break;
            case VK_UP:
                uMsg    = WM_VSCROLL;
                wParam  = SB_LINEUP;
                break;
            case VK_LEFT:
                uMsg    = WM_HSCROLL;
                wParam  = SB_LINELEFT;
                break;
            case VK_RIGHT:
                uMsg    = WM_HSCROLL;
                wParam  = SB_LINERIGHT;
                break;
            case VK_PRIOR:
                uMsg    = WM_VSCROLL;
                wParam  = SB_PAGEUP;
                break;
            case VK_NEXT:
                uMsg    = WM_VSCROLL;
                wParam  = SB_PAGEDOWN;
                break;
            case VK_HOME:
                uMsg    = WM_VSCROLL;
                wParam  = SB_TOP;
                break;
            case VK_END:
                uMsg    = WM_VSCROLL;
                wParam  = SB_BOTTOM;
                break;
            default:
                return 0;
            }
            SendMessage(hwnd, uMsg, wParam, 0);
            return 0;
        }
    case WM_VSCROLL:
        {
            si.cbSize   = sizeof(si);
            si.fMask    = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);
            iVertPos = si.nPos;

            switch(LOWORD(wParam))
            {
                //Scrolls to the upper left.
            case SB_TOP:
                si.nPos = si.nMin;
                break;
                //Scrolls to the lower right.
            case SB_BOTTOM:
                si.nPos = si.nMax;
                break;
                //Scrolls one line down.
            case SB_LINEDOWN:
                si.nPos++;
                break;
                //Scrolls one line up.
            case SB_LINEUP:
                si.nPos--;
                break;
                //Scrolls one page down.
            case SB_PAGEDOWN:
                si.nPos += si.nPage;
                break;
                //Scrolls one page up.
            case SB_PAGEUP:
                si.nPos -= si.nPage;
                break;
                //The user is dragging the scroll box. This message is sent repeatedly until the user releases the mouse button. The high-order word indicates the position that the scroll box has been dragged to.
            case SB_THUMBTRACK:
                si.nPos = si.nTrackPos;
                break;
            default:
                break;
            }
            //Set new position of vertical scrollbar
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            //Check the vertical scrollbar position, if the position was changed, repaint the window
            GetScrollInfo(hwnd, SB_VERT, &si);
            if (iVertPos != si.nPos)
            {
                ScrollWindow(hwnd, 0, cyFont * (iVertPos- si.nPos), NULL, NULL);
                UpdateWindow(hwnd);
            }
            return 0;
        }
    case WM_HSCROLL:
        {
            si.cbSize   = sizeof(si);
            si.fMask    = SIF_ALL;
            GetScrollInfo(hwnd, SB_HORZ, &si);
            iHorzPos    = si.nPos;

            switch(wParam)
            {
                //Scrolls to the upper left.
            case SB_LEFT:
                si.nPos = si.nMin;
                break;
                // Scrolls to the lower right.
            case SB_RIGHT:
                si.nPos = si.nMax;
                break;
                //Scrolls left by one unit.
            case SB_LINELEFT:
                si.nPos--;
                break;
                //Scrolls right by one unit.
            case SB_LINERIGHT:
                si.nPos++;
                break;
                //Scrolls left by the width of the window.
            case SB_PAGELEFT:
                si.nPos -= si.nPage;
                break;
                //Scrolls right by the width of the window.
            case SB_PAGERIGHT:
                si.nPos += si.nPage;
                break;
                //The user is dragging the scroll box. This message is sent repeatedly until the user releases the mouse button. The high-order word indicates the position that the scroll box has been dragged to.
            case SB_THUMBTRACK:
                si.nPos = si.nTrackPos;
                break;
            default:
                break;
            }
            si.cbSize = sizeof(si);
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

            GetScrollInfo(hwnd, SB_HORZ, &si);
            if (iHorzPos != si.nPos)
            {
                ScrollWindow(hwnd, cxFont * (iHorzPos - si.nPos), 0, NULL, NULL);
                UpdateWindow(hwnd);
            }
            return 0;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);

            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);
            iVertPos = si.nPos;

            GetScrollInfo(hwnd, SB_HORZ, &si);
            iHorzPos = si.nPos;

            iPaintBgn = max(0, iVertPos + ps.rcPaint.top / cyFont);
            iPaintEnd = min(METRICSCOUNT -1, iVertPos + ps.rcPaint.bottom / cyFont);

            for(i = iPaintBgn; i <= iPaintEnd; ++i)
            {
                x = (1 - iHorzPos) * cxFont;
                y = (i - iVertPos) * cyFont;
                TextOut(hdc, x, y, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
                TextOut(hdc, x + 22*cxCaps, y, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));
                SetTextAlign(hdc, TA_RIGHT);
                TextOut(hdc, x + 48*cxCaps, y, szBuffer, wsprintf(szBuffer,TEXT("%5d"), GetSystemMetrics(sysmetrics[i].iIndex)));
                SetTextAlign(hdc, TA_LEFT);
            }
            EndPaint(hwnd, &ps);
            return 0;
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
