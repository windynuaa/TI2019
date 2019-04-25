
#ifndef __FFT_H__
#define __FFT_H__

#define N_WAVE      1024    // full length of Sinewave[]
#define LOG2_N_WAVE 10      // log2(N_WAVE)
/*
  Short test program to accompany fix_fft.c
*/

#define DEBUG 1
#define SPECTRUM 0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FFT_SIZE  512
#define log2FFT   9
#define N         (2 * FFT_SIZE)
#define log2N     (log2FFT + 1)
#define FREQUENCY 5
#define AMPLITUDE 12288

short   FIX_MPY(short a, short b);
int     fix_fft(short fr[], short fi[], short m, short inverse);
int     fix_fftr(short f[], int m, int inverse);

extern const short   Sinewave[N_WAVE-N_WAVE/4];

#endif
