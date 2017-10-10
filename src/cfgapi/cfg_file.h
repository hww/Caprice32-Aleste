/* cfg_file.h */
/* Copyright (c) 2004 by Troels K. */

#ifndef __CFG_FILE_H__
#define __CFG_FILE_H__

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

#include "cfgapi.h"

EXTERN_C CFGHANDLEA cfg_ini_open  (const char* filename, const char* section, struct zlib_filefunc_def_s* fileapi, BOOL modify);
EXTERN_C BOOL       ini_getline(CFGHANDLE, int line, TCHAR* buf, size_t buf_size);

#if defined(_WCHAR_T_DEFINED) && !defined(_MSDOS)

EXTERN_C CFGHANDLEW cfg_ini_wopen(const wchar_t* filename, const wchar_t* section, struct zlib_filefunc_defW_s* fileapi, BOOL modify);

#endif

#if defined(UNICODE) || defined(_UNICODE)
   #define cfg_ini_topen cfg_ini_wopen
#else
   #define cfg_ini_topen cfg_ini_open
#endif

#endif /* __CFG_FILE_H__ */
