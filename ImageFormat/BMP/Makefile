all:
	gcc -Werror -c lib/bmp.c -o bmp.o
	gcc -Werror -c main.c -o main.o
	gcc bmp.o main.o -o main
	rm *.o

clean:
	rm main