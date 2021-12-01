/**
 * @file    test_img2txt.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.2
 * @brief   Digital Image Processing Fall2021 @ National Central University.
 *          Homework 2
 */
#include "../lib/bmp.h"
#include "../lib/fft.h"

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
    fread(&bitmap, sizeof(uint8_t), HEADER_SIZE, fd);

    pixelSize = bitmap.info_header.width * bitmap.info_header.height;
    bitmap.info_header.data_size = pixelSize * bitmap.info_header.bits_per_pixel / 8;
    bitmap.data = (uint8_t *)calloc(bitmap.info_header.data_size, sizeof(uint8_t));
    fread(bitmap.palette, sizeof(uint8_t), PALETTE_SIZE, fd);
    fread(bitmap.data, sizeof(uint8_t), bitmap.info_header.data_size, fd);
    fclose(fd);

    /**************************************************************************/
    /*                          Subsample Image.                              */
    /**************************************************************************/
    Subsampling_Half(&bitmap);
    saveBmpFile(&bitmap, "./Image/_subsample.bmp");

    /**************************************************************************/
    /*                          Image to Text.                                */
    /**************************************************************************/
    FILE *fd2;
    fd2 = fopen("./Image/_subsample.txt", "w");
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            fprintf(fd2, "%d ", *(bitmap.data + 256 * i + j));
        }
        fprintf(fd2, "\n");
    }
    fclose(fd2);

    free(bitmap.data);
    return 0;
}
