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

#ifndef CAP32_H
#define CAP32_H

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

//#define DEBUG
//#define DEBUG_CRTC
//#define DEBUG_CRTC_ONLY_ALESTE
//#define DEBUG_FDC
//#define DEBUG_GA
//#define DEBUG_NO_VIDEO
//#define DEBUG_TAPE
//#define DEBUG_Z80
//#define DEBUG_CRT_WRITE
//#define DEBUG_ALESTE_EXTEND
//#define DEBUG_ALESTE_MAPPER
//#define DEBUG_ALESTE_PALETE
//#define DEBUG_ALESTE_RTC
//#define DEBUG_ALESTE_RTC_AS
//#define DEBUG_ALESTE_MAGIC_SOUND
//#define DEBUG_PPI
//#define DEBUG_KBD
//#define DEBUG_IN
//#define DEBUG_OUT

// Will debug Z80 only when mapper on
//#define DEBUG_WHILE_MAMPMOD 


#ifndef _MAX_PATH
 #ifdef _POSIX_PATH_MAX
 #define _MAX_PATH _POSIX_PATH_MAX
 #else
 #define _MAX_PATH 256
 #endif
#endif

#define CYCLE_COUNT_INIT 80000 // 4MHz divided by 50Hz = number of CPU cycles per frame

#define CPC_SCR_WIDTH 1024 // max width
#define CPC_SCR_HEIGHT 312 // max height
#define CPC_VISIBLE_SCR_WIDTH 384 // visible width: 4+40+4 * 8
#define CPC_VISIBLE_SCR_HEIGHT 272 // visible height: 5+25+4 * 8

#define ICN_DISK_WIDTH 14
#define ICN_DISK_HEIGHT 16
#define ICN_TAPE_WIDTH 18
#define ICN_TAPE_HEIGHT 13

#define VOC_THRESHOLD 128

// CRTC flags
#define VS_flag      1
#define HS_flag      2
#define HDT_flag     4
#define VDT_flag     8
#define HT_flag      16
#define VT_flag      32
#define MR_flag      64
#define VTadj_flag   128
#define VSf_flag     256

// FDC constants
#define DSK_BPTMAX      8192
#define DSK_TRACKMAX    102   // max amount that fits in a DSK header
#define DSK_SIDEMAX     2
#define DSK_SECTORMAX   29    // max amount that fits in a track header

#define FDC_TO_CPU      0
#define CPU_TO_FDC      1

#define CMD_PHASE       0
#define EXEC_PHASE      1
#define RESULT_PHASE    2

#define SKIP_flag       1     // skip sectors with DDAM/DAM
#define SEEKDRVA_flag   2     // seek operation has finished for drive A
#define SEEKDRVB_flag   4     // seek operation has finished for drive B
#define RNDDE_flag      8     // simulate random DE sectors
#define OVERRUN_flag    16    // data transfer timed out
#define SCAN_flag       32    // one of the three scan commands is active
#define SCANFAILED_flag 64    // memory and sector data does not match
#define STATUSDRVA_flag 128   // status change of drive A
#define STATUSDRVB_flag 256   // status change of drive B

// Multiface 2 flags
#define MF2_ACTIVE      1
#define MF2_RUNNING     2
#define MF2_INVISIBLE   4

#define MAX_FREQ_ENTRIES 5
#define MAX_KBD_LAYOUTS 3
#define MAX_DISK_FORMAT 8
#define DEFAULT_DISK_FORMAT 0
#define FIRST_CUSTOM_DISK_FORMAT 2

