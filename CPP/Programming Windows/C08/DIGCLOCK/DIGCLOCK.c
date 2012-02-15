#include <windows.h>

#define IDTIMER		1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TCHAR       *szAppName  = TEXT("Beeper2");
	TCHAR       *szTitle    = TEXT("Time Beeper 2");
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

// Draw digits
void DisplayDigit(HDC hdc, WORD wDigit)
{
	static POINT ptSegment[7][6] = {
		7,  6,  11,  2,  31,  2,  35,  6,  31, 10,  11, 10,
		6,  7,  10, 11,  10, 31,   6, 35,   2, 31,   2, 11,
		36,  7,  40, 11,  40, 31,  36, 35,  32, 31,  32, 11,
		7, 36,  11, 32,  31, 32,  35, 36,  31, 40,  11, 40,
		6, 37,  10, 41,  10, 61,   6, 65,   2, 61,   2, 41,
		36, 37,  40, 41,  40, 61,  36, 65,  32, 61,  32, 41,
		7, 66,  11, 62,  31, 62,  35, 66,  31, 70,  11, 70 
	};
	static BOOL fSevenSegment [10][7] = {
			1, 1, 1, 0, 1, 1, 1,     // 0
			0, 0, 1, 0, 0, 1, 0,     // 1
			1, 0, 1, 1, 1, 0, 1,     // 2
			1, 0, 1, 1, 0, 1, 1,     // 3
			0, 1, 1, 1, 0, 1, 0,     // 4
			1, 1, 0, 1, 0, 1, 1,     // 5
			1, 1, 0, 1, 1, 1, 1,     // 6
			1, 0, 1, 0, 0, 1, 0,     // 7
			1, 1, 1, 1, 1, 1, 1,     // 8
			1, 1, 1, 1, 0, 1, 1		 //9
	};
	int i;

	if (hdc == NULL)
		return;
	if (wDigit < 0 || wDigit > 9)
		return;
	for (i = 0; i < 7; ++i)
	{
		if (fSevenSegment[wDigit][i] == 1)
		{
			Polygon(hdc, ptSegment[i], 6);
		}
	}

	OffsetWindowOrgEx(hdc, -42, 0, NULL);
}

// Show two digits, if wDigit lower than 10, it will Display zero instead
void DisplayTwoDigit(HDC hdc, WORD wDigit)
{
	//Check data
	if (hdc == NULL)
		return;

	if (wDigit < 0)
		return;

	// Display first digit
	if (wDigit / 10 > 0)
	{
		DisplayDigit(hdc, wDigit / 10);
	}
	else
	{
		DisplayDigit(hdc, 0);
	}

	// Display second digit
	DisplayDigit(hdc, wDigit % 10);
}

DisplayColon(HDC hdc)
{
     POINT ptColon [2][4] = { 2,  21,  6,  17,  10, 21,  6, 25,
                              2,  51,  6,  47,  10, 51,  6, 55 } ;

     Polygon (hdc, ptColon [0], 4) ;
     Polygon (hdc, ptColon [1], 4) ;
	 OffsetWindowOrgEx(hdc, -12, 0, NULL);
}

//Show Time
void DisplayTime(HDC hdc, BOOL b24Hour, BOOL bLeadingZero)
{
	SYSTEMTIME	st;
	WORD		wHour;
	GetLocalTime(&st);

	//Hour
	if (bLeadingZero)
	{
		DisplayTwoDigit(hdc, st.wHour);
	}
	else
	{
		// in 24 hour format
		if (b24Hour)
		{
			wHour = st.wHour;
		}
		//in 12 hour format
		else
		{
			wHour = st.wHour % 12;
		}

		if (wHour > 10)
		{
			DisplayTwoDigit(hdc, wHour);
		}
		else
		{
			DisplayDigit(hdc, wHour);
		}
	}

	//Colon
	DisplayColon(hdc);
	//Minute
	DisplayTwoDigit(hdc, st.wMinute);
	//Colon
	DisplayColon(hdc);
	//Second
	DisplayTwoDigit(hdc, st.wSecond);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static BOOL		b24Hour, bLeadingZero; 
	static int		cxClient, cyClient;
	static HBRUSH	brush;

	HDC				hdc;
	PAINTSTRUCT		ps;
	TCHAR			szBuffer[2];

	switch(uMsg)
	{
	case WM_CREATE:
		// Determine 24 or 12 hour format
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITIME, szBuffer, 2);
		b24Hour = szBuffer[0] == '1';

		//Determine Show leading zero for hours
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITLZERO, szBuffer, 2);
		bLeadingZero = szBuffer[0] == '1';
		brush = CreateSolidBrush(RGB(0, 0xFF, 00));
		SetTimer(hwnd, IDTIMER, 1000, NULL);
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	case WM_TIMER:
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, 276, 72, NULL);
		SetViewportExtEx(hdc, cxClient/2, cyClient/2, NULL);
		SetWindowOrgEx(hdc, 138, 36, NULL);
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);

		SelectObject(hdc, GetStockObject(NULL_PEN));
		SelectObject(hdc, brush);

		DisplayTime(hdc, b24Hour, bLeadingZero);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, IDTIMER);
		DeleteObject(brush);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
