/*Print the string "Hello, World!" in different colors
 *
 * 31 -- red
 * 32 -- green
 * 33 -- yellow
 *
 * */
#include <stdio.h>
main()
{
    //TODO:How to print the string in differnt colors with "for" loop
    const char *foreground = "\033[31;48m";
    const char *background = "\033[00m";
    printf("%sHello, World!%s\n", foreground, background);
}
