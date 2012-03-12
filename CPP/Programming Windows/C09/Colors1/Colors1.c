#include <windows.h>

#define     RED     0
#define     GREEN   0
#define     BLUE    0

TCHAR   *COLORTITLE[3] = {TEXT("RED"), TEXT("GREEN"), TEXT("BLUE")};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TCHAR       *szAppName  = TEXT("Colors1");
	TCHAR       *szTitle    = TEXT("Colors1");
	WNDCLASS    wc;
	HWND        hWnd;
	MSG         msg;

	wc.cbClsExtra       = 0;
	wc.cbWndExtra       = 0;
	wc.hbrBackground    = CreateSolidBrush(0);
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
    static HWND     hwndScrollBar[3], hwndColorTitle[3], hwndColorValue[3]; 
    static HWND     hwndLeft;
    static RECT     rcColor;
    static int      cxClient, cyClient;
    static int      cxChar, cyChar;
    static int      r, g, b;
    static COLORREF crPrim[3];
    static HBRUSH   hBrush[3];
    static HBRUSH   hBrushStatic ;

	HDC				hdc;
	PAINTSTRUCT		ps;
    SCROLLINFO      si;
    int             i;
    TCHAR           szBuffer[4];
    int             nCurrentPos, nNewPos;

	switch(uMsg)
	{
        //Create controls
    case WM_CREATE:
        {
            hwndLeft    = CreateWindow(TEXT("static"), TEXT(""), WS_CHILD | WS_VISIBLE | SS_WHITERECT, 0, 0, 0, 0, hwnd, (HMENU)9, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            //Create Scrollbar
            for (i = 0; i < 3; ++i )
            {
                hwndScrollBar[i]    = CreateWindow(TEXT("scrollbar"), TEXT(""), WS_CHILD | WS_VISIBLE | SBS_VERT | WS_TABSTOP, 20 * i, 0, 20, 200, hwnd, (HMENU)i, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
                hwndColorTitle[i]   = CreateWindow(TEXT("static"), COLORTITLE[i], WS_CHILD | WS_VISIBLE | SS_CENTER, 20 * i, 0, 20, 200, hwnd, (HMENU)(i + 3), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
                hwndColorValue[i]   = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, 20 * i, 0, 20, 200, hwnd, (HMENU)(i + 6), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            }
            hBrush[0] = CreateSolidBrush(RGB(0xFF, 0, 0));
            hBrush[1] = CreateSolidBrush(RGB(0, 0xFF, 0));
            hBrush[2] = CreateSolidBrush(RGB(0, 0, 0xFF));

            crPrim[0] = RGB(0xFF, 0, 0);
            crPrim[1] = RGB(0, 0xFF, 0);
            crPrim[2] = RGB(0, 0, 0xFF);
            hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
            break;
        }
        // Modify scrollbar color
    case WM_CTLCOLORSCROLLBAR:
        {
            i = GetWindowLong((HWND)lParam, GWL_ID);
            return (LRESULT)hBrush[i];
        }
    case WM_CTLCOLORSTATIC:
        {
            i = GetWindowLong ((HWND) lParam, GWL_ID) ;

            if (i >= 3 && i <= 8)    // static text controls
            {
                SetTextColor ((HDC) wParam, crPrim[i % 3]) ;
                SetBkColor ((HDC) wParam, GetSysColor (COLOR_BTNHIGHLIGHT));
                return (LRESULT) hBrushStatic ;
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
                DeleteObject((HGDIOBJ)SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(r, g, b))));
                InvalidateRect(hwnd, &rcColor,TRUE);
            }
            break;
        }
    case WM_SIZE:
        {
            //Client Window size
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);

            //Char size
            cxChar = LOWORD(GetDialogBaseUnits());
            cyChar = HIWORD(GetDialogBaseUnits());

            SetRect(&rcColor, cxClient / 2, 0, cxClient, cyClient); 
            MoveWindow(hwndLeft, 0, 0, cxClient / 2, cyClient, TRUE);

            for (i = 0; i < 3; ++i)
            {
                //Set Scrollbar range
                SetScrollRange(hwndScrollBar[i], SB_CTL, 0, 255, TRUE);
                //Move Scrollbar position
                MoveWindow(hwndScrollBar[i], (i * 2 + 1) * cxClient / 14, cyClient / 20, cxClient / 14, cyClient * 18 / 20, TRUE);

                //Set ColorTitle
                MoveWindow(hwndColorTitle[i], (i * 2 + 1) * cxClient / 14, 0, cxClient / 14, cyClient / 20, TRUE);
                SetWindowText(hwndColorTitle[i], COLORTITLE[i]); 

                //Set ColorValue
                MoveWindow(hwndColorValue[i], (i * 2 + 1) * cxClient / 14, cyClient * 19 / 20, cxClient / 14, cyClient / 20, TRUE);
                wsprintf(szBuffer, TEXT("%d"), r);
                SetWindowText(hwndColorValue[i], szBuffer); 
            }
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
