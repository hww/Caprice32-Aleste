/* cpcapi.h */
/* Generic CPC api/interface. Copyright (c) Troels K. 2003 */

#ifndef __CPCAPI_H__
#define __CPCAPI_H__

#include "bool.h"
//#include "..\include\vdutext.h"

#ifndef EXTERN_C   
   #ifdef __cplusplus
      #define EXTERN_C    extern "C"
   #else
      #define EXTERN_C    extern
   #endif
#endif

/* Forward declarations */
struct _CPCDATA;
struct _CPCIMPLEMENTATION;
struct _t_z80regs;
struct _Z80INTERCEPT;

/*
typedef struct _CPC_SYSVAR
{
   //B7C4 MODE
   //B726 TEXT Y
   //B727 TEXT X
} CPC_SYSVAR;
*/

typedef struct _CPCDATA     * CPCHANDLE;
typedef struct _Z80INTERCEPT* Z80INTERCEPTHANDLE;

EXTERN_C void z80_intercept_function(const struct _t_z80regs* p, void* lpUser);

typedef void (*Z80INTERCEPTFN)(const struct _t_z80regs*, void* lpUser);

EXTERN_C Z80INTERCEPTHANDLE Z80_AddInterceptHandler   (Z80INTERCEPTFN newhandler, void* pUser);
EXTERN_C void               Z80_RemoveInterceptHandler(Z80INTERCEPTHANDLE*);
EXTERN_C void               Z80_RemoveIntercept(void);

EXTERN_C Z80INTERCEPTHANDLE CPCAPI_Z80_SetInterceptHandler(CPCHANDLE);
EXTERN_C void CPCAPI_SetConsoleBreak(BOOL);
EXTERN_C BOOL CPCAPI_GetTextModeSize(int mode, int* x, int* y);

#endif /* __CPCAPI_H__ */
