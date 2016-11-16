//
// Created by Kamiya Keisuke on 2016/10/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fileIO.h>
#include <waves.h>

#define SEC 1

int main(){
  PCM pcm;
  int i, n;

  init_PCM(&pcm, 16, 44100, SEC);

  // 音声データ領域をcallocで確保
  if((pcm.s = (double *)calloc(pcm.len, sizeof(double))) == NULL){
    fprintf(stderr, "Error : ");
    perror(NULL);
  }

  srand((unsigned)time(NULL));

  double phi;

  for(i = 1 ; i <= pcm.fs/2 ; i++){

    phi = (double)rand() / RAND_MAX * 2.0 * M_PI;

    for(n = 0 ; n <= pcm.len; n++){
      pcm.s[n] += 0.001 * sin(2 * M_PI * i * n / pcm.fs + phi);
    }

  }

  // 白色雑音を生成する関数できました.
  // white_noise(&pcm, 0.001, 0, pcm.len);

  // 書き出し
  write_wave_mono(pcm, "noise.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}