/* Caprice32 - Amstrad CPC Emulator
   (c) Copyright 1997-2004 Ulrich Doewich

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

static unsigned char kbd_layout[MAX_KBD_LAYOUTS][240] = {
   { // french keyboard layout
      0xF0, 0xF3, 0xF1, 0x89, 0x86, 0x83, 0x8B, 0x8A, 0xF2, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80,
      0x10, 0x2A, 0x0D, 0x23, 0x84, 0xFF, 0x24, 0xFF, 0x2D, 0x29, 0x5E, 0x70, 0x7C, 0x6D, 0x3D, 0x3A,
      0x40, 0x5C, 0x6F, 0x69, 0x6C, 0x6B, 0x2C, 0x3B, 0x21, 0x7D, 0x75, 0x79, 0x68, 0x6A, 0x6E, 0x20,
      0x5D, 0x28, 0x72, 0x74, 0x67, 0x66, 0x62, 0x76, 0x27, 0x22, 0x65, 0x7A, 0x73, 0x64, 0x63, 0x78,
      0x26, 0x7B, 0xFC, 0x61, 0x09, 0x71, 0xFD, 0x77, 0x0B, 0x0A, 0x08, 0x09, 0x58, 0x5A, 0xFF, 0x7F,
      0xF4, 0xF7, 0xF5, 0x89, 0x86, 0x83, 0x8B, 0x8A, 0xF6, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80,
      0x10, 0x3C, 0x0D, 0x3E, 0x84, 0xFF, 0x40, 0xFF, 0x5F, 0x5B, 0x7C, 0x50, 0x25, 0x4D, 0x2B, 0x2F,
      0x30, 0x39, 0x4F, 0x49, 0x4C, 0x4B, 0x3F, 0x2E, 0x38, 0x37, 0x55, 0x59, 0x48, 0x4A, 0x4E, 0x20,
      0x36, 0x35, 0x52, 0x54, 0x47, 0x46, 0x42, 0x56, 0x34, 0x33, 0x45, 0x5A, 0x53, 0x44, 0x43, 0x58,
      0x31, 0x32, 0xFC, 0x41, 0x09, 0x51, 0xFD, 0x57, 0x0B, 0x0A, 0x08, 0x09, 0x58, 0x5A, 0xFF, 0x7F,
      0xF8, 0xFB, 0xF9, 0x89, 0x86, 0x83, 0x8C, 0x8A, 0xFA, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80,
      0x10, 0xFF, 0x0D, 0xFF, 0x84, 0xFF, 0x5C, 0xFF, 0x1F, 0xA2, 0x1E, 0x10, 0xFF, 0x0D, 0xFF, 0xFF,
      0x00, 0x1C, 0x0F, 0x09, 0x0C, 0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0x15, 0x19, 0x08, 0x0A, 0x0E, 0xFF,
      0xA6, 0xFF, 0x12, 0x14, 0x07, 0x06, 0x02, 0x16, 0xFF, 0x1D, 0x05, 0x1A, 0x13, 0x04, 0x03, 0x18,
      0x1B, 0x7E, 0xFC, 0x01, 0xE1, 0x11, 0xFE, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F
   },
   { // spanish keyboard layout
      0xF0, 0xF3, 0xF1, 0x89, 0x86, 0x83, 0x8B, 0x8A, 0xF2, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80,
      0x10, 0x5B, 0x0D, 0x5D, 0x84, 0xFF, 0x5C, 0xFF, 0x5E, 0x2D, 0x40, 0x70, 0x3B, 0xAB, 0x2F, 0x2E,
      0x30, 0x39, 0x6F, 0x69, 0x6C, 0x6B, 0x6D, 0x2C, 0x38, 0x37, 0x75, 0x79, 0x68, 0x6A, 0x6E, 0x20,
      0x36, 0x35, 0x72, 0x74, 0x67, 0x66, 0x62, 0x76, 0x34, 0x33, 0x65, 0x77, 0x73, 0x64, 0x63, 0x78,
      0x31, 0x32, 0xFC, 0x71, 0x09, 0x61, 0xFD, 0x7A, 0x0B, 0x0A, 0x08, 0x09, 0x58, 0x5A, 0xFF, 0x7F,
      0xF4, 0xF7, 0xF5, 0x89, 0x86, 0x83, 0x8B, 0x8A, 0xF6, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80,
      0x10, 0x2A, 0x0D, 0x2B, 0x84, 0xFF, 0x60, 0xFF, 0xA3, 0x3D, 0x7C, 0x50, 0x3A, 0xA1, 0x3F, 0x3E,
      0x5F, 0x29, 0x4F, 0x49, 0x4C, 0x4B, 0x4D, 0x3C, 0x28, 0x27, 0x55, 0x59, 0x48, 0x4A, 0x4E, 0x20,
      0x26, 0x25, 0x52, 0x54, 0x47, 0x46, 0x42, 0x56, 0x24, 0x23, 0x45, 0x57, 0x53, 0x44, 0x43, 0x58,
      0x21, 0x22, 0xFC, 0x51, 0x09, 0x41, 0xFD, 0x5A, 0x0B, 0x0A, 0x08, 0x09, 0x58, 0x5A, 0xFF, 0x7F,
      0xF8, 0xFB, 0xF9, 0x89, 0x86, 0x83, 0x8C, 0x8A, 0xFA, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80,
      0x10, 0x1B, 0x0D, 0x1D, 0x84, 0xFF, 0x1C, 0xFF, 0x1E, 0xFF, 0x00, 0x10, 0xFF, 0xFF, 0xAE, 0xFF,
      0x1F, 0x7D, 0x0F, 0x09, 0x0C, 0x0B, 0x0D, 0xFF, 0x7B, 0xFF, 0x15, 0x19, 0x08, 0x0A, 0x0E, 0xFF,
      0xFF, 0xFF, 0x12, 0x14, 0x07, 0x06, 0x02, 0x16, 0xFF, 0xFF, 0x05, 0x17, 0x13, 0x04, 0x03, 0x18,
      0xAF, 0x7E, 0xFC, 0x11, 0xE1, 0x01, 0xFE, 0x1A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F
   },
   { // danish keyboard layout
      0xF0, 0xF3, 0xF1, 0x89, 0x86, 0x83, 0x8B, 0x8A, 0xF2, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80, 
      0x10, 0x3B, 0x0D, 0x3A, 0x84, 0xFF, 0x40, 0xFF, 0x5E, 0x2D, 0x7D, 0x70, 0x7C, 0x7B, 0x2F, 0x2E, 
      0x30, 0x39, 0x6F, 0x69, 0x6C, 0x6B, 0x6D, 0x2C, 0x38, 0x37, 0x75, 0x79, 0x68, 0x6A, 0x6E, 0x20, 
      0x36, 0x35, 0x72, 0x74, 0x67, 0x66, 0x62, 0x76, 0x34, 0x33, 0x65, 0x77, 0x73, 0x64, 0x63, 0x78, 
      0x31, 0x32, 0xFC, 0x71, 0x09, 0x61, 0xFD, 0x7A, 0x0B, 0x0A, 0x08, 0x09, 0x58, 0x5A, 0xFF, 0x7F, 
      0xF4, 0xF7, 0xF5, 0x89, 0x86, 0x83, 0x8B, 0x8A, 0xF6, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80, 
      0x10, 0x2B, 0x0D, 0x2A, 0x84, 0xFF, 0x7C, 0xFF, 0xA3, 0x3D, 0x5D, 0x50, 0x5C, 0x5B, 0x3F, 0x3E, 
      0x5F, 0x29, 0x4F, 0x49, 0x4C, 0x4B, 0x4D, 0x3C, 0x28, 0x27, 0x55, 0x59, 0x48, 0x4A, 0x4E, 0x20, 
      0x26, 0x25, 0x52, 0x54, 0x47, 0x46, 0x42, 0x56, 0x24, 0x23, 0x45, 0x57, 0x53, 0x44, 0x43, 0x58,
      0x21, 0x22, 0xFC, 0x51, 0x09, 0x41, 0xFD, 0x5A, 0x0B, 0x0A, 0x08, 0x09, 0x58, 0x5A, 0xFF, 0x7F,
      0xF8, 0xFB, 0xF9, 0x89, 0x86, 0x83, 0x8C, 0x8A, 0xFA, 0xE0, 0x87, 0x88, 0x85, 0x81, 0x82, 0x80, 
      0x10, 0x1B, 0x0D, 0x1D, 0x84, 0xFF, 0x1C, 0xFF, 0x1E, 0xFF, 0x00, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 
      0x1F, 0xFF, 0x0F, 0x09, 0x0C, 0x0B, 0x0D, 0xFF, 0xFF, 0xFF, 0x15, 0x19, 0x08, 0x0A, 0x0E, 0xFF,
      0xFF, 0xFF, 0x12, 0x14, 0x07, 0x06, 0x02, 0x16, 0xFF, 0xFF, 0x05, 0x17, 0x13, 0x04, 0x03, 0x18, 
      0xFF, 0x7E, 0xFC, 0x11, 0xE1, 0x01, 0xFE, 0x1A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F
   }
};

/*
static unsigned char cpc_charset[MAX_KBD_LAYOUTS][2048] = {
   { // french character set
      0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
      0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF,
      0x0C, 0x18, 0x30, 0x7E, 0x0C, 0x18, 0x30, 0x00, 0xFF, 0xC3, 0xE7, 0xDB, 0xDB, 0xE7, 0xC3, 0xFF,
      0x00, 0x01, 0x03, 0x06, 0xCC, 0x78, 0x30, 0x00, 0x3C, 0x66, 0xC3, 0xC3, 0xFF, 0x24, 0xE7, 0x00,
      0x00, 0x00, 0x30, 0x60, 0xFF, 0x60, 0x30, 0x00, 0x00, 0x00, 0x0C, 0x06, 0xFF, 0x06, 0x0C, 0x00,
      0x18, 0x18, 0x18, 0x18, 0xDB, 0x7E, 0x3C, 0x18, 0x18, 0x3C, 0x7E, 0xDB, 0x18, 0x18, 0x18, 0x18,
      0x18, 0x5A, 0x3C, 0x99, 0xDB, 0x7E, 0x3C, 0x18, 0x00, 0x03, 0x33, 0x63, 0xFE, 0x60, 0x30, 0x00,
      0x3C, 0x66, 0xFF, 0xDB, 0xDB, 0xFF, 0x66, 0x3C, 0x3C, 0x66, 0xC3, 0xDB, 0xDB, 0xC3, 0x66, 0x3C,
      0xFF, 0xC3, 0xC3, 0xFF, 0xC3, 0xC3, 0xC3, 0xFF, 0x3C, 0x7E, 0xDB, 0xDB, 0xDF, 0xC3, 0x66, 0x3C,
      0x3C, 0x66, 0xC3, 0xDF, 0xDB, 0xDB, 0x7E, 0x3C, 0x3C, 0x66, 0xC3, 0xFB, 0xDB, 0xDB, 0x7E, 0x3C,
      0x3C, 0x7E, 0xDB, 0xDB, 0xFB, 0xC3, 0x66, 0x3C, 0x00, 0x01, 0x33, 0x1E, 0xCE, 0x7B, 0x31, 0x00,
      0x7E, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0xE7, 0x03, 0x03, 0x03, 0xFF, 0x03, 0x03, 0x03, 0x00,
      0xFF, 0x66, 0x3C, 0x18, 0x18, 0x3C, 0x66, 0xFF, 0x18, 0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x18, 0x18,
      0x3C, 0x66, 0x66, 0x30, 0x18, 0x00, 0x18, 0x00, 0x3C, 0x66, 0xC3, 0xFF, 0xC3, 0xC3, 0x66, 0x3C,
      0xFF, 0xDB, 0xDB, 0xDB, 0xFB, 0xC3, 0xC3, 0xFF, 0xFF, 0xC3, 0xC3, 0xFB, 0xDB, 0xDB, 0xDB, 0xFF,
      0xFF, 0xC3, 0xC3, 0xDF, 0xDB, 0xDB, 0xDB, 0xFF, 0xFF, 0xDB, 0xDB, 0xDB, 0xDF, 0xC3, 0xC3, 0xFF,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00,
      0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00,
      0x18, 0x3E, 0x58, 0x3C, 0x1A, 0x7C, 0x18, 0x00, 0x00, 0xC6, 0xCC, 0x18, 0x30, 0x66, 0xC6, 0x00,
      0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00,
      0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00,
      0x7C, 0xC6, 0xCE, 0xD6, 0xE6, 0xC6, 0x7C, 0x00, 0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00,
      0x3C, 0x66, 0x06, 0x3C, 0x60, 0x66, 0x7E, 0x00, 0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00,
      0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x1E, 0x00, 0x7E, 0x62, 0x60, 0x7C, 0x06, 0x66, 0x3C, 0x00,
      0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00, 0x7E, 0x66, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x00,
      0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00, 0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00,
      0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30,
      0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00,
      0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x3C, 0x66, 0x66, 0x0C, 0x18, 0x00, 0x18, 0x00,
      0x60, 0x10, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00, 0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00,
      0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00, 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00,
      0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00,
      0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00, 0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3E, 0x00,
      0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00,
      0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00, 0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00,
      0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00, 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00,
      0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00,
      0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xDA, 0xCC, 0x76, 0x00,
      0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00, 0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00,
      0x7E, 0x5A, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00,
      0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0xEE, 0xC6, 0x00,
      0xC6, 0x6C, 0x38, 0x38, 0x6C, 0xC6, 0xC6, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x3C, 0x00,
      0xFE, 0xC6, 0x8C, 0x18, 0x32, 0x66, 0xFE, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00,
      0x00, 0x00, 0x3C, 0x66, 0x60, 0x3E, 0x08, 0x18, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00,
      0x18, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
      0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
      0xE0, 0x60, 0x7C, 0x66, 0x66, 0x66, 0xDC, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x60, 0x66, 0x3C, 0x00,
      0x1C, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00,
      0x1C, 0x36, 0x30, 0x78, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x7C,
      0xE0, 0x60, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x3C, 0x00,
      0x06, 0x00, 0x0E, 0x06, 0x06, 0x66, 0x66, 0x3C, 0xE0, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x00,
      0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x6C, 0xFE, 0xD6, 0xD6, 0xC6, 0x00,
      0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00,
      0x00, 0x00, 0xDC, 0x66, 0x66, 0x7C, 0x60, 0xF0, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0x1E,
      0x00, 0x00, 0xDC, 0x76, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x3C, 0x60, 0x3C, 0x06, 0x7C, 0x00,
      0x30, 0x30, 0x7C, 0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00,
      0x00, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0x00, 0x00, 0xC6, 0xD6, 0xD6, 0xFE, 0x6C, 0x00,
      0x00, 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x7C,
      0x00, 0x00, 0x7E, 0x4C, 0x18, 0x32, 0x7E, 0x00, 0x06, 0x08, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00,
      0x30, 0x08, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00, 0x60, 0x10, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00,
      0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x33, 0xCC, 0x33, 0xCC, 0x33, 0xCC, 0x33,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00,
      0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
      0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0, 0xF0,
      0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F,
      0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F,
      0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF,
      0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
      0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0x0F, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xF8, 0xF0, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xF0, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0xFF, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18,
      0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x38, 0x44, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x60, 0xF8, 0x60, 0x66, 0xFE, 0x00,
      0x38, 0x44, 0xBA, 0xA2, 0xBA, 0x44, 0x38, 0x00, 0x7E, 0xF4, 0xF4, 0x74, 0x34, 0x34, 0x34, 0x00,
      0x1E, 0x30, 0x38, 0x6C, 0x38, 0x18, 0xF0, 0x00, 0x18, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x40, 0xC0, 0x44, 0x4C, 0x54, 0x1E, 0x04, 0x00, 0x40, 0xC0, 0x4C, 0x52, 0x44, 0x08, 0x1E, 0x00,
      0xE0, 0x10, 0x62, 0x16, 0xEA, 0x0F, 0x02, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x7E, 0x00,
      0x18, 0x18, 0x00, 0x7E, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x06, 0x06, 0x00, 0x00,
      0x18, 0x00, 0x18, 0x30, 0x66, 0x66, 0x3C, 0x00, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,
      0x00, 0x00, 0x73, 0xDE, 0xCC, 0xDE, 0x73, 0x00, 0x7C, 0xC6, 0xC6, 0xFC, 0xC6, 0xC6, 0xF8, 0xC0,
      0x00, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00, 0x3C, 0x60, 0x60, 0x3C, 0x66, 0x66, 0x3C, 0x00,
      0x00, 0x00, 0x1E, 0x30, 0x7C, 0x30, 0x1E, 0x00, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x6C, 0x38, 0x00,
      0x00, 0xC0, 0x60, 0x30, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60,
      0x00, 0x00, 0x00, 0xFE, 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xD8, 0xD8, 0x70, 0x00,
      0x03, 0x06, 0x0C, 0x3C, 0x66, 0x3C, 0x60, 0xC0, 0x03, 0x06, 0x0C, 0x66, 0x66, 0x3C, 0x60, 0xC0,
      0x00, 0xE6, 0x3C, 0x18, 0x38, 0x6C, 0xC7, 0x00, 0x00, 0x00, 0x66, 0xC3, 0xDB, 0xDB, 0x7E, 0x00,
      0xFE, 0xC6, 0x60, 0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x6C, 0xEE, 0x00,
      0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x18,
      0x18, 0x3C, 0x66, 0xC3, 0x81, 0x00, 0x00, 0x00, 0x18, 0x0C, 0x06, 0x03, 0x03, 0x06, 0x0C, 0x18,
      0x00, 0x00, 0x00, 0x81, 0xC3, 0x66, 0x3C, 0x18, 0x18, 0x30, 0x60, 0xC0, 0xC0, 0x60, 0x30, 0x18,
      0x18, 0x30, 0x60, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x18, 0x0C, 0x06, 0x83, 0xC1, 0x60, 0x30, 0x18,
      0x18, 0x3C, 0x66, 0xC3, 0xC3, 0x66, 0x3C, 0x18, 0xC3, 0xE7, 0x7E, 0x3C, 0x3C, 0x7E, 0xE7, 0xC3,
      0x03, 0x07, 0x0E, 0x1C, 0x38, 0x70, 0xE0, 0xC0, 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x07, 0x03,
      0xCC, 0xCC, 0x33, 0x33, 0xCC, 0xCC, 0x33, 0x33, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
      0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
      0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01,
      0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF,
      0xAA, 0x55, 0xAA, 0x55, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x05, 0x0A, 0x05, 0x0A, 0x05, 0x0A, 0x05,
      0x00, 0x00, 0x00, 0x00, 0xAA, 0x55, 0xAA, 0x55, 0xA0, 0x50, 0xA0, 0x50, 0xA0, 0x50, 0xA0, 0x50,
      0xAA, 0x54, 0xA8, 0x50, 0xA0, 0x40, 0x80, 0x00, 0xAA, 0x55, 0x2A, 0x15, 0x0A, 0x05, 0x02, 0x01,
      0x01, 0x02, 0x05, 0x0A, 0x15, 0x2A, 0x55, 0xAA, 0x00, 0x80, 0x40, 0xA0, 0x50, 0xA8, 0x54, 0xAA,
      0x7E, 0xFF, 0x99, 0xFF, 0xBD, 0xC3, 0xFF, 0x7E, 0x7E, 0xFF, 0x99, 0xFF, 0xC3, 0xBD, 0xFF, 0x7E,
      0x38, 0x38, 0xFE, 0xFE, 0xFE, 0x10, 0x38, 0x00, 0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x10, 0x00,
      0x6C, 0xFE, 0xFE, 0xFE, 0x7C, 0x38, 0x10, 0x00, 0x10, 0x38, 0x7C, 0xFE, 0xFE, 0x10, 0x38, 0x00,
      0x00, 0x3C, 0x66, 0xC3, 0xC3, 0x66, 0x3C, 0x00, 0x00, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x00,
      0x00, 0x7E, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00,
      0x0F, 0x07, 0x0D, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x7E, 0x18,
      0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x7C, 0x38, 0x18, 0x1C, 0x1E, 0x1B, 0x18, 0x78, 0xF8, 0x70,
      0x99, 0x5A, 0x24, 0xC3, 0xC3, 0x24, 0x5A, 0x99, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x7C, 0xD6,
      0x18, 0x3C, 0x7E, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0x7E, 0x3C, 0x18,
      0x10, 0x30, 0x70, 0xFF, 0xFF, 0x70, 0x30, 0x10, 0x08, 0x0C, 0x0E, 0xFF, 0xFF, 0x0E, 0x0C, 0x08,
      0x00, 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00,
      0x80, 0xE0, 0xF8, 0xFE, 0xF8, 0xE0, 0x80, 0x00, 0x02, 0x0E, 0x3E, 0xFE, 0x3E, 0x0E, 0x02, 0x00,
      0x38, 0x38, 0x92, 0x7C, 0x10, 0x28, 0x28, 0x28, 0x38, 0x38, 0x10, 0xFE, 0x10, 0x28, 0x44, 0x82,
      0x38, 0x38, 0x12, 0x7C, 0x90, 0x28, 0x24, 0x22, 0x38, 0x38, 0x90, 0x7C, 0x12, 0x28, 0x48, 0x88,
      0x00, 0x3C, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x00, 0x3C, 0xFF, 0xFF, 0x18, 0x0C, 0x18, 0x30, 0x18,
      0x18, 0x3C, 0x7E, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x00, 0x24, 0x66, 0xFF, 0x66, 0x24, 0x00, 0x00
   },
   { // spanish character set
      0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
      0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF,
      0x0C, 0x18, 0x30, 0x7E, 0x0C, 0x18, 0x30, 0x00, 0xFF, 0xC3, 0xE7, 0xDB, 0xDB, 0xE7, 0xC3, 0xFF,
      0x00, 0x01, 0x03, 0x06, 0xCC, 0x78, 0x30, 0x00, 0x3C, 0x66, 0xC3, 0xC3, 0xFF, 0x24, 0xE7, 0x00,
      0x00, 0x00, 0x30, 0x60, 0xFF, 0x60, 0x30, 0x00, 0x00, 0x00, 0x0C, 0x06, 0xFF, 0x06, 0x0C, 0x00,
      0x18, 0x18, 0x18, 0x18, 0xDB, 0x7E, 0x3C, 0x18, 0x18, 0x3C, 0x7E, 0xDB, 0x18, 0x18, 0x18, 0x18,
      0x18, 0x5A, 0x3C, 0x99, 0xDB, 0x7E, 0x3C, 0x18, 0x00, 0x03, 0x33, 0x63, 0xFE, 0x60, 0x30, 0x00,
      0x3C, 0x66, 0xFF, 0xDB, 0xDB, 0xFF, 0x66, 0x3C, 0x3C, 0x66, 0xC3, 0xDB, 0xDB, 0xC3, 0x66, 0x3C,
      0xFF, 0xC3, 0xC3, 0xFF, 0xC3, 0xC3, 0xC3, 0xFF, 0x3C, 0x7E, 0xDB, 0xDB, 0xDF, 0xC3, 0x66, 0x3C,
      0x3C, 0x66, 0xC3, 0xDF, 0xDB, 0xDB, 0x7E, 0x3C, 0x3C, 0x66, 0xC3, 0xFB, 0xDB, 0xDB, 0x7E, 0x3C,
      0x3C, 0x7E, 0xDB, 0xDB, 0xFB, 0xC3, 0x66, 0x3C, 0x00, 0x01, 0x33, 0x1E, 0xCE, 0x7B, 0x31, 0x00,
      0x7E, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0xE7, 0x03, 0x03, 0x03, 0xFF, 0x03, 0x03, 0x03, 0x00,
      0xFF, 0x66, 0x3C, 0x18, 0x18, 0x3C, 0x66, 0xFF, 0x18, 0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x18, 0x18,
      0x3C, 0x66, 0x66, 0x30, 0x18, 0x00, 0x18, 0x00, 0x3C, 0x66, 0xC3, 0xFF, 0xC3, 0xC3, 0x66, 0x3C,
      0xFF, 0xDB, 0xDB, 0xDB, 0xFB, 0xC3, 0xC3, 0xFF, 0xFF, 0xC3, 0xC3, 0xFB, 0xDB, 0xDB, 0xDB, 0xFF,
      0xFF, 0xC3, 0xC3, 0xDF, 0xDB, 0xDB, 0xDB, 0xFF, 0xFF, 0xDB, 0xDB, 0xDB, 0xDF, 0xC3, 0xC3, 0xFF,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00,
      0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00,
      0x18, 0x3E, 0x58, 0x3C, 0x1A, 0x7C, 0x18, 0x00, 0x00, 0xC6, 0xCC, 0x18, 0x30, 0x66, 0xC6, 0x00,
      0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00,
      0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00,
      0x7C, 0xC6, 0xCE, 0xD6, 0xE6, 0xC6, 0x7C, 0x00, 0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00,
      0x3C, 0x66, 0x06, 0x3C, 0x60, 0x66, 0x7E, 0x00, 0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00,
      0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x1E, 0x00, 0x7E, 0x62, 0x60, 0x7C, 0x06, 0x66, 0x3C, 0x00,
      0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00, 0x7E, 0x66, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x00,
      0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00, 0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00,
      0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30,
      0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00,
      0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x3C, 0x66, 0x66, 0x0C, 0x18, 0x00, 0x18, 0x00,
      0x7C, 0xC6, 0xDE, 0xDE, 0xDE, 0xC0, 0x7C, 0x00, 0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00,
      0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00, 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00,
      0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00,
      0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00, 0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3E, 0x00,
      0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00,
      0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00, 0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00,
      0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00, 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00,
      0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00,
      0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xDA, 0xCC, 0x76, 0x00,
      0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00, 0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00,
      0x7E, 0x5A, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00,
      0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0xEE, 0xC6, 0x00,
      0xC6, 0x6C, 0x38, 0x38, 0x6C, 0xC6, 0xC6, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x3C, 0x00,
      0xFE, 0xC6, 0x8C, 0x18, 0x32, 0x66, 0xFE, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00,
      0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00,
      0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
      0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
      0xE0, 0x60, 0x7C, 0x66, 0x66, 0x66, 0xDC, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x60, 0x66, 0x3C, 0x00,
      0x1C, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00,
      0x1C, 0x36, 0x30, 0x78, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x7C,
      0xE0, 0x60, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x3C, 0x00,
      0x06, 0x00, 0x0E, 0x06, 0x06, 0x66, 0x66, 0x3C, 0xE0, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x00,
      0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x6C, 0xFE, 0xD6, 0xD6, 0xC6, 0x00,
      0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00,
      0x00, 0x00, 0xDC, 0x66, 0x66, 0x7C, 0x60, 0xF0, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0x1E,
      0x00, 0x00, 0xDC, 0x76, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x3C, 0x60, 0x3C, 0x06, 0x7C, 0x00,
      0x30, 0x30, 0x7C, 0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00,
      0x00, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0x00, 0x00, 0xC6, 0xD6, 0xD6, 0xFE, 0x6C, 0x00,
      0x00, 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x7C,
      0x00, 0x00, 0x7E, 0x4C, 0x18, 0x32, 0x7E, 0x00, 0x0E, 0x18, 0x18, 0x70, 0x18, 0x18, 0x0E, 0x00,
      0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x70, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x70, 0x00,
      0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x33, 0xCC, 0x33, 0xCC, 0x33, 0xCC, 0x33,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00,
      0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
      0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0, 0xF0,
      0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F,
      0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F,
      0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF,
      0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
      0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0x0F, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xF8, 0xF0, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xF0, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0xFF, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18,
      0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x32, 0x4C, 0x00, 0x66, 0x76, 0x6E, 0x66, 0x00,
      0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x90, 0x94, 0xEE, 0x84, 0x84, 0x83, 0x00,
      0x38, 0x44, 0xBA, 0xA2, 0xBA, 0x44, 0x38, 0x00, 0x7E, 0xF4, 0xF4, 0x74, 0x34, 0x34, 0x34, 0x00,
      0x1E, 0x30, 0x38, 0x6C, 0x38, 0x18, 0xF0, 0x00, 0x18, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x40, 0xC0, 0x44, 0x4C, 0x54, 0x1E, 0x04, 0x00, 0x40, 0xC0, 0x4C, 0x52, 0x44, 0x08, 0x1E, 0x00,
      0xE0, 0x10, 0x62, 0x16, 0xEA, 0x0F, 0x02, 0x00, 0x32, 0x4C, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x00,
      0x18, 0x18, 0x00, 0x7E, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x06, 0x06, 0x00, 0x00,
      0x18, 0x00, 0x18, 0x30, 0x66, 0x66, 0x3C, 0x00, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,
      0x00, 0x00, 0x73, 0xDE, 0xCC, 0xDE, 0x73, 0x00, 0x7C, 0xC6, 0xC6, 0xFC, 0xC6, 0xC6, 0xF8, 0xC0,
      0x00, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00, 0x3C, 0x60, 0x60, 0x3C, 0x66, 0x66, 0x3C, 0x00,
      0x00, 0x00, 0x1E, 0x30, 0x7C, 0x30, 0x1E, 0x00, 0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x6C, 0x38, 0x00,
      0x00, 0xC0, 0x60, 0x30, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60,
      0x00, 0x00, 0x00, 0xFE, 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xD8, 0xD8, 0x70, 0x00,
      0x03, 0x06, 0x0C, 0x3C, 0x66, 0x3C, 0x60, 0xC0, 0x03, 0x06, 0x0C, 0x66, 0x66, 0x3C, 0x60, 0xC0,
      0x00, 0xE6, 0x3C, 0x18, 0x38, 0x6C, 0xC7, 0x00, 0x00, 0x00, 0x66, 0xC3, 0xDB, 0xDB, 0x7E, 0x00,
      0xFE, 0xC6, 0x60, 0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x6C, 0xEE, 0x00,
      0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x18,
      0x18, 0x3C, 0x66, 0xC3, 0x81, 0x00, 0x00, 0x00, 0x18, 0x0C, 0x06, 0x03, 0x03, 0x06, 0x0C, 0x18,
      0x00, 0x00, 0x00, 0x81, 0xC3, 0x66, 0x3C, 0x18, 0x18, 0x30, 0x60, 0xC0, 0xC0, 0x60, 0x30, 0x18,
      0x18, 0x30, 0x60, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x18, 0x0C, 0x06, 0x83, 0xC1, 0x60, 0x30, 0x18,
      0x18, 0x3C, 0x66, 0xC3, 0xC3, 0x66, 0x3C, 0x18, 0xC3, 0xE7, 0x7E, 0x3C, 0x3C, 0x7E, 0xE7, 0xC3,
      0x03, 0x07, 0x0E, 0x1C, 0x38, 0x70, 0xE0, 0xC0, 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x07, 0x03,
      0xCC, 0xCC, 0x33, 0x33, 0xCC, 0xCC, 0x33, 0x33, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
      0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
      0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01,
      0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF,
      0xAA, 0x55, 0xAA, 0x55, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x05, 0x0A, 0x05, 0x0A, 0x05, 0x0A, 0x05,
      0x00, 0x00, 0x00, 0x00, 0xAA, 0x55, 0xAA, 0x55, 0xA0, 0x50, 0xA0, 0x50, 0xA0, 0x50, 0xA0, 0x50,
      0xAA, 0x54, 0xA8, 0x50, 0xA0, 0x40, 0x80, 0x00, 0xAA, 0x55, 0x2A, 0x15, 0x0A, 0x05, 0x02, 0x01,
      0x01, 0x02, 0x05, 0x0A, 0x15, 0x2A, 0x55, 0xAA, 0x00, 0x80, 0x40, 0xA0, 0x50, 0xA8, 0x54, 0xAA,
      0x7E, 0xFF, 0x99, 0xFF, 0xBD, 0xC3, 0xFF, 0x7E, 0x7E, 0xFF, 0x99, 0xFF, 0xC3, 0xBD, 0xFF, 0x7E,
      0x38, 0x38, 0xFE, 0xFE, 0xFE, 0x10, 0x38, 0x00, 0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x10, 0x00,
      0x6C, 0xFE, 0xFE, 0xFE, 0x7C, 0x38, 0x10, 0x00, 0x10, 0x38, 0x7C, 0xFE, 0xFE, 0x10, 0x38, 0x00,
      0x00, 0x3C, 0x66, 0xC3, 0xC3, 0x66, 0x3C, 0x00, 0x00, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x00,
      0x00, 0x7E, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00,
      0x0F, 0x07, 0x0D, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x7E, 0x18,
      0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x7C, 0x38, 0x18, 0x1C, 0x1E, 0x1B, 0x18, 0x78, 0xF8, 0x70,
      0x99, 0x5A, 0x24, 0xC3, 0xC3, 0x24, 0x5A, 0x99, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x7C, 0xD6,
      0x18, 0x3C, 0x7E, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0x7E, 0x3C, 0x18,
      0x10, 0x30, 0x70, 0xFF, 0xFF, 0x70, 0x30, 0x10, 0x08, 0x0C, 0x0E, 0xFF, 0xFF, 0x0E, 0x0C, 0x08,
      0x00, 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00,
      0x80, 0xE0, 0xF8, 0xFE, 0xF8, 0xE0, 0x80, 0x00, 0x02, 0x0E, 0x3E, 0xFE, 0x3E, 0x0E, 0x02, 0x00,
      0x38, 0x38, 0x92, 0x7C, 0x10, 0x28, 0x28, 0x28, 0x38, 0x38, 0x10, 0xFE, 0x10, 0x28, 0x44, 0x82,
      0x38, 0x38, 0x12, 0x7C, 0x90, 0x28, 0x24, 0x22, 0x38, 0x38, 0x90, 0x7C, 0x12, 0x28, 0x48, 0x88,
      0x00, 0x3C, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x00, 0x3C, 0xFF, 0xFF, 0x18, 0x0C, 0x18, 0x30, 0x18,
      0x18, 0x3C, 0x7E, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x00, 0x24, 0x66, 0xFF, 0x66, 0x24, 0x00, 0x00
   }
};
*/