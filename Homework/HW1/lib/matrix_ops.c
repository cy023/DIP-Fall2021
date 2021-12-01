/**
 * @file    matrix_ops.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.24
 * @brief   Basic matrix operations (for square matrix).
 */
#include "matrix_ops.h"

// TODO: m x n size matrix operation.
// Note: The Image origin locates at bottom-left.
void Transpose(uint8_t *data, uint32_t width, uint32_t height)
{
    uint16_t i, j;
    for (i = 0; i < height; i++) {
        for (j = i + 1; j < width; j++) {
            data[height * i + j] ^= data[height * j + i];
            data[height * j + i] ^= data[height * i + j];
            data[height * i + j] ^= data[height * j + i];
        }
    }
}

void Invert(uint8_t *data, uint32_t width, uint32_t height)
{
    uint16_t i, j;
    for (i = 0; i < height / 2; i++) {
        for (j = 0; j < width; j++) {
            data[height * i + j] ^= data[height * (height - 1 - i) + j];
            data[height * (height - 1 - i) + j] ^= data[height * i + j];
            data[height * i + j] ^= data[height * (height - 1 - i) + j];
        }
    }
}

void Mirror(uint8_t *data, uint32_t width, uint32_t height)
{
    uint16_t i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width / 2; j++) {
            data[height * i + j] ^= data[height * i + (width - 1 - j)];
            data[height * i + (width - 1 - j)] ^= data[height * i + j];
            data[height * i + j] ^= data[height * i + (width - 1 - j)];
        }
    }
}
