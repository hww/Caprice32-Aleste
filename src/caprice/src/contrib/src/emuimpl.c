/* emushell.c */
/* Caprice shell implementation. Copyright (c) Troels K. 2003-2004 */

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <direct.h>
#include <io.h>
#include "../include/app.h"
#include "../../../../emushell/emushell.h"
#include "../../../../cfgapi/cfg_reg.h"
#include "../../../../cfgapi/cfg_file.h"
#include "../include/emuimpl.h"

#ifndef _countof
   #define _countof(array) (sizeof(array)/sizeof((array)[0]))
#endif

typedef struct _EMUIMPLEMENTATION
{
   TCHAR szPath[_MAX_PATH];
   
   CFGHANDLE profile;
   TCHAR szProfile[_MAX_PATH];
} CPCEMUIMPL;


/* CAPRICE IMPLEMENTATION */

static const struct _CAPRICEPROFILE
{
   struct
   {
      const TCHAR* szSection;
         const TCHAR* aPath[2];
         const TCHAR* aFile[2];
         const TCHAR* szScreenShotPath;
   } disk;
   struct
   {
      const TCHAR* szSection;
         const TCHAR* szPath;
         const TCHAR* aRom[14];
   } rom;
   struct
   {
      const TCHAR* szSection;
         const TCHAR* szStyle;
         const TCHAR* szWindow;
         const TCHAR* szTextMode;
   } video;
   struct
   {
      const TCHAR* szSection;
         const TCHAR* szRate;
   } sound;
   struct
   {
      const TCHAR* szSection;
         const TCHAR* szKeyboard;
   } control;
} MOD_caprice_profile = 
{
   {
      _T("file"),
         {
            _T("drvA_path"),
            _T("drvB_path")
         },
         {
            _T("drvA_file"),
            _T("drvB_file")
         },
         _T("sdump_path")
   },
   {
      _T("rom"),
         _T("rom_path"),
         {
            _T("slot02"),
            _T("slot03"),
            _T("slot04"),
            _T("slot05"),
            _T("slot06"),
            _T("slot07"),
            _T("slot08"),
            _T("slot09"),
            _T("slot10"),
            _T("slot11"),
            _T("slot12"),
            _T("slot13"),
            _T("slot14"),
            _T("slot15")
         }
   },
   {
      _T("video"),
         _T("scr_style"),
         _T("scr_window"),
         _T("mode")
   },
   {
      _T("sound"),
         _T("playback_rate")
   },
   {
      _T("control"),
         _T("kbd_layout")
   }
};

static void cpcemu_close(EMUHANDLE* handle)
{
   free((*handle)->impl);
   free(*handle);
   *handle = NULL;
}

static void caprice_close(EMUHANDLE* handle)
{
   if ((*handle)->impl->profile) CFG_CLOSE(&(*handle)->impl->profile);
   cpcemu_close(handle);
}

static BOOL caprice_get_fileprofile(EMUHANDLE handle, LPTSTR lpszBuffer, int cbBuffer)
{
   _tcsncpy(lpszBuffer, handle->impl->szProfile, cbBuffer);
   return TRUE;
}

static void caprice_put_exe_path_ext(EMUHANDLE handle, const TCHAR* lpszPath)
{
   TCHAR szDrive[_MAX_PATH], szDir[_MAX_PATH];
   _tcsncpy(handle->impl->szPath, lpszPath, _countof(handle->impl->szPath));
   _tsplitpath(lpszPath, szDrive, szDir, NULL, NULL);
   
   _tmakepath(handle->impl->szProfile, szDrive, szDir, _T("cap32"), _T("cfg"));
   
   if (handle->impl->profile) CFG_CLOSE(&handle->impl->profile);
   handle->impl->profile = cfg_ini_topen(handle->impl->szProfile, NULL, NULL, TRUE);
}

