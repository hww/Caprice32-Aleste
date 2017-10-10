/* cfg_file.c */
/* Copyright (c) 2004 by Troels K. */

#ifndef _MSDOS
#include <wchar.h>
#endif
#include <tchar.h>

#include <stdio.h>

#include "cfg_file.h"
#include "cfgapi.h"
#include "..\ioapi\ioapiw.h"

#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <tchar.h>
#include <io.h>
#include <sys\stat.h>

#ifndef _countof
   #define _countof(array) (sizeof(array)/sizeof((array)[0]))
#endif

/***** Routines to read profile strings --  by Joseph J. Graf ******/
/* Ported to cfgapi/ioapi by Troels K. */

#define MAX_LINE_LENGTH    256

static int zgetc(struct zlib_filefunc_def_s* fileapi, void *fp)
{
   unsigned char n;
   if (ZREAD(*fileapi, fp, &n, sizeof(n)))
   {
      return n;
   }
   else
   {
      return EOF;
   }
}

/*****************************************************************
* Function:     read_line()
* Arguments:    <FILE *> fp - a pointer to the file to be read from
*               <char *> bp - a pointer to the copy buffer
* Returns:      TRUE if successful FALSE otherwise
******************************************************************/
static BOOL read_line(struct zlib_filefunc_def_s* fileapi, void *fp, char* bp) 
{
   char c = 0;
   int i = 0;
   /* Read one line from the source file */
   for (;;)
   {
      c = (char)zgetc(fileapi, fp);
      if (c == '\r')
         break;
      switch (c)
      {
         case EOF:
            return FALSE;
         case '\n':
            continue;
      }
      bp[i++] = c;
   }
   bp[i] = 0;
   return TRUE;
}

/**************************************************************************
* Function:     get_private_profile_string()
* Arguments:    <char *> section - the name of the section to search for
*               <char *> entry - the name of the entry to find the szValue of
*               <char *> def - default string in the event of a failed read
*               <char *> buffer - a pointer to the buffer to copy into
*               <int> buffer_len - the max number of characters to copy
*               <char *> file_name - the name of the .ini file to read from
* Returns:      the number of characters copied into the supplied buffer
***************************************************************************/
unsigned long GetPrivateProfileString(
    const char*  section, // address of section name 
    const char*  entry  , // address of key name 
    const char*  def    , // address of default string 
    char      *  buffer , // address of destination buffer 
    int buffer_len      ,  // size of destination buffer 
    const char*  file_name, 
    struct zlib_filefunc_def_s* api
   ) 
{   
   char buff[MAX_LINE_LENGTH], t_section[MAX_LINE_LENGTH];
   const int len = strlen(entry);
   void *fp = (*api->zopen_file)(api->opaque, file_name, ZLIB_FILEFUNC_MODE_READ);
   char* ep;
   if (NULL == fp) return 0;
   sprintf(t_section, "[%s]", section);    /* Format the section name */
   /*  Move through file 1 line at a time until a section is matched or EOF */
   do
   {
      if (!read_line(api, fp,buff))
      {   
         ZCLOSE(*api, fp);
         if (def) strncpy(buffer,def,buffer_len);
         return def ? strlen(buffer) : 0;
      }
   }
   while (stricmp(buff,t_section));
   /* Now that the section has been found, find the entry.
    * Stop searching upon leaving the section's area. */
   do
   {
      if (!(read_line(api, fp,buff) && (*buff != '['))) 
      {
         ZCLOSE(*api, fp);
         if (def) strncpy(buffer,def,buffer_len);
         return def ? strlen(buffer) : 0;
      }
   } while (!((0 == strnicmp(buff,entry,len)) && (buff[len] == '=')));
   //ep = strchr(buff,'=');    /* Parse out the equal sign */
   ep = buff + len;
   if (ep && (*ep == '='))
   {
      ep++;
      /* Copy up to buffer_len chars to buffer */
      strncpy(buffer,ep,buffer_len - 2);
      buffer[buffer_len-1] = 0;
   }
   else
   {
      *buffer = 0;
   }
   ZCLOSE(*api, fp);               /* Clean up and return the amount copied */
   return strlen(buffer);
}

/*************************************************************************
 * Function:    write_private_profile_string()
 * Arguments:   <char *> section - the name of the section to search for
 *              <char *> entry - the name of the entry to find the szValue of
 *              <char *> buffer - pointer to the buffer that holds the string
 *              <char *> file_name - the name of the .ini file to read from
 * Returns:     TRUE if successful, otherwise FALSE
 *************************************************************************/
