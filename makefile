tail: main.c functions.c functions.h
	gcc -Wall -g main.c functions.c -o tail
clean:
	rm -f *tail