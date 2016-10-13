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
    pcm->s[n] = gain * sin(2 * M_PI * f0 * n / pcm->fs);
  }

  return;
}
