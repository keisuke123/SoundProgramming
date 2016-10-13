//
// Created by Kamiya Keisuke on 2016/10/13.
//

#include <stdio.h>
#include <math.h>
#include "fileIO.h"
#include "waves.h"


/***************************************/
/*
 * サイン波を生成(sin_curve)
 * pcm  : 音源ファイル
 * gain : 利得
 * f0   : 基本周波数
*/
/***************************************/
void sin_curve(PCM *pcm, double gain, double f0){
  int n;

  for (n = 0; n < pcm->len; ++n) {
    pcm->s[n] += gain * sin(2 * M_PI * f0 * n / pcm->fs);
  }

  return;
}

/***************************************/
/*
 * 矩形波を生成(square_curve)
 * pcm  : 音源ファイル
 * gain : 利得
 * f0   : 基本周波数
*/
/***************************************/
void square_curve(PCM *pcm, double gain, double f0) {
  int i, n;
  
  for(i = 1; i <= 44 ; i+=2){
    for (n = 0; n < pcm->len ; ++n) {
      pcm->s[n] += gain * 1.0 / i * sin(2.0 * M_PI * i * f0 * n / pcm->fs);
    }
  }
}

/***************************************/
/*
 * 三角波を生成(triangle_curve)
 * pcm  : 音源ファイル
 * gain : 利得
 * f0   : 基本周波数
*/
/***************************************/
void triangle_curve(PCM *pcm, double gain, double f0) {
  int i, n;

  for(i = 1; i <= 44 ; i+=2){
    for (n = 0; n < pcm->len ; ++n) {
      pcm->s[n] += gain * 1.0 / i / i * sin(i * M_PI / 2 ) * sin(2.0 * M_PI * i * f0 * n / pcm->fs);
    }
  }
}

/***************************************/
/*
 * のこぎり波を生成(sawtooth_curve)
 * pcm  : 音源ファイル
 * gain : 利得
 * f0   : 基本周波数
*/
/***************************************/
void sawtooth_curve(PCM *pcm, double gain, double f0) {
  int i, n;
  
  for (i = 1; i <= 44; ++i) {
    for(n = 0 ; n < pcm->len ; n++){
      pcm->s[n] += gain * 1.0 / i * sin(2.0 * M_PI * i * f0 * n / pcm->fs);
    }
  }
}