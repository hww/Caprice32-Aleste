/* xbm_cpc.c */
/* Copyright (c) Troels K. 2004 */

#include "../include/bool.h"
#include "../include/xbm_cpc.h"

static unsigned char mirror_byte(unsigned char x)
{
   int i;
   int result = 0;
   for (i = 0; i < 8; i++)
   {
      result|=((x >> i) & 1) << (7 - i);
   }
   return (unsigned char )result;
}

typedef struct _XBM_STRUCT
{
   const unsigned char* bits;
   int width;
   int height;
} XBM_STRUCT;

#define XBM_INIT(p,name) p.bits = name##_bits, p.width = name##_width, p.height = name##_height

#include "../fonts/cpcfont_fr.xbm" /* edit this file with Gimp */
#include "../fonts/cpcfont_sp.xbm" /* edit this file with Gimp */
#include "../fonts/cpcfont_dk.xbm" /* edit this file with Gimp */

/*
The xbm file format stores images mirrored, which is not good for us.
To mirror the image in Gimp: Tools|Transform|Flip + mouse click on image
*/

void memcpy_keyboard(void* ptr, int n, BOOL mirror)
{
   int index,y;
   unsigned char* bits = (unsigned char*)ptr;
   XBM_STRUCT xbm;
   switch (n)
   {
      case 0:
         XBM_INIT(xbm, cpcfont_fr);
         break;
      case 1:
         XBM_INIT(xbm, cpcfont_sp);
         break;
      case 2:
         XBM_INIT(xbm, cpcfont_dk);
         break;
   }
   for (index = 0; index < 256; index++)
   {
      for (y = 0; y < 8; y++)
      {
         bits[index*8 + y] = mirror ? mirror_byte(xbm.bits[y*256 + index]) : xbm.bits[y*256 + 256 - index - 1];
      }
   }
}

/*
This is how I create an xbm file:
void cpcbasic_dumpfont_xbm(const CPCROM_6128_FIRMWARE* src, const TCHAR* title, int (*out)(FILE*, const TCHAR* fmt, ...), FILE* dst)
{
   int y,i;
   BOOL mirror = TRUE;

   const int char_count = _countof(src->font);
   const int width = 8;
   const int height = _countof(src->font[0]);
   const int width_total = width * char_count;
   (*out)(dst, _T("#define %s_width %d\n")
               _T("#define %s_height %d\n")
               _T("static unsigned char %s_bits[] = {\n"),
               title, width_total, title, height, title);
   for (y = 0; y < height; y++)
   {
      if (y) (*out)(dst, _T(",\n"));
      (*out)(dst, _T("   "));      
      for (i = 0; i < char_count; i++)
      {
         if (i) (*out)(dst, _T(", "));
         (*out)(dst, _T("0x%02X"), mirror ? mirror_byte(src->font[i][y]) : src->font[i][y]);
      }
   }
   (*out)(dst, _T("\n};\n"));
}
*/
