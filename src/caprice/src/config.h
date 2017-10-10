/* config.h */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef _WIN32
   #define USE_CFGAPI    1 /* USE_CFGAPI=1 pulls in ../cfgapi and ../ioapi */
   #define USE_ROMFOLDER 0 /* roms are inside exe */
#else
   #define USE_CFGAPI    0 /* no real benefit from using cfgapi on Registry-less platforms */
   #define USE_ROMFOLDER 1 /* roms are in files */
#endif

#if USE_ROMFOLDER
   #define AMSDOS "amsdos.rom"
#else
   #define AMSDOS "<amsdos.rom>"
#endif

#ifndef ZLIB_H
   typedef unsigned char Byte;
   typedef unsigned long uLong;
   typedef unsigned int uInt;
#endif
typedef unsigned short word;

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

#ifndef _countof
   #define _countof(array) (sizeof(array)/sizeof((array)[0]))
#endif

#ifdef _MSC_VER
   #define inline __inline
   #ifdef __cplusplus
   #else
      /* bool is a C++ feature, only available in C++ mode in MSVC 
         you really shouldn't use bool in a mixed C/C++ program
         check out bool.h
      */
      #define bool unsigned char
      #define false 0
      #define true 1
   #endif

   #define int64_t __int64
   #define mktemp _mktemp
   #define getcwd _getcwd

   #define strncasecmp _tcsnicmp
   #define strcasecmp _tcsicmp

   #include <io.h>
   #include <direct.h>
   #include <math.h>

   __inline double rint1(double x)
   {
      double n = 0.0;
      double f = modf(x, &n);
      if (x > 0.0)
      {
         if (f > 0.5) n+=1.0;
      }
      else if (x < 0.0)
      {
         if (f < -0.5) n-=1.0;
      }
      return n;
   }
   __inline double rint2(double x)
   {
       _asm {
           fld [x]
           frndint
           fstp [x] 
       }
       return x;
   }
   __inline double rint3( double x)
   // Copyright (C) 2001 Tor M. Aamodt, University of Toronto
   // Permisssion to use for all purposes commercial and otherwise granted.
   // THIS MATERIAL IS PROVIDED "AS IS" WITHOUT WARRANTY, OR ANY CONDITION OR
   // OTHER TERM OF ANY KIND INCLUDING, WITHOUT LIMITATION, ANY WARRANTY
   // OF MERCHANTABILITY, SATISFACTORY QUALITY, OR FITNESS FOR A PARTICULAR
   // PURPOSE.
   {
       if( x > 0 ) {
           __int64 xint = (__int64) (x+0.5);
           if( xint % 2 ) {
               // then we might have an even number...
               double diff = x - (double)xint;
               if( diff == -0.5 )
                   return (double)(xint-1);
           }
           return (double)xint;
       } else {
           __int64 xint = (__int64) (x-0.5);
           if( xint % 2 ) {
               // then we might have an even number...
               double diff = x - (double)xint;
               if( diff == 0.5 )
                   return (double)(xint+1);
           }
           return (double)xint;
       }
   }
   #define rint rint2
#else
   #include <stdint.h>
   #include <unistd.h>
#endif

#include <tchar.h>
#undef _PC
#include "contrib/include/bool.h"

#endif /* __CONFIG_H__ */