#define CRLF "\r\n"
BOOL WritePrivateProfileString(
    const char* section, // address of section name 
    const char*  entry, // address of key name 
    const char*  buffer,  // address of string to add 
    const char*  file_name, struct zlib_filefunc_def_s* fileapi,
    const char* tmp_name
   ) 
{
   void* rfp;
   void* wfp;
   char buff[MAX_LINE_LENGTH], t_section[MAX_LINE_LENGTH];
   const int len = strlen(entry);
   
   sprintf(t_section, "[%s]", section);/* Format the section name */
   rfp = (*fileapi->zopen_file)(fileapi->opaque, file_name, ZLIB_FILEFUNC_MODE_READ);
   if (NULL == rfp)
   { /* If the .ini file doesn't exist */
      wfp = (*fileapi->zopen_file)(fileapi->opaque, file_name, ZLIB_FILEFUNC_MODE_CREATE | ZLIB_FILEFUNC_MODE_WRITE); 
      if (NULL == wfp ) /*  then make one */
         return FALSE;
      zprintf(fileapi, wfp, "%s"   CRLF, t_section    );
      zprintf(fileapi, wfp, "%s=%s"CRLF, entry, buffer);
      ZCLOSE(*fileapi, wfp);
      return TRUE;
   }
   wfp = (*fileapi->zopen_file)(fileapi->opaque, tmp_name, ZLIB_FILEFUNC_MODE_CREATE | ZLIB_FILEFUNC_MODE_WRITE);
   if(NULL == wfp) 
   {
      ZCLOSE(*fileapi, rfp);
      return FALSE;
   }
   /* Move through the file one line at a time until a section is
    * matched or until EOF. Copy to temp file as it is read. */
   do
   {   
      if (!read_line(fileapi, rfp,buff))
      {   /* Failed to find section, so add one to the end */
         zprintf(fileapi, wfp, CRLF"%s" CRLF, t_section    );
         zprintf(fileapi, wfp, "%s=%s"CRLF, entry, buffer);
         /* Clean up and rename */
         ZCLOSE(*fileapi, rfp);
         ZCLOSE(*fileapi, wfp);
         return TRUE;
      }
      zprintf(fileapi, wfp, "%s"CRLF, buff);
   } while( stricmp(buff,t_section) );

   /* Now that the section has been found, find the entry. Stop searching
    * upon leaving the section's area. Copy the file as it is read
    * and create an entry if one is not found.  */
   for(;;) 
   {   
      if (!read_line(fileapi, rfp, buff) )
      {   /* EOF without an entry so make one */
         zprintf(fileapi, wfp, "%s=%s"CRLF, entry, buffer);
         /* Clean up and rename */
         ZCLOSE(*fileapi, rfp);
         ZCLOSE(*fileapi, wfp);
         return TRUE;
      }
      if( (!strnicmp(buff,entry,len)) || (*buff == 0) || (*buff == '['))
      {
         break;
      }
      zprintf(fileapi, wfp, "%s"CRLF, buff);
   }
   zprintf(fileapi, wfp, "%s=%s"CRLF, entry, buffer);
   if (*buff)
   {
      while( read_line(fileapi, rfp,buff) )
      {
         zprintf(fileapi, wfp, "%s"CRLF,buff);
      }
   }
   else do
   {
      zprintf(fileapi, wfp, "%s"CRLF,buff);
   }
   while( read_line(fileapi, rfp,buff) );

   /* Clean up and rename */
   ZCLOSE(*fileapi, wfp);
   ZCLOSE(*fileapi, rfp);
   return TRUE;
}

typedef struct _CFGIMPLA
{
   struct zlib_filefunc_def_s fileapi;
   char filename[_MAX_PATH];
   char section[80];
   BOOL modify;
} FILEPROFILEA;

static void close_impl(CFGHANDLEA* handle)
{
   free((*handle)->impl);
   free(*handle);
   *handle = NULL;
}

