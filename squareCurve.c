//
// Created by Kamiya Keisuke on 2016/10/12.
//

#include "header/fileIO.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define F0 500

int main(){
  PCM pcm;
  int i, n;

  pcm.fs = 44100;
  pcm.bit = 16;
  pcm.len = pcm.fs * 1;
  pcm.s = (double *)calloc(pcm.len, sizeof(double));

  for(i = 1; i <= 44 ; i+=2){
    for (int n = 0; n < pcm.len ; ++n) {
      pcm.s[n] += 1.0 / i * sin(2.0 * M_PI * i * F0 * n / pcm.fs);
    }
  }

  for(i = 0 ; i < pcm.len ; i++) pcm.s[i] *= 0.1;

  write_wave_mono(&pcm, "squareCurve.wav");

  free(pcm.s);
  return 0;
}