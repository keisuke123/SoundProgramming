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

  // pcmを量子化ビット数16[bit], サンプリング周波数fs=44100[Hz], 長さ1[sec]で初期化
  init_PCM(&pcm, 16, 44100, SEC);

  // 3つのサイン波を合成(C4:261.63 E4:329.63 G4:392.0)
  sin_wave(&pcm, 0.1, C4, 0, pcm.fs);
  sin_wave(&pcm, 0.1, E4, 0, pcm.fs);
  sin_wave(&pcm, 0.1, G4, 0, pcm.fs);

  // 書き出し
  write_wave_mono(pcm, "compose_sin.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}