static BOOL put_string(CFGHANDLEA handle, const char* key, const char* sz)
{
   BOOL bOK;
   char tmp_name[_MAX_PATH];
   struct _stat temp;

#ifdef _MSDOS
    _fullpath(tmp_name, handle->impl->filename, sizeof(tmp_name));
    tmpnam(strrchr(tmp_name, '\\')); /* Get a temporary file name to copy to */
#else
   _makepath(tmp_name, NULL, NULL, handle->impl->filename, "tmp");
#endif

   bOK = WritePrivateProfileString(handle->impl->section, key, sz, handle->impl->filename, &handle->impl->fileapi, tmp_name);
   if (bOK && (0 == _stat(tmp_name, &temp)))
   {
      _unlink(handle->impl->filename);
      rename(tmp_name, handle->impl->filename);
   }
   return bOK;
}

static int get_string(CFGHANDLEA handle, const char* key, char* sz, int cc, const char* szDefault)
{
   unsigned long n = GetPrivateProfileString(handle->impl->section, key, NULL, sz, cc, handle->impl->filename, &handle->impl->fileapi);
   if (handle->impl->modify && (n == 0) && szDefault && *szDefault)
   {
      put_string(handle, key, szDefault);
      strncpy(sz, szDefault, cc);
      n = strlen(sz);
   }
   return n;
}

static long get_long(CFGHANDLEA handle, const char* key, long nDefault)
{
   long n = nDefault;
   char sz[80];
   ltoa(n, sz, 10);
   get_string(handle, key, sz, _countof(sz), sz);
   n = atol(sz);
   return n;
}

static BOOL put_long(CFGHANDLEA handle, const char* key, long n)
{
   char sz[80];
   ltoa(n, sz, 10);
   return put_string(handle, key, sz);
}

static BOOL set_section_impl(CFGHANDLEA handle, const char* section)
{
   strncpy(handle->impl->section , section , _countof(handle->impl->section));
   return TRUE;
}

CFGHANDLEA cfg_ini_open(const char* filename, const char* section, struct zlib_filefunc_def_s* fileapi, BOOL modify)
{
   CFGHANDLEA handle = (CFGDATAA*)malloc(sizeof(CFGDATAA));
   handle->impl = (FILEPROFILEA*)malloc(sizeof(FILEPROFILEA));
   
   handle->api.set_section = set_section_impl;
   handle->api.close       = close_impl;
   handle->api.get_string  = get_string;
   handle->api.put_string  = put_string;
   handle->api.get_long    = get_long;
   handle->api.put_long    = put_long;
   handle->api.get_binary  = NULL;
   handle->api.put_binary  = NULL;
   handle->api.opaque      = fileapi;

   if (fileapi)
   {
      handle->impl->fileapi = *fileapi;
   }
   else
   {
      fill_fopen_filefunc(&handle->impl->fileapi);
   }
   *handle->impl->section = *handle->impl->filename = 0;
   handle->impl->modify = modify;
   strncpy(handle->impl->filename, filename, _countof(handle->impl->filename));
   if (section) strncpy(handle->impl->section , section , _countof(handle->impl->section ));
   return handle;
}

#if !defined(_MSDOS)

typedef struct _CFGIMPLW
{
   struct zlib_filefunc_defW_s fileapi;
   wchar_t filename[_MAX_PATH];
   wchar_t section[80];
   BOOL    modify;
} FILEPROFILEW;

static void wclose_impl(CFGHANDLEW* handle)
{
   free((*handle)->impl);
   free(*handle);
   *handle = NULL;
}

static BOOL wput_string(CFGHANDLEW handle, const wchar_t* key, const wchar_t* sz)
{
   BOOL bOK;
   wchar_t tmp_name[_MAX_PATH];
   char akey[80];
   char asection[80];
   const int cc = wcslen(sz) + 1;
   char* asz = (char*)malloc(sizeof(char) * cc);
   struct _stat temp;

   _wmakepath(tmp_name, NULL, NULL, handle->impl->filename, L"tmp");

   wcstombs(akey    , key            , _countof(akey));
   wcstombs(asection, handle->impl->section, _countof(asection));
   wcstombs(asz     , sz             , cc);

   bOK = WritePrivateProfileString(asection, akey, asz, (char*)handle->impl->filename, (zlib_filefunc_def*)&handle->impl->fileapi, (char*)tmp_name);
   if (bOK && (0 == _wstat(tmp_name, &temp)))
   {
      _wunlink(handle->impl->filename);
      _wrename(tmp_name, handle->impl->filename);
   }
   free(asz);
   return bOK;
}

