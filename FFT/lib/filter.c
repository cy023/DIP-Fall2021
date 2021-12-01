/**
 * @file    filter.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.12.01
 * @brief   Image frequency domain filter.
 */

#include "filter.h"

void lowpass(Image_t *img, int16_t cutoff)
{
    int16_t i, j;
    int16_t M = img->height;
    int16_t N = img->width;
    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            if (sqrt((i-M/2)*(i-M/2) + (j-N/2)*(j-N/2)) > cutoff) {
                img->freq[i * img->width + j].re = 0;
                img->freq[i * img->width + j].im = 0;
            }
        }
    }
    normfreq(img);
}

void highpass(Image_t *img, int16_t cutoff)
{
    int16_t i, j;
    int16_t M = img->height;
    int16_t N = img->width;
    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            if (sqrt((i-M/2)*(i-M/2) + (j-N/2)*(j-N/2)) < cutoff) {
                img->freq[i * img->width + j].re = 0;
                img->freq[i * img->width + j].im = 0;
            }
        }
    }
    normfreq(img);
}

void bandpass(Image_t *img, int16_t lowb, int16_t upb)
{
    int16_t i, j;
    int16_t M = img->height;
    int16_t N = img->width;
    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            if (sqrt((i-M/2)*(i-M/2) + (j-N/2)*(j-N/2)) < lowb || \
                sqrt((i-M/2)*(i-M/2) + (j-N/2)*(j-N/2)) > upb ) {
                img->freq[i * img->width + j].re = 0;
                img->freq[i * img->width + j].im = 0;
            }
        }
    }
    normfreq(img);
}

void bandreject(Image_t *img, int16_t lowb, int16_t upb)
{
    int16_t i, j;
    int16_t M = img->height;
    int16_t N = img->width;
    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            if (sqrt((i-M/2)*(i-M/2) + (j-N/2)*(j-N/2)) > lowb && \
                sqrt((i-M/2)*(i-M/2) + (j-N/2)*(j-N/2)) < upb ) {
                img->freq[i * img->width + j].re = 0;
                img->freq[i * img->width + j].im = 0;
            }
        }
    }
    normfreq(img);
}



