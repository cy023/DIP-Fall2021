/**
 * @file    main.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.01
 * @brief   Digital Image Processing Fall2021 in National Central University.
 *          Practice
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib/bmp.h"

void saveGrayLevel_bmp(BMP_t *bmp, const char *path);

int main()
{
    uint16_t i, j;
    uint32_t pixelSize;
    BMP_t bitmap;

    /**************************************************************************/
    /*             Read original bitmap file.                                 */
    /**************************************************************************/
    FILE *fd;
    fd = fopen("./Image/lena.bmp", "rb");
    if (!fd) {
        perror("[ERROR] : open lena.bmp failed.\n");
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
    /*             Transfer Gray Level bitmap file to negative film.          */
    /**************************************************************************/
    NegativeFilmTransfer_GrayLevel(&bitmap);
    printGrayHistogram(bitmap.data, bitmap.info_header.data_size);
    saveGrayLevel_bmp(&bitmap, "./Image/negfilm.bmp");
    NegativeFilmTransfer_GrayLevel(&bitmap); // Recover
    
    /**************************************************************************/
    /*             Mirror/Invert Gray Level bitmap file.                      */
    /**************************************************************************/
    MirrorImage_GrayLevel(&bitmap);
    saveGrayLevel_bmp(&bitmap, "./Image/mirror.bmp");
    MirrorImage_GrayLevel(&bitmap); // Recover

    InvertImage_GrayLevel(&bitmap);
    saveGrayLevel_bmp(&bitmap, "./Image/invert.bmp");
    InvertImage_GrayLevel(&bitmap); // Recover

    /**************************************************************************/
    /*             Rotate Gray Level bitmap file.                             */
    /**************************************************************************/
    Rotate90CW_GrayLevel(&bitmap);
    saveGrayLevel_bmp(&bitmap, "./Image/rotCW90.bmp");
    Rotate90CCW_GrayLevel(&bitmap); // Recover

    Rotate90CCW_GrayLevel(&bitmap);
    saveGrayLevel_bmp(&bitmap, "./Image/rotCCW90.bmp");
    Rotate90CW_GrayLevel(&bitmap); // Recover

    /**************************************************************************/
    /*             Subsampling bitmap file.                                   */
    /**************************************************************************/
    Subsampling_Half(&bitmap);
    saveGrayLevel_bmp(&bitmap, "./Image/subsample256.bmp");

    Subsampling_Half(&bitmap);
    saveGrayLevel_bmp(&bitmap, "./Image/subsample128.bmp");

    Subsampling_Half(&bitmap);
    saveGrayLevel_bmp(&bitmap, "./Image/subsample64.bmp");

    Subsampling_Half(&bitmap);
    saveGrayLevel_bmp(&bitmap, "./Image/subsample32.bmp");

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