typedef struct {
   char id[8];
   char unused1[8];
   Byte version;
   Byte AF[2];
   Byte BC[2];
   Byte DE[2];
   Byte HL[2];
   Byte R;
   Byte I;
   Byte IFF0;
   Byte IFF1;
   Byte IX[2];
   Byte IY[2];
   Byte SP[2];
   Byte PC[2];
   Byte IM;
   Byte AFx[2];
   Byte BCx[2];
   Byte DEx[2];
   Byte HLx[2];
   Byte ga_pen;
   Byte ga_ink_values[17];
   Byte ga_ROM_config;
   Byte ga_RAM_config;
   Byte crtc_reg_select;
   Byte crtc_registers[18];
   Byte upper_ROM;
   Byte ppi_A;
   Byte ppi_B;
   Byte ppi_C;
   Byte ppi_control;
   Byte psg_reg_select;
   Byte psg_registers[16];
   Byte ram_size[2];
// version 2 info follows
   Byte cpc_model;
   Byte last_interrupt;
   Byte scr_modes[6];
// version 3 info follows
   Byte drvA_DOSfilename[13];
   Byte drvB_DOSfilename[13];
   Byte cart_DOSfilename[13];
   Byte fdc_motor;
   Byte drvA_current_track;
   Byte drvB_current_track;
   Byte drvC_current_track;
   Byte drvD_current_track;
   Byte printer_data;
   Byte psg_env_step;
   Byte psg_env_direction;
   Byte crtc_type;
   Byte crtc_addr[2];
   Byte crtc_scanline[2];
   Byte crtc_char_count[2];
   Byte crtc_line_count;
   Byte crtc_raster_count;
   Byte crtc_vt_adjust_count;
   Byte crtc_hsw_count;
   Byte crtc_vsw_count;
   Byte crtc_flags[2];
   Byte ga_int_delay;
   Byte ga_sl_count;
   Byte z80_int_pending;
   Byte unused2[75];
} t_SNA_header;

typedef struct {
   char id[34];
   char unused1[14];
   Byte tracks;
   Byte sides;
   Byte unused2[2];
   Byte track_size[DSK_TRACKMAX*DSK_SIDEMAX];
} t_DSK_header;

typedef struct {
   char id[12];
   char unused1[4];
   Byte track;
   Byte side;
   Byte unused2[2];
   Byte bps;
   Byte sectors;
   Byte gap3;
   Byte filler;
   Byte sector[DSK_SECTORMAX][8];
} t_track_header;



typedef struct {
   uInt model;
   uInt jumpers;
   uInt ram_size;
   uInt speed;
   uInt limit_speed;
   uInt paused;
   uInt auto_pause;
   uInt keyboard_line;
   uInt tape_motor;
   uInt tape_play_button;
   uInt printer;
   uInt printer_port;
   uInt mf2;
   uInt joysticks;
   int cycle_count;

   uInt scr_fs_width;
   uInt scr_fs_height;
   uInt scr_fs_bpp;
   uInt scr_style;
   uInt scr_vsync;
   uInt scr_led;
   uInt scr_fps;
   uInt scr_tube;
   uInt scr_intensity;
   uInt scr_window;
   uInt scr_bpp;
   uInt scr_bps;
   uInt scr_line_offs;
   uInt *scr_base;
   uInt scr_offs;
   uInt scr_line;

   uInt snd_enabled;
   uInt snd_playback_rate;
   uInt snd_bits;
   uInt snd_stereo;
   uInt snd_volume;
   uInt snd_pp_device;
   uInt snd_buffersize;
   Byte *snd_bufferptr;
   union {
      struct {
         uInt low;
         uInt high;
      };
      int64_t both;
   } snd_cycle_count_init;

   uInt kbd_layout;
   uInt default_mode;

   uInt max_tracksize;
   TCHAR snap_path[_MAX_PATH + 1];
   TCHAR snap_file[_MAX_PATH + 1];
   bool snap_zip;
   TCHAR drvA_path[_MAX_PATH + 1];
   TCHAR drvA_file[_MAX_PATH + 1];
   bool drvA_zip;
   uInt drvA_format;
   TCHAR drvB_path[_MAX_PATH + 1];
   TCHAR drvB_file[_MAX_PATH + 1];
   bool drvB_zip;
   uInt drvB_format;
   TCHAR tape_path[_MAX_PATH + 1];
   TCHAR tape_file[_MAX_PATH + 1];
   bool tape_zip;
   TCHAR printer_file[_MAX_PATH + 1];

   TCHAR sdump_path[_MAX_PATH + 1];
   TCHAR sdump_file[_MAX_PATH + 1];

   TCHAR rom_path[_MAX_PATH + 1];
   TCHAR rom_file[16][_MAX_PATH + 1];
   TCHAR rom_mf2[_MAX_PATH + 1];
} t_CPC;

typedef struct {
   uInt flags;
   uInt requested_addr;
   uInt addr;
   Byte char_count;
   Byte line_count;
   Byte raster_count;
   Byte hsw;
   Byte hsw_active;
   Byte hsw_count;
   Byte vsw;
   Byte vsw_count;
   Byte vt_adjust;
   Byte vt_adjust_count;
   Byte skew;
   Byte max_raster;
   Byte last_hdisp;
   Byte reg_select;
   Byte registers[18];
} t_CRTC;

