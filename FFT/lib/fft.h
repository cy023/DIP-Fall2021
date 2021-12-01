/**
 * @file    fft.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.23
 * @brief   Fast Fourier Transform implementation.
 */

#ifndef __FFT_H__
#define __FFT_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.1415926

typedef struct {
    double re;
    double im;
} Complex_t;

typedef struct {
    uint8_t *data;
    Complex_t *freq;
    uint64_t height;
    uint64_t width;
} Image_t;

void fft(int N, Complex_t *data, Complex_t *reserved);
void ifft(int N, Complex_t *data, Complex_t *reserved);

void imgfft2(Image_t *img);
void imgifft2(Image_t *img);

double c_abs(Complex_t c);
void cTranspose(Complex_t *data, uint32_t width, uint32_t height);

double mse(uint8_t *img1, uint8_t *img2, uint64_t size);
double psnr(uint8_t *img1, uint8_t *img2, uint64_t size);

#endif /* __FFT_H__ */