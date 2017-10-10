/* ffapi.c */
/* Copyright (c) 2004 by Troels K. */

#ifdef _WIN32
   #include <io.h> /* msvc: avoid wrong prototype in wchar.h! */
   #define HAVE_FINDFIRST   
#elif _MSDOS
   #include <dos.h>
   #define _findfirsti64(a,b) (_dos_findfirst((a),_A_NORMAL|_A_RDONLY|_A_HIDDEN|_A_SYSTEM|_A_ARCH,(b)) ? -1 : +1)
   #define _findnexti64(a,b) (_dos_findnext(b) ? -1 : 0)
   #define _findclose(a)
   #define HAVE_FINDFIRST   
#else /* posix */
   #include <dirent.h>
   #include <wchar.h>
   #include "../code/tchar.h"
   #define _FFIMPLW _FFIMPLA
#endif
#define _countof(array) (sizeof(array)/sizeof((array)[0]))
#include <sys/stat.h>

#include "ffapi.h"

#include <stdlib.h>
#include <string.h>

#ifndef LINKSPEC
   #define LINKSPEC __inline static
#endif

#if !defined(HAVE_FINDFIRST)
static int ffapi_host_stat_impl(const char* file, struct _finddatai64_t* dst)
{
   struct stat st;
   int result = stat(file, &st);
   if (result == 0)
   {
      dst->size         = st.st_size;
      dst->time_create  = st.st_ctime;
      dst->time_write   = st.st_mtime;
      dst->time_access  = st.st_atime;
      dst->attrib = 0;
      if ((st.st_mode & S_IFMT) == S_IFDIR ) dst->attrib|= _A_SUBDIR, dst->size = 0;
      if ((st.st_mode & S_IFMT) != S_IWRITE) dst->attrib|= _A_RDONLY;
   }
   return result;
}

static int ffapi_host_stat_implw(const wchar_t* file, struct _finddatai64_t* dst)
{
   struct _stat st;
   int result = _wstat(file, &st);
   if (result == 0)
   {
      dst->size         = st.st_size;
      dst->time_create  = st.st_ctime;
      dst->time_write   = st.st_mtime;
      dst->time_access  = st.st_atime;
      dst->attrib = 0;
      if ((st.st_mode & S_IFMT) == S_IFDIR ) dst->attrib|= _A_SUBDIR, dst->size = 0;
      if ((st.st_mode & S_IFMT) != S_IWRITE) dst->attrib|= _A_RDONLY;
   }
   return result;
}

static int dirent2finddata_helper(struct _finddatai64_t* dst, const struct dirent* src, const char* root)
{
   char szFullpath[_MAX_PATH];
   _makepath(szFullpath, NULL, root, src->d_name, NULL);
   return ffapi_host_stat_impl(szFullpath, dst);
}

static void dirent2finddata(struct _finddatai64_t* dst, const struct dirent* src, const char* root)
{
   dirent2finddata_helper(dst, src, root);
   strcpy(dst->name, src->d_name);
}

static void wdirent2finddata(struct _wfinddatai64_t* dst, const struct dirent* src, const char* root)
{
   dirent2finddata_helper((struct _finddatai64_t*)dst, src, root);
   mbstowcs(dst->name, src->d_name, _countof(dst->name));
}

typedef struct _FFIMPLA
{
   char root[_MAX_PATH];
   DIR* dir;
} FFIMPLA;

#endif

LINKSPEC FFHANDLEA findopen_impl(void* filesystem, const char* dir, struct _finddatai64_t* fileinfo)
{
#ifdef HAVE_FINDFIRST
   struct _finddatai64_t temp;
   char sz[_MAX_PATH];
   long ff;

   _makepath(sz, NULL, dir, "*.*", NULL);
   ff = _findfirsti64(sz, fileinfo ? fileinfo : &temp);
   return (ff != -1) ? (struct _FFIMPLA*)ff : NULL;
#else
   FFIMPLA* handle = NULL;
   DIR* dir = opendir (filter);
   if (dir)
   {
      handle = (FFIMPLA*)malloc(sizeof(FFIMPLA));
      handle->dir = dir;
      strcpy(handle->root, filter);
      if (fileinfo) dirent2finddata(fileinfo, readdir(dir), handle->root);
   }
   return handle;
#endif
}

LINKSPEC int findnext_impl(FFHANDLEA handle, struct _finddatai64_t* fileinfo)
{
#ifdef HAVE_FINDFIRST
   struct _finddatai64_t temp;
   return _findnexti64((long)handle, fileinfo ? fileinfo : &temp);
#else
   struct dirent* dir = readdir(handle->dir);
   if (dir) dirent2finddata(fileinfo, dir, handle->root);
   return dir ? 0 : -1;
#endif
}

LINKSPEC void findclose_impl(FFHANDLEA* handle)
{
#ifdef HAVE_FINDFIRST
   _findclose((long)*handle);
#else
   closedir ((*handle)->dir);
   free(*handle);
#endif
   *handle = NULL;
}

