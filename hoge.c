//
// Created by Kamiya Keisuke on 2016/10/13.
//

#include <stdio.h>
#include <stdlib.h>
#include "header/fileIO.h"
#include "header/waves.h"

int main(){
  PCM pcm;

  pcm.bit = 16;
  pcm.fs = 44100;
  pcm.len = pcm.fs * 1;
  pcm.s = (double *)calloc(pcm.len, sizeof(double));

  sin_curve(&pcm, 0.1, 500.0);

  write_wave_mono(&pcm, "sin.wav");

  free(pcm.s);
  return 0;
}