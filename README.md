# SoundProgramming
Sound program written by c.

* sin_curve(サイン波)
* square_curve(矩形波)
* triangle_curve(三角波)
* sawtooth_curve(のこぎり波)

関数の基本形は以下の通り
```c
void function(&pcm, gain, f0)
```
* pcmにはサンプリング周波数等を格納したPCM型のファイル
* gainは振幅調整
* f0には基本周波数
を格納してください。