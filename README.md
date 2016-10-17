# Sound Programming

16bit, モノラルの音声信号を扱うC言語のコードです.
このコードでは
* sin_wave(サイン波)
* square_wave(矩形波)
* triangle_wave(三角波)
* sawtooth_wave(のこぎり波)

の関数を呼び出すことで,その波形を作り出すことができます.

### 関数の仕様
これらの関数群を使用するにはheader/waves.hとheader/fileIO.hをインクルードしてください.

関数の仕様は以下の通りです。

```c
void sin_wave(PCM *pcm, double gain, double f0);
void square_wave(PCM *pcm, double gain, double f0);
void triangle_wave(PCM *pcm, double gain, double f0);
void sawtooth_wave(PCM *pcm, double gain, double f0);
```

* pcmにはサンプリング周波数等を格納したPCM型のファイル
* gainは振幅調整
* f0には基本周波数

を渡してください.
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
#include "header/fileIO.h" // PCM型の定義
#include "header/waves.h"  // sin_wave関数

int main(){
  PCM pcm;

  // 量子化ビット数
  pcm.bit = 16;

  // サンプリング周波数
  pcm.fs = 44100;

  // 長さ
  pcm.len = pcm.fs * 1;

  // 音声データ領域をcallocで確保
  pcm.s = (double *)calloc(pcm.len, sizeof(double));

  // 500Hzと1000Hzのサイン波を合成
  sin_wave(&pcm, 0.1, 500.0);
  sin_wave(&pcm, 0.1, 1000.0);

  // 書き出し
  write_wave_mono(&pcm, "sin.wav");

  // 領域の開放
  free(pcm.s);

  return 0;
}
```
関数を呼ぶと、領域sに書かれているデータとその関数によって生成される波形が合成されれます.  
サンプルファイルはsampleディレクトリに格納されています.上記のファイルはsample/compose_sin_curveです.

### その他
WAVEの仕様については、[こちら](./docs/WAVE.md)を参照して下さい.  