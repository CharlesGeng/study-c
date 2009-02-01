obj=E02 E03
E01: E01.c $(obj)
	cc -o E01 E01.c
E02: E02.c 	
	cc -o E02 E02.c
E03: E03.c opval.h opval.c getch.h getch.c	
	cc -o E03 E03.c opval.c getch.c
clean:
	rm E01 $(obj)
