// includeガード
#ifndef fileIO_H
#define fileIO_H

// header file

typedef struct {
  int fs; //標本化周波数
  int bit;
  int len;
  double *s;
} PCM;

typedef struct {
  char chunk_ID[4];
  long size;
  char format_type[4];
}RIFF;

typedef struct {
  char chunk_ID[4];
  long chunk_size;
  short format_type;
  short channel;

}FMT;

void read_wav_mono(PCM *pcm, char *file_name){
  
}


#endif
