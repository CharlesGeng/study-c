#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(){
    int N = 0;
    char src[33];
    scanf("%d", &N);
    while(N-- > 0){
        scanf("%s", src);
        int i = 0;
        int t = 0;
        while (i < 32){
            if (src[i] == '1'){
                t |= 1 << (7 - i % 8);
            }
            ++i;
            if ((i % 8) == 0){
                if (i != 32)
                    printf("%d.", t);
                else
                    printf("%d\n", t);
                t = 0;
            }
        }
    }
    return 0;
}
