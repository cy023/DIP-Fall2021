all:
	gcc -Werror -c lib/matrix_ops.c -o matrix_ops.o
	gcc -Werror -c lib/bmp.c -o bmp.o
	gcc -Werror -c main.c -o main.o
	gcc matrix_ops.o bmp.o main.o -o main
	rm *.o

clean:
	rm main