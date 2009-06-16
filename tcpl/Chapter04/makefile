obj=E02 E03 E04 E05
E01: E01.c $(obj)
	cc -o E01 E01.c
E02: E02.c
	cc -o E02 E02.c
E03: E03.c calculator.h stack.c getch.c
	cc -o E03 E03.c calculator.h stack.c getch.c
E04: E04.c calculator.h stack.c getch.c
	cc -o E04 E04.c calculator.h stack.c getch.c
E05: E05.c calculator.h stack.c getch.c
	cc -o E05 E05.c calculator.h stack.c getch.c
clean:
	rm E01 $(obj)
clear:
	rm *.exe
