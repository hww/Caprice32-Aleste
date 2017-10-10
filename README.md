# Caprice32 Aleste

It is first implemenation of [Aleste 520EX](https://github.com/hww/Aleste520EX) emulator based on Caprice32. It was coded at 2007, i did not updated it from that time. 

## Introduction

With small modifications Caprice32 starts Aleste BDOS ROM. Right now it does not have full support yet, but you can look at Aleste’s screens.

The simulator can load 720 KB FAT disk image witch you can make with PC or MSX computer. The disk image can be edited by PC or just WinImage tool. The archive file has few demo disk images. After reset Aleste’s shows boot screen (screen shifted to the left, hope this bag will fixed in future). If disk image mounted you will see MSX-DOS welcome screen. Disk image has few Aleste’s applications. The MAG player works but emulation is not optimized yet. Be sure that you have 32 bits screen mode.

## What does not work

- The keyboard layout is different from PC. For example ':' is on same button (as PC) but without shift. With shift there is '*'. Similar issues you may to see with other buttons.
- 8, 16, 24 bits per pixel of windows rendering
- Screens positions have troubles
- Mouse serial interface
- Mouse’s cursor pointer
- Split screen mode. (the timer which can split screen to 3 color zones)
- Dump file (dose not save all Aleste registers)
- RTC supported partially
- Magic Sound can have problems with frequency precision

## How to control emulator

F1-F5 are F1-F5 of the Aleste
HOME — Aleste HELP button
INSERT — Aleste INSERT
F6 — load drive A
SHIFT + F6 — save drive A
F7 — load tape
F8 — load options
F9 — load snap
SHIFT + F9 — save snap
F10 — reset
SHIFT + F10 — limit speed
CTRL + SHIFT + F10 — toggle FPS counter
SYSREQ — screenshot
PAUSE — pause
F11 — exit

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

## Other emulators

There are other emlators of Aleste 520EX just find it by any internet search service.