static void caprice_put_exe_path_int(EMUHANDLE handle, const TCHAR* lpszPath)
{
   TCHAR szDrive[_MAX_PATH], szDir[_MAX_PATH];
   _tcsncpy(handle->impl->szPath, lpszPath, _countof(handle->impl->szPath));
   _tsplitpath(lpszPath, szDrive, szDir, NULL, NULL);
}

static HANDLE run_external(EMUHANDLE handle, HWND hwndParent, int argc, TCHAR* argv[])
{
   /* Caprice 3.61 is sensitive to work dir */
   TCHAR szDrive[_MAX_PATH], szDir[_MAX_PATH], szTitle[_MAX_PATH], szExt[_MAX_PATH];
   _tsplitpath(handle->impl->szPath, szDrive, szDir, szTitle, szExt);
   _tcscat(szDrive, szDir);
   _tcscat(szTitle, szExt);
   //return ((int)ShellExecute(hwndParent, NULL, szTitle, NULL, szDrive, SW_SHOW) > 32);
   return EMUSHELL_Run(hwndParent, szTitle, NULL, szDrive);
}

static HANDLE run_internal(EMUHANDLE handle, HWND hwndParent, int argc, TCHAR* argv[])
{
   int result;
   if (argc == 2)
   {
      const TCHAR* arg = argv[1];

      TCHAR szExt[_MAX_PATH];
      _tsplitpath(arg, NULL, NULL, NULL, szExt);

      if (0 != _tcsicmp(szExt, _T(".sna")))
      {
         Caprice32_Autotype = _tcsdup(arg);
         argc = 1;
      }
   }
   result = caprice_main (argc, argv, TRUE);
   doCleanUp ();
   return (result == EXIT_SUCCESS) ? (HANDLE)1 : NULL;
}

static BOOL caprice_get_disk(EMUHANDLE handle, int no, LPTSTR lpszBuffer, int cbBuffer)
{
   const int drivecount = _countof(MOD_caprice_profile.disk.aFile);
   BOOL bOK = (no >= 0) && (no < drivecount) && ((NULL == lpszBuffer) || (cbBuffer >= _MAX_PATH));
   if (bOK && lpszBuffer)
   {
      CFGHANDLE profile = handle->impl->profile;
      TCHAR szFolder[_MAX_PATH], szFile[_MAX_PATH];
      bOK =    CFG_SETSECTION(profile, MOD_caprice_profile.disk.szSection)
            && CFG_GETSTRING (profile, MOD_caprice_profile.disk.aPath[no], szFolder, _countof(szFolder), NULL)
            && CFG_GETSTRING (profile, MOD_caprice_profile.disk.aFile[no], szFile  , _countof(szFile  ), NULL);

      if (bOK)
      {
         _tmakepath(lpszBuffer, NULL, szFolder, szFile, NULL);
      }
   }
   return bOK;
}

static BOOL caprice_put_disk(EMUHANDLE handle, int no, const TCHAR* lpszBuffer)
{
   const int drivecount = _countof(MOD_caprice_profile.disk.aFile);
   BOOL bOK = (no >= 0) && (no < drivecount) && lpszBuffer;
   if (bOK)
   {
      CFGHANDLE profile = handle->impl->profile;
      
      TCHAR szDrive[_MAX_PATH], szDir[_MAX_PATH], szTitle[_MAX_PATH], szExt[_MAX_PATH];

      _tsplitpath(lpszBuffer, szDrive, szDir, szTitle, szExt);
      _tcscat(szDrive, szDir);
      _tcscat(szTitle, szExt);
      
      bOK =    CFG_SETSECTION(profile, MOD_caprice_profile.disk.szSection)
            && CFG_PUTSTRING (profile, MOD_caprice_profile.disk.aPath[no], szDrive)
            && CFG_PUTSTRING (profile, MOD_caprice_profile.disk.aFile[no], szTitle);
   }
   return bOK;
}

