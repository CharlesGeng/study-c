#include <windows.h>

#define ROWCOUNT        5
#define COLUMNCOUNT     5

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR *szAppName  = TEXT("Checker1");
    static TCHAR *szTitle    = TEXT("Checker1 Mouse hit");

    MSG         msg;
    WNDCLASS    wc;
    HWND        hwnd;

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
        return 0;
    }

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
    static int cxClient, cyClient;
    static int cxGrid, cyGrid;
    static int CheckedGrid[5][5];

    PAINTSTRUCT ps;
    HDC         hdc;
    int         i, j;
    int         cxCursor, cyCursor;
    RECT        rectGrid;

    switch(uMsg)
    {
    case WM_SIZE:
        {
            cxClient    = LOWORD(lParam);
            cyClient    = HIWORD(lParam);
            cxGrid      = cxClient / COLUMNCOUNT;
            cyGrid      = cyClient / ROWCOUNT;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_LBUTTONDOWN:
        {
            cxCursor = LOWORD(lParam);
            cyCursor = HIWORD(lParam);
            i = cxCursor / cxGrid;
            j = cyCursor /cyGrid;
            CheckedGrid[i][j] = !CheckedGrid[i][j];
            rectGrid.left   = i * cxGrid;
            rectGrid.right  = (i+1) * cxGrid;
            rectGrid.top    = j * cyGrid;
            rectGrid.bottom = (j+1) * cyGrid;
            InvalidateRect(hwnd, &rectGrid, TRUE);
            break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);

            // Draw lines
            for (i = 0; i < ROWCOUNT; ++i)
            {
                MoveToEx(hdc, 0, cyGrid * (1 + i), NULL);
                LineTo(hdc, cxGrid * COLUMNCOUNT, cyGrid * (1 + i));
            }
            for (i = 0; i < COLUMNCOUNT; ++i)
            {
                MoveToEx(hdc, cxGrid * (1 + i), 0, NULL);
                LineTo(hdc, cxGrid * (1 + i), cyGrid * ROWCOUNT);
            }

            for (i = 0; i < ROWCOUNT; ++i)
            {
                for (j=0; j < COLUMNCOUNT; ++j)
                {
                    if (CheckedGrid[i][j])
                    {
                        //Draw Cross line
                        MoveToEx(hdc, i * cxGrid, j * cyGrid, NULL);
                        LineTo(hdc, (i+1) * cxGrid, (j+1) * cyGrid);

                        MoveToEx(hdc, (i+1) * cxGrid, j * cyGrid, NULL);
                        LineTo(hdc, i * cxGrid, (j+1) * cyGrid);
                    }
                }
            }
            // Draw Checkers
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
