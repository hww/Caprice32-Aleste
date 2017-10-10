# Microsoft Visual C++ generated build script - Do not modify

PROJ = CFGAPI
DEBUG = 0
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\TRK\CODE\CFGAPI\DEMO\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = MAIN.C      
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /G2 /W4 /Zi /AM /Od /D "_DEBUG" /D "_DOS" /Fd"cfgapi.PDB"
CFLAGS_R_DEXE = /Gs /G2 /W4 /AL /Ox /D "NDEBUG" /D "_DOS" 
LFLAGS_D_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /CO /STACK:5120
LFLAGS_R_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /STACK:5120
LIBS_D_DEXE = oldnames mlibce
LIBS_R_DEXE = oldnames llibce
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
SBRS = MAIN.SBR \
		CFG_FILE.SBR \
		IOAPI.SBR


MAIN_DEP = o:\compiler\msvc\include\tchar.h \
	d:\trk\code\cfgapi\cfgapi.h \
	d:\trk\code\cfgapi\cfg_file.h \
	d:\trk\code\ioapi\ioapiw.h \
	d:\trk\code\ioapi\zlib.h \
	d:\trk\code\ioapi\unzip\ioapi.h \
	d:\trk\code\ioapi\unzip\iowin32.h


CFG_FILE_DEP = o:\compiler\msvc\include\tchar.h \
	d:\trk\code\cfgapi\cfg_file.h \
	d:\trk\code\cfgapi\cfgapi.h \
	d:\trk\code\ioapi\ioapiw.h \
	d:\trk\code\ioapi\zlib.h \
	d:\trk\code\ioapi\unzip\ioapi.h \
	d:\trk\code\ioapi\unzip\iowin32.h


IOAPI_DEP = d:\trk\code\ioapi\unzip\ioapi.h


all:	$(PROJ).EXE

MAIN.OBJ:	MAIN.C $(MAIN_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c MAIN.C

CFG_FILE.OBJ:	..\CFG_FILE.C $(CFG_FILE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\CFG_FILE.C

IOAPI.OBJ:	..\..\IOAPI\UNZIP\IOAPI.C $(IOAPI_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\IOAPI\UNZIP\IOAPI.C

$(PROJ).EXE::	MAIN.OBJ CFG_FILE.OBJ IOAPI.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
MAIN.OBJ +
CFG_FILE.OBJ +
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
