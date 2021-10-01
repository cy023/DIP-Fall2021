/**
 * @file    main.h
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.01
 * @brief   Digital Image Processing Fall2021 in National Central University.
 *          Homework 1
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib/bmp.h"

int main()
{
    uint16_t i, j;
    BMP_t bitmap;
    
    FILE *fd1;
    fd1 = fopen("./Image/lena.bmp", "rb");
    if (!fd1) {
        perror("[ERROR] : open lena.bmp failed.\n");
        exit(1);
    }
    fread(&bitmap, sizeof(uint8_t), HEADER_SIZE, fd1);
    
    bitmap.dataLength = 3 * bitmap.info_header.width * bitmap.info_header.height;
    bitmap.data = (uint8_t *)calloc(bitmap.dataLength, sizeof(uint8_t));
    fread(bitmap.data, sizeof(uint8_t), bitmap.dataLength, fd1);

    printHeader(&bitmap);
    RGBToGrayLevel(&bitmap);
    printHeader(&bitmap);

    FILE *fd2;
    fd2 = fopen("./Image/gray.bmp", "wb");
    if (!fd2) {
        perror("[ERROR] : open gray.bmp failed.\n");
        exit(1);
    }
    fwrite(&bitmap, sizeof(uint8_t), HEADER_SIZE + PALETTE_SIZE, fd2);
    fwrite(bitmap.data, sizeof(uint8_t), bitmap.dataLength, fd2);

    printGrayHistogram(bitmap.data, bitmap.dataLength);

    NegativeFilmTransfer(&bitmap);

    printGrayHistogram(bitmap.data, bitmap.dataLength);

    FILE *fd3;
    fd2 = fopen("./Image/negfilm.bmp", "wb");
    if (!fd2) {
        perror("[ERROR] : open gray.bmp failed.\n");
        exit(1);
    }
    fwrite(&bitmap, sizeof(uint8_t), HEADER_SIZE + PALETTE_SIZE, fd2);
    fwrite(bitmap.data, sizeof(uint8_t), bitmap.dataLength, fd2);

    free(bitmap.data);
    fclose(fd1);
    fclose(fd2);
    return 0;
}
