/* autoexec.c */
/* Autorun feature. Copyright (c) Troels K. 2003-2004 */
/* All this code just to find out when the CPC is ready to receive key strokes */

#include <tchar.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "..\include\cpcapi.h"
#include "..\..\z80.h"
#include "..\include\autotype.h"
#include "..\include\cpcfirmware.h"
#include "..\include\autoexec.h"

#define ARNOLD

typedef unsigned char Byte;

#define  LIT_soh                       '\x1'
#define  LIT_stx                       '\x2'
#define  LIT_etx                       '\x3'
#define  LIT_eot                       '\x4'
#define  LIT_bel                       '\x7'
#define  LIT_bs                        '\x8'
#define  LIT_tab                       '\t'
#define  LIT_cr                        '\r'
#define  LIT_lf                        '\n'
#define  LIT_nl                        LIT_lf
#define  LIT_ff                        '\f'

typedef struct _AUTOEXEC
{
   Z80INTERCEPTHANDLE intercept;
   TCHAR*      initstring;
   BOOL        ready;
   int         iPos;
} AUTOEXEC;

static void OnChar(AUTOEXEC* handle, char ch, int* iPos)
{
   const char* szReady = "Ready";
   if (ch == szReady[*iPos])
   {
      if (!szReady[++(*iPos)])
      {
         handle->ready = TRUE;
      }
   }
   else
   {
      *iPos = 0;
   }
}

static void z80_autoexec_function(const t_z80regs* p, void* pUser)
{
   AUTOEXECHANDLE handle = (AUTOEXEC*)pUser;
   
   switch (p->PC.w.l)
   {
      case TXT_OUT_ACTION:
      {
         enum
         {
            ENUM_char_setmode = 0x04,
            ENUM_char_clrscr  = 0x0C,
            ENUM_char_invers  = 0x18,
            ENUM_char_topleft = 0x1E,
            ENUM_char_setpos  = 0x1F,
            ENUM_char_escape  = 0x1B
         };
         static enum
         {
            ENUM_mode_default,
            ENUM_mode_setpos_x,
            ENUM_mode_setpos_y,
            ENUM_mode_setmode,
         } mode = ENUM_mode_default;
         Byte ch = p->AF.b.h;
         switch (mode)
         {
            case ENUM_mode_default:
               switch (ch)
               {
                  case ENUM_char_setmode:
                     mode = ENUM_mode_setmode;
                     break;
                  case ENUM_char_clrscr:
                     break;
                  case ENUM_char_topleft:
                     break;
                  case ENUM_char_setpos:
                     break;
                  case ENUM_char_invers:
                  case ENUM_char_escape:
                     break;
                  case LIT_bs:
                  case LIT_tab:
                  case LIT_cr:
                     _asm NOP
                  case LIT_lf:
                     _asm NOP
                  default:
                  {
                     Byte ch = p->AF.b.h;
                     static int iPos = 0;
                     OnChar(handle, ch, &iPos); /* CPC464-triggered */
                     break;
                  }
               }
               break;
            default:
               break;
         }
         break;
      }
      case TXT_WRITE_CHAR:
      {
         Byte ch = p->AF.b.h;
         static int iPos = 0;
         OnChar(handle, ch, &iPos); /* CPC6128-triggered */
         break;
      }
      case TXT_DRAW_CURSOR:
         if (handle->ready)
         {
            AutoType_SetString(handle->initstring, TRUE);
            Z80_RemoveInterceptHandler(&handle->intercept);
         }
         break;
      case TXT_SET_ROW:
      case TXT_SET_COLUMN:
      case 0xBBC0:
      case 0xBBC9:
      case TXT_SET_CURSOR:
      case SCR_SET_MODE:
      case TXT_CLR_WINDOW:
      case GRA_WR_CHAR:
      case TXT_WR_CHAR:
      case TXT_OUTPUT:
      case TXT_CUR_ENABLE:
      default:
         break;
   }
}

AUTOEXECHANDLE autoexec_open(const TCHAR* InitString)
{
   AUTOEXECHANDLE handle = NULL;
   struct _stat buffer;
   const int len = _tcslen(InitString)+1;
   
   handle = (AUTOEXECHANDLE)malloc(sizeof(AUTOEXEC));
   handle->initstring = (TCHAR*)malloc((len+1) * sizeof(TCHAR));
   _tcsncpy(handle->initstring, InitString, len+1);

   _tcscat(handle->initstring, _T("\n"));

   handle->intercept    = Z80_AddInterceptHandler(z80_autoexec_function, handle);
   handle->ready        = FALSE;
   handle->iPos         = 0;
   return handle;
}

void autoexec_close(AUTOEXECHANDLE* handle)
{
   if ((*handle)->intercept) Z80_RemoveInterceptHandler(&(*handle)->intercept);
   free((*handle)->initstring);
   free(*handle);
   *handle = NULL;
}