typedef struct {
   int timeout;
   int motor;
   int led;
   int flags;
   int phase;
   int byte_count;
   int buffer_count;
   int cmd_length;
   int res_length;
   int cmd_direction;
   void (*cmd_handler)(void);
   Byte *buffer_ptr;
   Byte *buffer_endptr;
   Byte command[12];
   Byte result[8];
} t_FDC;

typedef struct {
   Byte ROM_config;
   Byte RAM_bank;
   Byte RAM_config;
   Byte upper_ROM;
   void (*requested_scr_mode)(uInt addr);
   void (*scr_mode)(uInt addr);
   void (*scr_border)(void);
   Byte pen;
   Byte ink_values[17];
   uInt palette[17];
   Byte sl_count;
   Byte int_delay;
} t_GateArray;

typedef struct {
   Byte control;
   Byte portA;
   Byte portB;
   Byte portC;
} t_PPI;

typedef struct {
   union {
      struct {
         uInt low;
         uInt high;
      };
      int64_t both;
   } cycle_count;
   Byte control;
   Byte reg_select;
   union {
      Byte Index[16];
      struct {
         Byte TonALo, TonAHi;
         Byte TonBLo, TonBHi;
         Byte TonCLo, TonCHi;
         Byte Noise;
         Byte Mixer;
         Byte AmplitudeA, AmplitudeB, AmplitudeC;
         Byte EnvelopeLo, EnvelopeHi;
         Byte EnvType;
         Byte PortA;
         Byte PortB;
      };
   } RegisterAY;
   int AmplitudeEnv;
   bool FirstPeriod;
   void (*Synthesizer)(void);
} t_PSG;

typedef struct {
   uInt hsw;
   uInt hsw_active;
   uInt hsw_count;
   uInt vsw_count;
   uInt hdelay;
   uInt vdelay;
   uInt scanline;
   uInt scanline_min;
   uInt frame_completed;
   uInt char_count;
   uInt hcount;
   uInt hstart;
   uInt hwidth;
   uInt vcount;
   uInt vstart;
   uInt vheight;
} t_VDU;

typedef struct {
   Byte CHRN[4]; // the CHRN for this sector
   Byte flags[4]; // ST1 and ST2 - reflects any possible error conditions
   uInt size; // sector size in bytes
   Byte *data; // pointer to sector data
} t_sector;

typedef struct {
   uInt sectors; // sector count for this track
   uInt size; // track size in bytes
   Byte *data; // pointer to track data
   t_sector sector[DSK_SECTORMAX]; // array of sector information structures
} t_track;

typedef struct {
   uInt tracks; // total number of tracks
   uInt current_track; // location of drive head
   uInt sides; // total number of sides
   uInt current_side; // side being accessed
   uInt current_sector; // sector being accessed
   uInt altered; // has the image been modified?
   uInt write_protected; // is the image write protected?
   uInt random_DEs; // sectors with Data Errors return random data?
   uInt flipped; // reverse the side to access?
   t_track track[DSK_TRACKMAX][DSK_SIDEMAX]; // array of track information structures
} t_drive;

typedef struct {
   TCHAR *pchZipFile;
   TCHAR *pchExtension;
   TCHAR *pchFileNames;
   TCHAR *pchSelection;
   int iFiles;
   uInt dwOffset;
} t_zip_info;

typedef struct {
   Byte label[40]; // label to display in options dialog
   uInt tracks; // number of tracks
   uInt sides; // number of sides
   uInt sectors; // sectors per track
   uInt sector_size; // sector size as N value
   uInt gap3_length; // GAP#3 size
   Byte filler_byte; // default byte to use
   Byte sector_ids[2][16]; // sector IDs
} t_disk_format;

EXTERN_C t_disk_format disk_format[MAX_DISK_FORMAT];


// cap32.cpp
void emulator_reset(bool bolMF2Reset);

// fdc.c
EXTERN_C void fdc_write_data(Byte val);
EXTERN_C Byte fdc_read_status(void);
EXTERN_C Byte fdc_read_data(void);

// psg.c
EXTERN_C void SetAYRegister(int Num, Byte Value);
EXTERN_C void Calculate_Level_Tables(void);
EXTERN_C void ResetAYChipEmulation(void);
EXTERN_C void InitAYCounterVars(void);
EXTERN_C void InitAY(void);
EXTERN_C void loadConfiguration (t_CPC* CPC, BOOL registry, const TCHAR* chAppPath);

#endif
