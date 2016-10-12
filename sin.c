//
// Created by Kamiya Keisuke on 2016/10/11.
//


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "header/wave.h"
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

  for (int n = 0; n < pcm.len; ++n) {
    pcm.s[n] = A * sin(2 * M_PI * F0 * n / pcm.fs);
  }

  write_wave_mono(&pcm, "sin.wav");

//  MONO_PCM pcm;
//  int n;
//
//  pcm.bits = 16;
//  pcm.fs = 44100;
//  pcm.length = pcm.fs * 1;
//  pcm.s = (double *)calloc(pcm.length, sizeof(double));
//
//  for (int n = 0; n < pcm.length; ++n) {
//    pcm.s[n] = A * sin(2 * M_PI * F0 * n / pcm.fs);
//  }
//
//  wave_write_16bit_mono(&pcm, "sin2.wav");

}