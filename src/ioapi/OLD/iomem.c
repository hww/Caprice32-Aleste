/* iomem.c - Troels K. 2003-2004 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zlib.h"
#ifndef _ZLIBIOAPI_H
   #include "ioapi.h"
#endif
#include "iomem.h"
#include "../code/fseek.h"

typedef struct _MEMFILEDATA
{
   BOOL   bModified;
   time_t utc;
   size_t length;
   unsigned char* p;
   TCHAR* szFileName;
   struct _MEMFILEDATA* next;
} MEMFILEDATA; 

typedef struct _MEMFILEIMPL
{
   MEMFILEDATA* file;
   size_t position;
} MEMFILE;

typedef struct _FILESYSTEMIMPL
{
   struct _MEMFILEDATA* file_list;
} MEMFS;

static uLong ZCALLBACK mem_read (voidpf opaque, voidpf stream, void* dst, uLong cb)
{
   MEMFILEHANDLE handle = (MEMFILE*)stream;
   size_t dwRead = 0;
   if (handle->position < handle->file->length)
   {
      dwRead = min(cb, (handle->file->length - handle->position));
      memcpy(dst, handle->file->p + handle->position, dwRead);   
      handle->position+=dwRead;
   }
   return dwRead;
}

static uLong ZCALLBACK mem_write (voidpf opaque, voidpf stream, const void* src, uLong cb)
{
   MEMFILEHANDLE handle = (MEMFILE*)stream;
   size_t oldlength = handle->file->length;
   handle->file->length = max(handle->position + cb, handle->file->length);
   handle->file->p      = (unsigned char*)realloc(handle->file->p, handle->file->length);
   if (handle->position > oldlength)
   {
      memset(handle->file->p + oldlength, 0, handle->position - oldlength);
   }
   memcpy(handle->file->p + handle->position, src, cb);
   handle->position+=cb;
   handle->file->bModified = TRUE;
   handle->file->utc = time(NULL);
   return cb;
}

static long ZCALLBACK mem_tell (voidpf opaque, voidpf stream)
{
   MEMFILEHANDLE handle = (MEMFILE*)stream;
   return handle->position;
}

static long ZCALLBACK mem_seek (voidpf opaque, voidpf stream, uLong offset, int origin)
{
   MEMFILEHANDLE handle = (MEMFILE*)stream;
   return fseek_calc(offset, origin, &handle->position, handle->file->length);
}

static int ZCALLBACK mem_close (voidpf opaque, voidpf stream)
{
   MEMFILEHANDLE handle = (MEMFILE*)stream;
   free(handle);
   return 0;
}

static int ZCALLBACK mem_error (voidpf opaque, voidpf stream)
{
   MEMFILEHANDLE handle = (MEMFILE*)stream;
   return 0;
}

size_t mem_filelength(MEMFILEHANDLE handle)
{
   return handle->file->length;
}

BOOL mem_feof(MEMFILEHANDLE handle)
{
   return (handle->position >= handle->file->length);
}

int mem_touch(MEMFILEHANDLE handle, time_t utc)
{
   handle->file->utc = utc;
   return 0;
}

void mem_remove(MEMFILEDATA** handle)
{
   free((*handle)->p);
   free((*handle)->szFileName);
   free(*handle);
   *handle = NULL;
}

void iomem_fill_filefunc(tzlib_filefunc_def* api, MEMFILEHANDLE handle)
{
   api->zopen_file  = NULL;
   api->zread_file  = mem_read;
   api->zwrite_file = mem_write;
   api->ztell_file  = mem_tell;
   api->zseek_file  = mem_seek;
   api->zclose_file = mem_close;
   api->zerror_file = mem_error;
   api->opaque      = handle;
}

MEMFILEHANDLE mem_create_file(tzlib_filefunc_def* api, LPCTSTR name, void* buffer, size_t buf_len)
{
   MEMFILE    * handle   = (MEMFILE    *)malloc(sizeof(MEMFILE    ));
   MEMFILEDATA* filedata = (MEMFILEDATA*)malloc(sizeof(MEMFILEDATA));
 
   iomem_fill_filefunc(api, handle);
   handle->position = 0;
   handle->file = filedata;
   filedata->p  = (unsigned char*)buffer;
   filedata->length = buf_len;
   filedata->utc        = time(NULL);
   filedata->szFileName = _tcsdup(name);
   filedata->next       = NULL;
   filedata->bModified  = FALSE;
   return handle;
}

MEMFILEHANDLE mem_open_file(tzlib_filefunc_def* api, MEMFILEDATA* filedata)
{
   MEMFILEHANDLE handle = malloc(sizeof(*handle));
   handle->position = 0;
   handle->file = filedata;
   iomem_fill_filefunc(api, handle);
   return handle;
}
