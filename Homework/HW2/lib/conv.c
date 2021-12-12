/**
 * @file    conv.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.12.01
 * @brief   Image mask filter.
 */

#include "conv.h"

void normdata(Image_t *img, int32_t *buff)
{
    uint64_t i, j;
    for (i = 0; i < img->height * img->width; i++) {
        if (buff[i] < 0)
            img->data[i] = 0;
        else if (buff[i] > 255)
            img->data[i] = 255;
        else
            img->data[i] = buff[i];
    }
    printf("%d %d %d \n", buff[0], buff[1], buff[1234]);
}

void edgeMask(Image_t *img)
{
    uint64_t i, j;
    int32_t *buff;
    int16_t mask[3][3] = { {-1,-1,-1},
                           {-1, 8,-1},
                           {-1,-1,-1}};
    
    buff = (int32_t *)calloc(img->height * img->width, sizeof(int16_t));
    if (!buff) {
        printf("fuck!!!\n");
    }

    // buff[0] =                                       \
    //     3          * img->data[0] +                 \
    //     mask[1][2] * img->data[1] +                 \
    //     mask[2][1] * img->data[img->width] +        \
    //     mask[2][2] * img->data[img->width+1];

    // buff[img->width-1] =                            \
    //     mask[1][0] * img->data[img->width-2] +      \
    //     3          * img->data[img->width-1] +      \
    //     mask[2][0] * img->data[2*img->width-2] +    \
    //     mask[2][1] * img->data[2*img->width-1];

    // buff[(img->height-1)*img->width] = \
    //     mask[0][1] * img->data[(img->height-2)*img->width  ] +  \
    //     mask[0][2] * img->data[(img->height-2)*img->width+1] +  \
    //     3          * img->data[(img->height-1)*img->width  ] +  \
    //     mask[1][2] * img->data[(img->height-1)*img->width+1];

    // buff[(img->height-1)*img->width+img->width-1] = \
    //     mask[0][0] * img->data[(img->height-1)*img->width-1] +  \
    //     mask[0][1] * img->data[(img->height-1)*img->width-2] +  \
    //     mask[1][0] * img->data[(img->height  )*img->width-1] +  \
    //     3          * img->data[(img->height  )*img->width-2];

    // for (i = 1; i < img->height - 1; i++) {
    //     buff[i] = \
    //         mask[1][0] * img->data[i-1] +               \
    //         5          * img->data[ i ] +               \
    //         mask[1][2] * img->data[i+1] +               \
    //         mask[2][0] * img->data[img->width+i-1] +    \
    //         mask[2][1] * img->data[img->width+ i ] +    \
    //         mask[2][2] * img->data[img->width+i+1];
    // }

    // for (i = 1; i < img->height - 1; i++) {
    //     buff[(img->height-1)*img->width+i] = \
    //         mask[0][0] * img->data[(img->height-2)*img->width+i-1] + \
    //         mask[0][1] * img->data[(img->height-2)*img->width+ i ] + \
    //         mask[0][2] * img->data[(img->height-2)*img->width+i+1] + \
    //         mask[1][0] * img->data[(img->height-1)*img->width+i-1] + \
    //         5          * img->data[(img->height-1)*img->width+ i ] + \
    //         mask[1][2] * img->data[(img->height-1)*img->width+i+1];
    // }

    // for (i = 1; i < img->height - 1; i++) {
    //     buff[i*img->width] = \
    //         mask[0][1] * img->data[(i-1)*img->width  ] + \
    //         mask[0][2] * img->data[(i-1)*img->width+1] + \
    //         5          * img->data[( i )*img->width  ] + \
    //         mask[1][2] * img->data[( i )*img->width+1] + \
    //         mask[2][1] * img->data[(i+1)*img->width  ] + \
    //         mask[2][2] * img->data[(i+1)*img->width+1];
    // }

    // for (i = 1; i < img->height - 1; i++) {
    //     buff[i*img->width+img->width-1] = \
    //         mask[0][0] * img->data[(i-1)*img->width-1] + \
    //         mask[0][1] * img->data[(i-1)*img->width  ] + \
    //         mask[1][0] * img->data[( i )*img->width-1] + \
    //         5          * img->data[( i )*img->width  ] + \
    //         mask[2][0] * img->data[(i+1)*img->width-1] + \
    //         mask[2][1] * img->data[(i+1)*img->width  ];
    // }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (i == 0 || i == 9 || j == 0 || j == 9)
                printf(" * ");
            else
                printf("%ld ", 10*i+j);
        }
        printf("\n");
    }

    for (i = 1; i < img->height - 1; i++) {
        for (j = 1; j < img->width - 1; j++) {
                // printf("%d \n", buff[i*img->width+j]);
                buff[i*img->width+j]++;
                // int tmp = i*img->width+j;
                // int tmp2 = (i-1)*(img->width)+j-1;
                // printf("%d %d \n", tmp, tmp2);
                // buff[tmp] += img->data[tmp2];
                // buff[i*img->width+j] += img->data[(i-1)*img->width+ j ];
                // buff[i*img->width+j] += img->data[(i-1)*img->width+j+1];
                // buff[i*img->width+j] += img->data[( i )*img->width+j-1];
                // buff[i*img->width+j] += img->data[( i )*img->width+ j ];
                // buff[i*img->width+j] += img->data[( i )*img->width+j+1];
                // buff[i*img->width+j] += img->data[(i+1)*img->width+j-1];
                // buff[i*img->width+j] += img->data[(i+1)*img->width+ j ];
                // buff[i*img->width+j] += img->data[(i+1)*img->width+j+1];
            // buff[i*img->width+j] =                             \
            //     mask[0][0] * img->data[(i-1)*img->width+j-1] + \
            //     mask[0][1] * img->data[(i-1)*img->width+ j ] + \
            //     mask[0][2] * img->data[(i-1)*img->width+j+1] + \
            //     mask[1][0] * img->data[( i )*img->width+j-1] + \
            //     mask[1][1] * img->data[( i )*img->width+ j ] + \
            //     mask[1][2] * img->data[( i )*img->width+j+1] + \
            //     mask[2][0] * img->data[(i+1)*img->width+j-1] + \
            //     mask[2][1] * img->data[(i+1)*img->width+ j ] + \
            //     mask[2][2] * img->data[(i+1)*img->width+j+1];
        }
    }
    // normdata(img, buff);
    free(buff);
}

