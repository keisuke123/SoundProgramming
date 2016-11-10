//
// Created by Kamiya Keisuke on 2016/10/27.
//

#include <stdio.h>
#include <stdlib.h>
#include "../../header/fileIO.h"
#include "../../header/waves.h"

int main(int argc, char* argv[]) {
    PCM pcm;

    //矩形波
    init_PCM(&pcm, 16, 44100, 2);
    square_wave(&pcm, 0.1, 500, 0, 2);
    write_wave_mono(pcm, "square_wave.wav");
    free(pcm.s);

    //三角波
    init_PCM(&pcm, 16, 44100, 2);
    triangle_wave(&pcm, 0.1, 500, 0, 2);
    write_wave_mono(pcm, "triangle_wave.wav");
    free(pcm.s);

    //ノコギリ波
    init_PCM(&pcm, 16, 44100, 2);
    sawtooth_wave(&pcm, 0.1, 500, 0, 2);
    write_wave_mono(pcm, "sawtooth_wave.wav");
    free(pcm.s);

    return 0;
}