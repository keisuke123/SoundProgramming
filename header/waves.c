//
// Created by Kamiya Keisuke on 2016/10/13.
//

#include <stdio.h>
#include <math.h>
#include "fileIO.h"
#include "waves.h"


/***************************************
 * サイン波を生成(sin_wave)
 * pcm    : 音源ファイル
 * gain   : 利得
 * f0     : 基本周波数
 * offset : 音源開始位置
 * length : 音源の長さ
***************************************/
void sin_wave(PCM *pcm, double gain, double f0, int offset, int length){
  int n;

  for (n = 0; n < length; ++n) {
    pcm->s[n+offset] += gain * sin(2 * M_PI * f0 * n / pcm->fs);
  }

  return;
}

/***************************************
 * 矩形波を生成(square_wave)
 * pcm    : 音源ファイル
 * gain   : 利得
 * f0     : 基本周波数
 * offset : 音源開始位置
 * length : 音源の長さ
***************************************/
void square_wave(PCM *pcm, double gain, double f0, int offset, int length) {
  int i, n;
  
  for(i = 1; i <= 44 ; i+=2){
    for (n = 0; n < length ; ++n) {
      pcm->s[n+offset] += gain * 1.0 / i * sin(2.0 * M_PI * i * f0 * n / pcm->fs);
    }
  }
}

/***************************************
 * 三角波を生成(triangle_wave)
 * pcm    : 音源ファイル
 * gain   : 利得
 * f0     : 基本周波数
 * offset : 音源開始位置
 * length : 音源の長さ
***************************************/
void triangle_wave(PCM *pcm, double gain, double f0, int offset, int length) {
  int i, n;

  for(i = 1; i <= 44 ; i+=2){
    for (n = 0; n < length ; ++n) {
      pcm->s[n+offset] += gain * 1.0 / i / i * sin(i * M_PI / 2 ) * sin(2.0 * M_PI * i * f0 * n / pcm->fs);
    }
  }
}

/***************************************
 * のこぎり波を生成(sawtooth_wave)
 * pcm    : 音源ファイル
 * gain   : 利得
 * f0     : 基本周波数
 * offset : 音源開始位置
 * length : 音源の長さ
***************************************/
void sawtooth_wave(PCM *pcm, double gain, double f0, int offset, int length) {
  int i, n;
  
  for (i = 1; i <= 44; ++i) {
    for(n = 0 ; n < length ; n++){
      pcm->s[n+offset] += gain * 1.0 / i * sin(2.0 * M_PI * i * f0 * n / pcm->fs);
    }
  }
}