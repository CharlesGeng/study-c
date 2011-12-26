#include <windows.h>

#define PENSCOUNT    (sizeof(PENS) / sizeof(PENS[0]))

struct
{
    int style;
    int width;
    COLORREF color;
}
PENS[] =
{
    PS_SOLID,       1, RGB(255, 0, 0),
    PS_DASH,        1, RGB(0, 255, 0),
    PS_DOT,         1, RGB(0, 0, 255),
    PS_DASHDOT,     1, RGB(255, 0, 0),
    PS_DASHDOTDOT,  1, RGB(0, 255, 0),
    PS_NULL,        1, RGB(0, 0, 255),
    PS_INSIDEFRAME, 2, RGB(255, 0, 0),
    PS_USERSTYLE,   1, RGB(0, 255, 0),
    PS_ALTERNATE,   1, RGB(0, 0, 255),
};
