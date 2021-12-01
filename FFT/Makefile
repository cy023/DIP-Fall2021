.PHONY: all test clean

all:
	gcc -Werror -c lib/matrix_ops.c -o matrix_ops.o
	gcc -Werror -c lib/bmp.c -o bmp.o
	gcc -Werror -c lib/fft.c -o fft.o
	gcc -Werror -c hw2.c -o hw2.o
	gcc matrix_ops.o bmp.o fft.o hw2.o -lm -o hw2.out
	rm *.o

test:
	gcc -Werror -c lib/matrix_ops.c -o matrix_ops.o
	gcc -Werror -c lib/bmp.c -o bmp.o
	gcc -Werror -c lib/fft.c -o fft.o
	gcc -Werror -c lib/noise.c -o noise.o
	gcc -Werror -c lib/filter.c -o filter.o

	gcc -Werror -c test/test_fft.c -o test_fft.o
	gcc matrix_ops.o bmp.o fft.o test_fft.o -lm -o test_fft.out

	gcc -Werror -c test/test_fft2.c -o test_fft2.o
	gcc matrix_ops.o bmp.o fft.o test_fft2.o -lm -o test_fft2.out

	gcc -Werror -c test/test_img2txt.c -o test_img2txt.o
	gcc matrix_ops.o bmp.o fft.o test_img2txt.o -lm -o test_img2txt.out

	gcc -Werror -c test/test_noise.c -o test_noise.o
	gcc matrix_ops.o bmp.o fft.o noise.o test_noise.o -lm -o test_noise.out

	gcc -Werror -c test/test_filter.c -o test_filter.o
	gcc matrix_ops.o bmp.o fft.o filter.o test_filter.o -lm -o test_filter.out

	rm *.o

# test:
# 	gcc -Werror -c lib/matrix_ops.c -o matrix_ops.o
# 	gcc -Werror -c lib/bmp.c -o bmp.o
# 	gcc -Werror -c test/test_32bit.c -o test_32bit.o
# 	gcc -Werror -c test/test_mov.c -o test_mov.o
# 	gcc -Werror -c test/test_subsample.c -o test_subsample.o
# 	gcc -Werror -c test/test_graylevel_tf.c -o test_graylevel_tf.o
# 	gcc matrix_ops.o bmp.o test_32bit.o -o test_32bit.out
# 	gcc matrix_ops.o bmp.o test_mov.o -o test_mov.out
# 	gcc matrix_ops.o bmp.o test_subsample.o -o test_subsample.out
# 	gcc matrix_ops.o bmp.o test_graylevel_tf.o -o test_graylevel_tf.out
# 	rm *.o

clean:
	rm -f *.out
	find ./Image | grep -e '^./Image/_.*' | xargs rm -f
	# rm -f ./script/*.png ./script/*.txt
