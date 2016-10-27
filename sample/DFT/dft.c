//
// Created by Kamiya Keisuke on 2016/10/27.
//

#include <stdio.h>
#include <stdlib.h>
#include "../../header/fileIO.h"
#include "../../header/waves.h"

int main(int argc, char* argv[]) {
  PCM pcm;
  int n;
  double *result;
  char *inputFile = argv[1];
  char *outputFile = argv[2];

  if (argc != 3) {
    fprintf(stderr, "Please input a file name.\n");
    exit(0);
  }

  read_wave_mono(&pcm, inputFile);

  result = DFT(&pcm, 44100);

  FILE *fp = fopen(outputFile, "w");
  for (n = 0; n < 44100; n++) {
    fprintf(fp, "%d %f\n", n, result[n]);
  }

  free(pcm.s);
  free(result);
  fclose(fp);

  return 0;
}