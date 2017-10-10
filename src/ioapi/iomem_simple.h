#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

EXTERN_C void* mem_simple_create_file(zlib_filefunc_def*, void* buffer, size_t buflen);
EXTERN_C void* mem_simple_detach(void* stream);
