/* zlib.h */

#ifndef ZLIB_H
#define ZLIB_H

/* dummy file to satisfy ioapi.c - can be deleted if zlib\zlib.h is in path */

   #ifndef FAR
   #   define FAR
   #endif
   typedef void FAR *voidpf;
   typedef void     *voidp;
   typedef unsigned long  uLong; /* 32 bits or more */
   #ifndef OF
      #define OF(args)  args
   #endif

#endif
