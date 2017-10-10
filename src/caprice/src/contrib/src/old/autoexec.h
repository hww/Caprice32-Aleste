/* autoexec.h */
/* Win32 autorun feature. Copyright (c) Troels K. 2003 */

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

struct _AUTOEXEC;

typedef struct _AUTOEXEC* AUTOEXECHANDLE;

EXTERN_C AUTOEXECHANDLE autoexec_open (const TCHAR* InitString);
EXTERN_C void           autoexec_close(AUTOEXECHANDLE*);