static int wget_string(CFGHANDLEW handle, const wchar_t* key, wchar_t* sz, int cc, const wchar_t* szDefault)
{
   char akey[80];
   char asection[80];
   char* asz = (char*)malloc(sizeof(char) * cc);
   unsigned long n;

   wcstombs(akey    , key, _countof(akey));
   wcstombs(asection, handle->impl->section, _countof(asection));
   
   n = GetPrivateProfileString(asection, akey, NULL, asz, cc, (char*)handle->impl->filename, (zlib_filefunc_def*)&handle->impl->fileapi);
   if (n == 0)
   {
      if (handle->impl->modify && szDefault && *szDefault)
      {
         wput_string(handle, key, szDefault);
         wcsncpy(sz, szDefault, cc);
         n = wcslen(sz);
      }
   }
   else
   {
      mbstowcs(sz, asz, cc);
   }
   free(asz);
   return n;
}

static long wget_long(CFGHANDLEW handle, const wchar_t* key, long nDefault)
{
   long n = nDefault;
   wchar_t sz[80];
   _ltow(n, sz, 10);
   wget_string(handle, key, sz, _countof(sz), sz);
   n = _wtol(sz);
   return n;
}

static BOOL wput_long(CFGHANDLEW handle, const wchar_t* key, long n)
{
   wchar_t sz[80];
   _ltow(n, sz, 10);
   return wput_string(handle, key, sz);
}

static BOOL wset_section_impl(CFGHANDLEW handle, const wchar_t* section)
{
   wcsncpy(handle->impl->section , section , _countof(handle->impl->section ));
   return TRUE;
}

CFGHANDLEW cfg_ini_wopen(const wchar_t* filename, const wchar_t* section, struct zlib_filefunc_defW_s* fileapi, BOOL modify)
{
   CFGHANDLEW handle = (CFGDATAW*)malloc(sizeof(CFGDATAW));
   handle->impl = (FILEPROFILEW*)malloc(sizeof(FILEPROFILEW));
   handle->api.set_section = wset_section_impl;
   handle->api.close       = wclose_impl;
   handle->api.get_string  = wget_string;
   handle->api.put_string  = wput_string;
   handle->api.get_long    = wget_long;
   handle->api.put_long    = wput_long;
   handle->api.get_binary  = NULL;
   handle->api.put_binary  = NULL;
   handle->api.opaque      = fileapi;
   if (fileapi)
   {
      handle->impl->fileapi = *fileapi;
   }
   else
   {
      fill_fopen_filefuncW(&handle->impl->fileapi);
   }
   handle->impl->modify = modify;
   wcsncpy(handle->impl->filename, filename, _countof(handle->impl->filename));
   if (section) wcsncpy(handle->impl->section , section , _countof(handle->impl->section ));
   return handle;
}

#endif

BOOL ini_getline(CFGHANDLE handle, int line, TCHAR* buf, size_t buf_size)
{
   BOOL bOK;
   CFGIMPL* impl = handle->impl;
   char buff[MAX_LINE_LENGTH], t_section[MAX_LINE_LENGTH];
   void* stream = (*impl->fileapi.zopen_file)(impl->fileapi.opaque, impl->filename, ZLIB_FILEFUNC_MODE_READ);
   bOK = (stream != NULL);
   if (bOK)
   {
   #if defined(_UNICODE) || defined(UNICODE)
      char asection[80];
      wcstombs(asection, impl->section, _countof(asection));
      sprintf(t_section, "[%s]", asection);    /* Format the section name */
   #else
      sprintf(t_section, "[%s]", impl->section);    /* Format the section name */
   #endif
      /*  Move through file 1 line at a time until a section is matched or EOF */
      do
      {
         if (!read_line((struct zlib_filefunc_def_s*)&impl->fileapi, stream, buff))
         {  
            bOK = FALSE;
            break;
         }
      }
      while (stricmp(buff,t_section));
      if (bOK)
      {
         int i;
         for (i = 0; i <= line; i++)
         {
            if (!read_line((struct zlib_filefunc_def_s*)&impl->fileapi, stream, buff))
            {
               bOK = FALSE;
               break;
            }
            if (*buff == '[')
            {
               bOK = FALSE;
               break;
            }
         }
         if (bOK)
         {
         #if defined(_UNICODE) || defined(UNICODE)
            mbstowcs(buf, buff, buf_size);
         #else
            strncpy(buf, buff, buf_size);
         #endif
         }
      }
      ZCLOSE(impl->fileapi, stream);
   }
   return bOK;
}
