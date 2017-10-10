/* cpcapi.c */
/* Generic CPC api/interface. Copyright (c) Troels K. 2003 */
/* This module maps from the CPC world to the CPCAPI world */

#include <tchar.h>
#include <stdlib.h>
#include "..\include\cpcapi.h"
#include "..\..\z80.h"
#include "..\include\cpcfirmware.h"
#ifndef _WINNT_
   #define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
#endif
#ifndef _countof
   #define _countof(array) (sizeof(array)/sizeof((array)[0]))
#endif
#ifndef _INC_WINDOWS
   typedef unsigned short WORD ;
   typedef unsigned char  BYTE ;
#endif
typedef struct _Z80INTERCEPT
{
   Z80INTERCEPTFN function;
   void* pUser;
   struct _Z80INTERCEPT* next;
} Z80INTERCEPT;

static Z80INTERCEPT* MOD_intercept = NULL;

Z80INTERCEPTHANDLE Z80_AddInterceptHandler(Z80INTERCEPTFN function, void* pUser)
{
   Z80INTERCEPTHANDLE handle;
   Z80INTERCEPT** element;
   for (element = &MOD_intercept; *element; element = &(*element)->next)
   {
   }
   handle = *element = (Z80INTERCEPT*)malloc(sizeof(Z80INTERCEPT));
   handle->function = function;
   handle->pUser    = pUser;
   handle->next     = NULL;
   return handle;
}

void Z80_RemoveIntercept(void)
{
   Z80INTERCEPT* element;
   for (element = MOD_intercept; element; )
   {
      Z80INTERCEPT* temp = element;
      element = element->next;
      free(temp);
   }
   MOD_intercept = NULL;
}

void Z80_RemoveInterceptHandler(Z80INTERCEPTHANDLE* handle)
{
   Z80INTERCEPT** element;
   for (element = &MOD_intercept; *element; element = &(*element)->next)
   {
      if (*element == *handle)
      {
         *element = (*element)->next;
         free(*handle);
         break;
      }
   }
   *handle = NULL;
}

void Z80_InterceptChain(const t_z80regs* p)
{
   Z80INTERCEPT* element;
   Z80INTERCEPT* next;
   for (element = MOD_intercept; element; )
   {
      next = element->next; /* preserve next */
      (*element->function)(p, element->pUser); /* element might not longer be valid after this call */
      element = next;
   }
}

