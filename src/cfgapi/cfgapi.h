/* cfgapi.h */
/* Copyright (c) 2004 by Troels K. */

#ifndef __CFG_API_H__
#define __CFG_API_H__

#include "bool.h"

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

struct _CFGDATAA;
typedef struct _CFGDATAA* CFGHANDLEA;

struct zlib_filefunc_def_s;
typedef struct _CFGAPIA
{
// CFGHANDLEA (*open       )(void* user, const char* filename, const char* section);
   BOOL       (*set_section)(CFGHANDLEA, const char* szSection);
   void       (*close      )(CFGHANDLEA*);
   int        (*get_string )(CFGHANDLEA, const char* szEntry, char* buf, int buf_size, const char* szDefault);
   BOOL       (*put_string )(CFGHANDLEA, const char* szEntry, const char* sz);
   long       (*get_long   )(CFGHANDLEA, const char* szEntry, long nDefault);
   BOOL       (*put_long   )(CFGHANDLEA, const char* szEntry, long);
   BOOL       (*get_binary )(CFGHANDLEA, const char* szEntry,       void* buffer, size_t buf_size);
   BOOL       (*put_binary )(CFGHANDLEA, const char* szEntry, const void* buffer, size_t buf_size);
   void*      opaque;
} CFGAPIA;

struct _CFGIMPLA;

typedef struct _CFGDATAA
{
   CFGAPIA api;
   struct _CFGIMPLA* impl;
} CFGDATAA;

#if defined(_WCHAR_T_DEFINED) && !defined(_MSDOS)

struct _CFGDATAW;
typedef struct _CFGDATAW* CFGHANDLEW;

struct zlib_filefunc_defW_s;
typedef struct _CFGAPIW
{
// CFGHANDLEW (*open       )(void* user, const wchar_t* filename, const wchar_t* section);
   BOOL       (*set_section)(CFGHANDLEW, const wchar_t* szSection);
   void       (*close      )(CFGHANDLEW*);
   int        (*get_string )(CFGHANDLEW, const wchar_t* szEntry, wchar_t* buf, int buf_size, const wchar_t* szDefault);
   BOOL       (*put_string )(CFGHANDLEW, const wchar_t* szEntry, const wchar_t* sz);
   long       (*get_long   )(CFGHANDLEW, const wchar_t* szEntry, long nDefault);
   BOOL       (*put_long   )(CFGHANDLEW, const wchar_t* szEntry, long);
   BOOL       (*get_binary )(CFGHANDLEW, const wchar_t* szEntry,       void* buffer, size_t buf_size);
   BOOL       (*put_binary )(CFGHANDLEW, const wchar_t* szEntry, const void* buffer, size_t buf_size);
   void*      opaque;
} CFGAPIW;

struct _CFGIMPLW;

typedef struct _CFGDATAW
{
   CFGAPIW api;
   struct _CFGIMPLW* impl;
} CFGDATAW;

#endif

#if defined(UNICODE) || defined(_UNICODE)
   #define CFGAPI    struct _CFGAPIW
   #define CFGIMPL   struct _CFGIMPLW
   #define CFGHANDLE CFGHANDLEW
#else
   #define CFGAPI    struct _CFGAPIA
   #define CFGIMPL   struct _CFGIMPLA
   #define CFGHANDLE CFGHANDLEA
#endif

#define CFG_SETSECTION(handle,section)               ( (*(handle)->api.set_section)(handle,section))
#define CFG_GETSTRING(handle,entry,buf,buf_size,def) ( (*(handle)->api.get_string )(handle,entry,buf,buf_size,def))
#define CFG_GETLONG(handle,entry,def)                ( (*(handle)->api.get_long   )(handle,entry,def))

#define CFG_PUTSTRING(handle,entry,buf) ( (*(handle)->api.put_string)(handle,entry,buf))
#define CFG_PUTLONG(handle,entry,value) ( (*(handle)->api.put_long  )(handle,entry,value))

#define CFG_CLOSE(handle) ( (*(*(handle))->api.close)(handle))


#endif /* __CFG_API_H__ */
