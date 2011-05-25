objects = 1000 1001 1002 1009 1068
all : $(objects)
.PHONY : all clean

1000 : 1000.c
	gcc -o 1000 -Wall 1000.c
1001 : 1001.c
	gcc -o 1001 -Wall -g 1001.c
1002 : 1002.c
	gcc -o 1002 -Wall -g 1002.c
1009 : 1009.c
	gcc -o 1009 -Wall -g 1009.c
1068 : 1068.c
	gcc -o 1068 -Wall -g 1068.c
clean:
	rm -f *.exe
clear:
	rm -f $(objects)
