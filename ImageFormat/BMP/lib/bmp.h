/**
 * @file    bmp.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.07
 * @brief   bit map file format
 */
#ifndef __BMP_H__
#define __BMP_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define FILE_HEADER_SIZE    sizeof(BMP_FILE_HEADER_t)
#define INFO_HEADER_SIZE    sizeof(BMP_INFO_HEADER_t)
#define HEADER_SIZE         FILE_HEADER_SIZE + INFO_HEADER_SIZE
#define PALETTE_SIZE        (4 * (1 << 8))

#pragma pack(1)
typedef struct {
    uint16_t ID;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t offset;
} BMP_FILE_HEADER_t;
#pragma pack()

#pragma pack(1)
typedef struct {
    uint32_t hdr_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t data_size;
    uint32_t H_res;
    uint32_t V_res;
    uint32_t used_colors;
    uint32_t important_colors;
} BMP_INFO_HEADER_t;
#pragma pack()

typedef struct {
    BMP_FILE_HEADER_t file_header;
    BMP_INFO_HEADER_t info_header;
    uint8_t palette[PALETTE_SIZE];
    uint8_t *data;
} BMP_t;

void printHeader(BMP_t *bmp);
void RGBToGrayLevel(BMP_t *bmp);
void NegativeFilmTransfer_GrayLevel(BMP_t *bmp);
void InvertImage_GrayLevel(BMP_t *bmp);
void MirrorImage_GrayLevel(BMP_t *bmp);
void Rotate90CCW_GrayLevel(BMP_t *bmp);
void Rotate90CW_GrayLevel(BMP_t *bmp);
void printGrayHistogram(uint8_t *data, uint32_t dataLength);

void Subsampling_Half(BMP_t *bmp);
void Upsampling_Double(BMP_t *bmp);

#endif /* __BMP_H__ */