static void caprice_get_exe_folder(EMUHANDLE handle, LPTSTR lpszBuffer, int cbBuffer)
{
   TCHAR szDrive[_MAX_PATH], szDir[_MAX_PATH];

   _tsplitpath(handle->impl->szPath, szDrive, szDir, NULL      , NULL);
   _tmakepath(lpszBuffer, szDrive, szDir, NULL, NULL);
}

static void strcpy_normalize(EMUHANDLE handle, TCHAR* lpszBuffer, int cbBuffer, const TCHAR* temp)
{
   switch (*temp)
   {
      case '.':
      {
         TCHAR exe_folder[_MAX_PATH];
         const TCHAR* sz = temp;
         caprice_get_exe_folder(handle, exe_folder, _countof(exe_folder));
         while (_tcschr(_T("./\\"), *sz)) sz++;
         
         _tmakepath(lpszBuffer, NULL, exe_folder, sz, NULL);
         break;
      }
      default:
         _tcsncpy(lpszBuffer, temp, cbBuffer);
         break;
   }
}

static BOOL caprice_get_path(EMUHANDLE handle, enum emupath index, LPTSTR lpszBuffer, int cbBuffer)
{
   BOOL bOK;
   switch (index)
   {
      case ENUM_emupath_exe:
         caprice_get_exe_folder(handle, lpszBuffer, cbBuffer);
         bOK = TRUE;
         break;
      case ENUM_emupath_rom:
      {
         CFGHANDLE profile = handle->impl->profile;
         TCHAR temp[_MAX_PATH];

         bOK =    CFG_SETSECTION(profile, MOD_caprice_profile.rom.szSection)
               && CFG_GETSTRING (profile, MOD_caprice_profile.rom.szPath, temp, _countof(temp), NULL);
         if (bOK)
         {
            strcpy_normalize(handle, lpszBuffer, cbBuffer, temp);
         }
         break;
      }
      case ENUM_emupath_snapshot:
         break;
      case ENUM_emupath_snapshot_screen:
      {
         CFGHANDLE profile = handle->impl->profile;
         TCHAR temp[_MAX_PATH];

         bOK =    CFG_SETSECTION(profile, MOD_caprice_profile.disk.szSection)
               && CFG_GETSTRING (profile, MOD_caprice_profile.disk.szScreenShotPath, temp, _countof(temp), NULL);
         if (bOK)
         {
            strcpy_normalize(handle, lpszBuffer, cbBuffer, temp);
         }
         break;
      }
      default:
         bOK = FALSE;
         break;
   }
   return bOK;
}

static BOOL set_path(EMUHANDLE handle, enum emupath index, LPCTSTR lpszBuffer)
{
   BOOL bOK = (NULL != lpszBuffer);
   if (bOK)
   {
      switch (index)
      {
         case ENUM_emupath_exe:
            _tmakepath(handle->impl->szPath, NULL, lpszBuffer, NULL, NULL);
            break;
         case ENUM_emupath_rom:
            //bOK = CFG_PUTSTRING(handle->impl->profile, MOD_arnold_profile.szPath_Rom, lpszBuffer);
            break;
         case ENUM_emupath_snapshot:
            //bOK = CFG_PUTSTRING(handle->impl->profile, MOD_arnold_profile.szPath_Snapshot, lpszBuffer);
            break;
         case ENUM_emupath_snapshot_screen:
         {
            CFGHANDLE profile = handle->impl->profile;
            //bOK = CFG_PUTSTRING(handle->impl->profile, MOD_arnold_profile.szPath_Snapshot_Screen, lpszBuffer);
            bOK =    CFG_SETSECTION(profile, MOD_caprice_profile.disk.szSection)
                  && CFG_PUTSTRING (profile, MOD_caprice_profile.disk.szScreenShotPath, lpszBuffer);
            break;
         }
         default:
            bOK = FALSE;
            break;
      }
   }
   return bOK;
}

