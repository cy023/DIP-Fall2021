/**
 * @file    test_graylevel_tf.c
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
    /*             Read original gray level bitmap file.                      */
    /**************************************************************************/
    FILE *fd;
    fd = fopen("./Image/ClaudeShannon.bmp", "rb");
    if (!fd) {
        perror("[ERROR] : open ClaudeShannon.bmp failed.\n");
        exit(1);
    }
    fread(&bitmap, sizeof(uint8_t), HEADER_SIZE + PALETTE_SIZE, fd);
    
    pixelSize = bitmap.info_header.width * bitmap.info_header.height;
    bitmap.info_header.data_size = pixelSize * bitmap.info_header.bits_per_pixel/8;
    bitmap.data = (uint8_t *)calloc(bitmap.info_header.data_size, sizeof(uint8_t));
    if (!bitmap.data) {
        printf("[ERROR] : bitmap.data calloc failed.\n");
        exit(1);
    }
    
    fread(bitmap.data, sizeof(uint8_t), bitmap.info_header.data_size, fd);
    fclose(fd);

    /**************************************************************************/
    /*           Transfer Gray Level bitmap file to negative film.            */
    /**************************************************************************/
    NegativeFilmTransfer_GrayLevel(&bitmap);
    saveBmpFile(&bitmap, "./Image/_negfilm.bmp");

    free(bitmap.data);
    return 0;
}
