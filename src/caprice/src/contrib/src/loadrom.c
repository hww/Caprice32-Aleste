/* loadrom.c */

/* Copyright (c) Troels K. 2003-2004 */

#include <stdio.h>
#include <tchar.h>

#include "../include/loadrom.h"

#ifdef _WIN32
   #include <windows.h>
   HINSTANCE PUB_CapriceResourceInstance = NULL;
#endif

#ifdef _WIN32

BOOL load_rom(const TCHAR* src, void* dst, size_t len)
{
   TCHAR title[_MAX_PATH], ext[_MAX_PATH];
   HINSTANCE hInstance = PUB_CapriceResourceInstance;
   HRSRC hResource;
   BOOL bOK = FALSE;
   TCHAR chPath[_MAX_PATH];
   TCHAR* begin, *end;
   _tcscpy(chPath, src);
   
   begin = _tcschr(chPath, '<');
   end   = _tcschr(chPath, '>');
   if (end) *end = 0;

   _tsplitpath(chPath + (begin ? 1 : 0), NULL, NULL, title, ext);

   hResource = FindResource(hInstance, title, ext + ((*ext == '.') ? 1 : 0));
   if (hResource)
   {
      HGLOBAL hMem = LoadResource(hInstance, hResource);
      if (hMem)
      {
         void* p = LockResource(hMem);
         memcpy(dst, p, len);
         bOK = TRUE;
      }
   }
   return bOK;
}
#else
BOOL load_rom(const char* chPath, void* dst, size_t len)
{
   FILE* pfileObject = fopen(chPath, "rb");
   BOOL bOK = (pfileObject != NULL);
   if (bOK)
   { // load CPC OS + Basic
      fread(dst, len, 1, pfileObject);
      fclose(pfileObject);
   }
   return bOK;
}
#endif