static BOOL caprice_get_video(EMUHANDLE handle, int* mode)
{
   CFGHANDLE profile = handle->impl->profile;
   CFG_SETSECTION(profile, MOD_caprice_profile.video.szSection);
   *mode = CFG_GETLONG(profile, MOD_caprice_profile.video.szStyle, *mode);
   return TRUE;
}

static BOOL caprice_set_video(EMUHANDLE handle, int mode)
{
   CFGHANDLE profile = handle->impl->profile;
   CFG_SETSECTION(profile, MOD_caprice_profile.video.szSection);
   CFG_PUTLONG(profile, MOD_caprice_profile.video.szStyle, mode);
   return TRUE;
}

static BOOL caprice_get_rom(EMUHANDLE handle, int no, LPTSTR lpszBuffer, int cbBuffer)
{
   BOOL bOK =    (no >= 0) && (no < _countof(MOD_caprice_profile.rom.aRom));
   if (bOK && lpszBuffer)
   {
      CFGHANDLE profile = handle->impl->profile;
      TCHAR szRom[_MAX_PATH];

      bOK =    CFG_SETSECTION(profile, MOD_caprice_profile.rom.szSection)
            && CFG_GETSTRING (profile, MOD_caprice_profile.rom.aRom[no], szRom, _countof(szRom), NULL);
      if (bOK) switch (*szRom)
      {
         case 0:
            bOK = FALSE;
            break;
         case '<':
            _tcscpy(lpszBuffer, szRom);
            break;
         default:
         {
            TCHAR szRomDir[_MAX_PATH];

            bOK = (*handle->api->get_path)(handle, ENUM_emupath_rom, szRomDir, _countof(szRomDir));
            if (bOK)
            {
               _tmakepath(lpszBuffer, NULL, szRomDir, szRom, NULL);
            }
            break;
         }
      }
   }
   return bOK;
}

#ifndef ISSLASH
   #define ISSLASH(a)  ((a) == _T('\\') || (a) == _T('/'))
#endif

static void normalize_slash(TCHAR* sz)
{
   for (sz; *sz; sz++)
   {
      if (ISSLASH(*sz)) *sz = '\\';
   }
}

static void trimright(TCHAR* sz)
{
   int i;
   for (i = _tcslen(sz)-1; (i >= 0) && ISSLASH(sz[i]); i--)
   {
      sz[i] = 0;
   }
}


static BOOL caprice_put_rom(EMUHANDLE handle, int no, const TCHAR* lpszBuffer)
{
   BOOL bOK = (no >= 0) && (no < _countof(MOD_caprice_profile.rom.aRom)) && lpszBuffer;
   if (bOK)
   {
      TCHAR szTitle[_MAX_PATH];
      switch (*lpszBuffer)
      {
         case 0:
            *szTitle = 0;
            break;
         case '<':
            _tcscpy(szTitle, lpszBuffer);
            break;
         default:
         {
            TCHAR szRomDir[_MAX_PATH];
            bOK = (*handle->api->get_path)(handle, ENUM_emupath_rom, szRomDir, _countof(szRomDir))
                && (0 == _taccess(lpszBuffer, 0));
            if (bOK)
            {
               TCHAR szDrive[_MAX_PATH], szDir[_MAX_PATH], szExt[_MAX_PATH];
               TCHAR szFrom[_MAX_PATH];//, szTo[_MAX_PATH];

               _tcscpy(szFrom, lpszBuffer);
   
               _tsplitpath(lpszBuffer, szDrive, szDir, szTitle, szExt);
               _tcscat(szDrive, szDir);
               normalize_slash(szDrive);
               normalize_slash(szRomDir);
               trimright(szDrive);
               trimright(szRomDir);
               if (0 != lstrcmpi(szDrive, szRomDir))
               {
                  SHFILEOPSTRUCT parm;
                  szFrom  [lstrlen(szFrom  )+1] = 0; /* \0\0 */
                  szRomDir[lstrlen(szRomDir)+1] = 0; /* \0\0 */

                  parm.hwnd   = NULL; 
                  parm.wFunc  = FO_COPY; 
                  parm.pFrom  = szFrom; 
                  parm.pTo    = szRomDir; 
                  parm.fFlags = FOF_SILENT; 
                  parm.fAnyOperationsAborted = FALSE; 
                  parm.hNameMappings = NULL; 
                  parm.lpszProgressTitle = NULL;

                  SHFileOperation(&parm);
               }

               _tcscat(szTitle, szExt);
            }
            break;
         }
      }
      if (bOK)
      {
         CFGHANDLE profile = handle->impl->profile;
         bOK =    CFG_SETSECTION(profile, MOD_caprice_profile.rom.szSection)
               && CFG_PUTSTRING (profile, MOD_caprice_profile.rom.aRom[no], szTitle);
      }
   }
   return bOK;
}

