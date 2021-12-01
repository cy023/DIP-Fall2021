/**
 * @file    test_mov.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.24
 * @brief   Digital Image Processing Fall2021 @ National Central University.
 *          Practice
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/bmp.h"

int main()
{
    uint16_t i, j;
    uint64_t pixelSize;
    BMP_t bitmap;

    /**************************************************************************/
    /*             Read original bitmap file.                                 */
    /**************************************************************************/
    FILE *fd;
    fd = fopen("./Image/Building.bmp", "rb");
    if (!fd) {
        perror("[ERROR] : open Building.bmp failed.\n");
        exit(1);
    }
    fread(&bitmap, sizeof(uint8_t), HEADER_SIZE, fd);
    
    pixelSize = bitmap.info_header.width * bitmap.info_header.height;
    bitmap.info_header.data_size = pixelSize * bitmap.info_header.bits_per_pixel/8;
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
    printf("Gray-Level Image.\n");
    printHeader(&bitmap);
    saveBmpFile(&bitmap, "./Image/_gray.bmp");

    /**************************************************************************/
    /*             Rotate Gray Level bitmap file.                             */
    /**************************************************************************/
    Rotate90CW_GrayLevel(&bitmap);
    saveBmpFile(&bitmap, "./Image/_rotCW90.bmp");
    Rotate90CCW_GrayLevel(&bitmap); // Recover

    Rotate90CCW_GrayLevel(&bitmap);
    saveBmpFile(&bitmap, "./Image/_rotCCW90.bmp");
    Rotate90CW_GrayLevel(&bitmap); // Recover

    /**************************************************************************/
    /*             Invert/Mirror Gray Level bitmap file.                      */
    /**************************************************************************/
    InvertImage_GrayLevel(&bitmap);
    saveBmpFile(&bitmap, "./Image/_invert.bmp");
    InvertImage_GrayLevel(&bitmap); // Recover

    MirrorImage_GrayLevel(&bitmap);
    saveBmpFile(&bitmap, "./Image/_mirror.bmp");
    MirrorImage_GrayLevel(&bitmap); // Recover

    free(bitmap.data);
    return 0;
}
