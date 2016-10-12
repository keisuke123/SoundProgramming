#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"

int main(){

  PCM pcm0, pcm1;
  int n;
  
  read_wave_mono(&pcm0, "a.wav");
  pcm1.fs = pcm0.fs;
  pcm1.bit = pcm0.bit;
  pcm1.len = pcm0.len;
  pcm1.s = calloc(pcm1.len, sizeof(double));

  for(n = 0 ; n < pcm1.length ; n++){
    pcm1.s[n] = pcm0.s[n];
  }

  write_wave_mono(&pcm1, "c.wav");
  //wave_write_16bit_mono(&pcm1, "c.wav");
  free(pcm0.s);
  free(pcm1.s);

  return 0;
}
