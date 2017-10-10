/* app.c */

#include <windows.h>
#include <tchar.h>
#include "../include/app.h"

#define USE_EMUSHELL 0

#if USE_EMUSHELL
   #include "../../../../emushell/emushell.h"
#endif
#include "../include/emuimpl.h"

extern HINSTANCE PUB_CapriceResourceInstance;

#ifdef _WIN32 // TROELS
   #include <windows.h>
   int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int iCmdShow)
   {
#if USE_EMUSHELL
      // use registry, GetOpenFileName etc.
      EMUHANDLE handle = (*EMUSHELL_CapriceInternal()->open)(NULL);
      if (handle)
      {
         (*handle->api->run)  (handle, NULL, __argc, __targv);
         (*handle->api->close)(&handle);
      }
#else
      // use cfg file, no GetOpenFileName
      int result;
      PUB_CapriceResourceInstance = hInstance;
      result = caprice_main(__argc, __targv, FALSE); doCleanUp();
      //result = caprice_main(__argc, __targv, FALSE); doCleanUp();
      return result;
#endif
   }
#else
   int main (int argc, char **argv)
   {
      int result;
      result = caprice_main(argc, argv, FALSE);
      doCleanUp();
      return result;
   }
#endif
