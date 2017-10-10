/* ioapiw.c - Achar/Wchar support - by Troels K. 2003 */

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include "unzip\iowin32.c" /* sadly we need WIN32FILE_IOWIN */
#include "ioapiw.h"

#ifndef _countof
   #define _countof(array) (sizeof(array)/sizeof((array)[0]))
#endif

#ifdef _WIN32
   #include <windows.h>
#endif

#ifndef C_ASSERT
   #define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
#endif
C_ASSERT(sizeof(zlib_filefunc_defW) == sizeof(zlib_filefunc_def));

/* I want to #include "ioapi.c", and 'call' the functions inline, with no function call overhead. Troels */
#ifndef LINKSPEC
   #define LINKSPEC __inline static
#endif

LINKSPEC voidpf ZCALLBACK fopen_file_funcW(voidpf opaque, const wchar_t* filename, int mode)
{
   FILE* file = NULL;
   const wchar_t* mode_fopen = NULL;
   if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER)==ZLIB_FILEFUNC_MODE_READ)
      mode_fopen = L"rb";
   else if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
      mode_fopen = L"r+b";
   else if (mode & ZLIB_FILEFUNC_MODE_CREATE)
      mode_fopen = L"wb";
   if (!((filename == NULL) || (mode_fopen == NULL)))
      file = _wfopen(filename, mode_fopen);
   return file;
}

void fill_filefuncA2W(zlib_filefunc_defW* wapi, const zlib_filefunc_def* api, open_file_funcW open_fn)
{
   wapi->zopen_file  = open_fn;
   wapi->zread_file  = api->zread_file  ; /* not Ansi/Wide-sensitive */
   wapi->zwrite_file = api->zwrite_file ; /* -"- */
   wapi->ztell_file  = api->ztell_file  ; /* -"- */
   wapi->zseek_file  = api->zseek_file  ; /* -"- */
   wapi->zclose_file = api->zclose_file ; /* -"- */
   wapi->zerror_file = api->zerror_file ; /* -"- */
   wapi->opaque      = api->opaque;
}

void fill_fopen_filefuncW (zlib_filefunc_defW* wapi)
{
   zlib_filefunc_def api;
   fill_fopen_filefunc(&api);
   fill_filefuncA2W(wapi, &api, fopen_file_funcW);
}

#ifdef _WIN32
static voidpf ZCALLBACK win32_open_file_funcW (voidpf opaque, const wchar_t* filename, int mode)
{
/*  const wchar_t* mode_fopen = NULL; */
    DWORD dwDesiredAccess,dwCreationDisposition,dwShareMode,dwFlagsAndAttributes ;
    HANDLE hFile = NULL;
    voidpf ret=NULL;

    dwDesiredAccess = dwShareMode = dwFlagsAndAttributes = dwCreationDisposition = 0;

    if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER)==ZLIB_FILEFUNC_MODE_READ)
    {
        dwDesiredAccess = GENERIC_READ;
        dwCreationDisposition = OPEN_EXISTING;
        dwShareMode = FILE_SHARE_READ;
    }
    else if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
    {
        dwDesiredAccess = GENERIC_WRITE | GENERIC_READ;
        dwCreationDisposition = OPEN_EXISTING;
    }
    else if (mode & ZLIB_FILEFUNC_MODE_CREATE)
    {
        dwDesiredAccess = GENERIC_WRITE | GENERIC_READ;
        dwCreationDisposition = CREATE_ALWAYS;
    }

    if ((filename!=NULL) && (dwDesiredAccess != 0))
        hFile = CreateFileW(filename, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
        hFile = NULL;

    if (hFile != NULL)
    {
        WIN32FILE_IOWIN w32fiow;
        w32fiow.hf = hFile;
        w32fiow.error = 0;
        ret = malloc(sizeof(WIN32FILE_IOWIN));
        if (ret==NULL)
            CloseHandle(hFile);
        else *((WIN32FILE_IOWIN*)ret) = w32fiow;
    }
    return ret;
}

void fill_win32_filefuncW (zlib_filefunc_defW* wapi)
{
   zlib_filefunc_def api;
   fill_win32_filefunc(&api);
   wapi->zopen_file  = win32_open_file_funcW;
   wapi->zread_file  = api.zread_file  ;
   wapi->zwrite_file = api.zwrite_file ;
   wapi->ztell_file  = api.ztell_file  ;
   wapi->zseek_file  = api.zseek_file  ;
   wapi->zclose_file = api.zclose_file ;
   wapi->zerror_file = api.zerror_file ;
   wapi->opaque      = api.opaque;
}

#include <stdio.h> /* _fileno */
#include <io.h>    /* _chsize */

int win32_setlength(voidpf opaque, voidpf stream, ZPOS_T size)
{
   HANDLE handle = ((WIN32FILE_IOWIN*)stream)->hf;
   ZPOS_T pos = win32_tell_file_func(opaque, stream);
   uLong ret = win32_seek_file_func(opaque, stream, size, ZLIB_FILEFUNC_SEEK_SET);
   if (0 == ret)
   {
      ret = SetEndOfFile(handle) ? 0 : -1;
      win32_seek_file_func(opaque, stream, pos, ZLIB_FILEFUNC_SEEK_SET);
   }
   return ret;
}

