/**
 * @file    conv.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.12.01
 * @brief   Image mask filter.
 */

#ifndef __CONV_H__
#define __CONV_H__

#include "fft.h"

void normdata(Image_t *img, int32_t *buff);

void edgeMask(Image_t *img);
// void blurMask(Image_t *img);
// void sharpenMask(Image_t *img);
// void embossMask(Image_t *img);
// void bottomSobelMask(Image_t *img);
// void topSobelMask(Image_t *img);
// void leftSobelMask(Image_t *img);
// void rightSobelMask(Image_t *img);

#endif /* __CONV_H__ */