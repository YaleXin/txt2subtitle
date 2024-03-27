## 简介

将txt文件转为字幕

##　用法

将字幕文本保存为`subtitle.txt`，每行一句。

### 用法1

```shell
g++ subtitle.cpp -o subtitle.exe
subtitle.exe
```

该方法为默认用法，每个字幕持续5秒钟。

## 用法2

```shell
g++ subtitle.cpp -o subtitle.exe
subtitle.exe 0 2
```

每个字幕持续2秒钟，且字幕的下标从0开始。

## 用法3

```
subtitle.exe 0 5 20
```

从第5秒开始到第20秒结束，且字幕的下标从0开始，如果字幕共有10行，则每个字母持续的时间为`(20-5)/10`