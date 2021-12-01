/**
 * @file    noise.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.26
 * @brief   bit map file format noise
 */
#ifndef __NOISE_H__
#define __NOISE_H__

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void uniform_noise(int16_t **noise, uint32_t width, uint32_t height, int16_t a, int16_t b);
void gassian_noise(uint8_t *origin, uint8_t *addnoise);
void saltpeppr_noise(uint8_t *origin, uint8_t *addnoise);

void statistics_noise(int16_t **noise, uint32_t width, uint32_t height, int16_t lower, int16_t upper);

#endif /* __NOISE_H__ */