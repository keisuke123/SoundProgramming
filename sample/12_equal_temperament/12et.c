//
// Created by Kamiya Keisuke on 2016/10/18.
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
  pcm.len = pcm.fs * 8;

  printf("len : %d\n", pcm.len);

  // 音声データ領域をcallocで確保
  if((pcm->s = (double *)calloc(pcm->len, sizeof(double))) == NULL){
    fprintf(stderr, "Error : ");
    perror(NULL);
  }

  // 12平均律（ドから一オクターブ上のドまで）
  sin_wave(&pcm, 0.1, C4, 0, pcm.fs);
  sin_wave(&pcm, 0.1, D4, pcm.fs * 1, pcm.fs);
  sin_wave(&pcm, 0.1, E4, pcm.fs * 2, pcm.fs);
  sin_wave(&pcm, 0.1, F4, pcm.fs * 3, pcm.fs);
  sin_wave(&pcm, 0.1, G4, pcm.fs * 4, pcm.fs);
  sin_wave(&pcm, 0.1, A4, pcm.fs * 5, pcm.fs);
  sin_wave(&pcm, 0.1, B4, pcm.fs * 6, pcm.fs);
  sin_wave(&pcm, 0.1, C4*2, pcm.fs * 7, pcm.fs);

  // 書き出し
  write_wave_mono(&pcm, "12ET.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}
