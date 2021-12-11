/**
 * @file    noise.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.26
 * @brief   Noise Generator.
 */
#include "noise.h"

void uniform_noise(int16_t *noise, uint64_t nsize, int16_t a, int16_t b)
{
    srand(time(NULL));
    uint64_t i, j;
    int16_t min = a < b ? a : b;
    int16_t range = abs(b - a);
    for (i = 0; i < nsize; i++) {
        noise[i] = (rand() % (range + 1)) + min;
    }
}

void gassian_noise(int16_t *noise, uint64_t nsize)
{
    srand(time(NULL));
    // TODO:
}

void saltpeppr_noise(int16_t *noise, uint64_t nsize)
{
    srand(time(NULL));
    // TODO:
}

void statistics_noise(int16_t *noise, uint64_t nsize, int16_t lower, int16_t upper)
{
    uint64_t i, j, max_level = 0;
    uint16_t *buff;
    uint16_t size = upper - lower + 1;
    buff = (uint16_t *)calloc(size, sizeof(uint16_t));
    if (!buff) {
        printf("[ERROR] : In noise.c, \
            function statistics_noise buff calloc failed.\n");
        exit(1);
    }

    for (i = 0; i < nsize; i++) {
        if (noise[i] >= lower)
            buff[noise[i] - lower]++;
    }

    printf("\x1b[5m |");
    for (i = 0; i < size; i++) {
        printf("-");
        max_level = buff[i] > max_level ? buff[i] : max_level;
    }
    for (int32_t i = max_level; i > 0; i-=500) {
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
    
    free(buff);
}
