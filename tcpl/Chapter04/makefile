obj=E02 E03 E04 E05 E06 E07 E08 E10 E11 E12 E13
E01: E01.c $(obj)
	cc -o E01 -Wall E01.c
E02: E02.c
	cc -o E02 -Wall E02.c
E03: E03.c calculator.h stack.c getch.c
	cc -o E03 -lm  -Wall E03.c calculator.h stack.c getch.c
E04: E04.c calculator.h stack.c getch.c
	cc -o E04 -Wall E04.c calculator.h stack.c getch.c
E05: E05.c calculator.h stack.c getch.c
	cc -o E05 -lm -Wall E05.c calculator.h stack.c getch.c
E06: E06.c calculator.h stack.c getch.c
	cc -o E06 -lm -Wall E06.c calculator.h stack.c getch.c
E07: E07.c calculator.h stack.c getch.c
	cc -o E07 -lm -Wall E07.c calculator.h stack.c getch.c
E08: E08.c calculator.h stack.c getch.c
	cc -o E08 -lm -Wall E08.c calculator.h stack.c getch.c
E10: E10.c calculator.h stack.c getch.c
	cc -o E10 -lm -Wall E10.c calculator.h stack.c getch.c
E11: E11.c calculator.h stack.c getch.c
	cc -o E11 -lm -Wall E11.c calculator.h stack.c getch.c
E12: E12.c
	cc -o E12 -Wall E12.c
E13: E13.c
	cc -o E13 -Wall E13.c
clean:
	rm E01 $(obj)
clear:
	rm *.exe
