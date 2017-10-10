/* ioapiw.h - Achar/Wchar support - by Troels K. 2003 */
/* if you use zip/unzip by Gilles Vollant, make sure that unzip\* is in sync */

#ifndef __IOAPI_H__
#define __IOAPI_H__

#ifndef ZLIB_H
   #include "zlib.h" /* zconf.h subset */
#endif


#ifndef _ZLIBIOAPI_H
   #include "unzip\ioapi.h"
#endif
#ifdef x_WIN32
   #include "unzip\iowin32.h"
#endif

#ifdef __cplusplus
   extern "C" {
#endif

extern int fopen_setlength  OF((voidpf opaque, voidpf stream, ZPOS_T size));

extern ZPOS_T zgetlength_file  OF((voidpf stream, zlib_filefunc_def *));
extern char*  zgets_file (void* stream, const struct zlib_filefunc_def_s* , char   * szDst, int nMax, int* bUnicode);
extern int    zeof_file  OF((voidpf stream, zlib_filefunc_def *));

#ifdef _WCHAR_T_DEFINED

typedef voidpf (ZCALLBACK *open_file_funcW) OF((voidpf opaque, const wchar_t* filename, int mode));

typedef struct zlib_filefunc_defW_s
{
    open_file_funcW     zopen_file;
    read_file_func      zread_file;
    write_file_func     zwrite_file;
    tell_file_func      ztell_file;
    seek_file_func      zseek_file;
    close_file_func     zclose_file;
    testerror_file_func zerror_file;
    voidpf              opaque;
} zlib_filefunc_defW;

extern void fill_fopen_filefuncW OF((zlib_filefunc_defW*));
extern void fill_filefuncA2W(zlib_filefunc_defW* wapi, const zlib_filefunc_def* api, open_file_funcW open_fn);
extern int  zprintf(struct zlib_filefunc_def_s*, void *fp, const char* fmt, ...);

extern ZPOS_T   zgetlength_fileW OF((voidpf stream, zlib_filefunc_defW*));
extern wchar_t* zgets_fileW(void* stream, const struct zlib_filefunc_defW_s*, wchar_t* szDst, int nMax, int* bUnicode);
extern int      zeof_fileW OF((voidpf stream, zlib_filefunc_defW*));

   #ifdef _WIN32
      extern void fill_win32_filefuncW OF((zlib_filefunc_defW*));
      extern int  win32_chsize         OF((voidpf opaque, voidpf stream, ZPOS_T size));
      #ifdef _INC_WINDOWS
         extern HANDLE win32_createfilemapping(voidpf opaque, voidpf stream, 
            LPSECURITY_ATTRIBUTES, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCTSTR lpName);
         extern HANDLE fopen_createfilemapping(voidpf opaque, voidpf stream, 
            LPSECURITY_ATTRIBUTES, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCTSTR lpName);
      #endif
   #endif
#endif

#ifdef _UNICODE
   #define tfill_fopen_filefunc fill_fopen_filefuncW
   #define tzlib_filefunc_def   zlib_filefunc_defW
   #define tfill_win32_filefunc fill_win32_filefuncW 
   #define tzlib_filefunc_def_s zlib_filefunc_defW_s
   #define tzgetlength_file     zgetlength_fileW
   #define tzeof_file           zeof_fileW
   #define tzgets_file          zgets_fileW
#else
   #define tfill_fopen_filefunc fill_fopen_filefunc
   #define tzlib_filefunc_def   zlib_filefunc_def
   #define tfill_win32_filefunc fill_win32_filefunc
   #define tzlib_filefunc_def_s zlib_filefunc_def_s
   #define tzgetlength_file     zgetlength_file
   #define tzeof_file           zeof_file
   #define tzgets_file          zgets_file
#endif

#ifdef __cplusplus
   }
#endif

#define ZOPEN(filefunc,filename,mode) (*(filefunc).zopen_file)((filefunc).opaque,filename,mode)
#define ZGETS(filefunc,filestream,szDst,nMax,bUnicode) tzgets_file(filestream,&(filefunc),szDst,nMax,bUnicode)
#define ZEOF(filefunc,filestream) tzeof_file(filestream,&(filefunc))

#endif /* __IOAPI_H__ */
