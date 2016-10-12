typedef struct
{
  int fs; /* �W�{�����g�� */
  int bits; /* �ʎq�����x */
  int length; /* ���f�[�^�̒��� */
  double *s; /* ���f�[�^ */
} MONO_PCM;

typedef struct
{
  int fs; /* �W�{�����g�� */
  int bits; /* �ʎq�����x */
  int length; /* ���f�[�^�̒��� */
  double *sL; /* ���f�[�^�iL�`�����l���j */
  double *sR; /* ���f�[�^�iR�`�����l���j */
} STEREO_PCM;

void wave_read_16bit_mono(MONO_PCM *pcm, char *file_name)
{
  FILE *fp;
  char riff_chunk_ID[4];
  long riff_chunk_size;
  char file_format_type[4];
  char fmt_chunk_ID[4];
  long fmt_chunk_size;
  short wave_format_type;
  short channel;
  long samples_per_sec;
  long bytes_per_sec;
  short block_size;
  short bits_per_sample;
  char data_chunk_ID[4];
  long data_chunk_size;
  short data;
  int n;
  
  fp = fopen(file_name, "rb");
  
  fread(riff_chunk_ID, 1, 4, fp);
  fread(&riff_chunk_size, 4, 1, fp);
  fread(file_format_type, 1, 4, fp);
  fread(fmt_chunk_ID, 1, 4, fp);
  fread(&fmt_chunk_size, 4, 1, fp);
  fread(&wave_format_type, 2, 1, fp);
  fread(&channel, 2, 1, fp);
  fread(&samples_per_sec, 4, 1, fp);
  fread(&bytes_per_sec, 4, 1, fp);
  fread(&block_size, 2, 1, fp);
  fread(&bits_per_sample, 2, 1, fp);
  fread(data_chunk_ID, 1, 4, fp);
  fread(&data_chunk_size, 4, 1, fp);
  
  pcm->fs = samples_per_sec; /* �W�{�����g�� */
  pcm->bits = bits_per_sample; /* �ʎq�����x */
  pcm->length = data_chunk_size / 2; /* ���f�[�^�̒��� */
  pcm->s = calloc(pcm->length, sizeof(double)); /* �������̊m�� */
  
  for (n = 0; n < pcm->length; n++)
  {
    fread(&data, 2, 1, fp); /* ���f�[�^�̓ǂݎ�� */
    pcm->s[n] = (double)data / 32768.0; /* ���f�[�^��-1�ȏ�1�����͈̔͂ɐ��K������ */
  }
  
  fclose(fp);
}

void wave_write_16bit_mono(MONO_PCM *pcm, char *file_name)
{
  FILE *fp;
  char riff_chunk_ID[4];
  long riff_chunk_size;
  char file_format_type[4];
  char fmt_chunk_ID[4];
  long fmt_chunk_size;
  short wave_format_type;
  short channel;
  long samples_per_sec;
  long bytes_per_sec;
  short block_size;
  short bits_per_sample;
  char data_chunk_ID[4];
  long data_chunk_size;
  double s;
  short data;
  int n;
  
  riff_chunk_ID[0] = 'R';
  riff_chunk_ID[1] = 'I';
  riff_chunk_ID[2] = 'F';
  riff_chunk_ID[3] = 'F';
  riff_chunk_size = 36 + pcm->length * 2;
  file_format_type[0] = 'W';
  file_format_type[1] = 'A';
  file_format_type[2] = 'V';
  file_format_type[3] = 'E';
  
  fmt_chunk_ID[0] = 'f';
  fmt_chunk_ID[1] = 'm';
  fmt_chunk_ID[2] = 't';
  fmt_chunk_ID[3] = ' ';
  fmt_chunk_size = 16;
  wave_format_type = 1;
  channel = 1;
  samples_per_sec = pcm->fs; /* �W�{�����g�� */
  bytes_per_sec = pcm->fs * pcm->bits / 8;
  block_size = pcm->bits / 8;
  bits_per_sample = pcm->bits; /* �ʎq�����x */
  
  data_chunk_ID[0] = 'd';
  data_chunk_ID[1] = 'a';
  data_chunk_ID[2] = 't';
  data_chunk_ID[3] = 'a';
  data_chunk_size = pcm->length * 2;
  
  fp = fopen(file_name, "wb");
  
  fwrite(riff_chunk_ID, 1, 4, fp);
  fwrite(&riff_chunk_size, 4, 1, fp);
  fwrite(file_format_type, 1, 4, fp);
  fwrite(fmt_chunk_ID, 1, 4, fp);
  fwrite(&fmt_chunk_size, 4, 1, fp);
  fwrite(&wave_format_type, 2, 1, fp);
  fwrite(&channel, 2, 1, fp);
  fwrite(&samples_per_sec, 4, 1, fp);
  fwrite(&bytes_per_sec, 4, 1, fp);
  fwrite(&block_size, 2, 1, fp);
  fwrite(&bits_per_sample, 2, 1, fp);
  fwrite(data_chunk_ID, 1, 4, fp);
  fwrite(&data_chunk_size, 4, 1, fp);
  
  for (n = 0; n < pcm->length; n++)
  {
    s = (pcm->s[n] + 1.0) / 2.0 * 65536.0;
    
    if (s > 65535.0)
    {
      s = 65535.0; /* �N���b�s���O */
    }
    else if (s < 0.0)
    {
      s = 0.0; /* �N���b�s���O */
    }
    
    data = (short)((int)(s + 0.5) - 32768); /* �l�̌ܓ��ƃI�t�Z�b�g�̒��� */
    fwrite(&data, 2, 1, fp); /* ���f�[�^�̏����o�� */
  }
  
  fclose(fp);
}
