.PHONY: all test clean

all:
	gcc -Werror -c lib/matrix_ops.c -o matrix_ops.o
	gcc -Werror -c lib/bmp.c -o bmp.o
	gcc -Werror -c hw1.c -o hw1.o
	gcc matrix_ops.o bmp.o hw1.o -o hw1.out
	rm *.o

test:
	gcc -Werror -c lib/matrix_ops.c -o matrix_ops.o
	gcc -Werror -c lib/bmp.c -o bmp.o
	gcc -Werror -c test/test_32bit.c -o test_32bit.o
	gcc -Werror -c test/test_mov.c -o test_mov.o
	gcc -Werror -c test/test_subsample.c -o test_subsample.o
	gcc -Werror -c test/test_graylevel_tf.c -o test_graylevel_tf.o
	gcc matrix_ops.o bmp.o test_32bit.o -o test_32bit.out
	gcc matrix_ops.o bmp.o test_mov.o -o test_mov.out
	gcc matrix_ops.o bmp.o test_subsample.o -o test_subsample.out
	gcc matrix_ops.o bmp.o test_graylevel_tf.o -o test_graylevel_tf.out
	rm *.o

clean:
	rm -f *.out
	rm -f ./script/*.png ./script/*.txt
	find ./Image | grep -e '^./Image/_.*' | xargs rm -f
