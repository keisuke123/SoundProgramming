//
// Created by Kamiya Keisuke on 2016/10/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <waves.h>
#include <fileIO.h>

int main(){
  PCM pcm;

  init_PCM(&pcm, 16, 44100, 8);

  // 12平均律（ドから一オクターブ上のドまで）
  sin_wave(&pcm, 0.1, C4, 0, 1);
  sin_wave(&pcm, 0.1, D4, pcm.fs * 1, 1);
  sin_wave(&pcm, 0.1, E4, pcm.fs * 2, 1);
  sin_wave(&pcm, 0.1, F4, pcm.fs * 3, 1);
  sin_wave(&pcm, 0.1, G4, pcm.fs * 4, 1);
  sin_wave(&pcm, 0.1, A4, pcm.fs * 5, 1);
  sin_wave(&pcm, 0.1, B4, pcm.fs * 6, 1);
  sin_wave(&pcm, 0.1, C4*2, pcm.fs * 7, 1);

  // 書き出し
  write_wave_mono(pcm, "12ET.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}
