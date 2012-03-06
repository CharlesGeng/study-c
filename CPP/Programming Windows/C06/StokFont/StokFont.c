#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TCHAR		*szAppName = TEXT("StokFont");
	TCHAR		*szTitle = TEXT("Stock Font");
	MSG			msg;
	WNDCLASS	wc;
	HWND		hwnd;

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

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static struct
	{
		int		iFontIndex;
		TCHAR	*szFontName;
	}
	fonts[] = {
		OEM_FIXED_FONT,			TEXT("OEM_FIXED_FONT"),
		ANSI_FIXED_FONT,		TEXT("ANSI_FIXED_FONT"),
		ANSI_VAR_FONT,			TEXT("ANSI_VAR_FONT"),
		SYSTEM_FONT,			TEXT("SYSTEM_FONT"),
		DEVICE_DEFAULT_FONT,	TEXT("DEVICE_DEFAULT_FONT"),
		SYSTEM_FIXED_FONT,		TEXT("SYSTEM_FIXED_FONT"),
		DEFAULT_GUI_FONT,		TEXT("DEFAULT_GUI_FONT"),
	};
	static int		iFontCount = sizeof(fonts) / sizeof(fonts[0]);
	static int		iIndex;

	TCHAR			szBuffer[64];
	TCHAR			szFaceName[32];
	int				iCharSet;
	PAINTSTRUCT     ps;
	HDC             hdc;
	TEXTMETRIC		tm;
	int				cxChar, cyChar;
	int				i, j;
	SCROLLINFO		si;
	int				iOldPos;
	static int		cyClient;
	RECT			rectClient;


	switch (uMsg)
	{
	case WM_CREATE:
		{
			//hdc = GetDC(hwnd);
			//GetTextMetrics(hdc, &tm);
			iIndex = 0;
			SetScrollRange(hwnd, SB_VERT, 0, iFontCount - 1, TRUE);
			break;
		}
	case WM_SIZE:
		{
			cyClient = HIWORD(lParam);
			break;
		}
	case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);

			SetBkMode(hdc, TRANSPARENT);

			SelectObject(hdc, GetStockObject(fonts[iIndex].iFontIndex));

			GetTextMetrics(hdc, &tm);
			iCharSet = tm.tmCharSet;
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;

			GetTextFace(hdc, sizeof(szFaceName) /sizeof(WORD), szFaceName);

            //Print text name, face name, char set
			TextOut(hdc, cxChar, 0, szBuffer, wsprintf(szBuffer, TEXT("%s: Face Name = %s, CharSet = %d"), fonts[iIndex].szFontName, szFaceName, iCharSet));

            //print lines
            for (i = 0; i < 17; ++i)
            {
                //print vertical lines
                MoveToEx(hdc, (8 + i*4) * cxChar, 3 * cyChar, NULL);
				LineTo(hdc, (8+i*4) * cxChar, (3+20)*cyChar);
                //print horizontal lines
				MoveToEx(hdc, 4 * cxChar, (4 + i) * (cyChar+2), NULL);
				LineTo(hdc, (4+ 68) * cxChar, (4+i)*(cyChar+2));
            }
            for (i = 0; i < 16; ++i)
			{
				//print row / column number in hex decimal
				TextOut(hdc, (9 + i*4) * cxChar, 3 * cyChar, szBuffer, wsprintf(szBuffer, TEXT("%X-"), i));
				//print row / column number in hex decimal
				TextOut(hdc, 6 * cxChar, (4 +i)* (cyChar+2), szBuffer, wsprintf(szBuffer, TEXT("-%X"), i));
				//print char
				for(j=0; j < 16; ++j)
				{
					TextOut(hdc,(9+4*i) * cxChar,(4+j) * (cyChar+2), szBuffer, wsprintf(szBuffer, TEXT("%c"), i * 16 + j));
				}
			}

			EndPaint(hwnd, &ps);
			break;
		}
	case WM_VSCROLL:
		{
			si.cbSize	= sizeof(si);
			si.fMask	= SIF_ALL;
			GetScrollInfo(hwnd, SB_VERT, &si);

			iOldPos = si.nPos;

			switch (LOWORD(wParam))
			{
			case SB_LINEDOWN:
			case SB_PAGEDOWN:
				{
					iIndex++;
					break;
				}
			case SB_LINEUP:
			case SB_PAGEUP:
				{
					--iIndex;
					break;
				}
			case SB_TOP:
				{
					iIndex = 0;
					break;
				}
			case SB_BOTTOM:
				{
					iIndex = iFontCount - 1;
					break;
				}
				//case
			default:
				{
					break;
				}
			}
			iIndex = min(iIndex, iFontCount - 1);
			iIndex = max(0, iIndex);

			if (iOldPos != iIndex)
			{
				SetScrollPos(hwnd, SB_VERT, iIndex, TRUE);
//				ScrollWindow(hwnd, 0, (iOldPos - iIndex) * cyClient, NULL, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}
			break;
		}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		{
			switch (wParam)
			{
			case VK_PRIOR:
			case VK_UP:
			case VK_LEFT:
				{
					SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0);
					break;
				}
			case VK_NEXT:
			case VK_RIGHT:
			case VK_DOWN:
				{
					SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0);
					break;
				}
			case VK_END:
				{
					SendMessage(hwnd, WM_VSCROLL, SB_BOTTOM, 0);
					break;
				}
			case VK_HOME:
				{
					SendMessage(hwnd, WM_VSCROLL, SB_TOP, 0);
					break;
				}
			}
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	default:
		{
			break;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