static int cpcemu_get_name(EMUHANDLE handle, LPTSTR lpszBuffer, int cbBuffer)
{
   return _tcslen(_tcsncpy(lpszBuffer, _T("Caprice32"), cbBuffer));
}

static BOOL get_fullscreen(EMUHANDLE handle)
{
   CFGHANDLE profile = handle->impl->profile;
   BOOL b = CFG_SETSECTION(profile, MOD_caprice_profile.video.szSection);
   if (b)
   {
      b = !CFG_GETLONG(profile, MOD_caprice_profile.video.szWindow, 1);
   }
   return b;
}

static BOOL put_fullscreen(EMUHANDLE handle, BOOL bEnable)
{
   CFGHANDLE profile = handle->impl->profile;
   BOOL bOK = CFG_SETSECTION(profile, MOD_caprice_profile.video.szSection);
   if (bOK)
   {
      CFG_PUTLONG(profile, MOD_caprice_profile.video.szWindow, !bEnable);
   }
   return bOK;
}

static BOOL get_keyboard(EMUHANDLE handle, int* keyboard)
{
   CFGHANDLE profile = handle->impl->profile;
   BOOL b = CFG_SETSECTION(profile, MOD_caprice_profile.control.szSection);
   if (b)
   {
      *keyboard = CFG_GETLONG(profile, MOD_caprice_profile.control.szKeyboard, 0);
   }
   return b;
}

static BOOL put_keyboard(EMUHANDLE handle, int keyboard)
{
   CFGHANDLE profile = handle->impl->profile;
   BOOL bOK = CFG_SETSECTION(profile, MOD_caprice_profile.control.szSection);
   if (bOK)
   {
      CFG_PUTLONG(profile, MOD_caprice_profile.control.szKeyboard, keyboard);
   }
   return bOK;
}

static BOOL get_text_mode(EMUHANDLE handle, int* mode)
{
   CFGHANDLE profile = handle->impl->profile;
   BOOL b = CFG_SETSECTION(profile, MOD_caprice_profile.video.szSection);
   if (b)
   {
      *mode = CFG_GETLONG(profile, MOD_caprice_profile.video.szTextMode, 0);
   }
   return b;
}

static BOOL put_text_mode(EMUHANDLE handle, int mode)
{
   CFGHANDLE profile = handle->impl->profile;
   BOOL bOK = CFG_SETSECTION(profile, MOD_caprice_profile.video.szSection);
   if (bOK)
   {
      CFG_PUTLONG(profile, MOD_caprice_profile.video.szTextMode, mode);
   }
   return bOK;
}

static EMUHANDLE create_internal(LPCTSTR lpszPath);
static EMUHANDLE create_external(LPCTSTR lpszPath);

static EMUAPI MOD_InternalAPI =
{
   create_internal, caprice_put_exe_path_int, run_internal, caprice_get_disk, caprice_put_disk, 
   caprice_get_rom, caprice_put_rom, cpcemu_get_name, caprice_get_fileprofile, caprice_get_path, 
   set_path, caprice_get_video, caprice_set_video, get_fullscreen, put_fullscreen, 
   get_keyboard, put_keyboard, get_text_mode, put_text_mode,
   caprice_close
};

