//
// Created by Kamiya Keisuke on 2016/10/13.
//

#include <stdio.h>
#include <stdlib.h>
#include "../../header/fileIO.h"
#include "../../header/waves.h"

int main(){
  PCM pcm;

  // 量子化ビット数
  pcm.bit = 16;

  // サンプリング周波数
  pcm.fs = 44100;

  // 長さ
  pcm.len = pcm.fs * 3;

  printf("len : %d\n", pcm.len);

  // 音声データ領域をcallocで確保
  pcm.s = (double *)calloc(pcm.len, sizeof(double));

  // 3つのサイン波を合成(C:261.63 D:329.63 E:392.00)
  sin_wave(&pcm, 0.1, C4, 0, pcm.fs);
  sin_wave(&pcm, 0.1, D4, 0, pcm.fs);
  sin_wave(&pcm, 0.1, E4, 0, pcm.fs);

  // 書き出し
  write_wave_mono(&pcm, "sin.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}