// void blurMask(Image_t *img)
// {
        // int16_t mask[3][3] = {  {0.0625, 0.125, 0.0625},
        //                         { 0.125,  0.25,  0.125},
        //                         {0.0625, 0.125, 0.0625}};
// }

// void sharpenMask(Image_t *img)
// {
        // int16_t mask[3][3] = {  { 0, -1,  0},
        //                         {-1,  5, -1},
        //                         { 0, -1,  0}};
// }

// void embossMask(Image_t *img)
// {
        // int16_t mask[3][3] = {  {-2, -1,  0},
        //                         {-1,  1,  1},
        //                         { 0,  1,  2}};
// }

// void bottomSobelMask(Image_t *img)
// {
        // int16_t mask[3][3] = {  {-1, -2, -1},
        //                         { 0,  0,  0},
        //                         { 1,  2,  1}};
// }

// void topSobelMask(Image_t *img)
// {
        // int16_t mask[3][3] = {  { 1,  2,  1},
        //                         { 0,  0,  0},
        //                         {-1, -2, -1}};
// }

// void leftSobelMask(Image_t *img)
// {
        // int16_t mask[3][3] = {  { 1,  0, -1},
        //                         { 2,  0, -2},
        //                         { 1,  0, -1}};
// }

// void rightSobelMask(Image_t *img)
// {
        // int16_t mask[3][3] = {  {-1,  0,  1},
        //                         {-2,  0,  2},
        //                         {-1,  0,  1}};
// }