static EMUAPI MOD_ExternalAPI =
{
   create_external, caprice_put_exe_path_ext, run_external, caprice_get_disk, caprice_put_disk, 
   caprice_get_rom, caprice_put_rom, cpcemu_get_name, caprice_get_fileprofile, caprice_get_path, 
   set_path, caprice_get_video, caprice_set_video, get_fullscreen, put_fullscreen, 
   get_keyboard, put_keyboard, get_text_mode, put_text_mode,
   caprice_close
};

static void set_defaults(CFGHANDLE profile)
{
   TCHAR sz[_MAX_PATH];
   
   if (CFG_SETSECTION(profile, MOD_caprice_profile.rom.szSection))
   {
      TCHAR szDrive[_MAX_PATH], szDir[_MAX_PATH];
      GetModuleFileName(NULL, sz, _countof(sz));
      _tsplitpath(sz, szDrive, szDir, NULL, NULL);
      _tmakepath (sz, szDrive, szDir, _T("rom"), NULL);
      
      CFG_GETSTRING (profile, MOD_caprice_profile.rom.szPath, sz, _countof(sz), sz);
      _tcscpy(sz, _T("<amsdos.rom>"));
      CFG_GETSTRING (profile, MOD_caprice_profile.rom.aRom[5], sz, _countof(sz), sz);
   }
   if (CFG_SETSECTION(profile, MOD_caprice_profile.video.szSection))
   {
      CFG_GETLONG(profile, MOD_caprice_profile.video.szStyle , 1);
      CFG_GETLONG(profile, MOD_caprice_profile.video.szWindow, 0);
   }
   if (CFG_SETSECTION(profile, MOD_caprice_profile.sound.szSection))
   {
      CFG_GETLONG(profile, MOD_caprice_profile.sound.szRate, 4);
   }
}

static EMUHANDLE create_internal(LPCTSTR lpszPath)
{
   TCHAR sz[80];
   EMUHANDLE handle = (EMUSHELL*)malloc(sizeof(EMUSHELL));
   CFGHANDLE profile;
   handle->api  = &MOD_InternalAPI;
   handle->impl = (CPCEMUIMPL*)malloc(sizeof(CPCEMUIMPL));
   handle->impl->profile = NULL;
   *handle->impl->szProfile = 0;
   
   _tcscpy(handle->impl->szPath, lpszPath ? lpszPath : _T(""));

   _sntprintf(sz, _countof(sz), _T("Software\\%s"), Caprice32_Profile);
   profile = handle->impl->profile = cfg_reg_topen(HKEY_CURRENT_USER, sz);

   set_defaults(profile);
   if (lpszPath) (*handle->api->put_exe_path)(handle, lpszPath);
   return handle;
}

static EMUHANDLE create_external(LPCTSTR lpszPath)
{
   EMUHANDLE handle = (EMUSHELL*)malloc(sizeof(EMUSHELL));
   handle->api  = &MOD_ExternalAPI;
   handle->impl = (CPCEMUIMPL*)malloc(sizeof(CPCEMUIMPL));
   handle->impl->profile = NULL;
   *handle->impl->szProfile = 0;
   
   _tcscpy(handle->impl->szPath, lpszPath ? lpszPath : _T(""));

   _tmakepath(handle->impl->szProfile, NULL, lpszPath, _T("cap32"), _T("cfg"));

   if (lpszPath) (*handle->api->put_exe_path)(handle, lpszPath);
   return handle;
}

const EMUAPI* EMUSHELL_CapriceInternal(void)
{
   return &MOD_InternalAPI;
}

const EMUAPI* EMUSHELL_CapriceExternal(void)
{
   return &MOD_ExternalAPI;
}
