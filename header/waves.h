//
// Created by Kamiya Keisuke on 2016/10/13.
//

#ifndef SOUNDPROGRAMMING_WAVES_H
#define SOUNDPROGRAMMING_WAVES_H

#include "fileIO.h"

void sin_wave(PCM *pcm, double gain, double f0);
void square_wave(PCM *pcm, double gain, double f0);
void triangle_wave(PCM *pcm, double gain, double f0);
void sawtooth_wave(PCM *pcm, double gain, double f0);

#endif