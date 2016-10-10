// includeガード
#ifndef fileIO_H
#define fileIO_H

// header file
#include <stdio.h>

typedef struct {
  int fs; //標本化周波数
  int bit;
  int len;
  double *s;
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
  long chunk_size[4];
  short data;
}DATA_CHUNK;

typedef struct {
  RIFF_CHUNK rc;
  FMT_CHUNK fc;
  DATA_CHUNK dc;
}WAVE;

void read_wave_mono(PCM *pcm, char *file_name){
  FILE *fp;
  WAVE data;
  
  fp = fopen(file_name, "rb");

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

  /* Data Chunk*/
  fread(data.dc.chunk_id, 1, 4, fp);
  fread(&data.dc.chunk_size, 4, 1, fp);
  
  fclose(fp);
}


#endif

