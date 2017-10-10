#include "bool.h"

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

EXTERN_C BOOL load_rom(const TCHAR* chPath, void* dst, size_t len);

