/* main.h */

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

#include "bool.h"

EXTERN_C int caprice_main (int argc, TCHAR**argv, BOOL registry);
EXTERN_C void doCleanUp (void);
EXTERN_C const TCHAR* Caprice32_Profile;
EXTERN_C const TCHAR* Caprice32_Autotype;
