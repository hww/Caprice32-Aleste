/* cfg_reg.h */
/* Copyright (c) 2004 by Troels K. */

#ifndef __CFG_REGISTRY_H__
#define __CFG_REGISTRY_H__

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif
#include "cfgapi.h"

#if !(defined(_INC_WINDOWS) || defined(_WINDOWS_H))
   #define HKEY void*
#endif

EXTERN_C CFGHANDLEA cfg_reg_open  (HKEY root, const char* section_root);
EXTERN_C CFGHANDLEA cfg_reg_attach(HKEY key);
EXTERN_C void       cfg_reg_detach(CFGHANDLEA*);
EXTERN_C HKEY       cfg_reg_getkey(CFGHANDLEA);

#if defined(_WCHAR_T_DEFINED) && !defined(_MSDOS)

EXTERN_C CFGHANDLEW cfg_reg_wopen  (HKEY root, const wchar_t* section_root);
EXTERN_C CFGHANDLEW cfg_reg_wattach(HKEY key);
EXTERN_C void       cfg_reg_wdetach(CFGHANDLEW*);
EXTERN_C HKEY       cfg_reg_wgetkey(CFGHANDLEW);

#endif

#if defined(UNICODE) || defined(_UNICODE)
   #define cfg_reg_topen   cfg_reg_wopen
   #define cfg_reg_tattach cfg_reg_wattach
   #define cfg_reg_tgetkey cfg_reg_wgetkey
#else
   #define cfg_reg_topen   cfg_reg_open
   #define cfg_reg_tattach cfg_reg_attach
   #define cfg_reg_tgetkey cfg_reg_getkey
#endif

#endif /* __CFG_REGISTRY_H__ */
