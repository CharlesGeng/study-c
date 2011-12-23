#include <windows.h>
#include "SystemMetrics.h"

//window�ص�����(window message)
LRESULT CALLBACK WndProc( HWND , UINT , WPARAM , LPARAM );

int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    static TCHAR *szAppName = TEXT("StudyScrollBar");
    WNDCLASS    wc;
    HWND        hwnd;
    MSG         msg;

    wc.style            = CS_HREDRAW | CS_VREDRAW;              //���񣬸���ϱ�ʾ�������λ�÷����ı���߿�߷����仯ʱ���ػ���������
    wc.lpfnWndProc      = WndProc;                              //������Ļص�����
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);        //����ͼ��
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);            //�������
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);    //��ȡͼ�ζ���
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = szAppName;

    if (!RegisterClass(&wc))    //ע�ᴰ����
    {
        MessageBox(NULL, TEXT("Register Window Class Structure Error!"), TEXT("ERROR"), MB_ICONERROR);
        return 0;
    }

    //�������ڴ�����Ĵ���
    hwnd = CreateWindow(szAppName,
                        TEXT("The Hello Program"),
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

LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    static int cxChar;              //Сд�ַ����
    static int cxCaps;              //��д�ַ����
    static int cyChar;              //�ַ��߶�
    static int iVScrollPos;         //������λ��
    static int cxClient;            //�û����ڿ��
    static int cyClient;            //�û����ڸ߶�
    SCROLLINFO si;                  //��������Ϣ

    int iPaintBeg, iPaintEnd;
    int y;

    int i;
    TCHAR szBuffer[10];
    HDC hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch(uMsg)
    {
        case WM_CREATE:
        {
            hdc = GetDC(hwnd);
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hwnd, hdc);
            return 0;
        }
        //���ڴ�С�����仯
        case WM_SIZE:
        {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);

            //���ô�ֱ������
            si.cbSize   = sizeof(SCROLLINFO);
            si.fMask    = SIF_RANGE | SIF_PAGE;
            si.nMin     = 0;
            si.nMax     = NUMLINES - 1;
            si.nPage    = cyClient / cyChar;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            return 0;
        }
        //��ֱ������
        case WM_VSCROLL:
        {
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);

            iVScrollPos = si.nPos;

            switch (LOWORD(wParam))
            {
            case SB_TOP:
                {
                    si.nPos = si.nMin;
                    break;
                }
            case SB_BOTTOM:
                {
                    si.nPos = si.nMax;
                    break;
                }
            case SB_LINEUP:
                {
                    si.nPos -= 1;
                    break;
                }
            case SB_LINEDOWN:
                {
                    si.nPos += 1;
                    break;
                }
            case SB_PAGEUP:
                {
                    si.nPos -= si.nPage;
                    break;
                }
            case SB_PAGEDOWN:
                {
                    si.nPos += si.nPage;
                    break;
                }
            case SB_THUMBTRACK:
                {
                    si.nPos = si.nTrackPos;
                    break;
                }
            default:
                {
                    break;
                }
            }

            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
            GetScrollInfo(hwnd, SB_VERT, &si);

            if (iVScrollPos != si.nPos)
            {
                ScrollWindow(hwnd, 0, cyChar * (iVScrollPos - si.nPos), NULL, NULL );
                UpdateWindow(hwnd);
            }
            return 0;
        }
        case WM_HSCROLL:
        {
        }
        case WM_PAINT:
        {
            HDC hdc = BeginPaint(hwnd, &ps);
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_POS;
            GetScrollInfo(hwnd, SB_VERT, &si);
            iVScrollPos = si.nPos;

            iPaintBeg = max (0, iVScrollPos + ps.rcPaint.top / cyChar) ;
            iPaintEnd = min (NUMLINES - 1, iVScrollPos + ps.rcPaint.bottom / cyChar) ;

            for (i = iPaintBeg ; i <= iPaintEnd ; ++i)
            {
                y = cyChar * (i - iVScrollPos) ;

                //��һ��
                TextOut(hdc, 0, y, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
                //�ڶ���
                TextOut(hdc, 22 * cxCaps, y, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));

                SetTextAlign(hdc, TA_RIGHT | TA_TOP);
                //������
                TextOut(hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].iIndex)));
                SetTextAlign(hdc, TA_LEFT | TA_TOP);
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
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    return 0;
}
