# Microsoft Developer Studio Project File - Name="caprice" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=caprice - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "caprice.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "caprice.mak" CFG="caprice - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "caprice - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "caprice - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "caprice - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "caprice - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "caprice - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\release\caprice"
# PROP Intermediate_Dir "..\release\caprice"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GF /c
# SUBTRACT CPP /nologo
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 sdl.lib advapi32.lib shell32.lib comdlg32.lib user32.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin/cap32.exe" /libpath:"..\lib" /libpath:"..\sdl\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=..\fe\utils\upx.exe -9 ..\bin\cap32.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "caprice - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\debug\caprice"
# PROP Intermediate_Dir "..\debug\caprice"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /GF /c
# SUBTRACT CPP /nologo
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 sdl.lib advapi32.lib shell32.lib comdlg32.lib user32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin/cap32_d.exe" /pdbtype:sept /libpath:"..\lib" /libpath:"..\sdl\lib"

!ELSEIF  "$(CFG)" == "caprice - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "caprice___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "caprice___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\release\caprice\unicode"
# PROP Intermediate_Dir "..\release\caprice\unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GF /c
# SUBTRACT BASE CPP /nologo
# ADD CPP /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX /FD /GF /c
# SUBTRACT CPP /nologo
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sdl.lib advapi32.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin/cap32.exe" /libpath:"..\sdl\lib"
# ADD LINK32 libz.lib sdl.lib advapi32.lib shell32.lib comdlg32.lib user32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"zlib32_d.lib" /out:"..\bin/cap32w.exe" /libpath:"..\lib" /libpath:"..\sdl\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=..\fe\utils\upx.exe -9 ..\bin\cap32w.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "caprice - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "caprice___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "caprice___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\debug\caprice\unicode"
# PROP Intermediate_Dir "..\debug\caprice\unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /GF /c
# SUBTRACT BASE CPP /nologo
# ADD CPP /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX /FD /GZ /GF /c
# SUBTRACT CPP /nologo
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 sdl.lib advapi32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin/cap32_d.exe" /pdbtype:sept /libpath:"..\sdl\lib"
# ADD LINK32 libz_d.lib sdl.lib advapi32.lib shell32.lib comdlg32.lib user32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"zlib32.lib" /out:"..\bin/cap32w_d.exe" /pdbtype:sept /libpath:"..\lib" /libpath:"..\sdl\lib"

!ENDIF 

# Begin Target

# Name "caprice - Win32 Release"
# Name "caprice - Win32 Debug"
# Name "caprice - Win32 Unicode Release"
# Name "caprice - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\contrib\src\app.c
# End Source File
# Begin Source File

SOURCE=.\src\win\caprice.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\cap32.h
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
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "CFGAPI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\cfgapi\cfg_file.c
# End Source File
# Begin Source File

SOURCE=..\cfgapi\cfg_reg.c
# End Source File
# End Group
# Begin Group "IOAPI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ioapi\unzip\ioapi.c
# ADD CPP /I "..\zlib"
# End Source File
# Begin Source File

SOURCE=..\ioapi\ioapiw.c
# End Source File
# End Group
# Begin Group "Contribution"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\emushell\emushell.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\cap32.cfg
# End Source File
# End Target
# End Project
