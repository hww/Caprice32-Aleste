# Microsoft Visual C++ generated build script - Do not modify

PROJ = IOAPI
DEBUG = 0
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\TRK\CODE\IOAPI\DEMO\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = APP.C       
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /D "_DOS" /FR /Fd"IOAPI.PDB"
CFLAGS_R_DEXE = /Gs /G2 /W4 /AM /Ox /D "NDEBUG" /D "_DOS" 
LFLAGS_D_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /CO /STACK:5120
LFLAGS_R_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /STACK:5120
LIBS_D_DEXE = oldnames mlibce
LIBS_R_DEXE = oldnames mlibce
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE)
LFLAGS = $(LFLAGS_D_DEXE)
LIBS = $(LIBS_D_DEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_DEXE)
LFLAGS = $(LFLAGS_R_DEXE)
LIBS = $(LIBS_R_DEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = APP.SBR \
		IOAPI.SBR


APP_DEP = d:\trk\code\ioapi\demo\src\stdafx.h \
	o:\compiler\msvc\include\tchar.h \
	d:\trk\code\ioapi\demo\src\app.h \
	d:\trk\code\ioapi\ioapiw.h \
	d:\trk\code\ioapi\zlib.h \
	d:\trk\code\ioapi\unzip\ioapi.h \
	d:\trk\code\ioapi\unzip\iowin32.h


IOAPI_DEP = d:\trk\code\ioapi\unzip\ioapi.h


all:	$(PROJ).EXE

APP.OBJ:	SRC\APP.C $(APP_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c SRC\APP.C

IOAPI.OBJ:	..\UNZIP\IOAPI.C $(IOAPI_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\UNZIP\IOAPI.C

$(PROJ).EXE::	APP.OBJ IOAPI.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
APP.OBJ +
IOAPI.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
O:\COMPILER\MSVC\LIB\+
O:\COMPILER\MSVC\MFC\LIB\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
