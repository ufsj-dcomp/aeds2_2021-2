all: conjunto.o main.o
	gcc conjunto.o main.o -o conjunto

conjunto.o: conjunto.c conjunto.h
	gcc -c -Wall -g conjunto.c

main.o: main.c conjunto.h
	gcc -c -Wall -g main.c

clean:
	rm *.o conjunto

