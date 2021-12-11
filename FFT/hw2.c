/**
 * @file    hw2.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.10
 * @brief   Digital Image Processing Fall2021 @ National Central University.
 *          Homework 2
 */
#include "lib/bmp.h"
#include "lib/fft.h"
#include "lib/noise.h"
#include "lib/filter.h"

int main()
{
    uint64_t i, j;
    uint64_t pixelSize;
    uint64_t dataSize;
    BMP_t bitmap;
    uint8_t *origin_img;

    /**************************************************************************/
    /*                          Read bitmap file.                             */
    /**************************************************************************/
    FILE *fd1;
    fd1 = fopen("./Image/DIPpic1_gray.bmp", "rb");
    if (!fd1) {
        perror("[ERROR] : open DIPpic1_gray.bmp failed.\n");
        exit(1);
    }
    fread(&bitmap, sizeof(uint8_t), HEADER_SIZE, fd1);

    pixelSize = bitmap.info_header.width * bitmap.info_header.height;
    bitmap.info_header.data_size = pixelSize * bitmap.info_header.bits_per_pixel / 8;
    bitmap.data = (uint8_t *)calloc(dataSize, sizeof(uint8_t));
    if (!bitmap.data) {
        printf("[ERROR] : bitmap.data calloc failed.\n");
        exit(1);
    }
    fread(bitmap.palette, sizeof(uint8_t), PALETTE_SIZE, fd1);
    fread(bitmap.data, sizeof(uint8_t), dataSize, fd1);
    fclose(fd1);

    /**************************************************************************/
    /*                      Downsample The Image.                             */
    /**************************************************************************/
    Subsampling_Half(&bitmap);
    dataSize = bitmap.info_header.data_size;
    origin_img = (uint8_t *)calloc(dataSize, sizeof(uint8_t));
    if (!origin_img) {
        printf("[ERROR] : origin_img calloc failed.\n");
        exit(1);
    }
    memcpy(origin_img, bitmap.data, dataSize);
    saveBmpFile(&bitmap, "./Image/_HW_2-1-0_subsample.bmp");

    /**************************************************************************/
    /*                              2-D FFT                                   */
    /**************************************************************************/
    Complex_t *freq_down = (Complex_t *)calloc(dataSize, sizeof(Complex_t));
    if (!freq_down) {
        printf("[ERROR] : freq_down calloc failed.\n");
        exit(1);
    }
    Image_t obj_down;
    obj_down.data = bitmap.data;
    obj_down.freq = freq_down;
    obj_down.height = bitmap.info_header.height;
    obj_down.width  = bitmap.info_header.width;

    imgfft2(&obj_down);
    saveBmpFile(&bitmap, "./Image/_HW_2-1_2-D_FFT.bmp.bmp");
    printf("\n[HW2-1] : Downsample the Image and 2D-FFT.\n");

    /**************************************************************************/
    /*                              2-D IFFT                                  */
    /**************************************************************************/
    imgifft2(&obj_down);
    saveBmpFile(&bitmap, "./Image/_HW_2-1_2-D_IFFT.bmp.bmp");

    printf("\n[HW2-2] : After 2D-FFT and 2D-IFFT.\n");
    printf("\tmse  = %lf   \n",  mse(origin_img, bitmap.data, dataSize));
    printf("\tpsnr = %lf dB\n", psnr(origin_img, bitmap.data, dataSize));

    free(freq_down);
    free(origin_img);
    free(bitmap.data);

    /**************************************************************************/
    /*                          Read bitmap file.                             */
    /**************************************************************************/
    FILE *fd2;
    fd2 = fopen("./Image/DIPpic1_gray.bmp", "rb");
    if (!fd2) {
        perror("[ERROR] : open DIPpic1_gray.bmp failed.\n");
        exit(1);
    }
    fread(&bitmap, sizeof(uint8_t), HEADER_SIZE, fd2);

    pixelSize = bitmap.info_header.width * bitmap.info_header.height;
    dataSize  = pixelSize * bitmap.info_header.bits_per_pixel / 8;
    bitmap.info_header.data_size = dataSize;
    bitmap.data = (uint8_t *)calloc(dataSize, sizeof(uint8_t));
    origin_img  = (uint8_t *)calloc(dataSize, sizeof(uint8_t));
    if (!bitmap.data || !origin_img) {
        printf("[ERROR] : bitmap.data/origin_img calloc failed.\n");
        exit(1);
    }
    fread(bitmap.palette, sizeof(uint8_t), PALETTE_SIZE, fd2);
    fread(bitmap.data, sizeof(uint8_t), dataSize, fd2);
    memcpy(origin_img, bitmap.data, dataSize);
    fclose(fd2);

    /**************************************************************************/
    /*                            Uniform noise                               */
    /**************************************************************************/
    int16_t *noise;
    noise = (int16_t *)calloc(dataSize, sizeof(int16_t));
    if (!noise) {
        printf("[ERROR] : noise calloc failed.\n");
        exit(1);
    }

    uniform_noise(noise, dataSize, -20, 20);
    // statistics_noise(noise, dataSize, -20, 20);

    for (i = 0; i < dataSize; i++) {
        if ((int16_t)bitmap.data[i] + noise[i] < 0)
            bitmap.data[i] = 0;
        else if ((int16_t)bitmap.data[i] + noise[i] > 255)
            bitmap.data[i] = 255;
        else
            bitmap.data[i] += noise[i];
    }
    saveBmpFile(&bitmap, "./Image/_HW_2-3_uniform_noise.bmp");

    printf("\n[HW2-3] : After Adding Uniform Noise to the Image.\n");
    printf("\tmse  = %lf   \n",  mse(origin_img, bitmap.data, dataSize));
    printf("\tpsnr = %lf dB\n", psnr(origin_img, bitmap.data, dataSize));

    /**************************************************************************/
    /*                              2-D FFT                                   */
    /**************************************************************************/
    Complex_t *freq = (Complex_t *)calloc(dataSize, sizeof(Complex_t));
    Image_t obj;
    obj.data = bitmap.data;
    obj.freq = freq;
    obj.height = bitmap.info_header.height;
    obj.width  = bitmap.info_header.width;

    imgfft2(&obj);
    saveBmpFile(&bitmap, "./Image/_HW_2-3-1_fft.bmp");

    /**************************************************************************/
    /*                            Low Pass Filter                             */
    /**************************************************************************/
    lowpass(&obj, 150);
    saveBmpFile(&bitmap, "./Image/_HW_2-4_lpf.bmp");
    printf("\n[HW2-4] : Ideal Low Pass Filter.\n");

    /**************************************************************************/
    /*                              2-D IFFT                                  */
    /**************************************************************************/
    imgifft2(&obj);
    saveBmpFile(&bitmap, "./Image/_HW_2-5_ifft.bmp");

    printf("\n[HW2-5] : After Processing by Ideal Low Pass Filter.\n");
    printf("\tmse  = %lf   \n",  mse(origin_img, bitmap.data, dataSize));
    printf("\tpsnr = %lf dB\n", psnr(origin_img, bitmap.data, dataSize));
    printf("\n");

    free(freq);
    free(origin_img);
    free(bitmap.data);
    return 0;
}
