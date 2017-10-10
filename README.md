# Caprice32 Aleste

It is first implemenation of [Aleste 520EX](https://github.com/hww/Aleste520EX) emulator based on Caprice32. It was coded at 2007, i did not updated it from that time. 

## Keyboard

The keyboard layout is different from PC. For example ':' is on same button (as PC) but without shift. With shift there is '*'. Similar issues you may to see with other buttons.

## How to play Aleste music

After boot you will see command prompt

```
a>
```

Type _dir_ and hit enter

```
a> dir
```

Yu will see list of .STM files on disk, also there are OS files, and MAG.COM player. Run MAG with .STM file as argument

```
a> MAG AXELF.STM
```

Enjoy

## How run MSX games

Switch current drive to B

```
a> b:
```

The display listing of files. And run one of games: LEO, VALEY, VKILLER. As usualy just type COM files name and hit enter.

## System software 

Same as expained abow you can run _Power Writer_ text editor (PW, PW211), or _Debugger_ (DBG) 

The english version of debugger's manual you can find here [Aleste 520EX](https://github.com/hww/Aleste520EX)
