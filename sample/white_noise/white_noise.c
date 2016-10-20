//
// Created by Kamiya Keisuke on 2016/10/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../../header/fileIO.h"
#include "../../header/waves.h"

int main(){
  PCM pcm;
  int i, n;
  double ak, omg_k, d_omg;

  // 量子化ビット数
  pcm.bit = 16;

  // サンプリング周波数
  pcm.fs = 44100;

  // 長さ
  pcm.len = pcm.fs * 2;

  printf("len : %d\n", pcm.len);

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
  write_wave_mono(&pcm, "noise.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}