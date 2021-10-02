/**
 * @file    matrix_ops.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.02
 * @brief   Basic matrix operations.
 */
#ifndef __MATRIX_OP_H__
#define __MATRIX_OP_H__

#include <stdint.h>

void Transpose(uint8_t *data, uint16_t width, uint16_t height);
void Invert(uint8_t *data, uint16_t width, uint16_t height);
void Mirror(uint8_t *data, uint16_t width, uint16_t height);

#endif /* __MATRIX_OP_H__ */