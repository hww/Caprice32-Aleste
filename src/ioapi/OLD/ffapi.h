/* ffapi.h */
/* Find file API. Copyright (c) 2004 by Troels K. */

#ifndef __FFAPI_H__
#define __FFAPI_H__

#ifndef ISSLASH
   #define ISSLASH(c) (((c) == '/') || ((c) == '\\'))
#endif

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

#include "bool.h"

#ifdef _WIN32
   struct _finddatai64_t;
   struct _wfinddatai64_t;
#elif _MSDOS
   struct _find_t;
   #define _finddatai64_t _find_t
#else /* posix */
   #define _MAX_PATH 260
   #define _A_NORMAL 0x00
   #define _A_RDONLY 0x01
   #define _A_HIDDEN 0x02
   #define _A_SYSTEM 0x04
   #define _A_SUBDIR 0x10
   #define _A_ARCH   0x20
   struct _wfinddatai64_t;
   #ifndef TCHAR
      #ifdef _UNICODE
         #define TCHAR wchar_t
      #else
         #define TCHAR char
      #endif
   #endif
   
   #ifndef _FINDDATA_T_DEFINED
   #include <time.h>
   #ifndef _FSIZE_T_DEFINED
   typedef unsigned long _fsize_t; /* Could be 64 bits for Win32 */
   #define _FSIZE_T_DEFINED
   #endif
   struct _finddatai64_t 
   {
       unsigned    attrib;
       time_t      time_create;    /* -1 for FAT file systems */
       time_t      time_access;    /* -1 for FAT file systems */
       time_t      time_write;
       _fsize_t    size;
       char        name[260];
   };
   struct _wfinddatai64_t 
   {
       unsigned    attrib;
       time_t      time_create;    /* -1 for FAT file systems */
       time_t      time_access;    /* -1 for FAT file systems */
       time_t      time_write;
       _fsize_t    size;
       wchar_t     name[260];
   };
   #ifdef _UNICODE
      #define _tfinddata_t _wfinddatai64_t
   #else
      #define _tfinddata_t _finddatai64_t
   #endif
   #define _FINDDATA_T_DEFINED
#endif /* posix */

#endif

struct _FFIMPLA;
typedef struct _FFIMPLA* FFHANDLEA;

typedef struct _FFAPIA
{
   FFHANDLEA (*open )(void* filesystem, const char* dir, struct _finddatai64_t*);
   int       (*next )(FFHANDLEA, struct _finddatai64_t*);
   void      (*close)(FFHANDLEA*);
   void*     filesystem;
} FFAPIA;

EXTERN_C void ffapi_host_fill(FFAPIA*);
EXTERN_C int  ffapi_host_stat(const char* file, struct _finddatai64_t*);
EXTERN_C BOOL ffapi_host_driveready(const char* dir);

#if defined(_WCHAR_T_DEFINED) && !defined(_MSDOS)

struct _FFIMPLW;
typedef struct _FFIMPLW* FFHANDLEW;

typedef struct _FFAPIW
{
   FFHANDLEW (*open )(void* filesystem, const wchar_t* dir, struct _wfinddatai64_t*);
   int       (*next )(FFHANDLEW, struct _wfinddatai64_t*);
   void      (*close)(FFHANDLEW*);
   void*     filesystem;
} FFAPIW;

EXTERN_C void ffapi_host_fillw(FFAPIW*);
EXTERN_C int  ffapi_host_statw(const wchar_t* file, struct _wfinddatai64_t*);
EXTERN_C void mbstowcs_finddata(struct _wfinddatai64_t*, const struct _finddatai64_t *);
EXTERN_C void wcstombs_finddata(struct _finddatai64_t *, const struct _wfinddatai64_t*);
EXTERN_C BOOL ffapi_host_drivereadyw(const wchar_t* dir);

#endif

#if defined(UNICODE) || defined(_UNICODE)
   #define FFHANDLE FFHANDLEW
   #define tffapi_host_fill ffapi_host_fillw
   #define tffapi_host_stat ffapi_host_statw
   #define tffapi_host_driveready ffapi_host_drivereadyw
#else
   #define FFHANDLE FFHANDLEA
   #define tffapi_host_fill ffapi_host_fill
   #define tffapi_host_stat ffapi_host_stat
   #define tffapi_host_driveready ffapi_host_driveready
#endif

#ifndef FFAPI 
   #if defined(UNICODE) || defined(_UNICODE)
      #define FFAPI struct _FFAPIW
   #else
      #define FFAPI struct _FFAPIA
   #endif
#endif

#endif /* __FFAPI_H__ */
