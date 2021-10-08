/**
 * @file    bmp.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.10.07
 * @brief   bit map file format
 */
#include "bmp.h"
#include "matrix_ops.h"

void printHeader(BMP_t *bmp)
{
    printf("\n");
    printf("\t======= \x1b[;31;1mBMP FILE HEADER\x1b[0;m =======\n");
    printf("\t| ID               : %8d |\n", bmp->file_header.ID);
    printf("\t| file_size        : %8d |\n", bmp->file_header.file_size);
    printf("\t| offset           : %8d |\n", bmp->file_header.offset);
    printf("\t===============================\n");
    printf("\t======= \x1b[;31;1mBMP INFO HEADER\x1b[0;m =======\n");
    printf("\t| hdr_size         : %8d |\n", bmp->info_header.hdr_size);
    printf("\t| width            : %8d |\n", bmp->info_header.width);
    printf("\t| height           : %8d |\n", bmp->info_header.height);
    printf("\t| planes           : %8d |\n", bmp->info_header.planes);
    printf("\t| bit_per_pixel    : %8d |\n", bmp->info_header.bits_per_pixel);
    printf("\t| compression      : %8d |\n", bmp->info_header.compression);
    printf("\t| data_size        : %8d |\n", bmp->info_header.data_size);
    printf("\t| H_res            : %8d |\n", bmp->info_header.H_res);
    printf("\t| V_res            : %8d |\n", bmp->info_header.V_res);
    printf("\t| used_colors      : %8d |\n", bmp->info_header.used_colors);
    printf("\t| important_colors : %8d |\n", bmp->info_header.important_colors);
    printf("\t===============================\n\n");
}

void RGBToGrayLevel(BMP_t *bmp)
{
    uint32_t i, j;
    uint32_t pixelSize;

    bmp->file_header.offset = HEADER_SIZE + PALETTE_SIZE;
    bmp->info_header.bits_per_pixel = 8;
    pixelSize = bmp->info_header.width * bmp->info_header.height;
    bmp->info_header.data_size = pixelSize * bmp->info_header.bits_per_pixel/8;
    bmp->file_header.file_size = bmp->file_header.offset + \
                                    bmp->info_header.data_size;

    for (i = 0; i < 256; i++) {
        bmp->palette[(4 * i)]     = i;      // B
        bmp->palette[(4 * i) + 1] = i;      // G
        bmp->palette[(4 * i) + 2] = i;      // R
        bmp->palette[(4 * i) + 3] = 0;
    }
    
    for (i = 0; i < bmp->info_header.height; i++) {
        for (j = 0; j < bmp->info_header.width; j++) {
            bmp->data[i * bmp->info_header.width + j] =                        \
                (bmp->data[3 * (i * bmp->info_header.width + j)    ] * 0.114) +\
                (bmp->data[3 * (i * bmp->info_header.width + j) + 1] * 0.587) +\
                (bmp->data[3 * (i * bmp->info_header.width + j) + 2] * 0.299);
        }
    }

    bmp->data = (uint8_t *)realloc(bmp->data, bmp->info_header.data_size);
    if (!bmp->data) {
        perror("[ERROR] : realloc failed.\n");
        exit(1);
    }
}

void NegativeFilmTransfer_GrayLevel(BMP_t *bmp)
{
    uint32_t i, j;

    if (bmp->info_header.bits_per_pixel != 8) {
        printf("[Warning] : Please check the image foramt.\n");
        printf("In Function NegativeFilmTransfer_GrayLevel();\n");
        return ;
    }
    for (i = 0; i < bmp->info_header.height; i++) {
        for (j = 0; j < bmp->info_header.width; j++) {
            bmp->data[i * bmp->info_header.width + j] = 
                ~bmp->data[i * bmp->info_header.width + j];
        }
    } 
}

void InvertImage_GrayLevel(BMP_t *bmp)
{
    if (bmp->info_header.bits_per_pixel != 8) {
        printf("[Warning] : Please check the image foramt.\n");
        printf("In Function MirrorImage_GrayLevel();\n");
        return ;
    }
    Invert(bmp->data, bmp->info_header.width, bmp->info_header.height);
}

void MirrorImage_GrayLevel(BMP_t *bmp)
{
    if (bmp->info_header.bits_per_pixel != 8) {
        printf("[Warning] : Please check the image foramt.\n");
        printf("In Function MirrorImage_GrayLevel();\n");
        return ;
    }
    Mirror(bmp->data, bmp->info_header.width, bmp->info_header.height);
}

void Rotate90CCW_GrayLevel(BMP_t *bmp)
{
    if (bmp->info_header.bits_per_pixel != 8) {
        printf("[Warning] : Please check the image foramt.\n");
        printf("In Function Rotate90CCW_GrayLevel();\n");
        return ;
    }
    Transpose(bmp->data, bmp->info_header.width, bmp->info_header.height);
    Mirror(bmp->data, bmp->info_header.width, bmp->info_header.height);
}

void Rotate90CW_GrayLevel(BMP_t *bmp)
{
    if (bmp->info_header.bits_per_pixel != 8) {
        printf("[Warning] : Please check the image foramt.\n");
        printf("In Function Rotate90CW_GrayLevel();\n");
        return ;
    }
    Mirror(bmp->data, bmp->info_header.width, bmp->info_header.height);
    Transpose(bmp->data, bmp->info_header.width, bmp->info_header.height);
}

void printGrayHistogram(uint8_t *data, uint32_t dataLength)
{
    uint32_t buff[256] = {0};
    uint32_t max_level = 0;

    for (uint32_t i = 0; i < dataLength; i++) {
        buff[data[i]]++;
    }
    for (uint32_t i = 0; i < 256; i++) {
        printf("%d ", buff[i]);
    }
    printf("\x1b[5m |");
    for (uint32_t i = 0; i < 256; i++) {
        printf("-");
        max_level = buff[i] > max_level ? buff[i] : max_level;
    }
    for (int32_t i = max_level; i >= 0; i-=50) {
        printf("\x1b[5m|\n |\x1b[0;m");
        for (uint32_t j = 0; j < 256; j++) {
            if ((buff[j]) >= i)
                printf("\x1b[;32;34m*\x1b[0;m");
            else
                printf(" ");
        }
    }
    printf("\x1b[5m|\n |");
    for (uint32_t i = 0; i < 256; i++) {
        printf("-");
    }
    printf("|\n\x1b[0;m");
}

void Subsampling_Half(BMP_t *bmp)
{
    uint32_t pixelSize, i, j;

    bmp->info_header.width /= 2;
    bmp->info_header.height /= 2;
    pixelSize = bmp->info_header.width * bmp->info_header.height;
    bmp->info_header.data_size = pixelSize * bmp->info_header.bits_per_pixel/8;
    bmp->file_header.file_size = bmp->file_header.offset + \
                                    bmp->info_header.data_size;

    for (i = 0; i < 2 * pixelSize; i++) {
        bmp->data[i] = (bmp->data[2*i] + bmp->data[2*i+1]) / 2;
    }

    for (i = 0; i < bmp->info_header.height; i++) {
        for (j = 0; j < bmp->info_header.width; j++) {
            bmp->data[i * bmp->info_header.width + j] = \
                (bmp->data[(2*i) * bmp->info_header.width + j] / 2) + \
                (bmp->data[(2*i+1) * bmp->info_header.width + j] / 2);
        }
    }

    bmp->data = (uint8_t *)realloc(bmp->data, bmp->info_header.data_size);
    if (!bmp->data) {
        perror("[ERROR] : realloc failed.\n");
        exit(1);
    }
}



void Upsampling_Double(BMP_t *bmp){

}
