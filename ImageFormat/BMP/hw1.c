/**
 * @file    hw1.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.24
 * @brief   Digital Image Processing Fall2021 @ National Central University.
 *          Homework 1
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "lib/bmp.h"

void subsample_along_row(BMP_t *bmp);

int main()
{
    uint16_t i, j;
    uint64_t pixelSize;
    BMP_t bitmap;

    /**************************************************************************/
    /*             Read original bitmap file.                                 */
    /**************************************************************************/
    FILE *fd;
    fd = fopen("./Image/rgb24.bmp", "rb");
    if (!fd) {
        perror("[ERROR] : open Building.bmp failed.\n");
        exit(1);
    }
    fread(&bitmap, sizeof(uint8_t), HEADER_SIZE, fd);

    pixelSize = bitmap.info_header.width * bitmap.info_header.height;
    bitmap.info_header.data_size = pixelSize * bitmap.info_header.bits_per_pixel / 8;
    bitmap.data = (uint8_t *)calloc(bitmap.info_header.data_size, sizeof(uint8_t));
    if (!bitmap.data) {
        printf("[ERROR] : bitmap.data calloc failed.\n");
        exit(1);
    }

    fread(bitmap.data, sizeof(uint8_t), bitmap.info_header.data_size, fd);
    fclose(fd);

    printf("Origin Image.\n");
    printHeader(&bitmap);

    /**************************************************************************/
    /*             Transfer RGB bitmap file to Gray Level.                    */
    /**************************************************************************/
    RGBToGrayLevel(&bitmap);
    printf("Gray Level Image.\n");
    printHeader(&bitmap);
    printGrayHistogram(bitmap.data, bitmap.info_header.data_size, "./script/gray.txt");
    saveBmpFile(&bitmap, "./Image/_graylevel.bmp");

    /**************************************************************************/
    /*             Downsampling bitmap file and merge.                        */
    /**************************************************************************/
    subsample_along_row(&bitmap);
    printGrayHistogram(bitmap.data, bitmap.info_header.data_size, "./script/subsample.txt");
    saveBmpFile(&bitmap, "./Image/_downsample_merge.bmp");

    free(bitmap.data);
    return 0;
}

void subsample_along_row(BMP_t *bmp)
{
    uint32_t i, j;
    uint32_t halflen = bmp->info_header.data_size / 2;
    uint32_t rowsize = bmp->info_header.width * (bmp->info_header.bits_per_pixel / 8);

    uint8_t *odd = (uint8_t *)malloc(halflen * sizeof(uint8_t));
    
    if (bmp->info_header.width % 4) {
        for (i = 0; i < bmp->info_header.height - 1; i++) {
            if ((i % 2)) {
                memcpy(&(odd[((i-1)/2) * rowsize + ((i-1)/2)]), &(bmp->data[i * rowsize + i]), rowsize);
            } else {
                memcpy(&(bmp->data[(i/2) * rowsize + (i/2)]), &(bmp->data[i * rowsize + i]), rowsize);
            }
        }
        i = bmp->info_header.height / 2 - 1;
        memcpy(&(bmp->data[i * rowsize + i]), odd, halflen);
        free(odd);
    } else {
        for (i = 1; i < bmp->info_header.height; i++) {
            if ((i % 2)) {
                memcpy(&(odd[((i-1)/2) * rowsize]), &(bmp->data[i * rowsize]), rowsize);
            } else {
                memcpy(&(bmp->data[(i/2) * rowsize]), &(bmp->data[i * rowsize]), rowsize);
            }
        }
        memcpy(&(bmp->data[halflen]), odd, halflen);
        free(odd);
    }

}
