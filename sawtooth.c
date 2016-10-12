//
// Created by Kamiya Keisuke on 2016/10/12.
//

#include "header/fileIO.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define F0 1000

int main(){
  PCM pcm;

  pcm.fs = 44100;
  pcm.bit = 16;
  pcm.len = pcm.fs * 1;
  pcm.s = (double *)calloc(pcm.len, sizeof(double));

  int i, n;

  for (i = 1; i <= 44; ++i) {
    for(n = 0 ; n < pcm.len ; n++){
      pcm.s[n] += 1.0 / i * sin(2.0 * M_PI * i * F0 * n / pcm.fs);
    }
  }

  write_wave_mono(&pcm, "sawtooth1.wav");

  free(pcm.s);

  return 0;
}
