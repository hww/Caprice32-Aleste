# use "make RELEASE=TRUE" to create release executable

CC	= g++

GFLAGS	= -mwindows -Wall -Wstrict-prototypes

ifdef RELEASE
CFLAGS	= $(GFLAGS) -O2 -funroll-loops -ffast-math -fomit-frame-pointer -fno-strength-reduce -finline-functions -s
else
CFLAGS	= $(GFLAGS) -gstabs+
endif

IPATHS	= -I/mingw/SDL/include -L/mingw/SDL/lib

cap32: cap32.cpp crtc.o fdc.o psg.o tape.o z80.o cap32.h z80.h
	$(CC) $(CFLAGS) $(IPATHS) -o cap32.exe cap32.cpp crtc.o fdc.o psg.o tape.o z80.o -lmingw32 -lSDLmain -lSDL -lz

crtc.o: crtc.c draw_8bpp.c draw_16bpp.c draw_24bpp.c draw_32bpp.c cap32.h crtc.h z80.h
	$(CC) $(CFLAGS) $(IPATHS) -c crtc.c

fdc.o: fdc.c cap32.h z80.h
	$(CC) $(CFLAGS) $(IPATHS) -c fdc.c

psg.o: psg.c cap32.h z80.h
	$(CC) $(CFLAGS) $(IPATHS) -c psg.c

tape.o: tape.c cap32.h tape.h z80.h
	$(CC) $(CFLAGS) $(IPATHS) -c tape.c

z80.o: z80.c z80.h cap32.h
	$(CC) $(CFLAGS) $(IPATHS) -c z80.c

clean:
	del .\*.o
	del cap32.exe
