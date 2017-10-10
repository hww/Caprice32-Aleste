/* iomem.h */

#ifndef __IOMEM_H__
#define __IOMEM_H__

#ifndef EXTERN_C
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

#ifndef tzlib_filefunc_def_s
   #ifdef _UNICODE
      #define tzlib_filefunc_def_s zlib_filefunc_defW_s
   #else
      #define tzlib_filefunc_def_s zlib_filefunc_def_s
   #endif
#endif

struct _MEMFILEDATA;
struct _MEMFILEIMPL;

typedef struct _MEMFILEIMPL* MEMFILEHANDLE;

EXTERN_C MEMFILEHANDLE mem_create_file(struct tzlib_filefunc_def_s*, LPCTSTR name, void* buffer, size_t buflen);
EXTERN_C MEMFILEHANDLE mem_open_file  (struct tzlib_filefunc_def_s*, struct _MEMFILEDATA*);
EXTERN_C void   mem_remove    (struct _MEMFILEDATA**);
EXTERN_C size_t mem_filelength(MEMFILEHANDLE);
EXTERN_C BOOL   mem_feof      (MEMFILEHANDLE);
EXTERN_C int    mem_touch     (MEMFILEHANDLE, time_t utc);

#endif /* __IOMEM_H__ */
