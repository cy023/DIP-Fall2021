/**
 * @file    test_subsample.c
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
    /*             Subsampling bitmap file.                                   */
    /**************************************************************************/
    Subsampling_Half(&bitmap);
    saveBmpFile(&bitmap, "./Image/_subsample256.bmp");

    Subsampling_Half(&bitmap);
    saveBmpFile(&bitmap, "./Image/_subsample128.bmp");

    Subsampling_Half(&bitmap);
    saveBmpFile(&bitmap, "./Image/_subsample64.bmp");

    Subsampling_Half(&bitmap);
    saveBmpFile(&bitmap, "./Image/_subsample32.bmp");

    free(bitmap.data);
    return 0;
}
