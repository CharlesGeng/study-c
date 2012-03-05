#include <Windows.h>

#define ID_EDIT         1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR    szAppName[] = TEXT("POPPAD1");

    MSG         msg;
    WNDCLASS    wc;
    HWND        hwnd;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = (HCURSOR)LoadCursor(hInstance, IDC_ARROW);
    wc.hIcon            = (HICON)LoadIcon(hInstance, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Register class error!"), TEXT("ERROR"), MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("POPPAD 1st"), WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
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
    static HWND    hwndEdit;

    switch(uMsg)
    {
    case WM_CREATE:
        {
            hwndEdit = CreateWindow(TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | ES_MULTILINE, 
                0, 0, 0, 0, hwnd, (HMENU)ID_EDIT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            break;
        }
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        MoveWindow(hwndEdit, 0, 0, cxClient, cyClient, TRUE);
        break;
    case WM_SETFOCUS:
        {
            SetFocus(hwndEdit);
            break;
        }
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_EDIT)
        {
            if (HIWORD(wParam) == EN_ERRSPACE || HIWORD(wParam) == EN_MAXTEXT)
            {
                MessageBox(hwnd, TEXT("The text edit is full of characters"), TEXT("ERROR"), MB_ICONERROR);
            }
        }
        break;
    case WM_CLOSE:
        {
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}