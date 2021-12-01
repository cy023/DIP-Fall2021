/**
 * @file    noise.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.26
 * @brief   bit map file format noise
 */
#ifndef __NOISE_H__
#define __NOISE_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void uniform_noise(int16_t *noise, uint64_t nsize, int16_t a, int16_t b);
void gassian_noise(int16_t *noise, uint64_t nsize);
void saltpeppr_noise(int16_t *noise, uint64_t nsize);

void statistics_noise(int16_t *noise, uint64_t nsize, int16_t lower, int16_t upper);

#endif /* __NOISE_H__ */