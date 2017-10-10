/* cpcrom.h */
/* CPC ROM layout. Copyright (c) Troels K 2004 */

#ifndef __CPCROM_H__
#define __CPCROM_H__

#pragma pack(1)

typedef struct _CPCROM_464_FIRMWARE
{
   char signature[8];
   struct
   {
      unsigned char mem[2795];
   } unknown0;
   unsigned char mode;
   struct
   {
      unsigned char mem[7521-2795-1];
   } unknown1;
   unsigned char keyboard[240]; /* 0x1D69 */
   struct
   {
      unsigned char mem[6567];
   } unknown2;
   unsigned char font[256][8];   /* 0x3800 */
} CPCROM_464_FIRMWARE;

typedef struct _CPCROM_6128_FIRMWARE
{
   char signature[8];
   struct
   {
      unsigned char mem[2827];
   } unknown0;
   unsigned char mode;
   struct
   {
      unsigned char mem[7911-2827-1];
   } unknown1;
   unsigned char keyboard[240]; /* 0x1EEF */
   struct
   {
      unsigned char mem[6177];
   } unknown2;
   unsigned char font[256][8];   /* 0x3800 */
} CPCROM_6128_FIRMWARE;

typedef struct _CPCROM_6128_BASIC
{
   char signature[3];
   struct
   {
      unsigned char mem[0x2449];
   } unknown;
   unsigned char tokens[0x314];
   struct
   {
      unsigned char mem[0x18A0];
   } unknown2;
} CPCROM_6128_BASIC;

#pragma pack()

#endif /* __CPCROM_H__ */
