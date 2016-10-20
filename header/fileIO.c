#include "fileIO.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// WAVEのフォーマットについては以下のURL参照
// https://goo.gl/72sPnr

#define PATHSIZE 100
/***************************************************
 * waveファイル(モノラル, 16bit)の読み込み
 * pcm       : データ格納先のPCM構造体
 * file_name : 読み込むファイルの名前
****************************************************/
void read_wave_mono(PCM *pcm, char *file_name){
  FILE *fp;
  WAVE data;
  short d;
  char path[100];

  // バイナリモードで開く
  fp = fopen(file_name, "rb");

  /******************** 読み込み ********************/
  /* Riff Chunk */
  fread(data.rc.chunk_id, 1, 4, fp);
  fread(&data.rc.chunk_size, 4, 1, fp);
  fread(data.rc.format_type, 1, 4, fp);

  /* FMT Chunk*/
  fread(data.fc.chunk_id, 1, 4, fp);
  fread(&data.fc.chunk_size, 4, 1, fp);
  fread(&data.fc.format_type, 2, 1, fp);
  fread(&data.fc.channel, 2, 1, fp);
  fread(&data.fc.sample_per_sec, 4, 1, fp);
  fread(&data.fc.bytes_per_sec, 4, 1, fp);
  fread(&data.fc.block_size, 2, 1, fp);
  fread(&data.fc.bits_per_sample, 2, 1, fp);

  /* Data Chunk */
  fread(data.dc.chunk_id, 1, 4, fp);
  fread(&data.dc.chunk_size, 4, 1, fp);

  // サンプリング周波数
  pcm->fs = data.fc.sample_per_sec;

  // 量子化ビット数
  pcm->bit = data.fc.bits_per_sample;

  // データの長さ
  pcm->len = data.dc.chunk_size / 2;

  // データ格納用のメモリを確保
  if((pcm->s = (double *)calloc(pcm->len, sizeof(double))) == NULL){
    fprintf(stderr, "Error : ");
    perror(NULL);
  }

  // 32768.0で正規化
  int i;
  for(i = 0 ; i < pcm->len ; i++){
    fread(&d, 2, 1, fp);
    pcm->s[i] = (double)d/(32768.0);
  }

  fclose(fp);

  // パスの作成
  getcwd(path, PATHSIZE);
  strcat(path, "/");
  strcat(path, file_name);

  // 読み込んだデータの詳細(pathは読み込んだファイルのパス)
  puts("************* File Info *************");
  printf("filename         : %s\n", file_name);
  printf("sampling rate    : %d[Hz]\n", pcm->fs);
  printf("Quantization bit : %d[bit]\n", pcm->bit);
  printf("data length      : %f[sec]\n", (double)pcm->len / pcm->fs);
  printf("path             : %s\n", path);
  puts("");
}

/***************************************************
 * waveファイル(モノラル, 16bit)の生成（書き込み）
 * pcm       : データ格納先のPCM構造体
 * file_name : 読み込むファイルの名前
****************************************************/
void write_wave_mono(PCM *pcm, char *file_name){
  FILE *fp;
  WAVE data;
  short d;
  char path[100];

  /****************** データを構造体に格納 ******************/
  /* Riff Chunk */
  data.rc.chunk_id[0] = 'R';
  data.rc.chunk_id[1] = 'I';
  data.rc.chunk_id[2] = 'F';
  data.rc.chunk_id[3] = 'F';
  data.rc.chunk_size = 36 + pcm->len * 2;
  data.rc.format_type[0] = 'W';
  data.rc.format_type[1] = 'A';
  data.rc.format_type[2] = 'V';
  data.rc.format_type[3] = 'E';

  /* FMT Chunk*/
  data.fc.chunk_id[0] = 'f';
  data.fc.chunk_id[1] = 'm';
  data.fc.chunk_id[2] = 't';
  data.fc.chunk_id[3] = ' ';
  data.fc.chunk_size = 16;   //idとchunkを除いたサイズ
  data.fc.format_type = 1;
  data.fc.channel = 1;
  data.fc.sample_per_sec = pcm->fs;
  data.fc.bits_per_sample = pcm->bit;
  data.fc.block_size = data.fc.bits_per_sample * data.fc.channel / 8;
  data.fc.bytes_per_sec = pcm->fs * data.fc.block_size;
  

  /* Data Chunk**/
  data.dc.chunk_id[0] = 'd';
  data.dc.chunk_id[1] = 'a';
  data.dc.chunk_id[2] = 't';
  data.dc.chunk_id[3] = 'a';
  data.dc.chunk_size = pcm->len * data.fc.channel * 2;

  // バイナリモードで書き出す
  fp = fopen(file_name, "wb");

  /****************** 書き出し ******************/

   /* Riff Chunk */
  fwrite(data.rc.chunk_id, 1, 4, fp);
  fwrite(&data.rc.chunk_size, 4, 1, fp);
  fwrite(data.rc.format_type, 1, 4, fp);

  /* FMT Chunk */
  fwrite(data.fc.chunk_id, 1, 4, fp);
  fwrite(&data.fc.chunk_size, 4, 1, fp);
  fwrite(&data.fc.format_type, 2, 1, fp);
  fwrite(&data.fc.channel, 2, 1, fp);
  fwrite(&data.fc.sample_per_sec, 4, 1, fp);
  fwrite(&data.fc.bytes_per_sec, 4, 1, fp);
  fwrite(&data.fc.block_size, 2, 1, fp);
  fwrite(&data.fc.bits_per_sample, 2, 1, fp);

  /* Data Chunk */
  fwrite(data.dc.chunk_id, 1, 4, fp);
  fwrite(&data.dc.chunk_size, 4, 1, fp);
  
  /****************** 音源の書き出し ******************/
  int i;
  for(i = 0 ; i < pcm->len ; i++){
    printf("pcm->s[%d] : %f\n", i, pcm->s[i]);
    double s = (pcm->s[i] + 1.0) * 32768.0;

    // クリッピング
    if (s > 65535.0){
      s = 65535.0;
    } else if (s < 0.0) {
      s = 0.0;
    }
    d = (short)((int)(s + 0.5) - 32768);      // オフセット
    fwrite(&d, 2, 1, fp);
  }

  fclose(fp);

  // パスの生成
  getcwd(path, PATHSIZE);
  strcat(path, "/");
  strcat(path, file_name);

  // 作成したデータの詳細
  puts("************* File Info *************");
  printf("filename         : %s\n", file_name);
  printf("sampling rate    : %d[Hz]\n", pcm->fs);
  printf("Quantization bit : %d[bit]\n", pcm->bit);
  printf("data length      : %f[sec]\n", (double)pcm->len / pcm->fs);
  printf("file created at %s\n", path);
  puts("");
}


