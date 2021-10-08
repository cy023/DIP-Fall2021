/**
 * @file    main.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.07
 * @brief   Digital Image Processing Fall2021 in National Central University.
 *          Homework 1
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib/bmp.h"

void downsample_along_row(BMP_t *bmp);
void recover_downsample_along_row(BMP_t *bmp);
void saveGrayLevel_bmp(BMP_t *bmp, const char *path);

int main()
{
    uint16_t i, j;
    uint64_t pixelSize;
    BMP_t bitmap;

    /**************************************************************************/
    /*             Read original bitmap file.                                 */
    /**************************************************************************/
    FILE *fd;
    fd = fopen("./Image/building.bmp", "rb");
    if (!fd) {
        perror("[ERROR] : open building.bmp failed.\n");
        exit(1);
    }
    fread(&bitmap, sizeof(uint8_t), HEADER_SIZE, fd);
    
    pixelSize = bitmap.info_header.width * bitmap.info_header.height;
    bitmap.info_header.data_size = pixelSize * bitmap.info_header.bits_per_pixel/8;
    bitmap.data = (uint8_t *)calloc(bitmap.info_header.data_size, sizeof(uint8_t));
    fread(bitmap.data, sizeof(uint8_t), bitmap.info_header.data_size, fd);
    fclose(fd);

    printHeader(&bitmap);

    /**************************************************************************/
    /*             Transfer RGB bitmap file to Gray Level.                    */
    /**************************************************************************/
    RGBToGrayLevel(&bitmap);
    printHeader(&bitmap);
    printGrayHistogram(bitmap.data, bitmap.info_header.data_size);
    saveGrayLevel_bmp(&bitmap, "./Image/gray.bmp");

    /**************************************************************************/
    /*             Downsampling bitmap file and merge.                        */
    /**************************************************************************/
    downsample_along_row(&bitmap);
    printGrayHistogram(bitmap.data, bitmap.info_header.data_size);
    saveGrayLevel_bmp(&bitmap, "./Image/downsample_merge.bmp");

    free(bitmap.data);
    return 0;
}

void saveGrayLevel_bmp(BMP_t *bmp, const char *path)
{
    FILE *fd;
    fd = fopen(path, "wb");
    if (!fd) {
        printf("[ERROR] : open %s bmp failed.\n", path);
        exit(1);
    }
    fwrite(bmp, sizeof(uint8_t), HEADER_SIZE + PALETTE_SIZE, fd);
    fwrite(bmp->data, sizeof(uint8_t), bmp->info_header.data_size, fd);
    fclose(fd);
}

void downsample_along_row(BMP_t *bmp)
{
    uint32_t i, j;
    uint32_t halflen = bmp->info_header.data_size / 2;

    uint8_t *odd = (uint8_t *)malloc(halflen * sizeof(uint8_t));
    uint8_t *even = (uint8_t *)malloc(halflen * sizeof(uint8_t));
    
    for (i = 0; i < bmp->info_header.height; i++) {
        for (j = 0; j < bmp->info_header.width; j++) {
            if (!(i % 2)) {
                even[(i / 2) * bmp->info_header.width + j] = 
                    bmp->data[i * bmp->info_header.width + j];
            } else {
                odd[(i / 2) * bmp->info_header.width + j] = 
                    bmp->data[i * bmp->info_header.width + j];
            }
        }
    }
    for (i = 0; i < bmp->info_header.height; i++) {
        for (j = 0; j < bmp->info_header.width; j++) {
            if (i < (bmp->info_header.height / 2)) {
                bmp->data[i * bmp->info_header.width + j] = 
                    odd[i * bmp->info_header.width + j];
            } else {
                bmp->data[i * bmp->info_header.width + j] = 
                    even[(i - bmp->info_header.height / 2) * bmp->info_header.width + j];
            }
        }
    }
    free(odd);
    free(even);
}

void recover_downsample_along_row(BMP_t *bmp)
{
    uint32_t i, j;
    uint32_t halflen = bmp->info_header.data_size / 2;
    uint8_t *odd = (uint8_t *)malloc(halflen * sizeof(uint8_t));
    uint8_t *even = (uint8_t *)malloc(halflen * sizeof(uint8_t));
    
    for (i = 0; i < bmp->info_header.height; i++) {
        for (j = 0; j < bmp->info_header.width; j++) {
            if (i < (bmp->info_header.height / 2)) {
                odd[i * bmp->info_header.width + j] = 
                    bmp->data[i * bmp->info_header.width + j];
            } else {
                even[(i - bmp->info_header.height / 2) * bmp->info_header.width + j] = 
                    bmp->data[i * bmp->info_header.width + j];
            }
        }
    }
    for (i = 0; i < bmp->info_header.height; i++) {
        for (j = 0; j < bmp->info_header.width; j++) {
            if (!(i % 2)) {
                bmp->data[i * bmp->info_header.width + j] = 
                    even[(i / 2) * bmp->info_header.width + j];
            } else {
                bmp->data[i * bmp->info_header.width + j] = 
                    odd[(i / 2) * bmp->info_header.width + j];
            }
        }
    }
    free(odd);
    free(even);
}
