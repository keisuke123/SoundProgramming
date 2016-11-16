//
// Created by Kamiya Keisuke on 2016/10/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <waves.h>
#include <fileIO.h>

int main(){
  PCM pcm;
  int n;

  read_wave_mono(&pcm, "sin(500Hz).wav");

  for (n = 0; n < pcm.len; ++n) {
    printf("pcm.s[%d]:%f\n", n, pcm.s[n]);
  }

  free(pcm.s);

  return 0;
}