#/bin/sh
outputstr:outputstr.c
	gcc -g -o outputstr outputstr.c
clean:
	rm *.o