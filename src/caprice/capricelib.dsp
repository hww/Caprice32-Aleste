# Microsoft Developer Studio Project File - Name="capricelib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=capricelib - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "capricelib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "capricelib.mak" CFG="capricelib - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "capricelib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "capricelib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "capricelib - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "capricelib - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "capricelib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\release\caprice\lib"
# PROP Intermediate_Dir "..\release\caprice\lib"
# PROP Target_Dir ""
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /MT /W3 /GX /O1 /I "..\zlib" /I "..\sdl\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GF /c
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\caprice.lib"

!ELSEIF  "$(CFG)" == "capricelib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\debug\caprice\lib"
# PROP Intermediate_Dir "..\debug\caprice\lib"
# PROP Target_Dir ""
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /MDd /W3 /Gm /GX /Zi /Od /I "..\zlib" /I "..\sdl\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /GF /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\caprice_d.lib"

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "capricelib___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "capricelib___Win32_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\release\caprice\lib\unicode"
# PROP Intermediate_Dir "..\release\caprice\lib\unicode"
# PROP Target_Dir ""
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /MT /W3 /GX /O1 /I "..\zlib" /I "..\sdl\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GF /c
# ADD CPP /MT /W3 /GX /O1 /I "..\zlib" /I "..\sdl\include" /D "WIN32" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "_LIB" /YX /FD /GF /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\caprice.lib"
# ADD LIB32 /nologo /out:"..\lib\capricew.lib"

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "capricelib___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "capricelib___Win32_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\debug\caprice\lib\unicode"
# PROP Intermediate_Dir "..\debug\caprice\lib\unicode"
# PROP Target_Dir ""
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /MDd /W3 /Gm /GX /ZI /Od /I "..\zlib" /I "..\sdl\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /GF /c
# ADD CPP /MDd /W3 /Gm /GX /Zi /Od /I "..\zlib" /I "..\sdl\include" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "_LIB" /YX /FD /GZ /GF /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\caprice_d.lib"
# ADD LIB32 /nologo /out:"..\lib\capricew_d.lib"

!ENDIF 

# Begin Target

# Name "capricelib - Win32 Release"
# Name "capricelib - Win32 Debug"
# Name "capricelib - Win32 Unicode Release"
# Name "capricelib - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\cap32.cpp
# End Source File
# Begin Source File

SOURCE=.\src\capzip.c
# End Source File
# Begin Source File

SOURCE=.\src\config.c
# End Source File
# Begin Source File

SOURCE=.\src\crtc.c
# End Source File
# Begin Source File

SOURCE=.\src\draw_16bpp.c

!IF  "$(CFG)" == "capricelib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\draw_24bpp.c

!IF  "$(CFG)" == "capricelib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\draw_32bpp.c

!IF  "$(CFG)" == "capricelib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\draw_8bpp.c

!IF  "$(CFG)" == "capricelib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\fdc.c
# End Source File
# Begin Source File

SOURCE=.\src\font.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psg.c
# End Source File
# Begin Source File

SOURCE=.\src\rom_mods.c

!IF  "$(CFG)" == "capricelib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "capricelib - Win32 Unicode Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\tape.c
# End Source File
# Begin Source File

SOURCE=.\src\z80.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\contrib\include\app.h
# End Source File
# Begin Source File

SOURCE=.\src\cap32.h
# End Source File
# Begin Source File

SOURCE=.\src\caperr.h
# End Source File
# Begin Source File

SOURCE=.\src\capzip.h
# End Source File
# Begin Source File

SOURCE=.\src\config.h
# End Source File
# Begin Source File

SOURCE=.\src\crtc.h
# End Source File
# Begin Source File

SOURCE=.\src\tape.h
# End Source File
# Begin Source File

SOURCE=.\src\z80.h
# End Source File
# Begin Source File

SOURCE=.\src\z80daa.h
# End Source File
# End Group
# Begin Group "Contribution"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\contrib\src\autotype.c
# End Source File
# Begin Source File

SOURCE=.\src\contrib\src\dialogs.c
# End Source File
# Begin Source File

SOURCE=.\src\contrib\src\emuimpl.c
# End Source File
# Begin Source File

SOURCE=.\src\contrib\src\loadrom.c
# End Source File
# Begin Source File

SOURCE=.\src\contrib\src\xbm_cpc.c
# End Source File
# End Group
# End Target
# End Project
