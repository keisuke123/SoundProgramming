// includeガード
#ifndef fileIO_H
#define fileIO_H

// WAVEのフォーマットについては以下のURL参照
// https://goo.gl/72sPnr

typedef struct {
  int fs;       // 標本化周波数
  int bit;      // 量子化ビット数
  int len;      // データの長さ
  double *s;    // 音源格納用
} PCM;

typedef struct {
  char chunk_id[4];
  long chunk_size;
  char format_type[4];
}RIFF_CHUNK;

typedef struct {
  char chunk_id[4];
  long chunk_size;
  short format_type;
  short channel;
  long sample_per_sec;
  long bytes_per_sec;
  short block_size;
  short bits_per_sample;
}FMT_CHUNK;

typedef struct {
  char chunk_id[4];
  long chunk_size;
  short data;
}DATA_CHUNK;

typedef struct {
  RIFF_CHUNK rc;
  FMT_CHUNK fc;
  DATA_CHUNK dc;
}WAVE;

void read_wave_mono(PCM *pcm, char *file_name);
void write_wave_mono(PCM pcm, char *file_name);
void init_PCM(PCM *pcm, int bit, int fs, int len);

#endif

