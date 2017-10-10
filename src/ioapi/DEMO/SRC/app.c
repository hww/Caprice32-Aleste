// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "app.h"
#include "..\..\ioapiw.h"
//#include "zlib\zlib.h" // testing co-existence with zlib

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
   if (argc > 1)
   {
      voidpf stream;
      tzlib_filefunc_def api;

      tfill_fopen_filefunc(&api);
      stream = (*api.zopen_file)(NULL, argv[1], ZLIB_FILEFUNC_MODE_READ);
      if (stream)
      {
         char buffer[80];
         size_t dwRead = 0;

         _tprintf(_T("Printing contents of %s...\n"), argv[1]);
         do
         {
            dwRead = ZREAD(api,stream,buffer,_countof(buffer));
            printf("%.*s", dwRead, buffer);
         } while(_countof(buffer) == dwRead);
         ZCLOSE(api, stream);
      }
   }
   else
   {
      _tprintf(_T("usage:\n%s filename\n"), _T("ioapi.exe"));
   }
   return EXIT_SUCCESS;
}
