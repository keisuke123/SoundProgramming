//
// Created by Kamiya Keisuke on 2016/10/13.
//

#include <stdio.h>
#include <math.h>
#include "fileIO.h"
#include "waves.h"

void sin_curve(PCM *pcm, double gain, double f0){
  int n;

  for (n = 0; n < pcm->len; ++n) {
    pcm->s[n] += gain * sin(2 * M_PI * f0 * n / pcm->fs);
  }

  return;
}

void square_curve(PCM *pcm, double gain, double f0) {
  int i, n;
  
  for(i = 1; i <= 44 ; i+=2){
    for (int n = 0; n < pcm->len ; ++n) {
      pcm->s[n] += 1.0 / i * sin(2.0 * M_PI * i * F0 * n / pcm->fs);
    }
  }
}

void triangle_curve(PCM *pcm, double gain, double f0) {
  int i, n;

  for(i = 1; i <= 44 ; i+=2){
    for (int n = 0; n < pcm->len ; ++n) {
      pcm->s[n] += 1.0 / i / i * sin(i * M_PI / 2 ) * sin(2.0 * M_PI * i * F0 * n / pcm->fs);
    }
  }
}

void sawtooth_curve(PCM *pcm, double gain, double f0) {
  int i, n;
  
  for (i = 1; i <= 44; ++i) {
    for(n = 0 ; n < pcm->len ; n++){
      pcm->s[n] += 1.0 / i * sin(2.0 * M_PI * i * F0 * n / pcm->fs);
    }
  }
}