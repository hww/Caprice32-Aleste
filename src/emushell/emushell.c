/* emushell.c */

#include <windows.h>
#include <tchar.h>
#include "emushell.h"

HANDLE EMUSHELL_Run(HWND hwnd, LPCTSTR lpszFile, LPCTSTR lpszParm, LPCTSTR lpszDir)
{
   HANDLE handle = NULL;
   SHELLEXECUTEINFO parm;
   parm.cbSize      = sizeof(parm);
   parm.fMask       = SEE_MASK_NOCLOSEPROCESS; 
   parm.hwnd        = hwnd; 
   parm.lpVerb      = _T("open"); 
   parm.lpFile      = lpszFile;
   parm.lpParameters= lpszParm; 
   parm.lpDirectory = lpszDir; 
   parm.nShow       = SW_SHOW; 
   parm.hInstApp    = NULL; 
   
   // Optional members 
   parm.lpIDList    = NULL; 
   parm.lpClass     = NULL; 
   parm.hkeyClass   = NULL; 
   parm.dwHotKey    = 0; 
   parm.hIcon       = NULL; 
   parm.hProcess    = NULL;
   if (ShellExecuteEx(&parm))
   {
      handle = parm.hProcess;
   }
   return handle;
}

