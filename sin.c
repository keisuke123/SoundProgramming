//
// Created by Kamiya Keisuke on 2016/10/11.
//


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "header/fileIO.h"

// A  : 振幅
// F0 : 基本周波数
#define A 0.1
#define F0 500

int main(){
  PCM pcm;
  int n;

  pcm.bit = 16;
  pcm.fs = 44100;
  pcm.len = pcm.fs * 1;
  pcm.s = (double *)calloc(pcm.len, sizeof(double));

  for (n = 0; n < pcm.len; ++n) {
    pcm.s[n] = A * sin(2 * M_PI * F0 * n / pcm.fs);
  }

  write_wave_mono(&pcm, "sin.wav");

  return 0;
}
