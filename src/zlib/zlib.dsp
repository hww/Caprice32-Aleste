# Microsoft Developer Studio Project File - Name="zlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=zlib - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "zlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "zlib.mak" CFG="zlib - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "zlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib - Win32 Static Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib - Win32 Static Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "zlib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ".\zlib"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\release\zlib"
# PROP Intermediate_Dir "..\release\zlib"
# PROP Target_Dir ".\zlib"
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /MT /W4 /GR /GX /O1 /I ".\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /FD /GF /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x406
# ADD RSC /l 0x406
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\libz.lib"

!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ".\zlib"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\debug\zlib"
# PROP Intermediate_Dir "..\debug\zlib"
# PROP Target_Dir ".\zlib"
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /MDd /W4 /GR /GX /Zi /O1 /I ".\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FD /GF /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x406
# ADD RSC /l 0x406
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\libz_d.lib"

!ELSEIF  "$(CFG)" == "zlib - Win32 Static Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "zlib\Static Debug"
# PROP BASE Intermediate_Dir "zlib\Static Debug"
# PROP BASE Target_Dir "zlib"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug\Static"
# PROP Intermediate_Dir ".\Debug\Static"
# PROP Target_Dir "zlib"
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /MTd /W3 /GR /GX /Z7 /O1 /I ".\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_LMRTBUILD" /D "_WINRT" /YX"stdafx.h" /FD /GF /c
# ADD CPP /MTd /W4 /GR /GX /Zi /O1 /I ".\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FD /GF /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x406
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\LIB\lmrt32sd.lib"
# ADD LIB32 /nologo /out:".\LIB\zlib32std.lib"

!ELSEIF  "$(CFG)" == "zlib - Win32 Static Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "zlib\Static Release"
# PROP BASE Intermediate_Dir "zlib\Static Release"
# PROP BASE Target_Dir "zlib"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release\Static"
# PROP Intermediate_Dir ".\Release\Static"
# PROP Target_Dir "zlib"
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /MT /W3 /GR /GX /O1 /I ".\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_LMRTBUILD" /D "_WINRT" /YX"stdafx.h" /FD /GF /c
# ADD CPP /MT /W4 /GR /GX /O1 /I ".\include" /I "..\zlib" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /FD /GF /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x406
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\LIB\lmrt32s.lib"
# ADD LIB32 /nologo /out:".\LIB\zlib32st.lib"

!ENDIF 

# Begin Target

# Name "zlib - Win32 Release"
# Name "zlib - Win32 Debug"
# Name "zlib - Win32 Static Debug"
# Name "zlib - Win32 Static Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\adler32.c
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\compress.c
# End Source File
# Begin Source File

SOURCE=.\crc32.c
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\deflate.c
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\inffast.c
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\inflate.c
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\inftrees.c
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\trees.c
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\zutil.c
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
