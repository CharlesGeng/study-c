#include <windows.h>

#define     RED     0
#define     GREEN   0
#define     BLUE    0


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //TODO: Application name
	TCHAR       *szAppName  = TEXT("Colors1");
    //TODO: Widow's title
	TCHAR       *szTitle    = TEXT("Colors1");
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

void PaintRectangle(HWND hwnd, RECT rectColor, int r, int g, int b)
{
    HDC     hdc;
    HBRUSH  brush;

    hdc = GetDC(hwnd);
    brush = CreateSolidBrush(RGB(r, g, b));
    FillRect(hdc, &rectColor, brush);
    DeleteObject(brush);
    ReleaseDC(hwnd, hdc);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND     hwndScrollBar[3];
    static RECT     rectColor;
    static int      cxClient, cyClient;
    static int      r, g, b;

	HDC				hdc;
	PAINTSTRUCT		ps;
    SCROLLINFO      si;
    int             i;
    TCHAR           szBuffer[4];
    int             nCurrentPos, nNewPos;
    HBRUSH          brush;

	switch(uMsg)
	{
    case WM_CREATE:
        {
            for (i = 0; i < 3; ++i )
            {
                //Create Scrollbar
                hwndScrollBar[i] = CreateWindow(TEXT("scrollbar"), TEXT(""), WS_CHILD | WS_VISIBLE | SBS_VERT |WS_TABSTOP, 20 * i, 0, 20, 200, hwnd, (HMENU)i, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            }
            break;
        }
    case WM_VSCROLL:
        {
            si.cbSize   = sizeof(SCROLLINFO);
            si.fMask    = SIF_ALL;
            GetScrollInfo((HWND)lParam, SB_CTL, &si);
            nCurrentPos = si.nPos;
            nNewPos     = si.nPos;

            switch(LOWORD(wParam))
            {
                case SB_LINEUP:     nNewPos--; break;
                case SB_LINEDOWN:   nNewPos++; break;
                case SB_TOP:        nNewPos = 0; break;
                case SB_BOTTOM:     nNewPos = 255; break;
                case SB_PAGEUP:     nNewPos -= 16; break;
                case SB_PAGEDOWN:   nNewPos += 16; break;
                case SB_THUMBTRACK: nNewPos = HIWORD(wParam); break;
                default:
                    break;
            }

            if (nCurrentPos != nNewPos)
            {
                nNewPos = max(0, nNewPos);
                nNewPos = min(si.nMax, nNewPos);
                si.fMask = SIF_POS;
                si.nPos = nNewPos;
                SetScrollInfo((HWND)lParam, SB_CTL, &si, TRUE);

                if ((HWND)lParam == hwndScrollBar[0])
                {
                    r = nNewPos;
                }
                else if ((HWND)lParam == hwndScrollBar[1])
                {
                    g = nNewPos;
                }
                else if ((HWND)lParam == hwndScrollBar[2])
                {
                    b = nNewPos;
                }
                PaintRectangle(hwnd, rectColor, r, g, b);
           }
            break;
        }
    case WM_SIZE:
        {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            rectColor.left  = cxClient / 2;
            rectColor.right = cxClient;
            rectColor.top   = 0; 
            rectColor.bottom= cyClient;

            for (i = 0; i < 3; ++i)
            {
                hdc = GetDC(hwnd);
                TextOut(hdc, (i+1) * cxClient / 8, 0, szBuffer, wsprintf(szBuffer, TEXT("%s"), TEXT("red")));
                TextOut(hdc, (i+1) * cxClient / 8, 19 * cyClient / 20, szBuffer, wsprintf(szBuffer, TEXT("%d"), r));
                ReleaseDC(hwnd, hdc);

                //Set Scroll range
                SetScrollRange(hwndScrollBar[i], SB_CTL, 0, 255, TRUE);
                MoveWindow(hwndScrollBar[i], (i * 2 + 1) * cxClient / 14, cyClient / 20, cxClient / 14, cyClient * 18 / 20, TRUE);
            }
            PaintRectangle(hwnd, rectColor, r, g, b);
            break;
        }
    //case WM_SETFOCUS:
    //    SetFocus(hwndScrollBar[0]);
    //    break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
