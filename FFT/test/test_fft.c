/**
 * @file    test_fft.c
 * @author  cy023 (cyyang@g.ncu.edu.tw)
 * @date    2021.11.23
 * @brief   Digital Image Processing Fall2021 @ National Central University.
 *          Homework 2
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/fft.h"

int main()
{
    Complex_t test[8];
    Complex_t tm[8];

    // test[0].re = 4;
    // test[1].re = 2;
    // test[2].re = 1;
    // test[3].re = -3;
    // test[4].re = 1.5;
    // test[5].re = 0;
    // test[6].re = 0;
    // test[7].re = 0;
    for (int i = 0; i < 8; i++) {
        test[i].re = cos(2*PI*i/(double)8) + 5;
        // test[i].im = 0;
        test[i].im = sin(2*PI*i/(double)8);
    }

    printf("===== DATA =====\n");
    for (int i = 0; i < 8; i++) {
        printf("test[%d] : %lf + %lf i\n", i, test[i].re, test[i].im);
    }

    fft(8, test, tm);
    printf("===== FFT =====\n");
    for (int i = 0; i < 8; i++) {
        printf("test[%d] : %lf + %lf i\n", i, test[i].re, test[i].im);
    }

    ifft(8, test, tm);
    printf("===== IFFT =====\n");
    for (int i = 0; i < 8; i++) {
        printf("test[%d] : %lf + %lf i\n", i, test[i].re, test[i].im);
    }

    return 0;
}