HANDLE win32_createfilemapping(voidpf opaque, voidpf stream, 
   LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, 
   DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCTSTR lpName)
{
   HANDLE handle = ((WIN32FILE_IOWIN*)stream)->hf;
   return CreateFileMapping(handle, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
}

HANDLE fopen_createfilemapping(voidpf opaque, voidpf stream, 
   LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, 
   DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCTSTR lpName)
{
   HANDLE handle = (HANDLE)_get_osfhandle(_fileno((FILE*)stream));
   return CreateFileMapping(handle, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
}

#endif /* _WIN32 */

#ifdef _WIN32
   int fopen_setlength(voidpf opaque, voidpf stream, ZPOS_T size)
   {
      int ret = -1;
      FILE* file = (FILE*)stream;
      /* let's go 64 bit, regardless of ZLIBIOAPI64 */
      fpos_t newpos = size;
      fpos_t oldpos;
      if (0 == fgetpos(file, &oldpos))
      {
         if (0 == fsetpos(file, &newpos))
         {
            HANDLE handle = (HANDLE)_get_osfhandle(_fileno(file));
            if (SetEndOfFile(handle))
            {
               ret = fsetpos(file, &oldpos);
            }
         }
      }
      return ret;
   }
#else
   int fopen_setlength(voidpf opaque, voidpf stream, ZPOS_T size)
   {
      int ret;
      ret = _chsize(_fileno((FILE*)stream), size /* signed long */);
      return ret;
   }
#endif

#ifdef _MSDOS

extern long ZCALLBACK fseek_file_func OF((
   voidpf opaque,
   voidpf stream,
   ZPOS_T offset,
   int origin));

int fopen_setlength(voidpf opaque, voidpf stream, ZPOS_T size)
{
   int ret = fseek_file_func(opaque, stream, size, ZLIB_FILEFUNC_SEEK_SET);
   if (0 == ret)
   {
	   UINT nWritten = 0;
	   ret = _dos_write(_fileno((FILE*)stream), NULL, 0, &nWritten);
   }
   return ret;
}
#endif

ZPOS_T zgetlength_file(voidpf stream, zlib_filefunc_def* pzlib_filefunc_def)
{
   ZPOS_T len;
   const ZPOS_T pos = ZTELL(*pzlib_filefunc_def, stream);
   ZSEEK(*pzlib_filefunc_def, stream, 0, ZLIB_FILEFUNC_SEEK_END);
   len = ZTELL(*pzlib_filefunc_def, stream);
   ZSEEK(*pzlib_filefunc_def, stream, pos, ZLIB_FILEFUNC_SEEK_SET);
   return len;
}

ZPOS_T zgetlength_fileW(voidpf stream, zlib_filefunc_defW* pzlib_filefunc_def)
{
   ZPOS_T len;
   const ZPOS_T pos = ZTELL(*pzlib_filefunc_def, stream);
   ZSEEK(*pzlib_filefunc_def, stream, 0, ZLIB_FILEFUNC_SEEK_END);
   len = ZTELL(*pzlib_filefunc_def, stream);
   ZSEEK(*pzlib_filefunc_def, stream, pos, ZLIB_FILEFUNC_SEEK_SET);
   return len;
}

int zeof_file(voidpf stream, zlib_filefunc_def* pzlib_filefunc_def)
{
   ZPOS_T len;
   const ZPOS_T pos = ZTELL(*pzlib_filefunc_def, stream);
   ZSEEK(*pzlib_filefunc_def, stream, 0, ZLIB_FILEFUNC_SEEK_END);
   len = ZTELL(*pzlib_filefunc_def, stream);
   ZSEEK(*pzlib_filefunc_def, stream, pos, ZLIB_FILEFUNC_SEEK_SET);
   return (pos >= len);
}

int zeof_fileW(voidpf stream, zlib_filefunc_defW* pzlib_filefunc_def)
{
   ZPOS_T len;
   const ZPOS_T pos = ZTELL(*pzlib_filefunc_def, stream);
   ZSEEK(*pzlib_filefunc_def, stream, 0, ZLIB_FILEFUNC_SEEK_END);
   len = ZTELL(*pzlib_filefunc_def, stream);
   ZSEEK(*pzlib_filefunc_def, stream, pos, ZLIB_FILEFUNC_SEEK_SET);
   return (pos >= len);
}

#ifndef IMAGE_UNICODE_SIGNATURE
   #define IMAGE_UNICODE_SIGNATURE 0xFEFF /* magic number - unicode text file */
#endif
#ifndef CPM_TEXT_TERMINATOR
   #define CPM_TEXT_TERMINATOR 0x1A
#endif
#ifndef LOBYTE
   #define LOBYTE(w)           ((unsigned char)(w))
#endif
#ifndef HIBYTE
   #define HIBYTE(w)           ((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))
#endif

#define ALLOC_STRINGA(len) (char   *)(malloc((len) * sizeof(char   )))
#define ALLOC_STRINGW(len) (wchar_t*)(malloc((len) * sizeof(wchar_t)))

char* zgets_file(void* stream, const struct zlib_filefunc_def_s* api, char* szDst, int nMax, int* bUnicode)
{
   char* sz = szDst;
   wchar_t* wsz = NULL;
   BOOL bContinue;
   int count = 0, unicode_count = 0;

   for (bContinue = TRUE; bContinue && (count < (nMax - 1)); )
   {
      if (*bUnicode)
      {
         if (wsz == NULL) wsz = ALLOC_STRINGW(nMax);
         bContinue = ZREAD(*api, stream, &wsz[count], sizeof(wsz[0]));
         if (bContinue) switch (wsz[count])
         {
            case '\r':
               break;
            case '\n':
               count++;
               bContinue = FALSE;
               break;
            case '\0':
               bContinue = FALSE;
               break;
            default:
               count++;
               break;
         }
      }
      else
      {
         bContinue = ZREAD(*api, stream, &sz[count], sizeof(sz[0]));
         if (bContinue) switch ((unsigned char)sz[count])
         {
            case LOBYTE(IMAGE_UNICODE_SIGNATURE):
               if (1 == ZTELL(*api, stream))
               {
                  unicode_count++;
                  continue;
               }
               break;
            case HIBYTE(IMAGE_UNICODE_SIGNATURE):
               if (2 == ZTELL(*api, stream))
               {
                  unicode_count++;
                  if (unicode_count == 2)
                  {
                     count = 0;
                     *bUnicode = TRUE;
                  }
                  continue;
               }
               break;
            default:
               break;
         }
         if (bContinue) switch (sz[count])
         {
            case '\r':
               break;
            case '\n':
               count++;
               bContinue = FALSE;
               break;
            case CPM_TEXT_TERMINATOR:
               /* move to end */
               ZSEEK(*api, stream, 0, ZLIB_FILEFUNC_SEEK_END);
               bContinue = FALSE;
               break;
            case '\0':
               bContinue = FALSE;
               break;
            default:
               count++;
               break;
         }
      }
   }
   if (count)
   {
      if (wsz)
      {
         wsz[count] = 0;
         wcstombs(szDst, wsz, nMax);
      }
      else
      {
         sz[count] = 0;
      }
   }
   free(wsz);
   return (count ? szDst : NULL);
}

wchar_t* zgets_fileW(void* stream, const struct zlib_filefunc_defW_s* api, wchar_t* szDst, int nMax, int* bUnicode)
{
   wchar_t* wsz = NULL;
   char* sz = ALLOC_STRINGA(nMax);
   BOOL bContinue;
   int count = 0, unicode_count = 0;

   for (bContinue = TRUE; bContinue && (count < (nMax - 1)); )
   {
      if (*bUnicode)
      {
         if (wsz == NULL) wsz = szDst;
         bContinue = ZREAD(*api, stream, &wsz[count], sizeof(wsz[0]));
         if (bContinue) switch (wsz[count])
         {
            case '\r':
               break;
            case '\n':
               count++;
               bContinue = FALSE;
               break;
            case '\0':
               bContinue = FALSE;
               break;
            default:
               count++;
               break;
         }
      }
      else
      {
         bContinue = ZREAD(*api, stream, &sz[count], sizeof(sz[0]));
         if (bContinue) switch ((unsigned char)sz[count])
         {
            case LOBYTE(IMAGE_UNICODE_SIGNATURE):
               if (1 == ZTELL(*api, stream))
               {
                  unicode_count++;
                  continue;
               }
               break;
            case HIBYTE(IMAGE_UNICODE_SIGNATURE):
               if (2 == ZTELL(*api, stream))
               {
                  unicode_count++;
                  if (unicode_count == 2)
                  {
                     count = 0;
                     *bUnicode = TRUE;
                  }
                  continue;
               }
               break;
            default:
               break;
         }
         if (bContinue) switch (sz[count])
         {
            case '\r':
               break;
            case '\n':
               count++;
               bContinue = FALSE;
               break;
            case CPM_TEXT_TERMINATOR:
               /* move to end */
               ZSEEK(*api, stream, 0, ZLIB_FILEFUNC_SEEK_END);
               bContinue = FALSE;
               break;
            case '\0':
               bContinue = FALSE;
               break;
            default:
               count++;
               break;
         }
      }
   }
   if (count)
   {
      if (wsz)
      {
         wsz[count] = 0;
      }
      else
      {
         sz[count] = 0;
         mbstowcs(szDst, sz, nMax);
      }
   }
   free(sz);
   return (count ? szDst : NULL);
}

int zprintf(struct zlib_filefunc_def_s* fileapi, void *fp, const char* fmt, ...)
{
   char sz[512];
   int len;
   va_list args;

   va_start(args, fmt);
   len = _vsnprintf(sz, _countof(sz), fmt, args);
   va_end(args);
   ZWRITE(*fileapi, fp, sz, len);
   return len;
}

