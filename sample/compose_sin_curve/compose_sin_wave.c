//
// Created by Kamiya Keisuke on 2016/10/13.
//

#include <stdio.h>
#include <stdlib.h>
#include "../../header/fileIO.h"
#include "../../header/waves.h"

#define SEC 1

int main(){
  PCM pcm;

  // 量子化ビット数
  pcm.bit = 16;

  // サンプリング周波数
  pcm.fs = 44100;

  // 長さ
  pcm.len = pcm.fs * SEC;

  printf("len : %d\n", pcm.len);

  // 音声データ領域をcallocで確保
  if((pcm.s = (double *)calloc(pcm.len, sizeof(double))) == NULL){
    fprintf(stderr, "Error : ");
    perror(NULL);
  }

  // 3つのサイン波を合成(C4:261.63 D4:293.66 E4:329.63)
  sin_wave(&pcm, 0.1, C4, 0, pcm.fs);
  sin_wave(&pcm, 0.1, D4, 0, pcm.fs);
  sin_wave(&pcm, 0.1, E4, 0, pcm.fs);

  // 書き出し
  write_wave_mono(&pcm, "compose_sin.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}