void ffapi_host_fill(FFAPIA* api)
{
   api->open  = findopen_impl;
   api->next  = findnext_impl;
   api->close = findclose_impl;
   api->filesystem = NULL;
}

int ffapi_host_stat(const char* file, struct _finddatai64_t* fileinfo)
{
   struct _finddatai64_t temp;
   BOOL bOK = (NULL == strpbrk(file, "*?"));
#ifdef HAVE_FINDFIRST
   if (bOK)
   {
      long ff;
      ff = _findfirsti64(file, fileinfo ? fileinfo : &temp);
      bOK = (ff != -1);
      if (bOK)
      {
         _findclose(ff);
      }
   }
   return bOK ? 0 : -1;
#else
   int result = -1;
   if (bOK)
   {
      result = ffapi_host_stat_impl(file, fileinfo ? fileinfo : &temp);
      if (0 == result)
      {
         const char* end = max(strrchr(file, '\\'), strrchr(file, '/'));
         strncpy(fileinfo->name, end ? (end + 1) : file, _countof(fileinfo->name));
      }
   }
   return result;
#endif
}

BOOL ffapi_host_driveready(const char* dir)
{
   return (0 == _access(dir, 0));
}

#if !defined(_MSDOS)

LINKSPEC FFHANDLEW wfindopen_impl(void* filesystem, const wchar_t* dir, struct _wfinddatai64_t* fileinfo)
{
#ifdef HAVE_FINDFIRST
   struct _wfinddatai64_t temp;
   wchar_t sz[_MAX_PATH];
   long ff;
   
   _wmakepath(sz, NULL, dir, L"*.*", NULL);
   ff = _wfindfirsti64(sz, fileinfo ? fileinfo : &temp);
   filesystem;
   return (ff != -1) ? (struct _FFIMPLW*)ff : NULL;
#else
   char sz[_MAX_PATH];
   FFIMPLA* handle = NULL;
   DIR* dir;

   wcstombs(sz, filter, _countof(sz));
   dir  = opendir (sz);
   if (dir)
   {
      handle = (FFIMPLA*)malloc(sizeof(FFIMPLA));
      handle->dir = dir;
      strcpy(handle->root, sz);
      if (fileinfo) wdirent2finddata(fileinfo, readdir(dir), handle->root);
   }
   return handle;
#endif
}

LINKSPEC int wfindnext_impl(FFHANDLEW handle, struct _wfinddatai64_t* fileinfo)
{
#ifdef HAVE_FINDFIRST
   struct _wfinddatai64_t temp;
   return _wfindnexti64((long)handle, fileinfo ? fileinfo : &temp);
#else
   struct dirent* dir = readdir(handle->dir);
   if (dir)
   {
      wdirent2finddata(fileinfo, dir, handle->root);
   }
   return dir ? 0 : -1;
#endif
}

LINKSPEC void wfindclose_impl(FFHANDLEW* handle)
{
#ifdef HAVE_FINDFIRST
   _findclose((long)*handle);
#else
   closedir ((*handle)->dir);
   free(*handle);
#endif
   *handle = NULL;
}

void ffapi_host_fillw(FFAPIW* api)
{
   api->open  = wfindopen_impl;
   api->next  = wfindnext_impl;
   api->close = wfindclose_impl;
   api->filesystem = NULL;
}

int ffapi_host_statw(const wchar_t* file, struct _wfinddatai64_t* fileinfo)
{
   struct _wfinddatai64_t temp;
   BOOL bOK = (NULL == wcspbrk(file, L"*?"));
#ifdef HAVE_FINDFIRST
   if (bOK)
   {
      long ff;
      ff = _wfindfirsti64(file, fileinfo ? fileinfo : &temp);
      bOK = (ff != -1);
      if (bOK)
      {
         _findclose(ff);
      }
   }
   return bOK ? 0 : -1;
#else
   int result = -1;
   if (bOK)
   {
      result = ffapi_host_stat_implw(file, (struct _finddatai64_t*)(fileinfo ? fileinfo : &temp));
      if (0 == result)
      {
         wcsncpy(fileinfo->name, file, _countof(fileinfo->name));
      }
   }
   return result;
#endif
}

void mbstowcs_finddata(struct _wfinddatai64_t* dst, const struct _finddatai64_t* src)
{
   dst->attrib      = src->attrib;
   dst->time_create = src->time_create;
   dst->time_access = src->time_access;
   dst->time_write  = src->time_write;
   dst->size        = src->size;
   mbstowcs(dst->name, src->name, _countof(dst->name));
}

void wcstombs_finddata(struct _finddatai64_t* dst, const struct _wfinddatai64_t* src)
{
   dst->attrib      = src->attrib;
   dst->time_create = src->time_create;
   dst->time_access = src->time_access;
   dst->time_write  = src->time_write;
   dst->size        = src->size;
   wcstombs(dst->name, src->name, _countof(dst->name));
}

BOOL ffapi_host_drivereadyw(const wchar_t* dir)
{
   return (0 == _waccess(dir, 0));
}

#endif /* !_MSDOS */


