/* main.c - this module uses TCHAR */

#ifndef _MSDOS
   #include <windows.h>
#endif
#include <tchar.h>
#include "..\cfgapi.h"
#include "..\cfg_file.h"
#ifndef _MSDOS
   #include "..\cfg_reg.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#ifdef _MSDOS
   #include <dos.h>
#else
   #include <io.h>
#endif

#ifndef _countof
   #define _countof(array) (sizeof(array)/sizeof((array)[0]))
#endif

void Try(CFGAPI* api, CFGHANDLE handle)
{
   TCHAR sz[80];
   long n;
   (*api->put_string  )(handle, _T("Text"), _T("Testing3"));
   (*api->get_string  )(handle, _T("Text"), sz, _countof(sz), NULL);
   n = (*api->get_long)(handle, _T("Value"), 555);
   _tprintf(_T("%s - %d\n"), sz, n);
}

int _tmain(void)
{
   const TCHAR* szSection = _T("Section A");
   CFGAPI ini_api;
#ifndef _MSDOS
   CFGAPI reg_api;
#endif
   CFGHANDLE handle;

   handle = cfg_ini_topen(&ini_api, _T("test.ini"), szSection, NULL);
   if (handle)
   {
      Try(&ini_api, handle);
      (*ini_api.close)(&handle);
   }

#if defined(_WINDOWS) || defined(_WIN32)
   handle = cfg_reg_topen(&reg_api, HKEY_CURRENT_USER, _T("SOFTWARE\\Troels K.\\Settings"));
   if (handle)
   {
      Try(&reg_api, handle);
      (*reg_api.close)(&handle);
   }
#endif
   return EXIT_SUCCESS;
}
