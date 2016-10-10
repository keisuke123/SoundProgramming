// includeガード
#ifndef fileIO_H
#define fileIO_H

// header file
//#include <stdio.h>
//#include <stdlib.h>

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
  long chunk_size;
  short data;
}DATA_CHUNK;

typedef struct {
  RIFF_CHUNK rc;
  FMT_CHUNK fc;
  DATA_CHUNK dc;
}WAVE;

void write_wave_mono(PCM *pcm, char *file_name);
void read_wave_mono(PCM *pcm, char *file_name);

void read_wave_mono(PCM *pcm, char *file_name){
  FILE *fp;
  WAVE data;
  double d;
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
  
  pcm->fs = data.fc.sample_per_sec;
  pcm->bit = data.fc.bits_per_sample;
  pcm->len = data.dc.chunk_size;
  pcm->s = (double *)calloc(pcm->len, sizeof(double));
  
  int i;
  for(i = 0 ; i < pcm->len ; i++){
    fread(&d, 2, 1, fp);
    pcm->s[i] = (double)d/(32768.0);
  }

  fclose(fp);
}

void write_wave_mono(PCM *pcm, char *file_name){
  FILE *fp;
  WAVE data;
  double d;

  /* Riff Chunk */
  data.rc.chunk_id[0] = 'R';
  data.rc.chunk_id[1] = 'I';
  data.rc.chunk_id[2] = 'F';
  data.rc.chunk_id[3] = 'F';
  data.rc.chunk_size = 36 + pcm->len * 2;
  data.rc.format_type[0] = 'W';
  data.rc.format_type[0] = 'A';
  data.rc.format_type[0] = 'V';
  data.rc.format_type[0] = 'E';

  /* FMT Chunk*/
  data.fc.chunk_id[0] = 'f';
  data.fc.chunk_id[1] = 'm';
  data.fc.chunk_id[2] = 't';
  data.fc.chunk_id[3] = ' ';
  data.fc.chunk_size = 16;   //idとchunkを除いたサイズ
  data.fc.format_type = 1;
  data.fc.channel = 1;
  data.fc.sample_per_sec = pcm->fs;
  data.fc.bytes_per_sec = pcm->fs * pcm->bit/8;
  data.fc.block_size = pcm->bit / 8;
  data.fc.bits_per_sample = pcm->bit;

  /*
  data.fc.bits_per_sample = pcm->bit;
  data.fc.block_size = data.fc.bits_per_sample * data.fc.channel / 8;
  data.fc.bytes_per_sec = pcm->fs * data.fc.block_size;
  */

  /* Data Chunk**/
  data.dc.chunk_id[0] = 'd';
  data.dc.chunk_id[0] = 'a';
  data.dc.chunk_id[0] = 't';
  data.dc.chunk_id[0] = 'a';
  data.dc.chunk_size = pcm->len * data.fc.channel;
  
  fp = fopen(file_name, "wb");

  /******************** 書き出し ********************/

   /* Riff Chunk */
  fwrite(data.rc.chunk_id, 1, 4, fp);
  fwrite(&data.rc.chunk_size, 4, 1, fp);
  fwrite(data.rc.format_type, 1, 4, fp);

  /* FMT Chunk*/
  fwrite(data.fc.chunk_id, 1, 4, fp);
  fwrite(&data.fc.chunk_size, 4, 1, fp);
  fwrite(&data.fc.format_type, 2, 1, fp);
  fwrite(&data.fc.channel, 2, 1, fp);
  fwrite(&data.fc.sample_per_sec, 4, 1, fp);
  fwrite(&data.fc.bytes_per_sec, 4, 1, fp);
  fwrite(&data.fc.block_size, 2, 1, fp);
  fwrite(&data.fc.bits_per_sample, 2, 1, fp);

  /* Data Chunk*/
  fwrite(data.dc.chunk_id, 1, 4, fp);
  fwrite(&data.dc.chunk_size, 4, 1, fp);

  
  int i;
  for(i = 0 ; i < pcm->len ; i++){
    double s = (pcm->s[i] + 1.0) / 2.0 * 65536.0;
    
    if (s > 65535.0)
    {
      s = 65535.0; /* クリッピング */
    }
    else if (s < 0.0)
    {
      s = 0.0; /* クリッピング */
    }
    
    short data = (short)((int)(s + 0.5) - 32768); /* 四捨五入とオフセットの調節 */
    fwrite(&data, 2, 1, fp); /* 音データの書き出し */
  }

  fclose(fp);
}

#endif

