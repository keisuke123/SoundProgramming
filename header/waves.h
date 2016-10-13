//
// Created by Kamiya Keisuke on 2016/10/13.
//

#ifndef SOUNDPROGRAMMING_WAVES_H
#define SOUNDPROGRAMMING_WAVES_H

void sin_curve(PCM *pcm, double gain, double f0);
void square_curve(PCM *pcm, double gain, double f0);
void triangle_curve(PCM *pcm, double gain, double f0);
void sawtooth_curve(PCM *pcm, double gain, double f0);

#endif