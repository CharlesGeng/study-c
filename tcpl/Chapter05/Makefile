objects := E01 E02
all : $(objects)
.PHONY : all clean

E01: C05.h E01.c getch.c
	gcc -o E01 -Wall -g C05.h E01.c getch.c
E02: C05.h E02.c getch.c
	gcc -o E02 -Wall -g C05.h E02.c getch.c
clean:
	-rm -f $(objects)
