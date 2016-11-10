//
// Created by Kamiya Keisuke on 2016/10/13.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
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

  for (n = 0; n < pcm->fs*length; ++n) {
    pcm->s[n+offset] += gain * sin(2 * M_PI * f0 * n / pcm->fs);
  }

  return;
}

/***************************************
 * コサイン波を生成(cos_wave)
 * pcm    : 音源ファイル
 * gain   : 利得
 * f0     : 基本周波数
 * offset : 音源開始位置
 * length : 音源の長さ
***************************************/
void cos_wave(PCM *pcm, double gain, double f0, int offset, int length){
  int n;

  for (n = 0; n < pcm->fs*length; ++n) {
    pcm->s[n+offset] += gain * cos(2 * M_PI * f0 * n / pcm->fs);
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
    for (n = 0; n < pcm->fs*length ; ++n) {
      pcm->s[n + offset] += gain * 1.0 / i * sin(2.0 * M_PI * i * f0 * n / pcm->fs);
    }
  }

  for(n = 0 ; n < pcm->fs*pcm->len ; n++){
    pcm->s[n] *= 4.0 / M_PI;
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
    for (n = 0; n < pcm->fs*length ; ++n) {
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
    for(n = 0 ; n < pcm->fs*length ; n++){
      pcm->s[n+offset] += gain * 1.0 / i * sin(2.0 * M_PI * i * f0 * n / pcm->fs);
    }
  }
}

/***************************************
 * 白色雑音を生成(white_noise)
 * pcm    : 音源ファイル
 * gain   : 利得
 * offset : 音源開始位置
 * length : 音源の長さ
***************************************/
void white_noise(PCM *pcm, double gain, int offset, int length){
  int n, i;

  srand((unsigned)time(NULL));

  double phi;

  for(i = 1 ; i <= pcm->fs/2 ; i++){
    phi = (double)rand() / RAND_MAX * 2.0 * M_PI;
    for(n = 0 ; n <= pcm->fs*length; n++){
      pcm->s[n + offset] += gain * sin(2 * M_PI * i * n / pcm->fs + phi);
    }
  }
  return;
}

/***************************************
 * 離散フーリエ変換(DFT)
 * pcm    : 音源ファイル
 * N      : 長さ
 * O(n^2)なので遅い
***************************************/
double *DFT(PCM *pcm, int N){
  double *Xr, *Xi, *result;
  int k, n;

  // 実部
  Xr = (double *)calloc(N, sizeof(double));

  // 虚部
  Xi = (double *)calloc(N, sizeof(double));

  // 結果を格納する領域を確保
  result = (double *)calloc(N, sizeof(double));

  puts("------------- DFT start -------------");
  for(k = 0 ; k < N ; k++){
    for(n = 0 ; n < N ; n++){
      Xr[k] += pcm->s[n] *  cos(2 * M_PI * k * n / N);
      Xi[k] += pcm->s[n] * -sin(2 * M_PI * k * n / N);
    }
  }

  // 変換結果
  for(k = 0 ; k < N ; k++){
    result[k] = sqrt(pow(Xr[k], 2) + pow(Xi[k], 2));
  }

  puts("------------ finish ------------------");

  // 領域開放
  free(Xr);
  free(Xi);

  return result;
}