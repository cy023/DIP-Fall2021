/**
 * @file    test_32bit.c
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
    fd = fopen("./Image/Earth_rgba.bmp", "rb");
    if (!fd) {
        perror("[ERROR] : open Earth.bmp failed.\n");
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
    for (i = 0; i < bitmap.info_header.height; i++) {
        for (j = 0; j < bitmap.info_header.width; j++) {
            if (i < 3000 && j < 3000) {
                bitmap.data[4 * i * bitmap.info_header.width + 4 * j] = 0;
                bitmap.data[4 * i * bitmap.info_header.width + 4 * j + 1] = 0;
                bitmap.data[4 * i * bitmap.info_header.width + 4 * j + 2] = 0;
                bitmap.data[4 * i * bitmap.info_header.width + 4 * j + 3] = 0;
            }
        }
    }
    saveBmpFile(&bitmap, "./Image/_32test.bmp");

    free(bitmap.data);
    return 0;
}
