/* emushell.h */
/* Generic CPC emulator app api/interface. Copyright (c) Troels K. 2003-2004 */

#ifndef __EMUSHELL_H__
#define __EMUSHELL_H__

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

#include "bool.h"

enum emushell_version
{
   LIT_current_version = 0x0100
};

#define EMUSHELL_ENTRYPOINT      emushell_open
#define EMUSHELL_ENTRYPOINT_TEXT "emushell_open"

struct _EMUSHELL;
typedef struct _EMUSHELL *EMUHANDLE;

enum emupath
{
   ENUM_emupath_exe,
   ENUM_emupath_rom,
   ENUM_emupath_snapshot,
   ENUM_emupath_snapshot_screen,
   ENUM_emupath_enumcount
};

enum keyboard
{
   ENUM_keyboard_uk,
   ENUM_keyboard_fr,
   ENUM_keyboard_sp,
   ENUM_keyboard_dk,
   ENUM_keyboard_enumcount
};

typedef struct _EMUAPI
{
   EMUHANDLE (*open     )(const TCHAR* lpszPath/* = NULL */);
   void   (*put_exe_path)(EMUHANDLE, const TCHAR* lpszPath);
   HANDLE (*run         )(EMUHANDLE, HWND hwndParent, int argc, TCHAR* argv[]);
   BOOL   (*get_disk    )(EMUHANDLE, int no, LPTSTR  lpszBuffer, int cbBuffer); /* lpszBuffer = NULL is ok */
   BOOL   (*put_disk    )(EMUHANDLE, int no, const TCHAR* lpszBuffer);
   BOOL   (*get_rom     )(EMUHANDLE, int no, LPTSTR  lpszBuffer, int cbBuffer); /* lpszBuffer = NULL is ok */
   BOOL   (*put_rom     )(EMUHANDLE, int no, const TCHAR* lpszName);
   int    (*get_name    )(EMUHANDLE, LPTSTR lpszBuffer, int cbBuffer);
   BOOL   (*get_fileprofile)(EMUHANDLE, LPTSTR lpszBuffer, int cbBuffer);
   BOOL   (*get_path    )(EMUHANDLE, enum emupath, LPTSTR lpszBuffer, int cbBuffer);
   BOOL   (*put_path    )(EMUHANDLE, enum emupath, const TCHAR* lpszBuffer);

   BOOL   (*get_video_mode)(EMUHANDLE, int* mode);
   BOOL   (*put_video_mode)(EMUHANDLE, int mode);

   BOOL   (*get_fullscreen)(EMUHANDLE);
   BOOL   (*put_fullscreen)(EMUHANDLE, BOOL bEnable);

   BOOL   (*get_keyboard)(EMUHANDLE, int* keyboard);
   BOOL   (*put_keyboard)(EMUHANDLE, int keyboard);

   BOOL   (*get_text_mode)(EMUHANDLE, int* mode);
   BOOL   (*put_text_mode)(EMUHANDLE, int mode);

   void   (*close       )(EMUHANDLE*);
} EMUAPI;

struct _EMUIMPLEMENTATION;

typedef struct _EMUSHELL
{
   const EMUAPI* api;
   struct _EMUIMPLEMENTATION* impl; /* instance data */
} EMUSHELL;

EXTERN_C HANDLE EMUSHELL_Run(HWND hwnd, LPCTSTR lpszFile, LPCTSTR lpszParm, LPCTSTR lpszDir);

#ifdef __cplusplus
#include "emushell.hpp"
#endif

#endif /* __EMUSHELL_H__ */
