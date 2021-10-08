all:
	gcc -Werror -c lib/matrix_ops.c -o matrix_ops.o
	gcc -Werror -c lib/bmp.c -o bmp.o
	gcc -Werror -c main.c -o main.o
	gcc -Werror -c hw1.c -o hw1.o
	gcc matrix_ops.o bmp.o main.o -o main
	gcc matrix_ops.o bmp.o hw1.o -o hw1
	rm *.o

clean_image:
	rm ./Image/gray.bmp ./Image/negfilm.bmp
	rm ./Image/invert.bmp ./Image/mirror.bmp
	rm ./Image/rotCCW90.bmp ./Image/rotCW90.bmp
	rm ./Image/subsample256.bmp ./Image/subsample128.bmp
	rm ./Image/subsample64.bmp ./Image/subsample32.bmp

clean:
	rm main hw1
	