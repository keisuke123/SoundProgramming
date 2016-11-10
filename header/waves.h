//
// Created by Kamiya Keisuke on 2016/10/13.
//

#ifndef SOUNDPROGRAMMING_WAVES_H
#define SOUNDPROGRAMMING_WAVES_H

#include "fileIO.h"

void sin_wave(PCM *pcm, double gain, double f0, int offset, int length);
void sin_wave(PCM *pcm, double gain, double f0, int offset, int length);
void square_wave(PCM *pcm, double gain, double f0, int offset, int length);
void triangle_wave(PCM *pcm, double gain, double f0, int offset, int length);
void sawtooth_wave(PCM *pcm, double gain, double f0, int offset, int length);
void white_noise(PCM *pcm, double gain, int offset, int length);
double *DFT(PCM *pcm, int N);

// 12平均律音階
#define C4  261.63
#define Cs4 277.18
#define D4  293.66
#define Ds4 311.13
#define E4  329.63
#define F4  349.23
#define Fs4 369.99
#define G4  392.0
#define Gs4 415.3
#define A4  440.0
#define As4 466.16
#define B4  493.88

#endif