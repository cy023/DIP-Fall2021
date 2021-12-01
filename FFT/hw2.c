/**
 * @file    hw2.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.2
 * @brief   Digital Image Processing Fall2021 @ National Central University.
 *          Homework 2
 */
#include "lib/bmp.h"
#include "lib/fft.h"

int main()
{
    uint16_t i, j;
    uint64_t pixelSize;
    BMP_t bitmap;

    /**************************************************************************/
    /*                          Read bitmap file.                             */
    /**************************************************************************/
    FILE *fd;
    fd = fopen("./Image/DIPpic1_gray.bmp", "rb");
    if (!fd) {
        perror("[ERROR] : open DIPpic1_gray.bmp failed.\n");
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
    fread(bitmap.palette, sizeof(uint8_t), PALETTE_SIZE, fd);
    fread(bitmap.data, sizeof(uint8_t), bitmap.info_header.data_size, fd);
    fclose(fd);

    Subsampling_Half(&bitmap);
    saveBmpFile(&bitmap, "./Image/_subsample.bmp");

    free(bitmap.data);
    return 0;
}
