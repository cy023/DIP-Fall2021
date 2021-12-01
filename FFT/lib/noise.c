/**
 * @file    noise.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.26
 * @brief   bit map file format noise
 */
#include "noise.h"
#include <stdio.h>

void uniform_noise(int16_t **noise, uint32_t width, uint32_t height, int16_t a, int16_t b)
{
    srand(time(NULL));
    uint64_t i, j;
    int16_t min = a < b ? a : b;
    int16_t range = abs(b - a);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (rand() % range == 0) {
                noise[i][j] = (rand() % (range + 1)) + min;
            }
        }
    }
}

void gassian_noise(uint8_t *origin, uint8_t *addnoise)
{
    srand(time(NULL));

}

void saltpeppr_noise(uint8_t *origin, uint8_t *addnoise)
{
    srand(time(NULL));

}

void statistics_noise(int16_t **noise, uint32_t width, uint32_t height, int16_t lower, int16_t upper)
{
    uint32_t i, j, max_level = 0;
    uint16_t *buff;
    uint16_t size = upper - lower + 1;
    buff = (uint16_t *)malloc(size * sizeof(uint16_t));
    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (noise[i][j] != 0)
                buff[noise[i][j] - lower]++;
        }
    }
    
    printf("\x1b[5m |");
    for (i = 0; i < size; i++) {
        printf("-");
        max_level = buff[i] > max_level ? buff[i] : max_level;
    }
    for (int32_t i = max_level; i > 0; i--) {
        printf("\x1b[5m|\n |\x1b[0;m");
        for (j = 0; j < size; j++) {
            if ((buff[j]) >= i)
                printf("\x1b[;32;34m*\x1b[0;m");
            else
                printf(" ");
        }
    }
    printf("\x1b[5m|\n |");
    for (i = 0; i < size; i++) {
        printf("-");
    }
    printf("|\n\x1b[0;m");
}
