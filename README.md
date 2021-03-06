# Sound Programming

16bit, モノラルの音声信号を扱うC言語のコードです.
このコードでは
* sin_wave(サイン波)
* square_wave(矩形波)
* triangle_wave(三角波)
* sawtooth_wave(のこぎり波)
* white_noise(白色雑音)
* DFT(離散フーリエ変換)  

の関数を呼び出すことで,その波形を作り出すことができます.

### 関数の仕様
これらの関数群を使用するにはheader/waves.hとheader/fileIO.hをインクルードしてください.

関数の仕様は以下の通りです。

```c
void sin_wave(PCM *pcm, double gain, double f0, int offset, int length);
void square_wave(PCM *pcm, double gain, double f0, int offset, int length);
void triangle_wave(PCM *pcm, double gain, double f0, int offset, int length);
void sawtooth_wave(PCM *pcm, double gain, double f0, int offset, int length);
void white_noise(PCM *pcm, double gain, int offset, int length);
double *DFT(PCM *pcm, int N);
```

* pcm  
サンプリング周波数等を格納したPCM型のファイル
* gain  
振幅調整(実数)
* f0  
基本周波数[Hz]
* offset  
波形の開始位置[sec]
* length  
波形を生成する時間(整数[sec])

を渡してください.white_noiseのみf0が不要です.  
PCM型のパラメータは以下のとおりです.

```c
typedef struct {
  int fs;       // 標本化周波数
  int bit;      // 量子化ビット数
  int len;      // データの長さ
  double *s;    // 音源データ格納用
} PCM;
```

### 使用例
以下にプログラム例を示します.

```c
#include <stdio.h>
#include <stdlib.h>
#include <fileIO.h>
#include <waves.h>

#define SEC 1

int main(){
  PCM pcm;

  // pcmを量子化ビット数16[bit], サンプリング周波数fs=44100[Hz], 長さ1[sec]で初期化
  init_PCM(&pcm, 16, 44100, SEC);

  // 3つのサイン波を合成(C4:261.63 E4:329.63 G4:392.0)
  sin_wave(&pcm, 0.1, C4, 0, 1);
  sin_wave(&pcm, 0.1, E4, 0, 1);
  sin_wave(&pcm, 0.1, G4, 0, 1);

  // 書き出し
  write_wave_mono(pcm, "compose_sin.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}
```
関数を呼ぶと、領域sに書かれているデータとその関数によって生成される波形が合成されれます.  
サンプルファイルはsampleディレクトリに格納されています.上記のファイルはsample/compose_sin_curveです.その他にも
* 12_equal_temperament  
12平均律を再現したプログラム.  
* compose_sin_curve  
サイン波を合成するプログラム.
* DFT  
離散フーリエ変換によって, 周波数特性を観察する.(FFTではないのでものすごく遅い)
* read_wave_file  
wavファイルを読み込むプログラム.
* white_noise  
white_noise関数を用いたホワイトノイズ発生プログラム.  

があります.

### その他
WAVEの仕様については、[こちら](./docs/WAVE.md)を参照して下さい.  