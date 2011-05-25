/*Print the string "Hello, World!" in different colors
 *
 * 31 -- red
 * 32 -- green
 * 33 -- yellow
 *
 * */
#include <stdio.h>
int main()
{
    //TODO:How to print the string in differnt colors with "for" loop
    /*const char *foreground = "\033[30;48m";
    const char *background = "\033[00m";
    printf("%sHello, World!%s\n", foreground, background);

    */

    char *foreground = "\033[30;48m";
    char *background = "\033[00m";
    int colorIndex = 0;
    for(;colorIndex < 10; ++colorIndex)
    {
        foreground[3] = 0x30 + colorIndex;
        printf("%sHello, World!%s\n", foreground, background);
    }
    return 0;
}
