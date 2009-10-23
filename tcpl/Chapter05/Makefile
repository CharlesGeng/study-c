objects := E01 E02 E03 E04 E05 E06_getline Generator GetLine
all : $(objects)
.PHONY : all clean clear

E01: C05.h E01.c getch.c
	gcc -o E01 -Wall -g C05.h E01.c getch.c
E02: C05.h E02.c getch.c
	gcc -o E02 -Wall -g C05.h E02.c getch.c
E03: E03.c
	gcc -o E03 -Wall -g E03.c
E04: E04.c
	gcc -o E04 -Wall -g E04.c
E05: E05.c
	gcc -o E05 -Wall -g E05.c
E06_getline: E06_getline.c
	gcc -o E06_getline -Wall -g E06_getline.c
Generator: GenerateText.c
	gcc -o Generator -Wall -g GenerateText.c
GetLine: getline.c
	gcc -o GetLine -Wall -g getline.c
clean:
	-rm -f $(objects)
clear:
	-rm -f *.exe
