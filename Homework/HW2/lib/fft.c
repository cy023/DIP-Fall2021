/**
 * @file    fft.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.23
 * @brief   Fast Fourier Transform implementation.
 */

#include "fft.h"

void fft(int N, Complex_t *data, Complex_t *reserved)
{
    if (N == 1) return ;

    int32_t i;
    Complex_t w, z, *fe, *fo;
    
    fe = reserved;
    fo = reserved + N / 2;
    
    for (i = 0; i < N / 2; i++) {
        fe[i] = data[2 * i];
        fo[i] = data[2 * i + 1];
    }

    fft(N/2, fe, data);
    fft(N/2, fo, data);

    for (i = 0; i < N / 2; i++) {
        w.re =  cos(2 * PI * (double)i / (double)N);
        w.im = -sin(2 * PI * (double)i / (double)N);
        z.re = w.re * fo[i].re - w.im * fo[i].im;
        z.im = w.re * fo[i].im + w.im * fo[i].re;
        data[i].re = fe[i].re + z.re;
        data[i].im = fe[i].im + z.im;
        data[i + N / 2].re = fe[i].re - z.re;
        data[i + N / 2].im = fe[i].im - z.im;
    }
}

void ifft(int N, Complex_t *data, Complex_t *reserved)
{
    if (N == 1) return ;

    int32_t i;
    Complex_t w, z, *fe, *fo;
    
    fe = reserved;
    fo = reserved + N / 2;
    
    for (i = 0; i < N / 2; i++) {
        fe[i] = data[2 * i];
        fo[i] = data[2 * i + 1];
    }

    ifft(N/2, fe, data);
    ifft(N/2, fo, data);

    for (i = 0; i < N / 2; i++) {
        w.re = cos(2 * PI * (double)i / (double)N);
        w.im = sin(2 * PI * (double)i / (double)N);
        z.re = w.re * fo[i].re - w.im * fo[i].im;
        z.im = w.re * fo[i].im + w.im * fo[i].re;
        data[i].re = fe[i].re + z.re;
        data[i].im = fe[i].im + z.im;
        data[i + N / 2].re = fe[i].re - z.re;
        data[i + N / 2].im = fe[i].im - z.im;
    }
    for (i = 0; i < N; i++) {
        data[i].re /= 2;
        data[i].im /= 2;
    }
}

// TODO: non square image.
void imgfft2(Image_t *img)
{
    Complex_t *tmprow, *tmpcol;
    uint64_t i, j;

    tmprow = (Complex_t *)calloc(img->width, sizeof(Complex_t));
    tmpcol = (Complex_t *)calloc(img->height, sizeof(Complex_t));

    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            double factor = (i + j) % 2 ? -1 : 1;
            img->freq[i*img->width+j].re = img->data[i*img->width+j] * factor;
        }
    }

    for (i = 0; i < img->height; i++) {
        fft(img->width, (Complex_t *)(&img->freq[img->width*i]), tmprow);
    }
    cTranspose(img->freq, img->height, img->width);
    for (int i = 0; i < img->width; i++) {
        fft(img->height, (Complex_t *)(&img->freq[img->width*i]), tmpcol);
    }
    cTranspose(img->freq, img->height, img->width);

    normfreq(img);
    
    free(tmprow);
    free(tmpcol);
}

void imgifft2(Image_t *img)
{
    Complex_t *tmprow, *tmpcol;
    uint64_t i, j;

    tmprow = (Complex_t *)calloc(img->width, sizeof(Complex_t));
    tmpcol = (Complex_t *)calloc(img->height, sizeof(Complex_t));

    for (int i = 0; i < img->width; i++) {
        ifft(img->height, (Complex_t *)(&img->freq[img->width*i]), tmpcol);
    }
    cTranspose(img->freq, img->height, img->width);
    for (i = 0; i < img->height; i++) {
        ifft(img->width, (Complex_t *)(&img->freq[img->width*i]), tmprow);
    }
    cTranspose(img->freq, img->height, img->width);

    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            double factor = (i + j) % 2 ? -1 : 1;
            img->data[i*img->width+j] = img->freq[i*img->width+j].re * factor;
        }
    }
    free(tmprow);
    free(tmpcol);
}

double c_abs(Complex_t c)
{
    return sqrt(c.re * c.re + c.im * c.im);
}

void cTranspose(Complex_t *data, uint32_t width, uint32_t height)
{
    uint32_t i, j;
    for (i = 0; i < height; i++) {
        for (j = i + 1; j < width; j++) {
            double t;
            t = data[i*width+j].re;
            data[i*width+j].re = data[j*width+i].re;
            data[j*width+i].re = t;

            t = data[i*width+j].im;
            data[i*width+j].im = data[j*width+i].im;
            data[j*width+i].im = t;
        }
    }
}

double mse(uint8_t *img1, uint8_t *img2, uint64_t size)
{
    double err = 0;
    for (int i = 0; i < size; i++) {
        err += (img1[i] - img2[i]) * (img1[i] - img2[i]);
    }
    return err / size;
}

double psnr(uint8_t *img1, uint8_t *img2, uint64_t size)
{
    return 10 * log10(255*255 / mse(img1, img2, size));
}

void normfreq(Image_t *img)
{
    uint64_t i, j;
    for (i = 0; i < img->height * img->width; i++) {
        if (20 * log10(c_abs(img->freq[i])) > 255) {
            img->data[i] = 255;
        }
        else {
            img->data[i] = (uint8_t)(20 * log10(c_abs(img->freq[i])));
        }
    }
}
