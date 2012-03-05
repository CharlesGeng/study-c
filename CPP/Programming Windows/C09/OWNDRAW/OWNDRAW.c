#include <windows.h>

#define SMALLBTN    1
#define BIGBTN      2

#define BUTTONWIDTH     (8 * cxChar)
#define BUTTONHEIGHT    (4 * cyChar)

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	TCHAR szAppName[] = TEXT ("OWNDRAW") ;
	TCHAR szAppTitle[] = TEXT ("Owner-Draw Button Demo") ;
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

void Triangle(HDC hdc, POINT pt[])
{
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	Polygon(hdc, pt, 3);
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
}
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndBig, hwndSmall;
	static int  cxChar, cyChar;
	static int  cxClient, cyClient;

	HDC         hdc ;
	PAINTSTRUCT ps ;
	RECT        rectWindow;
	POINT       pt[3];
	int         cSideLength;
	int         cx, cy;
	DRAWITEMSTRUCT *pdis;

	switch (message)
	{
	case WM_CREATE:
		{
			cxChar = LOWORD(GetDialogBaseUnits());
			cyChar = HIWORD(GetDialogBaseUnits());


			hwndBig = CreateWindow(TEXT("button"), TEXT(""),
				WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 0, 0, BUTTONWIDTH, BUTTONHEIGHT,
				hwnd, (HMENU)BIGBTN, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			hwndSmall = CreateWindow(TEXT("button"), TEXT(""),
				WS_CHILD | WS_VISIBLE| BS_OWNERDRAW, 0, 0, BUTTONWIDTH, BUTTONHEIGHT,
				hwnd, (HMENU)SMALLBTN, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			break;
		}
	case WM_DRAWITEM:
		{
			pdis        = (LPDRAWITEMSTRUCT)lParam;
			hdc         = ((LPDRAWITEMSTRUCT)lParam)->hDC;

			FillRect(hdc, &pdis->rcItem, (HBRUSH)GetStockObject(WHITE_BRUSH));
			FrameRect(hdc, &pdis->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));

			cSideLength = pdis->rcItem.right - pdis->rcItem.left;
			cx = pdis->rcItem.right - pdis->rcItem.left;
			cy = pdis->rcItem.bottom - pdis->rcItem.top;
			if (pdis->CtlID == BIGBTN)
			{
				// left triangle
				pt[0].x = cSideLength / 5;
				pt[0].y = cSideLength / 2;
				pt[1].x = cSideLength * 2 / 5;
				pt[1].y = cSideLength * 2 / 5;
				pt[2].x = cSideLength * 2 / 5;
				pt[2].y = cSideLength * 3 / 5;
				Triangle(hdc, pt);

				// top triangle
				pt[0].x = cSideLength / 2;
				pt[0].y = cSideLength / 6;
				pt[1].x = cSideLength * 2 / 5;
				pt[1].y = cSideLength * 2 / 5;
				pt[2].x = cSideLength * 3 / 5;
				pt[2].y = cSideLength * 2 / 5;
				Triangle(hdc, pt);

				//right triangle
				pt[0].x = cSideLength * 3 / 5;
				pt[0].y = cSideLength * 2 / 5;
				pt[1].x = cSideLength * 4 / 5;
				pt[1].y = cSideLength / 2;
				pt[2].x = cSideLength * 3 / 5;
				pt[2].y = cSideLength * 3 / 5;
				Triangle(hdc, pt);

				// bottom triangle
				pt[0].x = cSideLength * 2 / 5;
				pt[0].y = cSideLength * 3 / 5;
				pt[1].x = cSideLength * 3 / 5;
				pt[1].y = cSideLength * 3 / 5;
				pt[2].x = cSideLength / 2;
				pt[2].y = cSideLength * 4 / 5;
				Triangle(hdc, pt);
			}
			else if (pdis->CtlID == SMALLBTN)
			{
				// left triangle
				pt[0].x = cSideLength / 5;
				pt[0].y = cSideLength * 2 / 5;
				pt[1].x = cSideLength * 2 / 5;
				pt[1].y = cSideLength / 2;
				pt[2].x = cSideLength / 5;
				pt[2].y = cSideLength * 3 / 5;
				Triangle(hdc, pt);

				// top triangle
				pt[0].x = cSideLength * 2 / 5;
				pt[0].y = cSideLength / 5;
				pt[1].x = cSideLength * 3 / 5;
				pt[1].y = cSideLength / 5;
				pt[2].x = cSideLength / 2;
				pt[2].y = cSideLength * 2 / 5;
				Triangle(hdc, pt);

				//right triangle
				pt[0].x = cSideLength * 3 / 5;
				pt[0].y = cSideLength / 2;
				pt[1].x = cSideLength * 4 / 5;
				pt[1].y = cSideLength * 2 / 5;
				pt[2].x = cSideLength * 4 / 5;
				pt[2].y = cSideLength * 3 / 5;
				Triangle(hdc, pt);

				// bottom triangle
				pt[0].x = cSideLength * 2 / 5;
				pt[0].y = cSideLength * 4 / 5;
				pt[1].x = cSideLength / 2;
				pt[1].y = cSideLength * 3 / 5;
				pt[2].x = cSideLength * 3 / 5;
				pt[2].y = cSideLength * 4 / 5;
				Triangle(hdc, pt);
			}

			// Invert button color
			if (pdis->itemState & ODS_SELECTED)
			{
				InvertRect(hdc, &pdis->rcItem);
			}

			if (pdis->itemState & ODS_FOCUS)
			{
				pdis->rcItem.top += cSideLength / 10;
				pdis->rcItem.bottom -= cSideLength / 10;
				pdis->rcItem.left += cSideLength /10;
				pdis->rcItem.right -= cSideLength /10;
				DrawFocusRect(hdc, &pdis->rcItem);
			}
			break;
		}
	case WM_SIZE:
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			MoveWindow(hwndBig, cxClient / 2 - 3 * BUTTONWIDTH / 2, cyClient / 2 - BUTTONHEIGHT / 2, BUTTONWIDTH, BUTTONHEIGHT, TRUE);
			MoveWindow(hwndSmall, cxClient / 2 + BUTTONWIDTH / 2, cyClient / 2 - BUTTONHEIGHT / 2, BUTTONWIDTH, BUTTONHEIGHT, TRUE);
			break;
		}
	case WM_COMMAND:
		{
			GetWindowRect(hwnd, &rectWindow);
			if (LOWORD(wParam) == BIGBTN)
			{
				rectWindow.left     -= cxClient	/ 20;
				rectWindow.top      -= cyClient / 20;
				rectWindow.right    += cxClient / 20;
				rectWindow.bottom   += cyClient / 20;
				MoveWindow(hwnd, rectWindow.left, rectWindow.top,
					rectWindow.right - rectWindow.left, rectWindow.bottom - rectWindow.top,TRUE);

			}
			else if (LOWORD(wParam) == SMALLBTN)
			{
				rectWindow.left     += cxClient / 20;
				rectWindow.top      += cyClient / 20;
				rectWindow.right    -= cxClient / 20;
				rectWindow.bottom   -= cyClient / 20;
				MoveWindow(hwnd, rectWindow.left, rectWindow.top,
					rectWindow.right - rectWindow.left, rectWindow.bottom - rectWindow.top,TRUE);
			}
			break;
		}
	case WM_PAINT :
		{
			hdc = BeginPaint (hwnd, &ps) ;
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
