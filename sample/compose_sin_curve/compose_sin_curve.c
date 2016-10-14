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
  pcm.len = pcm.fs * 1;

  // 音声データ領域をcallocで確保
  pcm.s = (double *)calloc(pcm.len, sizeof(double));

  // 500Hzと1000Hzのサイン波を合成
  sin_curve(&pcm, 0.1, 500.0);
  sin_curve(&pcm, 0.1, 1000.0);

  // 書き出し
  write_wave_mono(&pcm, "sin.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}