/* dialogs.h */

#include "bool.h"

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif


EXTERN_C BOOL browse_for_dsk (TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption);
EXTERN_C BOOL browse_for_bmp (TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption);
EXTERN_C BOOL browse_for_snap(TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption, BOOL save);

