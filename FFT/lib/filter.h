/**
 * @file    filter.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.12.01
 * @brief   Image frequency domain filter.
 */
#ifndef __FILTER_H__
#define __FILTER_H__

#include "fft.h"

void lowpass(Image_t *img, int16_t cutoff);
void highpass(Image_t *img, int16_t cutoff);
void bandpass(Image_t *img, int16_t lowb, int16_t upb);
void bandreject(Image_t *img, int16_t lowb, int16_t upb);

#endif /* __FILTER_H__ */