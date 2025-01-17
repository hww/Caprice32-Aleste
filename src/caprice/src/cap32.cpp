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


   Oct 11, 2000 - 22:12 preliminary IN/OUT handlers; started with the GA OUT register write routines
   Oct 12, 2000 - 23:31 added GA ROM select to z80_OUT_handler
   Oct 14, 2000 - 13:58 added PPI IN/OUT handlers
   Oct 15, 2000 - 15:33 added CRTC IN/OUT handlers
   Oct 20, 2000 - 23:23 fixed some IN/OUT handler bugs
   Oct 27, 2000 - 17:39 added reset_CPC
   Oct 30, 2000 - 21:05 found the problem with the streched display: scr_bps needs to be in dwords, not bytes!
   Nov 01, 2000 - 23:43 aargh! found the BASIC 'reset' bug: the pbROMhi variable was pointing to the wrong location!
   Nov 03, 2000 - 18:03 added keyboard_interrupt handler
   Nov 03, 2000 - 19:10 added preliminary PSG register write handlers
   Nov 03, 2000 - 23:37 fixed the PPI port C handler; CPC keyboard works now!
   Dec 12, 2000 - 18:14 changed load_dsk() to work with a C based disk info structure
   Jan 24, 2001 - 22:28 loading from disk images works (again)!
   Apr 06, 2001 - 12:52 fixed the keyboard translation table (Allegro WIP 3.9.34 added 3 more keys to the array)

   Jun 13, 2001 - 17:25 added DirectDraw and DirectInput8 init routines for the new Windows port of Caprice32
   Jun 13, 2001 - 20:50 keyboard emualtion works now via the DI8 action mapping
   Jun 21, 2001 - 00:30 changed DDraw code to work in windowed mode; added routines to render CPC screen in 32bpp; added drag'n drop functionality for CPC drive A
   Jun 23, 2001 - 16:15 only the visible portion of the CPC screen is rendered to the frame buffer; Windows window is now sized to the proper CPC screen dimensions
   Jun 28, 2001 - 18:42 fixed the extended DSK parsing; loading DSK images via common dialog file selector; handling of joystick axis data
   Jun 29, 2001 - 20:16 speed throttling to original CPC speed; fixed the joystick mapping in the CPC keyboard matrix; implemented more menu commands
   Jun 30, 2001 - 22:57 settings stored in and retrieved from the registry; updated emulator_init and emulator_shutdown; file selector remembers path and selected file
   Jul 01, 2001 - 17:54 ROM slot cofiguration is stored in and retrieved from the registry; automatically loads last DSK images on startup
   Jul 04, 2001 - 00:34 colour tables for 16bpp (555 & 565) and 8bpp PC video modes; DDraw init updated with bit depth dependant code
   Jul 04, 2001 - 22:06 fixed 16bpp colour tables; updated VDU screen centering code to work with all bit depths
   Jul 06, 2001 - 00:35 implemented pause option; emulation is halted when application becomes inactive
   Jul 06, 2001 - 19:34 zip decompression for DSK and SNA loading
   Jul 07, 2001 - 00:58 fixed setting of GA colour table in load_snapshot; last DSK image load on startup supports ZIP files
   Jul 18, 2001 - 18:40 DirectSound init code finally works correctly!
   Jul 20, 2001 - 18:17 found the problem with the sound emulation: snd_multiplier calculation was done with integer arithmetic! grrrr...
   Jul 25, 2001 - 00:48 *finally* got a clean sound code that won't break up anymore!
   Aug 01, 2001 - 17:38 sound configuration is pulled from and stored in the registry
   Aug 02, 2001 - 18:31 floppy drive LED is now shown on the CPC screen during data transfers
   Aug 03, 2001 - 19:26 added About box
   Aug 03, 2001 - 23:49 altered load_dsk() to allocate memory on a track by track basis (in preparation of fdc_writeID() support)
   Aug 06, 2001 - 18:42 started work on the Options dialog
   Aug 10, 2001 - 19:10 finished the General Options property sheet
   Aug 11, 2001 - 17:29 up to 576KB of RAM supported
   Aug 12, 2001 - 21:43 extracted psg_reg_write() from the psg_write #define; fixed the PSG setup in load_snapshot()
   Aug 16, 2001 - 00:49 load_snapshot() now adjusts RAM size, and loads the correct CPC ROM as necessary
   Aug 20, 2001 - 00:59 added save_snapshot(); header contains preliminary v3 info
   Aug 20, 2001 - 16:10 updated load_snapshot() with processing of the 'official' v3 info
   Aug 22, 2001 - 23:26 added Audio Options property sheet to control PSG emulation
   Oct 06, 2001 - 13:22 removed the "experimental" joystick 2 support from the action map code - did not work as expected
   Oct 07, 2001 - 20:27 added the save_dsk() routine
   Oct 13, 2001 - 18:51 completed rewrite of zip handling; users can now choose images from multiple file archives
   Nov 08, 2001 - 19:08 bug fix: the zip_dir routine caused a crash if a zip archive would not open properly
   Nov 09, 2001 - 00:04 the ROM loading routine now checks the validity of the image, and skips a possible 128 bytes header

   May 09, 2002 - 19:07 removed the DDSCAPS_3DDEVICE flag from the InitDirectDraw code; modified UpdateBounds to prevent strechblits

   Jun 12, 2002 - 18:24 started converting DirectX specific stuff to Allegro
   Jun 14, 2002 - 17:49 emulator runs via GDI blits; re-implemented Allegro keyboard handler
   Jun 22, 2002 - 17:34 finally got the windowed DirectX mode working using the new Allegro CVS version
   Jun 25, 2002 - 18:41 added timer based speed throttling
   Jun 27, 2002 - 18:08 CPC screen blits correctly now: source coordinates were being mangled
   Jul 14, 2002 - 17:42 rewrote the PC sound playback routine to dynamically adjust the rate at which the buffer is filled
   Jul 24, 2002 - 22:16 fixed a possible crash on startup if a zipped DSK in drive A/B had been (re)moved between sessions
   Jul 27, 2002 - 16:45 added processing of a "language" file
   Jul 27, 2002 - 19:14 changed LoadConfiguration and SaveConfiguration to use the Allegro configuration rountines
   Jul 29, 2002 - 22:56 traced the 'access violation' problem back to the sound pause/resume functions
   Aug 02, 2002 - 22:37 added some error condition checks and modified sub-routines to report them properly

   Aug 24, 2002 - 23:00 determined Allegro to be unsuitable - reverting everything back to DirectX; implemented DirectInput keyboard translation
   Aug 26, 2002 - 22:51 fixed the initial application window size to use the correct dimensions
   Aug 27, 2002 - 18:23 streamlined the code to be more Windows friendly; app now goes to sleep when minimized
   Sep 07, 2002 - 18:28 added fullscreen mode; corrected 8bpp palette init; GDI calls (e.g. file selector) still work
   Sep 08, 2002 - 16:06 rewrote PCVideo init routines to support windowed/fullscreen mode switching
   Sep 12, 2002 - 00:02 fixed 50Hz timer by using QueryPerformanceCounter
   Sep 20, 2002 - 18:19 re-implemented DirectSound support; fixed timing problems - sound playback should no longer pop
   Sep 21, 2002 - 15:35 LoadConfiguration & SaveConfiguration now use the cap32.cfg file instead of the Registry
   Sep 25, 2002 - 22:49 full screen resolution is selectable in the Options dialog; auto-sizes visible portion; allows mode change while being fs
   Sep 26, 2002 - 22:26 added scanline and line doubling (in software) rendering modes
   Sep 28, 2002 - 17:38 added a speed slider to the General page of the Options dialog
   Sep 29, 2002 - 19:31 added colour monitor and green screen option; switched to QueryPerformanceCounter for the FPS counter
   Sep 29, 2002 - 23:03 added the 15 and 16 bpp green monitor colour maps - thanks to Ralf's Excel sheet!
   Oct 02, 2002 - 23:43 added fault condition checks to zip_dir, zip_extract and load_snapshot
   Oct 04, 2002 - 18:29 added fault condition checks to save_snapshot, load_dsk and save_dsk; added altered DSK check on exit
   Oct 04, 2002 - 22:34 added disk drive activity indicator
   Oct 07, 2002 - 17:48 fixed switching CPC monitor type "on-the-fly"; fixed surface restore in fullscreen mode
   Oct 07, 2002 - 21:58 added line doubling (in hardware) rendering mode
   Oct 16, 2002 - 22:18 added enumeration and initilization of all installed keyboards and joysticks
   Oct 17, 2002 - 23:40 replaced the controls property page in the options dialog
   Oct 28, 2002 - 19:50 added support for custom controls: CPC joystick functions can now be mapped to any attached input device(s)
   Nov 01, 2002 - 15:54 added custom print routine for on-screen messages (e.g. FPS counter)
   Nov 02, 2002 - 16:44 mouse cursor now auto-hides with no mouse movement for 2 seconds
   Nov 10, 2002 - 17:38 added ROM patching to support the french and spanish CPC keyboard layouts
   Nov 10, 2002 - 21:31 fixed PPI port C handler
   Nov 12, 2002 - 22:08 changes to the OUT handler: GA and CRTC cannot be accessed at the same time; fixed the GA pen selection
   Nov 13, 2002 - 22:48 tweaked the IN/OUT handlers a bit more
   Dec 05, 2002 - 00:06 fixed the problem with the tape startup delay: the PPI Port C bit manipulation only considered 4 instead of 8 bits
   Dec 08, 2002 - 22:05 updated the Z80_OUT_handler to accept FDC data on ports 0x7f and 0x7e, as per Kevin's I/O port document
   Dec 10, 2002 - 23:50 print now draws double spaced in scanline mode: don't have to remove the text again this way
   Dec 19, 2002 - 23:28 added 48 & 96 kHz audio options; added sanity checks for LoadConfiguration
   Dec 21, 2002 - 15:50 PCAudio_init reports if selected sample rate is not supported; added empty path handling to LoadConfiguration
   Dec 22, 2002 - 17:21 found a typo in my keyboard lookup table: CPC key 8 was returning the same as CPC key 0
   Jan 12, 2003 - 01:05 added the ability to search for multiple extensions to zip_dir
   Jan 12, 2003 - 15:57 completed processing of dropped dsk, sna and cdt files
   Jan 15, 2003 - 17:30 added the removal of the temp file to process_drop when uncompressing zip archives
   Jan 21, 2003 - 18:53 changed the window handle in all MessageBox calls from NULL to hAppWnd: errors display correctly in full-screen mode now
   Jan 24, 2003 - 00:44 altered the validity check on loading expansion ROMs, as some may not contain a jump instruction at offset 0x06
   Jan 25, 2003 - 16:49 fixed the FDC port handling in z80_in_handler: "Famous 5" loads now!
   Jan 27, 2003 - 18:47 updated the resource file to support themed Windows XP controls
   Jan 28, 2003 - 19:18 added insert_voc: converts a sound sample into a CDT direct recording block
   Jan 30, 2003 - 20:37 added 24bpp display mode support
   Jan 31, 2003 - 16:50 CPC speed slider range is now 50% to 800%, and can be set in 25% increments
   Jan 31, 2003 - 22:42 AMSDOS is placed in ROM slot 7 if the config file does not yet exist
   Feb 23, 2003 - 14:48 fixed the Windows system palette problems in 256 colour mode
   Mar 04, 2003 - 21:04 removed the background brush in the app window class; replaced "return 0L" with "break" in WindowProc
   Mar 11, 2003 - 22:38 emulation can now continue to run when focus is lost; added more invalid object checks to ensure clean exits
   Mar 12, 2003 - 18:08 had to add the background brush again: fullscreen mode would otherwise not update the unused area
   Mar 12, 2003 - 19:02 added the 'auto-pause on loss of focus' feature to the Options dialog
   Mar 12, 2003 - 22:07 added the display of HRESULT codes for DirectDraw function calls
   Mar 17, 2003 - 22:40 added a check_drvX call to the eject disk menu functions
   Mar 22, 2003 - 18:39 added the ability to insert blank disks in either CPC drive; the new Disk page in the Options dialog allows you to choose the format; implemented the Flip Disk option to reverse sides
   Mar 23, 2003 - 21:41 custom disk formats can now be specified in the config file; modified LoadConfiguration and SaveConfiguration to support this feature
   Mar 29, 2003 - 16:40 tape motor is not turned on if there is no tape in the drive
   Apr 02, 2003 - 21:31 changes to the Options dialog: moved the ROM slots to their own page; some cosmetic changes; remembers last page user was on
   Apr 03, 2003 - 22:12 added the option to capture printer output to file; aborting a save dialog for a changed DSK now drops back to the emulation without taking any further action
   Apr 07, 2003 - 19:09 modified the z80_OUT_handler to capture port writes for the MF2; added all the necessary bits for MF2 emulation, but for now it doesn't display the MF2 menu correctly (text is invisible!)...
   Apr 07, 2003 - 21:59 doh! fixed the MF2 problem: the MF2 page-out port always set RAM bank0 instead if checking if the lower ROM was active
   Apr 09, 2003 - 15:49 MF2 ROM is now restored at every reset to ensure the ROM area has not been corrupted by memory writes
   Apr 13, 2003 - 16:18 added code to display the logo in the About box with a transparent background
   Apr 16, 2003 - 16:18 joystick emulation can be toggled on/off; keyboard control assignments now override regular CPC keyboard actions; all dialogs now feature the "Caprice32 - " string to make identification easier; ZIP selector shows ZIP file name
   Apr 26, 2003 - 14:03 added CaptureScreenshot to save the screen contents to a PNG file
   Apr 26, 2003 - 16:25 finished screen capture implementation: added file selector and path/file storage to config file
   May 05, 2003 - 22:46 updated the Audio page in the Options dialog with controls to choose the sample size and adjust the volume
   May 06, 2003 - 18:59 load_snapshot and save_snapshot now use the v3 PSG information + the printer port data
   May 13, 2003 - 17:41 fixed the file selector problem on drag and drop: the exit condition check was reversed
   May 18, 2003 - 01:01 moved Gate Array memory handling to ga_memory_manager; save_snapshot correctly stores current RAM bank now
   May 21, 2003 - 00:31 changed the colour palette generation to support an intensity level slider
   May 21, 2003 - 14:42 added the Intensity slider control to the Video options
   May 26, 2003 - 20:06 emulation loop needs to keep running to produce proper key events: fixes the Pause problem
   May 28, 2003 - 13:59 modified the shadow of the print routine to make it more readable on a white background
   May 29, 2003 - 15:09 implemented the info message display system and added strings for most emulator actions and keyboard shortcuts
   May 30, 2003 - 12:17 added the tape PLAY/STOP button control for proper tape operation
   Jun 02, 2003 - 15:05 if the CreateSurface call fails with video memory, it now attempts to allocate it in system memory
   Jun 04, 2003 - 19:38 added the 'on printer port' drop-down to the Audio options page
   Aug 10, 2003 - 14:35 z80_IN_handler: CRTC write only registers return 0; load_snapshot: fixed broken snapshot support (PPI values were written to the wrong ports!); digiblaster/soundplayer combined into one - changed from a drop down to a check box

   May 19, 2004 - 23:13 removed all DirectX/Windows specific parts and replaced them (wherever possible) with the SDL equivalent
   May 23, 2004 - 17:48 dropped double buffer scheme in favour of a back buffer/custom blit operation; fixed colour palette init in 8bpp mode; added support for half size render mode; back buffer is cleared in video_init(); replaced the SDL_Flip operation with an SDL_BlitSurface; initial ExitCondition is now EC_FRAME_COMPLETE to ensure we have a valid video memory pointer to start with
   May 24, 2004 - 00:49 reintroduced snapshot_load & snapshot_save; modified vdu_init to update the two SDL_Rect structures to center or crop the CPC screen; introduced the dwXScale var to support the half size render mode
   May 29, 2004 - 18:09 reintroduced tape_eject, tape_insert and tape_insert_voc; added sound support via the native SDL audio routines
*/

#include <stddef.h> /* offsetof */
#include <time.h>
#include "SDL.h"

#include "cap32.h"
#include "crtc.h"
#include "tape.h"
#include "z80.h"
#include "contrib/include/app.h"
#include "contrib/include/cpckey.h"
#include "contrib/include/loadrom.h"
#include "contrib/include/xbm_cpc.h"
#include "contrib/include/cpcrom.h"
#include "contrib/include/autotype.h"
#include "contrib/include/dialogs.h"
#include "font.c"
#include "capzip.h"
#include "caperr.h"
#include "aleste.h"

#define VERSION_STRING "v4.1.0"
#define CAPTION "Caprice32 "VERSION_STRING

#define MSG_SNA_LOAD             32
#define MSG_SNA_SAVE             33
#define MSG_DSK_LOAD             34
#define MSG_DSK_SAVE             35
#define MSG_JOY_ENABLE           36
#define MSG_JOY_DISABLE          37
#define MSG_SPD_NORMAL           38
#define MSG_SPD_FULL             39
#define MSG_TAP_INSERT           40
#define MSG_SDUMP_SAVE           41
#define MSG_PAUSED               42
#define MSG_TAP_PLAY             43
#define MSG_TAP_STOP             44

extern "C" // TROELS
{
extern Byte bTapeLevel;
extern t_z80regs z80;

/* autotype string should not be here - it should be on the command line */
/* but the command line code make the assumption that all command line arguments are files! */
const TCHAR* Caprice32_Autotype = NULL;

SDL_AudioSpec *audio_spec = NULL;

SDL_Surface *video_surface = NULL;
SDL_Surface *back_surface = NULL;
SDL_Rect video_rect, back_rect;

uLong dwTicks, dwTicksOffset, dwTicksTarget, dwTicksTargetFPS;
uLong dwFPS, dwFrameCount;
uLong dwXScale, dwYScale;
uLong dwSndMinSafeDist, dwSndMaxSafeDist;

uLong dwBreakPoint, dwTrace, dwMF2ExitAddr;
uLong dwMF2Flags = 0;
Byte *pbGPBuffer = NULL;
Byte *pbSndBuffer = NULL;
Byte *pbSndBufferEnd = NULL;
Byte *pbSndStream = NULL;
Byte  *membank_read[4], *membank_write[4], *memmap_ROM[256];
Byte *pbRAM = NULL;
Byte *pbROMlo = NULL;
Byte *pbROMhi = NULL;
Byte *pbExpansionROM = NULL;
Byte *pbMF2ROMbackup = NULL;
Byte *pbMF2ROM = NULL;
Byte *pbTapeImage = NULL;
Byte *pbTapeImageEnd = NULL;
Byte mode0_table[512], mode1_table[1024];
Byte keyboard_matrix[16];

static Byte *membank_config[8][4];

FILE *pfileObject;
FILE *pfoPrinter;

#ifdef DEBUG
FILE *pfoDebug;
#endif

typedef void (*MH)(uInt);
typedef void (*BH)(void);

MH mode_handler[4] = {
   draw32bpp_mode0_double,
   draw32bpp_mode1_double,
   draw32bpp_mode2_double,
   draw32bpp_mode0_double,
};
BH border_handler = draw32bpp_border_double;

uLong freq_table[MAX_FREQ_ENTRIES] = {
   11025,
   22050,
   44100,
   48000,
   96000
};

static const double colours_rgb[32][3] = {
   { 0.5, 0.5, 0.5 }, { 0.5, 0.5, 0.5 },{ 0.0, 1.0, 0.5 }, { 1.0, 1.0, 0.5 },
   { 0.0, 0.0, 0.5 }, { 1.0, 0.0, 0.5 },{ 0.0, 0.5, 0.5 }, { 1.0, 0.5, 0.5 },
   { 1.0, 0.0, 0.5 }, { 1.0, 1.0, 0.5 },{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 1.0 },
   { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 1.0 },{ 1.0, 0.5, 0.0 }, { 1.0, 0.5, 1.0 },
   { 0.0, 0.0, 0.5 }, { 0.0, 1.0, 0.5 },{ 0.0, 1.0, 0.0 }, { 0.0, 1.0, 1.0 },
   { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 },{ 0.0, 0.5, 0.0 }, { 0.0, 0.5, 1.0 },
   { 0.5, 0.0, 0.5 }, { 0.5, 1.0, 0.5 },{ 0.5, 1.0, 0.0 }, { 0.5, 1.0, 1.0 },
   { 0.5, 0.0, 0.0 }, { 0.5, 0.0, 1.0 },{ 0.5, 0.5, 0.0 }, { 0.5, 0.5, 1.0 }
};

static const double colours_green[32] = {
   0.5647, 0.5647, 0.7529, 0.9412,
   0.1882, 0.3765, 0.4706, 0.6588,
   0.3765, 0.9412, 0.9098, 0.9725,
   0.3451, 0.4078, 0.6275, 0.6902,
   0.1882, 0.7529, 0.7216, 0.7843,
   0.1569, 0.2196, 0.4392, 0.5020,
   0.2824, 0.8471, 0.8157, 0.8784,
   0.2510, 0.3137, 0.5333, 0.5961
};

uLong colour_table[32];

static const Byte CRTC_values[2][14] = {
   {0x3f, 0x28, 0x2e, 0x8e, 0x1f, 0x06, 0x19, 0x1b, 0x00, 0x07, 0x00, 0x00, 0x30, 0x00},
   {0x3f, 0x28, 0x2e, 0x8e, 0x26, 0x00, 0x19, 0x1e, 0x00, 0x07, 0x00, 0x00, 0x30, 0x00}
};

static const Byte bit_values[8] = {
   0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

static const Byte keyboard_translation[] = 
{
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_DEL  , CPC_KEY_TAB  , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_RETURN, CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_ESC  , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_SPACE, CPC_KEY_NULL , CPC_KEY_3    , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_1    , CPC_KEY_SEMICOLON, // CPC_KEY_SEMICOLON was missing. TROELS
   CPC_KEY_5    , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_COMMA, CPC_KEY_MINUS , CPC_KEY_DOT  , CPC_KEY_BACKSLASH,
   CPC_KEY_ZERO , CPC_KEY_1    , CPC_KEY_2    , CPC_KEY_3    , CPC_KEY_4    , CPC_KEY_5     , CPC_KEY_6    , CPC_KEY_7    ,
   CPC_KEY_8    , CPC_KEY_9    , CPC_KEY_NULL , CPC_KEY_COLON, CPC_KEY_NULL , CPC_KEY_HAT   , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_AT   , CPC_KEY_CLOSE_SQUARE_BRACKET,CPC_KEY_OPEN_SQUARE_BRACKET,CPC_KEY_NULL,CPC_KEY_8,
   CPC_KEY_NULL , CPC_KEY_A    , CPC_KEY_B    , CPC_KEY_C    , CPC_KEY_D    , CPC_KEY_E     , CPC_KEY_F    , CPC_KEY_G    ,
   CPC_KEY_H    , CPC_KEY_I    , CPC_KEY_J    , CPC_KEY_K    , CPC_KEY_L    , CPC_KEY_M     , CPC_KEY_N    , CPC_KEY_O    ,
   CPC_KEY_P    , CPC_KEY_Q    , CPC_KEY_R    , CPC_KEY_S    , CPC_KEY_T    , CPC_KEY_U     , CPC_KEY_V    , CPC_KEY_W    ,
   CPC_KEY_X    , CPC_KEY_Y    , CPC_KEY_Z    , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_CLR ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_DEL  , CPC_KEY_TAB  , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_RETURN, CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_ZERO , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_9    ,
   CPC_KEY_7    , CPC_KEY_2    , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_F0   , CPC_KEY_F1   , CPC_KEY_F2   , CPC_KEY_F3   , CPC_KEY_F4   , CPC_KEY_F5    , CPC_KEY_F6   , CPC_KEY_F7   ,
   CPC_KEY_F8   , CPC_KEY_F9   , CPC_KEY_FDOT , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_SMALL_ENTER,
   CPC_KEY_NULL , CPC_KEY_CURSOR_UP, CPC_KEY_CURSOR_DOWN, CPC_KEY_CURSOR_RIGHT, CPC_KEY_CURSOR_LEFT, CPC_KEY_INSERT, CPC_KEY_HELP, CPC_KEY_NULL,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_F1F6 , CPC_KEY_F2F7 , CPC_KEY_F3F8 , CPC_KEY_F4F9  , CPC_KEY_F5F10 , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_CAPS_LOCK,CPC_KEY_NULL,CPC_KEY_SHIFT,
   CPC_KEY_SHIFT, CPC_KEY_NULL , CPC_KEY_CONTROL,CPC_KEY_NULL, CPC_KEY_COPY , CPC_KEY_NULL  , CPC_KEY_NULL , CPC_KEY_NULL ,
   CPC_KEY_NULL , CPC_KEY_FORWARD_SLASH,CPC_KEY_NULL,CPC_KEY_NULL,CPC_KEY_NULL,CPC_KEY_NULL , CPC_KEY_NULL , CPC_KEY_NULL
};

extern "C" void key_add(int cpc_key)
{
   keyboard_matrix[cpc_key >> 4] &= ~bit_values[cpc_key & 7]; // key is being held down
}

extern "C" void key_remove(int cpc_key)
{
   keyboard_matrix[cpc_key >> 4] |= bit_values[cpc_key & 7]; // key has been released
}



#define CAP32_FULLSCRN  SDLK_BACKQUOTE
#define CAP32_LOADDRVA  SDLK_F6 /* DRIVE B with shift */
//#define CAP32_LOADDRVB  SDLK_F6
#define CAP32_LOADTAPE  SDLK_F7 
#define CAP32_OPTIONS   SDLK_F8
#define CAP32_LOADSNAP  SDLK_F9 /* SAVE with shift */
//#define CAP32_SAVESNAP  SDLK_F9 
#define CAP32_EXIT      SDLK_F11
//#define CAP32_MF2STOP   SDLK_F11 /* ALESTE do not need it */
#define CAP32_RESET     SDLK_F10 /* SPEED with shift */
//#define CAP32_SPEED     SDLK_F11 
#define CAP32_PAUSE     SDLK_PAUSE
//#define CAP32_PAUSE     SDLK_BREAK  // doesn't work. Troels
// #define CAP32_SCRNSHOT  SDLK_PRINT // doesn't work. Troels
#define CAP32_SCRNSHOT  SDLK_SYSREQ

#include "rom_mods.c"

static TCHAR chAppPath[_MAX_PATH + 1];
char chROMSelected[_MAX_PATH + 1];
const TCHAR chROMFile[3][14] = {
   _T("cpc464.rom" ),
   _T("cpc664.rom" ),
   _T("cpc6128.rom")
};

t_CPC CPC;
t_CRTC CRTC;
t_FDC FDC;
t_GateArray GateArray;
t_PPI PPI;
t_PSG PSG;
t_VDU VDU;

t_drive driveA;
t_drive driveB;

t_zip_info zip_info;

t_disk_format disk_format[MAX_DISK_FORMAT] = {
   { "178K Data Format", 40, 1, 9, 2, 0x52, 0xe5, {{ 0xc1, 0xc6, 0xc2, 0xc7, 0xc3, 0xc8, 0xc4, 0xc9, 0xc5 }} },
   { "169K Vendor Format", 40, 1, 9, 2, 0x52, 0xe5, {{ 0x41, 0x46, 0x42, 0x47, 0x43, 0x48, 0x44, 0x49, 0x45 }} }
};

}; // extern "C"

#define psg_write \
{ \
   Byte control = PSG.control & 0xc0; /* isolate PSG control bits */ \
   if (control == 0xc0) { /* latch address? */ \
      PSG.reg_select = psg_data; /* select new PSG register */ \
   } else if (control == 0x80) { /* write? */ \
      if (PSG.reg_select < 16) { /* valid register? */ \
         SetAYRegister(PSG.reg_select, psg_data); \
      } \
   } \
}



void ga_init_banking (void)
{
   Byte *romb0, *romb1, *romb2, *romb3, *romb4, *romb5, *romb6, *romb7;
   Byte *pbRAMbank;

   romb0 = pbRAM;
   romb1 = pbRAM + 1*16384;
   romb2 = pbRAM + 2*16384;
   romb3 = pbRAM + 3*16384;

   pbRAMbank = pbRAM + ((GateArray.RAM_bank + 1) * 65536);
   romb4 = pbRAMbank;
   romb5 = pbRAMbank + 1*16384;
   romb6 = pbRAMbank + 2*16384;
   romb7 = pbRAMbank + 3*16384;

   membank_config[0][0] = romb0;
   membank_config[0][1] = romb1;
   membank_config[0][2] = romb2;
   membank_config[0][3] = romb3;

   membank_config[1][0] = romb0;
   membank_config[1][1] = romb1;
   membank_config[1][2] = romb2;
   membank_config[1][3] = romb7;

   membank_config[2][0] = romb4;
   membank_config[2][1] = romb5;
   membank_config[2][2] = romb6;
   membank_config[2][3] = romb7;

   membank_config[3][0] = romb0;
   membank_config[3][1] = romb3;
   membank_config[3][2] = romb2;
   membank_config[3][3] = romb7;

   membank_config[4][0] = romb0;
   membank_config[4][1] = romb4;
   membank_config[4][2] = romb2;
   membank_config[4][3] = romb3;

   membank_config[5][0] = romb0;
   membank_config[5][1] = romb5;
   membank_config[5][2] = romb2;
   membank_config[5][3] = romb3;

   membank_config[6][0] = romb0;
   membank_config[6][1] = romb6;
   membank_config[6][2] = romb2;
   membank_config[6][3] = romb3;

   membank_config[7][0] = romb0;
   membank_config[7][1] = romb7;
   membank_config[7][2] = romb2;
   membank_config[7][3] = romb3;
}



void ga_memory_manager (void)
{
   uLong mem_bank;
	if(ALESTE && alesteExtend.bit.MAPMOD){
		
		for (int n = 0; n < 4; n++) { // remap active memory banks
			mem_bank = (uLong)pbRAM + ((uLong)alesteMapper[n]<<14);
	    	membank_read[n] =  membank_write[n] = (Byte*)mem_bank;
		}
	 }else{
		    if (CPC.ram_size == 64) { // 64KB of RAM?
      mem_bank = 0; // no expansion memory
      GateArray.RAM_config = 0; // the only valid configuration is 0
   } else {
      mem_bank = (GateArray.RAM_config >> 3) & 7; // extract expansion memory bank
      if (((mem_bank+2)*64) > CPC.ram_size) { // selection is beyond available memory?
         mem_bank = 0; // force default mapping
      }
   }
   if (mem_bank != GateArray.RAM_bank) { // requested bank is different from the active one?
      GateArray.RAM_bank = mem_bank;
      ga_init_banking();
   }
   for (int n = 0; n < 4; n++) { // remap active memory banks
      membank_read[n] = membank_config[GateArray.RAM_config & 7][n];
      membank_write[n] = membank_config[GateArray.RAM_config & 7][n];
   }

	 }
   if (!(GateArray.ROM_config & 0x04)) { // lower ROM is enabled?
      if (dwMF2Flags & MF2_ACTIVE) { // is the Multiface 2 paged in?
         membank_read[0] = pbMF2ROM;
         membank_write[0] = pbMF2ROM;
      } else {
         membank_read[0] = pbROMlo; // 'page in' lower ROM
      }
   }
   if (!(GateArray.ROM_config & 0x08)) { // upper/expansion ROM is enabled?
      membank_read[3] = pbExpansionROM; // 'page in' upper/expansion ROM
   }
}

bool KeyboardScanned = false;

Byte z80_IN_handler (reg_pair port)
{
   Byte ret_val;

   ret_val = 0xff; // default return value
// ALESTE 520 MAPPER-----------------------------------------------------------
	if(ALESTE && !(port.b.h & 0x80)){
		ret_val = alesteMapper[(port.b.h & 3)] | ~ALESTE_MAPPER_MASK;		
	} 
// MAGIC SOUND ----------------------------------------------------------------
	if(ALESTE && !(port.b.h & 4) && !(port.b.l & 32)){
		ret_val = readMS(port);
	}
// CRTC -----------------------------------------------------------------------
   if (!(port.b.h & 0x40 )) { // CRTC chip select?
      if ((port.b.h & 3) == 3) { // read CRTC register?
         if ((CRTC.reg_select > 11) && (CRTC.reg_select < 18)) { // valid range?
            ret_val = CRTC.registers[CRTC.reg_select];
         }
         else {
            ret_val = 0; // write only registers return 0
         }
      }
   }
// CRTC -----------------------------------------------------------------------
   if (!(port.b.h & 0x40)) { // CRTC chip select?
      if ((port.b.h & 3) == 3) { // read CRTC register?
         if ((CRTC.reg_select > 11) && (CRTC.reg_select < 18)) { // valid range?
            ret_val = CRTC.registers[CRTC.reg_select];
         }
         else {
            ret_val = 0; // write only registers return 0
         }
      }
   }
// PPI ------------------------------------------------------------------------
   else if (!(port.b.h & 0x08)) { // PPI chip select?
      Byte ppi_port = port.b.h & 3;
      switch (ppi_port) {
         case 0: // read from port A?
            if (PPI.control & 0x10) { // port A set to input?
				if(~alesteExtend.bit.CSAY)
				{
				if ((PSG.control & 0xc0) == 0x40) { // PSG control set to read?
					if (PSG.reg_select < 16) { // within valid range?
						if (PSG.reg_select == 14) { // PSG port A?                        
							KeyboardScanned = true;
							if (!(PSG.RegisterAY.Index[7] & 0x40)) { // port A in input mode?
							ret_val = keyboard_matrix[CPC.keyboard_line & 0x0f]; // read keyboard matrix node status
							} else {
							ret_val = PSG.RegisterAY.Index[14] & (keyboard_matrix[CPC.keyboard_line & 0x0f]); // return last value w/ logic AND of input
							}
							#ifdef DEBUG_KBD
							if(ret_val!=0xFF)
								fprintf(pfoDebug, "KBD RD 0x%02x = 0x%02x \n", CPC.keyboard_line & 0x0f,ret_val);
							#endif
						} else if (PSG.reg_select == 15) { // PSG port B?
							if ((PSG.RegisterAY.Index[7] & 0x80)) { // port B in output mode?
							ret_val = PSG.RegisterAY.Index[15]; // return stored value
							}
						} else {
							ret_val = PSG.RegisterAY.Index[PSG.reg_select]; // read PSG register
						}
					}
				}
				} else {
               		if((PPI.portC & 0x07)==5){ // DS read
	               		ret_val = rtcRead();
               		} 
				}
            } else {
               ret_val = PPI.portA; // return last programmed value
            }
			#ifdef DEBUG_PPI
			fprintf(pfoDebug, "PPI RD A 0x%02x\r\n", ret_val);
			#endif

            break;

         case 1: // read from port B?
            if (PPI.control & 2) { // port B set to input?
               ret_val = bTapeLevel | // tape level when reading
                         (CPC.printer ? 0 : 0x40) | // ready line of connected printer
                         (CPC.jumpers & 0x7f) | // manufacturer + 50Hz
                         (CRTC.flags & VS_flag); // VSYNC status
			   if(ALESTE){
				   ret_val |= (fdc_interrupt ? 0x2 : 0);
			   }
            } else {
               ret_val = PPI.portB; // return last programmed value
            }
			#ifdef DEBUG_PPI
			fprintf(pfoDebug, "PPI RD B 0x%02x\r\n", ret_val);
			#endif
            break;

         case 2: // read from port C?
            Byte direction = PPI.control & 9; // isolate port C directions
            ret_val = PPI.portC; // default to last programmed value
            if (direction) { // either half set to input?
               if (direction & 8) { // upper half set to input?
                  ret_val &= 0x0f; // blank out upper half
                  Byte val = PPI.portC & 0xc0; // isolate PSG control bits
                  if (val == 0xc0) { // PSG specify register?
                     val = 0x80; // change to PSG write register
                  }
                  ret_val |= val | 0x20; // casette write data is always set
                  if (CPC.tape_motor) {
                     ret_val |= 0x10; // set the bit if the tape motor is running
                  }
               }
               if (!(direction & 1)) { // lower half set to output?
                  ret_val |= 0x0f; // invalid - set all bits
               }
            }
			#ifdef DEBUG_PPI
			fprintf(pfoDebug, "PPI RD C 0x%02x\r\n", ret_val);
			#endif
            break;
      }
   }
// ----------------------------------------------------------------------------
   else if (!(port.b.h & 0x04)) { // external peripheral?
      if ((port.b.h == 0xfb) && (!(port.b.l & 0x80))) { // FDC?
         if (!(port.b.l & 0x01)) { // FDC status register?
            ret_val = fdc_read_status();
         } else { // FDC data register
            ret_val = fdc_read_data();
         }
      }
   }
   #ifdef DEBUG_IN
   fprintf(pfoDebug, "IN  0x%04x 0x%02x\n",port.w, ret_val);
   #endif
   return ret_val;
}

static int video_init (void);
void vdu_init (bool bolInit);
void video_set_style (void);

void z80_OUT_handler (reg_pair port, Byte val)
{
   #ifdef DEBUG_OUT
   fprintf(pfoDebug, "OUT 0x%04x 0x%02x\n",port.w, val);
   #endif
   #ifdef DEBUG_ALESTE_EXTEND
		char str[16];
        strcpy(str, "--sabmyx");
   #endif
// Aleste EXTEND write only register ------------------------------------------
	if(ALESTE && port.w.l==0xFABF){
       	alesteExtend.b=val;		
	    #ifdef DEBUG_ALESTE_EXTEND
		   if(alesteExtend.bit.HIGHTX) str[7]-=0x20;
		   if(alesteExtend.bit.HIGHTY) str[6]-=0x20;
		   if(alesteExtend.bit.MAPMOD) str[5]-=0x20;
		   if(alesteExtend.bit.BLACKS) str[4]-=0x20;
		   if(alesteExtend.bit.CSAY)   str[3]-=0x20;
		   if(alesteExtend.bit.CS53)   str[2]-=0x20;
			
	       fprintf(pfoDebug, "EXTENT [0x%02x] %s\n",alesteExtend.b,str);
	    #endif
        ga_memory_manager();
		video_set_style();
		vdu_init(true);
    } 

// Aleste MAGIC SOUND ---------------------------------------------------------
	if(ALESTE && !(port.b.h & 4) && !(port.b.l & 32)){
		writeMS(port, val);
	}
// Gate Array -----------------------------------------------------------------
   if ((port.b.h & 0xc0) == 0x40) { // GA chip select?
      switch (val >> 6) {
         case 0: // select pen
            #ifdef DEBUG_GA
               fprintf(pfoDebug, "pen 0x%02x\r\n", val);
            #endif
            GateArray.pen = val & 0x10 ? 0x10 : val & 0x0f; // if bit 5 is set, pen indexes the border colour
            if (CPC.mf2) { // MF2 enabled?
               *(pbMF2ROM + 0x03fcf) = val;
            }
            break;
         case 1: // set colour
            {
	           if(ALESTE && alesteExtend.bit.MAPMOD){
					#ifdef DEBUG_ALESTE_PALETE
				       fprintf(pfoDebug, "Color[0x%02x]=0x%02x\n",GateArray.pen, val);
		            #endif
		            Byte r = ((val & 0x30)>>4)*(255/3); // isolate colour value
		            Byte g = ((val & 0x0C)>>2)*(255/3); // isolate colour value
		            Byte b = (val & 0x03)*(255/3); // isolate colour value
            		GateArray.palette[GateArray.pen] = SDL_MapRGB(back_surface->format,	r, g, b);
            	} else {
					#ifdef DEBUG_GA
				       fprintf(pfoDebug, "clr 0x%02x\r\n", val);
		            #endif

		           Byte colour = val & 0x1f; // isolate colour value
	               GateArray.ink_values[GateArray.pen] = colour;
				   GateArray.palette[GateArray.pen] = colour_table[colour];
				}
            }
            if (CPC.mf2) { // MF2 enabled?
               int iPen = *(pbMF2ROM + 0x03fcf);
               *(pbMF2ROM + (0x03f90 | ((iPen & 0x10) << 2) | (iPen & 0x0f))) = val;
            }
            break;
         case 2: // set mode
            #ifdef DEBUG_GA
               fprintf(pfoDebug, "rom 0x%02x\r\n", val);
            #endif
            GateArray.ROM_config = val;
            GateArray.requested_scr_mode = mode_handler[val & 0x03]; // request a new CPC screen mode
            ga_memory_manager();
			video_set_style();
			vdu_init(true);
			if (val & 0x10) { // delay Z80 interrupt?
               z80.int_pending = 0; // clear pending interrupts
               GateArray.sl_count = 0; // reset GA scanline counter
            }
            if (CPC.mf2) { // MF2 enabled?
               *(pbMF2ROM + 0x03fef) = val;
            }
            break;
         case 3: // set memory configuration
			if(ALESTE && alesteExtend.bit.MAPMOD){
				alesteMapper[(port.b.h & 3)]= val & ALESTE_MAPPER_MASK;		
				#ifdef DEBUG_ALESTE_MAPPER
					fprintf(pfoDebug, "Mapper[0x%02x]=0x%02x [0x%02x 0x%02x 0x%02x 0x%02x]\n", (port.b.h & 3), val & ALESTE_MAPPER_MASK, alesteMapper[0],alesteMapper[1],alesteMapper[2],alesteMapper[3]);
				#endif
		        ga_memory_manager();
			} else { 
				#ifdef DEBUG_GA
					fprintf(pfoDebug, "mem 0x%02x\r\n", val);
				#endif
				GateArray.RAM_config = val;
				ga_memory_manager();
				if (CPC.mf2) { // MF2 enabled?
				*(pbMF2ROM + 0x03fff) = val;
				}
			}
            break;
      }
   }
// CRTC -----------------------------------------------------------------------
   if (!(port.b.h & 0x40)) { // CRTC chip select?
      Byte crtc_port = port.b.h & 3;
      if (crtc_port == 0) { // CRTC register select?
         CRTC.reg_select = val;
         if (CPC.mf2) { // MF2 enabled?
            *(pbMF2ROM + 0x03cff) = val;
         }
      }
      else if (crtc_port == 1) { // CRTC write data?
         if (CRTC.reg_select < 16) { // only registers 0 - 15 can be written to

#ifdef DEBUG_CRT_WRITE
			 fprintf(pfoDebug, "CRT[0x%02x]=0x%02x\n", CRTC.reg_select, val);
#endif
            CRTC.registers[CRTC.reg_select] = val;
            switch (CRTC.reg_select) {
               case 3: // sync width
                  CRTC.hsw = val & 0x0f; // isolate horizontal sync width
                  VDU.hsw = CRTC.hsw - 2; // GA delays HSYNC by 2 chars
                  if (VDU.hsw < 0) { // negative value?
                     VDU.hsw = 0; // no VDU HSYNC
                  }
                  else if (VDU.hsw > 4) { // HSYNC longer than 4 chars?
                     VDU.hsw = 4; // maxium of 4
                  }
                  CRTC.vsw = val >> 4; // isolate vertical sync width
                  if (!CRTC.vsw) {
                     CRTC.vsw = 16; // 0 = width of 16
                  }
                  break;
               case 5: // vertical total adjust
                  CRTC.vt_adjust = val & 0x1f;
                  break;
               case 8: // interlace and skew
                  CRTC.skew = (val >> 4) & 3; // isolate display timing skew
                  if (CRTC.skew == 3) { // no output?
                     CRTC.skew = 0xff;
                  }
                  break;
               case 9: // maximum raster count
                  CRTC.max_raster = val << 3; // modify value for easier handling
                  break;
               case 12: // start address high Byte
               case 13: // start address low Byte
                  {
                     uLong val1 = CRTC.registers[12] & 0x3f;
                     uLong val2 = val1 & 0x0f; // isolate screen size
                     val1 = (val1 << 1) & 0x60; // isolate CPC RAM bank
                     val2 |= val1; // combine
                     CRTC.requested_addr = (CRTC.registers[13] + (val2 << 8)) << 1;
                  }
                  break;
            }
         }
         if (CPC.mf2) { // MF2 enabled?
            *(pbMF2ROM + (0x03db0 | (*(pbMF2ROM + 0x03cff) & 0x0f))) = val;
         }
      }
   }
// ROM select -----------------------------------------------------------------
   if (!(port.b.h & 0x20)) { // ROM select?
      GateArray.upper_ROM = val;
      pbExpansionROM = memmap_ROM[val];
      if (pbExpansionROM == NULL) { // selected expansion ROM not present?
         pbExpansionROM = pbROMhi; // revert to BASIC ROM
      }
      if (!(GateArray.ROM_config & 0x08)) { // upper/expansion ROM is enabled?
         membank_read[3] = pbExpansionROM; // 'page in' upper/expansion ROM
      }
      if (CPC.mf2) { // MF2 enabled?
         *(pbMF2ROM + 0x03aac) = val;
      }
   }
// printer port ---------------------------------------------------------------
   if (!(port.b.h & 0x10)) { // printer port?
      CPC.printer_port = val ^ 0x80; // invert bit 7
      if (pfoPrinter) {
         if (!(CPC.printer_port & 0x80)) { // only grab data bytes; ignore the strobe signal
            fputc(CPC.printer_port, pfoPrinter); // capture printer output to file
         }
      }
   }
// PPI ------------------------------------------------------------------------
   if (!(port.b.h & 0x08)) { // PPI chip select?
      switch (port.b.h & 3) {
         case 0: // write to port A?
			#ifdef DEBUG_PPI
			fprintf(pfoDebug, "PPI WR A 0x%02x\r\n", val);
		    #endif
            PPI.portA = val;
            if (!(PPI.control & 0x10)) { // port A set to output?
               Byte psg_data = val;
               psg_write
            }
            break;
         case 1: // write to port B?
            PPI.portB = val;
			#ifdef DEBUG_PPI
			fprintf(pfoDebug, "PPI WR B 0x%02x\r\n", val);
		    #endif
            break;
         case 2: // write to port C?
			#ifdef DEBUG_PPI
			fprintf(pfoDebug, "PPI WR C 0x%02x\r\n", val);
		    #endif
            PPI.portC = val;
            if (!(PPI.control & 1)) { // output lower half?
               CPC.keyboard_line = val;
               if(ALESTE && alesteExtend.bit.CSAY){
               		// Access to RTC
               		if(PPI.portC & 0x02){ // AS
               			rtcAS(PPI.portA);
               		} 
               		if((PPI.portC & 0x07)==4) { // DS write
	               		rtcWrite(PPI.portA);
               		}	   
               	   
               }
            }
            if (!(PPI.control & 8)) { // output upper half?
               CPC.tape_motor = val & 0x10; // update tape motor control
               PSG.control = val; // change PSG control
               Byte psg_data = PPI.portA;
               psg_write
            }
            break;
         case 3: // modify PPI control
            if (val & 0x80) { // change PPI configuration
               PPI.control = val; // update control Byte
               PPI.portA = 0; // clear data for all ports
               PPI.portB = 0;
               PPI.portC = 0;
            } else { // bit manipulation of port C data
               if (val & 1) { // set bit?
                  Byte bit = (val >> 1) & 7; // isolate bit to set
                  PPI.portC |= bit_values[bit]; // set requested bit
                  if (!(PPI.control & 1)) { // output lower half?
                     CPC.keyboard_line = PPI.portC;
                  }
                  if (!(PPI.control & 8)) { // output upper half?
                     CPC.tape_motor = PPI.portC & 0x10;
                     PSG.control = PPI.portC; // change PSG control
                     Byte psg_data = PPI.portA;
                     psg_write
                  }
               } else {
                  Byte bit = (val >> 1) & 7; // isolate bit to reset
                  PPI.portC &= ~(bit_values[bit]); // reset requested bit
                  if (!(PPI.control & 1)) { // output lower half?
                     CPC.keyboard_line = PPI.portC;
                  }
                  if (!(PPI.control & 8)) { // output upper half?
                     CPC.tape_motor = PPI.portC & 0x10;
                     PSG.control = PPI.portC; // change PSG control
                     Byte psg_data = PPI.portA;
                     psg_write
                  }
               }
            }
            if (CPC.mf2) { // MF2 enabled?
               *(pbMF2ROM + 0x037ff) = val;
            }
            break;
      }
   }
// ----------------------------------------------------------------------------
   if ((port.b.h == 0xfa) && (!(port.b.l & 0x80))) { // floppy motor control?
      FDC.motor = val & 0x01;
      #ifdef DEBUG_FDC
      fputs(FDC.motor ? "\r\n--- motor on" : "\r\n--- motor off", pfoDebug);
      #endif
      FDC.flags |= STATUSDRVA_flag | STATUSDRVB_flag;
   }
   else if ((port.b.h == 0xfb) && (!(port.b.l & 0x80))) { // FDC data register?
      fdc_write_data(val);
   }
   else if ((CPC.mf2) && (port.b.h == 0xfe)) { // Multiface 2?
      if ((port.b.l == 0xe8) && (!(dwMF2Flags & MF2_INVISIBLE))) { // page in MF2 ROM?
         dwMF2Flags |= MF2_ACTIVE;
         ga_memory_manager();
      }
      else if (port.b.l == 0xea) { // page out MF2 ROM?
         dwMF2Flags &= ~MF2_ACTIVE;
         ga_memory_manager();
      }
   }
}



void print (uLong *pdwAddr, char *pchStr, bool bolColour)
{
   int iLen, iIdx, iRow, iCol;
   uLong dwColour;
   word wColour;
   Byte bRow, bColour;

   switch (CPC.scr_bpp)
   {
      case 32:
      { // MSC
         dwColour = bolColour ? 0x00ffffff : 0;
         iLen = strlen(pchStr); // number of characters to process
         for (int n = 0; n < iLen; n++) {
            uLong *pdwLine, *pdwPixel;
            iIdx = (int)pchStr[n]; // get the ASCII value
            if ((iIdx < FNT_MIN_CHAR) || (iIdx > FNT_MAX_CHAR)) { // limit it to the range of chars in the font
               iIdx = FNT_BAD_CHAR;
            }
            iIdx -= FNT_MIN_CHAR; // zero base the index
            pdwLine = pdwAddr; // keep a reference to the current screen position
            for (iRow = 0; iRow < FNT_CHAR_HEIGHT; iRow++) { // loop for all rows in the font character
               pdwPixel = pdwLine;
               bRow = bFont[iIdx]; // get the bitmap information for one row
               for (iCol = 0; iCol < FNT_CHAR_WIDTH; iCol++) { // loop for all columns in the font character
                  if (bRow & 0x80) { // is the bit set?
                     *(pdwPixel+1) = 0; // draw the "shadow"
                     *(pdwPixel+CPC.scr_line_offs) = 0;
                     *(pdwPixel+CPC.scr_line_offs+1) = 0;
                     *pdwPixel = dwColour; // draw the character pixel
                  }
                  pdwPixel++; // update the screen position
                  bRow <<= 1; // advance to the next bit
               }
               pdwLine += CPC.scr_line_offs; // advance to next screen line
               iIdx += FNT_CHARS; // advance to next row in font data
            }
            pdwAddr += FNT_CHAR_WIDTH; // set screen address to next character position
         }
         break;
      } // MSC

      case 24:
      { // MSC
         dwColour = bolColour ? 0x00ffffff : 0;
         iLen = strlen(pchStr); // number of characters to process
         for (int n = 0; n < iLen; n++) {
            uLong *pdwLine;
            Byte *pbPixel;
            iIdx = (int)pchStr[n]; // get the ASCII value
            if ((iIdx < FNT_MIN_CHAR) || (iIdx > FNT_MAX_CHAR)) { // limit it to the range of chars in the font
               iIdx = FNT_BAD_CHAR;
            }
            iIdx -= FNT_MIN_CHAR; // zero base the index
            pdwLine = pdwAddr; // keep a reference to the current screen position
            for (iRow = 0; iRow < FNT_CHAR_HEIGHT; iRow++) { // loop for all rows in the font character
               pbPixel = (Byte *)pdwLine;
               bRow = bFont[iIdx]; // get the bitmap information for one row
               for (iCol = 0; iCol < FNT_CHAR_WIDTH; iCol++) { // loop for all columns in the font character
                  if (bRow & 0x80) { // is the bit set?
                     *((uLong *)pbPixel+CPC.scr_line_offs) = 0; // draw the "shadow"
                     *(uLong *)pbPixel = dwColour; // draw the character pixel
                  }
                  pbPixel += 3; // update the screen position
                  bRow <<= 1; // advance to the next bit
               }
               pdwLine += CPC.scr_line_offs; // advance to next screen line
               iIdx += FNT_CHARS; // advance to next row in font data
            }
            pdwAddr += FNT_CHAR_WIDTH-2; // set screen address to next character position
         }
         break;
      } // MSC
      case 15:
      case 16:
      { // MSC
         wColour = bolColour ? 0xffff : 0;
         iLen = strlen(pchStr); // number of characters to process
         for (int n = 0; n < iLen; n++) {
            uLong *pdwLine;
            word *pwPixel;
            iIdx = (int)pchStr[n]; // get the ASCII value
            if ((iIdx < FNT_MIN_CHAR) || (iIdx > FNT_MAX_CHAR)) { // limit it to the range of chars in the font
               iIdx = FNT_BAD_CHAR;
            }
            iIdx -= FNT_MIN_CHAR; // zero base the index
            pdwLine = pdwAddr; // keep a reference to the current screen position
            for (iRow = 0; iRow < FNT_CHAR_HEIGHT; iRow++) { // loop for all rows in the font character
               pwPixel = (word *)pdwLine;
               bRow = bFont[iIdx]; // get the bitmap information for one row
               for (iCol = 0; iCol < FNT_CHAR_WIDTH; iCol++) { // loop for all columns in the font character
                  if (bRow & 0x80) { // is the bit set?
                     *(pwPixel+1) = 0; // draw the "shadow"
                     *(word *)((uLong *)pwPixel+CPC.scr_line_offs) = 0;
                     *((word *)((uLong *)pwPixel+CPC.scr_line_offs)+1) = 0;
                     *pwPixel = wColour; // draw the character pixel
                  }
                  pwPixel++; // update the screen position
                  bRow <<= 1; // advance to the next bit
               }
               pdwLine += CPC.scr_line_offs; // advance to next screen line
               iIdx += FNT_CHARS; // advance to next row in font data
            }
            pdwAddr += FNT_CHAR_WIDTH/2; // set screen address to next character position
         }
         break;
      } // MSC
      case 8:
      { // MSC
         bColour = bolColour ? 0xff : 0;
         iLen = strlen(pchStr); // number of characters to process
         for (int n = 0; n < iLen; n++) {
            uLong *pdwLine;
            Byte *pbPixel;
            iIdx = (int)pchStr[n]; // get the ASCII value
            if ((iIdx < FNT_MIN_CHAR) || (iIdx > FNT_MAX_CHAR)) { // limit it to the range of chars in the font
               iIdx = FNT_BAD_CHAR;
            }
            iIdx -= FNT_MIN_CHAR; // zero base the index
            pdwLine = pdwAddr; // keep a reference to the current screen position
            for (iRow = 0; iRow < FNT_CHAR_HEIGHT; iRow++) { // loop for all rows in the font character
               pbPixel = (Byte *)pdwLine;
               bRow = bFont[iIdx]; // get the bitmap information for one row
               for (iCol = 0; iCol < FNT_CHAR_WIDTH; iCol++) { // loop for all columns in the font character
                  if (bRow & 0x80) { // is the bit set?
                     *(pbPixel+1) = 0; // draw the "shadow"
                     *(Byte *)((uLong *)pbPixel+CPC.scr_line_offs) = 0;
                     *((Byte *)((uLong *)pbPixel+CPC.scr_line_offs)+1) = 0;
                     *pbPixel = bColour; // draw the character pixel
                  }
                  pbPixel++; // update the screen position
                  bRow <<= 1; // advance to the next bit
               }
               pdwLine += CPC.scr_line_offs; // advance to next screen line
               iIdx += FNT_CHARS; // advance to next row in font data
            }
            pdwAddr += FNT_CHAR_WIDTH/4; // set screen address to next character position
         }
         break;
      } // MSC
   }
}



int file_size (int file_num)
{
   struct stat s;

   fstat(file_num, &s);
   return s.st_size;
}



static int snapshot_load (const TCHAR *pchFileName)
{
   int n;
   uLong dwSnapSize, dwModel;
   TCHAR chPath[_MAX_PATH + 1];
   Byte val;
   reg_pair port;
   t_SNA_header sh;

   memset(&sh, 0, sizeof(sh));
   if ((pfileObject = _tfopen(pchFileName, _T("rb"))) != NULL) {
      fread(&sh, sizeof(sh), 1, pfileObject); // read snapshot header
      if (memcmp(sh.id, "MV - SNA", 8) != 0) { // valid SNApshot image?
         fclose(pfileObject);
         return ERR_SNA_INVALID;
      }
      dwSnapSize = sh.ram_size[0] + (sh.ram_size[1] * 256); // memory dump size
      dwSnapSize &= ~0x3f; // limit to multiples of 64
      if (!dwSnapSize) {
         fclose(pfileObject);
         return ERR_SNA_SIZE;
      }
      if (dwSnapSize > CPC.ram_size) { // memory dump size differs from current RAM size?
         Byte *pbTemp;

         pbTemp = new Byte [dwSnapSize*1024];
         if (pbTemp) {
            delete [] pbRAM;
            CPC.ram_size = dwSnapSize;
            pbRAM = pbTemp;
         } else {
            fclose(pfileObject);
            return ERR_OUT_OF_MEMORY;
         }
      }
      emulator_reset(false);
      n = fread(pbRAM, dwSnapSize*1024, 1, pfileObject); // read memory dump into CPC RAM
      fclose(pfileObject);
      if (!n) {
         emulator_reset(false);
         return ERR_SNA_INVALID;
      }

// Z80
      _A = sh.AF[1];
      _F = sh.AF[0];
      _B = sh.BC[1];
      _C = sh.BC[0];
      _D = sh.DE[1];
      _E = sh.DE[0];
      _H = sh.HL[1];
      _L = sh.HL[0];
      _R = sh.R & 0x7f;
      _Rb7 = sh.R & 0x80; // bit 7 of R
      _I = sh.I;
      if (sh.IFF0)
         _IFF1 = Pflag;
      if (sh.IFF1)
         _IFF2 = Pflag;
      _IXh = sh.IX[1];
      _IXl = sh.IX[0];
      _IYh = sh.IY[1];
      _IYl = sh.IY[0];
      z80.SP.b.h = sh.SP[1];
      z80.SP.b.l = sh.SP[0];
      z80.PC.b.h = sh.PC[1];
      z80.PC.b.l = sh.PC[0];
      _IM = sh.IM; // interrupt mode
      z80.AFx.b.h = sh.AFx[1];
      z80.AFx.b.l = sh.AFx[0];
      z80.BCx.b.h = sh.BCx[1];
      z80.BCx.b.l = sh.BCx[0];
      z80.DEx.b.h = sh.DEx[1];
      z80.DEx.b.l = sh.DEx[0];
      z80.HLx.b.h = sh.HLx[1];
      z80.HLx.b.l = sh.HLx[0];
// Gate Array
      port.b.h = 0x7f;
      for (n = 0; n < 17; n++) { // loop for all colours + border
         GateArray.pen = n;
         val = sh.ga_ink_values[n]; // GA palette entry
         z80_OUT_handler(port, val | (1<<6));
      }
      val = sh.ga_pen; // GA pen
      z80_OUT_handler(port, (val & 0x3f));
      val = sh.ga_ROM_config; // GA ROM configuration
      z80_OUT_handler(port, (val & 0x3f) | (2<<6));
      val = sh.ga_RAM_config; // GA RAM configuration
      z80_OUT_handler(port, (val & 0x3f) | (3<<6));
// CRTC
      port.b.h = 0xbd;
      for (n = 0; n < 18; n++) { // loop for all CRTC registers
         val = sh.crtc_registers[n];
         CRTC.reg_select = n;
         z80_OUT_handler(port, val);
      }
      port.b.h = 0xbc;
      val = sh.crtc_reg_select; // CRTC register select
      z80_OUT_handler(port, val);
// ROM select
      port.b.h = 0xdf;
      val = sh.upper_ROM; // upper ROM number
      z80_OUT_handler(port, val);
// PPI
      port.b.h = 0xf4; // port A
      z80_OUT_handler(port, sh.ppi_A);
      port.b.h = 0xf5; // port B
      z80_OUT_handler(port, sh.ppi_B);
      port.b.h = 0xf6; // port C
      z80_OUT_handler(port, sh.ppi_C);
      port.b.h = 0xf7; // control
      z80_OUT_handler(port, sh.ppi_control);
// PSG
      PSG.control = PPI.portC;
      PSG.reg_select = sh.psg_reg_select;
      for (n = 0; n < 16; n++) { // loop for all PSG registers
         SetAYRegister(n, sh.psg_registers[n]);
      }

      if (sh.version > 1) { // does the snapshot have version 2 data?
         dwModel = sh.cpc_model; // determine the model it was saved for
         if (dwModel != CPC.model) { // different from what we're currently running?
            if (dwModel > 2) { // not one of the known models?
               emulator_reset(false);
               return ERR_SNA_CPC_TYPE;
            }
            _tcsncpy(chPath, CPC.rom_path, sizeof(chPath)-2);
            _tcscat(chPath, _T("/"));
            _tcsncat(chPath, chROMFile[dwModel], _countof(chPath)-1 - _tcslen(chPath)); // path to the required ROM image
            
            if ((pfileObject = _tfopen(chPath, _T("rb"))) != NULL) 
            {
               n = fread(pbROMlo, 2*16384, 1, pfileObject);
               fclose(pfileObject);
               if (!n) 
               {
                  emulator_reset(false);
                  return ERR_CPC_ROM_MISSING;
               }
               CPC.model = dwModel;
            } 
            else 
            { // ROM image load failed
               emulator_reset(false);
               return ERR_CPC_ROM_MISSING;
            }
         }
      }
      if (sh.version > 2) { // does the snapshot have version 3 data?
         FDC.motor = sh.fdc_motor;
         driveA.current_track = sh.drvA_current_track;
         driveB.current_track = sh.drvB_current_track;
         CPC.printer_port = sh.printer_data ^ 0x80; // invert bit 7 again
         PSG.AmplitudeEnv = sh.psg_env_step << 1; // multiply by 2 to bring it into the 0 - 30 range
         PSG.FirstPeriod = false;
         if (sh.psg_env_direction == 0x01) { // up
            switch (PSG.RegisterAY.EnvType)
            {
               case 4:
               case 5:
               case 6:
               case 7:
               case 13:
               case 14:
               case 15:
                  PSG.FirstPeriod = true;
                  break;
            }
         } else if (sh.psg_env_direction == 0xff) { // down
            switch (PSG.RegisterAY.EnvType)
            {
               case 0:
               case 1:
               case 2:
               case 3:
               case 9:
               case 10:
               case 11:
                  PSG.FirstPeriod = true;
                  break;
            }
         }
         CRTC.addr = sh.crtc_addr[0] + (sh.crtc_addr[1] * 256);
         VDU.scanline = sh.crtc_scanline[0] + (sh.crtc_scanline[1] * 256);
         CRTC.char_count = sh.crtc_char_count[0];
         CRTC.line_count = sh.crtc_line_count;
         CRTC.raster_count = sh.crtc_raster_count;
         CRTC.vt_adjust_count = sh.crtc_vt_adjust_count;
         CRTC.hsw_count = sh.crtc_hsw_count;
         CRTC.vsw_count = sh.crtc_vsw_count;
         CRTC.flags = sh.crtc_flags[0] + (sh.crtc_flags[1] * 256);
         GateArray.int_delay = sh.ga_int_delay;
         GateArray.sl_count = sh.ga_sl_count;
         z80.int_pending = sh.z80_int_pending;
      }
   } else {
      return ERR_FILE_NOT_FOUND;
   }

/* char *pchTmpBuffer = new char[MAX_LINE_LEN];
   LoadString(hAppInstance, MSG_SNA_LOAD, chMsgBuffer, sizeof(chMsgBuffer));
   snprintf(pchTmpBuffer, _MAX_PATH-1, chMsgBuffer, CPC.snap_file);
   add_message(pchTmpBuffer);
   delete [] pchTmpBuffer; */
   return 0;
}



static int snapshot_save (const TCHAR *pchFileName, int ram_size)
{
   t_SNA_header sh;
   int n;
   
   //ram_size = CPC.ram_size;

   memset(&sh, 0, sizeof(sh));
   strcpy(sh.id, "MV - SNA");
   sh.version = 3;
// Z80
   sh.AF[1] = _A;
   sh.AF[0] = _F;
   sh.BC[1] = _B;
   sh.BC[0] = _C;
   sh.DE[1] = _D;
   sh.DE[0] = _E;
   sh.HL[1] = _H;
   sh.HL[0] = _L;
   sh.R = (_R & 0x7f) | (_Rb7 & 0x80);
   sh.I = _I;
   if (_IFF1)
      sh.IFF0 = 1;
   if (_IFF2)
      sh.IFF1 = 1;
   sh.IX[1] = _IXh;
   sh.IX[0] = _IXl;
   sh.IY[1] = _IYh;
   sh.IY[0] = _IYl;
   sh.SP[1] = z80.SP.b.h;
   sh.SP[0] = z80.SP.b.l;
   sh.PC[1] = z80.PC.b.h;
   sh.PC[0] = z80.PC.b.l;
   sh.IM = _IM;
   sh.AFx[1] = z80.AFx.b.h;
   sh.AFx[0] = z80.AFx.b.l;
   sh.BCx[1] = z80.BCx.b.h;
   sh.BCx[0] = z80.BCx.b.l;
   sh.DEx[1] = z80.DEx.b.h;
   sh.DEx[0] = z80.DEx.b.l;
   sh.HLx[1] = z80.HLx.b.h;
   sh.HLx[0] = z80.HLx.b.l;
// Gate Array
   sh.ga_pen = GateArray.pen;
   for (n = 0; n < 17; n++) { // loop for all colours + border
      sh.ga_ink_values[n] = GateArray.ink_values[n];
   }
   sh.ga_ROM_config = GateArray.ROM_config;
   sh.ga_RAM_config = GateArray.RAM_config;
// CRTC
   sh.crtc_reg_select = CRTC.reg_select;
   for (n = 0; n < 18; n++) { // loop for all CRTC registers
      sh.crtc_registers[n] = CRTC.registers[n];
   }
// ROM select
   sh.upper_ROM = GateArray.upper_ROM;
// PPI
   sh.ppi_A = PPI.portA;
   sh.ppi_B = PPI.portB;
   sh.ppi_C = PPI.portC;
   sh.ppi_control = PPI.control;
// PSG
   sh.psg_reg_select = PSG.reg_select;
   for (n = 0; n < 16; n++) { // loop for all PSG registers
      sh.psg_registers[n] = PSG.RegisterAY.Index[n];
   }

   sh.ram_size[0] = ram_size & 0xff;
   sh.ram_size[1] = (ram_size >> 8) & 0xff;
// version 2 info
   sh.cpc_model = CPC.model;
// version 3 info
   sh.fdc_motor = FDC.motor;
   sh.drvA_current_track = driveA.current_track;
   sh.drvB_current_track = driveB.current_track;
   sh.printer_data = CPC.printer_port ^ 0x80; // invert bit 7 again
   sh.psg_env_step = PSG.AmplitudeEnv >> 1; // divide by 2 to bring it into the 0 - 15 range
   if (PSG.FirstPeriod) {
      switch (PSG.RegisterAY.EnvType)
      {
         case 0:
         case 1:
         case 2:
         case 3:
         case 8:
         case 9:
         case 10:
         case 11:
            sh.psg_env_direction = 0xff; // down
            break;
         case 4:
         case 5:
         case 6:
         case 7:
         case 12:
         case 13:
         case 14:
         case 15:
            sh.psg_env_direction = 0x01; // up
            break;
      }
   } else {
      switch (PSG.RegisterAY.EnvType)
      {
         case 0:
         case 1:
         case 2:
         case 3:
         case 4:
         case 5:
         case 6:
         case 7:
         case 9:
         case 11:
         case 13:
         case 15:
            sh.psg_env_direction = 0x00; // hold
            break;
         case 8:
         case 14:
            sh.psg_env_direction = 0xff; // down
            break;
         case 10:
         case 12:
            sh.psg_env_direction = 0x01; // up
            break;
      }
   }
   sh.crtc_addr[0] = CRTC.addr & 0xff;
   sh.crtc_addr[1] = (CRTC.addr >> 8) & 0xff;
   sh.crtc_scanline[0] = VDU.scanline & 0xff;
   sh.crtc_scanline[1] = (VDU.scanline >> 8) & 0xff;
   sh.crtc_char_count[0] = CRTC.char_count;
   sh.crtc_line_count = CRTC.line_count;
   sh.crtc_raster_count = CRTC.raster_count;
   sh.crtc_vt_adjust_count = CRTC.vt_adjust_count;
   sh.crtc_hsw_count = CRTC.hsw_count;
   sh.crtc_vsw_count = CRTC.vsw_count;
   sh.crtc_flags[0] = CRTC.flags & 0xff;
   sh.crtc_flags[1] = (CRTC.flags >> 8) & 0xff;
   sh.ga_int_delay = GateArray.int_delay;
   sh.ga_sl_count = GateArray.sl_count;
   sh.z80_int_pending = z80.int_pending;

   if ((pfileObject = _tfopen(pchFileName, _T("wb"))) != NULL) {
	   if (fwrite(&sh, sizeof(sh), 1, pfileObject) != 1) { // write snapshot header
         fclose(pfileObject);
         return ERR_SNA_WRITE;
      }  
      if (fwrite(pbRAM, ram_size*1024, 1, pfileObject) != 1) { // write memory contents to snapshot file
         fclose(pfileObject);
         return ERR_SNA_WRITE;
      }
	  fclose(pfileObject);
   } else {
      return ERR_SNA_WRITE;
   }
   if ((pfileObject = _tfopen("./memdump.bin", _T("wb"))) != NULL) {
      if (fwrite(pbRAM, ram_size*1024, 1, pfileObject) != 1) { // write memory contents to snapshot file
         fclose(pfileObject);
         return ERR_SNA_WRITE;
      }
	  fclose(pfileObject);
   } else {
      return ERR_SNA_WRITE;
   }

/* char *pchTmpBuffer = new char[MAX_LINE_LEN];
   LoadString(hAppInstance, MSG_SNA_SAVE, chMsgBuffer, sizeof(chMsgBuffer));
   snprintf(pchTmpBuffer, _MAX_PATH-1, chMsgBuffer, CPC.snap_file);
   add_message(pchTmpBuffer);
   delete [] pchTmpBuffer; */
   return 0;
}



static void dsk_eject (t_drive *drive)
{
   uLong track, side;

   for (track = 0; track < DSK_TRACKMAX; track++) { // loop for all tracks
      for (side = 0; side < DSK_SIDEMAX; side++) { // loop for all sides
         if (drive->track[track][side].data) { // track is formatted?
            free(drive->track[track][side].data); // release memory allocated for this track
         }
      }
   }
   uLong dwTemp = drive->current_track; // save the drive head position
   memset(drive, 0, sizeof(t_drive)); // clear drive info structure
   drive->current_track = dwTemp;
}

static int dsk_load (const TCHAR *pchFileName, t_drive *drive, char chID)
{
	int iRetCode;
	uLong dwTrackSize, track, side, sector, dwSectorSize, dwSectors;
	Byte *pbPtr, *pbDataPtr, *pbTempPtr, *pbTrackSizeTable;

	iRetCode = 0;
	dsk_eject(drive);
	if ((pfileObject = _tfopen(pchFileName, _T("rb"))) != NULL) {
		fread(pbGPBuffer, 0x100, 1, pfileObject); // read DSK header
		pbPtr = pbGPBuffer;

		if (memcmp(pbPtr, "MV - CPC", 8) == 0) { // normal DSK image?
			drive->tracks = *(pbPtr + 0x30); // grab number of tracks
			if (drive->tracks > DSK_TRACKMAX) { // compare against upper limit
				drive->tracks = DSK_TRACKMAX; // limit to maximum
			}
			drive->sides = *(pbPtr + 0x31); // grab number of sides
			if (drive->sides > DSK_SIDEMAX) { // abort if more than maximum
				iRetCode = ERR_DSK_SIDES;
				goto exit;
			}
			dwTrackSize = (*(pbPtr + 0x32) + (*(pbPtr + 0x33) << 8)) - 0x100; // determine track size in bytes, minus track header
			drive->sides--; // zero base number of sides
			for (track = 0; track < drive->tracks; track++) { // loop for all tracks
				for (side = 0; side <= drive->sides; side++) { // loop for all sides
					fread(pbGPBuffer+0x100, 0x100, 1, pfileObject); // read track header
					pbPtr = pbGPBuffer + 0x100;
					if (memcmp(pbPtr, "Track-Info", 10) != 0) { // abort if ID does not match
						iRetCode = ERR_DSK_INVALID;
						goto exit;
					}
					dwSectorSize = 0x80 << *(pbPtr + 0x14); // determine sector size in bytes
					dwSectors = *(pbPtr + 0x15); // grab number of sectors
					if (dwSectors > DSK_SECTORMAX) { // abort if sector count greater than maximum
						iRetCode = ERR_DSK_SECTORS;
						goto exit;
					}
					drive->track[track][side].sectors = dwSectors; // store sector count
					drive->track[track][side].size = dwTrackSize; // store track size
					drive->track[track][side].data = (Byte *)malloc(dwTrackSize); // attempt to allocate the required memory
					if (drive->track[track][side].data == NULL) { // abort if not enough
						iRetCode = ERR_OUT_OF_MEMORY;
						goto exit;
					}
					pbDataPtr = drive->track[track][side].data; // pointer to start of memory buffer
					pbTempPtr = pbDataPtr; // keep a pointer to the beginning of the buffer for the current track
					for (sector = 0; sector < dwSectors; sector++) { // loop for all sectors
						memcpy(drive->track[track][side].sector[sector].CHRN, (pbPtr + 0x18), 4); // copy CHRN
						memcpy(drive->track[track][side].sector[sector].flags, (pbPtr + 0x1c), 2); // copy ST1 & ST2
						drive->track[track][side].sector[sector].size = dwSectorSize;
						drive->track[track][side].sector[sector].data = pbDataPtr; // store pointer to sector data
						pbDataPtr += dwSectorSize;
						pbPtr += 8;
					}
					if (!fread(pbTempPtr, dwTrackSize, 1, pfileObject)) { // read entire track data in one go
						iRetCode = ERR_DSK_INVALID;
						goto exit;
					}
				}
			}
			drive->altered = 0; // disk is as yet unmodified
		} else {
			if (memcmp(pbPtr, "EXTENDED", 8) == 0) { // extended DSK image?
				drive->tracks = *(pbPtr + 0x30); // number of tracks
				if (drive->tracks > DSK_TRACKMAX) {  // limit to maximum possible
					drive->tracks = DSK_TRACKMAX;
				}
				drive->random_DEs = *(pbPtr + 0x31) & 0x80; // simulate random Data Errors?
				drive->sides = *(pbPtr + 0x31) & 3; // number of sides
				if (drive->sides > DSK_SIDEMAX) { // abort if more than maximum
					iRetCode = ERR_DSK_SIDES;
					goto exit;
				}
				pbTrackSizeTable = pbPtr + 0x34; // pointer to track size table in DSK header
				drive->sides--; // zero base number of sides
				for (track = 0; track < drive->tracks; track++) { // loop for all tracks
					for (side = 0; side <= drive->sides; side++) { // loop for all sides
						dwTrackSize = (*pbTrackSizeTable++ << 8); // track size in bytes
						if (dwTrackSize != 0) { // only process if track contains data
							dwTrackSize -= 0x100; // compensate for track header
							fread(pbGPBuffer+0x100, 0x100, 1, pfileObject); // read track header
							pbPtr = pbGPBuffer + 0x100;
							if (memcmp(pbPtr, "Track-Info", 10) != 0) { // valid track header?
								iRetCode = ERR_DSK_INVALID;
								goto exit;
							}
							dwSectors = *(pbPtr + 0x15); // number of sectors for this track
							if (dwSectors > DSK_SECTORMAX) { // abort if sector count greater than maximum
								iRetCode = ERR_DSK_SECTORS;
								goto exit;
							}
							drive->track[track][side].sectors = dwSectors; // store sector count
							drive->track[track][side].size = dwTrackSize; // store track size
							drive->track[track][side].data = (Byte *)malloc(dwTrackSize); // attempt to allocate the required memory
							if (drive->track[track][side].data == NULL) { // abort if not enough
								iRetCode = ERR_OUT_OF_MEMORY;
								goto exit;
							}
							pbDataPtr = drive->track[track][side].data; // pointer to start of memory buffer
							pbTempPtr = pbDataPtr; // keep a pointer to the beginning of the buffer for the current track
							for (sector = 0; sector < dwSectors; sector++) { // loop for all sectors
								memcpy(drive->track[track][side].sector[sector].CHRN, (pbPtr + 0x18), 4); // copy CHRN
								memcpy(drive->track[track][side].sector[sector].flags, (pbPtr + 0x1c), 2); // copy ST1 & ST2
								dwSectorSize = *(pbPtr + 0x1e) + (*(pbPtr + 0x1f) << 8); // sector size in bytes
								drive->track[track][side].sector[sector].size = dwSectorSize;
								drive->track[track][side].sector[sector].data = pbDataPtr; // store pointer to sector data
								pbDataPtr += dwSectorSize;
								pbPtr += 8;
							}
							if (!fread(pbTempPtr, dwTrackSize, 1, pfileObject)) { // read entire track data in one go
								iRetCode = ERR_DSK_INVALID;
								goto exit;
							}
						} else {
							memset(&drive->track[track][side], 0, sizeof(t_track)); // track not formatted
						}
					}
				}
				drive->altered = 0; // disk is as yet unmodified
			} else {
				if (ALESTE){
					fclose(pfileObject);
					if ((pfileObject = _tfopen(pchFileName, _T("rb"))) != NULL) {

						// 3.5" Double sided, 80 tracks per side, 9 sectors per track (720K).
						drive->tracks = 80;
						drive->sides = 2;
						drive->sides--; // zero base number of sides
						dwSectorSize = 0x200;
						dwSectors = 9; // grab number of sectors
						dwTrackSize = dwSectorSize * dwSectors;

						for (track = 0; track < drive->tracks; track++) { // loop for all tracks
							for (side = 0; side <= drive->sides; side++) { // loop for all sides
								drive->track[track][side].sectors = dwSectors; // store sector count
								drive->track[track][side].size = dwTrackSize; // store track size
								drive->track[track][side].data = (Byte *)malloc(dwTrackSize); // attempt to allocate the required memory
								if (drive->track[track][side].data == NULL) { // abort if not enough
									iRetCode = ERR_OUT_OF_MEMORY;
									goto exit;
								}
								pbDataPtr = drive->track[track][side].data; // pointer to start of memory buffer
								pbTempPtr = pbDataPtr; // keep a pointer to the beginning of the buffer for the current track
								for (sector = 0; sector < dwSectors; sector++) { // loop for all sectors
									Byte CHRN[4];
									CHRN[0] = (Byte)track;
									CHRN[1] = (Byte)side;
									CHRN[2] = (Byte)(sector+1);
									CHRN[3] = (Byte)(dwSectorSize>>8);

									memcpy(drive->track[track][side].sector[sector].CHRN, CHRN, 4); // copy CHRN
									drive->track[track][side].sector[sector].size = dwSectorSize;
									drive->track[track][side].sector[sector].data = pbDataPtr; // store pointer to sector data
									pbDataPtr += dwSectorSize;
									pbPtr += 8;
								}
								if (!fread(pbTempPtr, dwTrackSize, 1, pfileObject)) { // read entire track data in one go
									iRetCode = ERR_DSK_INVALID;
									goto exit;
								}
							}
						}
						drive->altered = 0; // disk is as yet unmodified
					}
				} else {
					iRetCode = ERR_DSK_INVALID; // file could not be identified as a valid DSK
				}
			}
		}
		/*    {
		char *pchTmpBuffer = new char[MAX_LINE_LEN];
		LoadString(hAppInstance, MSG_DSK_LOAD, chMsgBuffer, sizeof(chMsgBuffer));
		snprintf(pchTmpBuffer, _MAX_PATH-1, chMsgBuffer, chID, chID == 'A' ? CPC.drvA_file : CPC.drvB_file);
		add_message(pchTmpBuffer);
		delete [] pchTmpBuffer;
		} */
exit:
		fclose(pfileObject);
	} else {
		iRetCode = ERR_FILE_NOT_FOUND;
	}

	if (iRetCode != 0) { // on error, 'eject' disk from drive
		dsk_eject(drive);
	}
	return iRetCode;
}



static int dsk_save (const TCHAR* pchFileName, t_drive *drive, char chID)
{
   t_DSK_header dh;
   t_track_header th;
   uLong track, side, pos, sector;

   if(ALESTE && alesteExtend.bit.MAPMOD){
	if ((pfileObject = _tfopen(pchFileName, _T("wb"))) != NULL) {
		for (track = 0; track < drive->tracks; track++) { // loop for all tracks
			for (side = 0; side <= drive->sides; side++) { // loop for all sides
				if (!fwrite(drive->track[track][side].data, drive->track[track][side].size, 1, pfileObject)) { // write track data
					fclose(pfileObject);
					return ERR_DSK_WRITE;
				}
			}
		}
		fclose(pfileObject);
	} else {
		return ERR_DSK_WRITE; // write attempt failed
	}
   } else {
	if ((pfileObject = _tfopen(pchFileName, _T("wb"))) != NULL) {
		memset(&dh, 0, sizeof(dh));
		strcpy(dh.id, "EXTENDED CPC DSK File\r\nDisk-Info\r\n");
		strcpy(dh.unused1, "Caprice32\r\n");
		dh.tracks = drive->tracks;
		dh.sides = (drive->sides+1) | (drive->random_DEs); // correct side count and indicate random DEs, if necessary
		pos = 0;
		for (track = 0; track < drive->tracks; track++) { // loop for all tracks
			for (side = 0; side <= drive->sides; side++) { // loop for all sides
				if (drive->track[track][side].size) { // track is formatted?
				dh.track_size[pos] = (drive->track[track][side].size + 0x100) >> 8; // track size + header in bytes
				}
				pos++;
			}
		}
		if (!fwrite(&dh, sizeof(dh), 1, pfileObject)) { // write header to file
			fclose(pfileObject);
			return ERR_DSK_WRITE;
		}

		memset(&th, 0, sizeof(th));
		strcpy(th.id, "Track-Info\r\n");
		for (track = 0; track < drive->tracks; track++) { // loop for all tracks
			for (side = 0; side <= drive->sides; side++) { // loop for all sides
				if (drive->track[track][side].size) { // track is formatted?
				th.track = track;
				th.side = side;
				th.bps = 2;
				th.sectors = drive->track[track][side].sectors;
				th.gap3 = 0x4e;
				th.filler = 0xe5;
				for (sector = 0; sector < th.sectors; sector++) {
					memcpy(&th.sector[sector][0], drive->track[track][side].sector[sector].CHRN, 4); // copy CHRN
					memcpy(&th.sector[sector][4], drive->track[track][side].sector[sector].flags, 2); // copy ST1 & ST2
					th.sector[sector][6] = drive->track[track][side].sector[sector].size & 0xff;
					th.sector[sector][7] = (drive->track[track][side].sector[sector].size >> 8) & 0xff; // sector size in bytes
				}
				if (!fwrite(&th, sizeof(th), 1, pfileObject)) { // write track header
					fclose(pfileObject);
					return ERR_DSK_WRITE;
				}
				if (!fwrite(drive->track[track][side].data, drive->track[track][side].size, 1, pfileObject)) { // write track data
					fclose(pfileObject);
					return ERR_DSK_WRITE;
				}
				}
			}
		}
		fclose(pfileObject);
	} else {
		return ERR_DSK_WRITE; // write attempt failed
	}
  }

/* char *pchTmpBuffer = new char[MAX_LINE_LEN];
   LoadString(hAppInstance, MSG_DSK_SAVE, chMsgBuffer, sizeof(chMsgBuffer));
   snprintf(pchTmpBuffer, _MAX_PATH-1, chMsgBuffer, chID, chID == 'A' ? CPC.drvA_file : CPC.drvB_file);
   add_message(pchTmpBuffer);
   delete [] pchTmpBuffer; */
   return 0;
}



int dsk_format (t_drive *drive, int iFormat)
{
   int iRetCode = 0;
   uLong track;
   drive->tracks = disk_format[iFormat].tracks;
   if (drive->tracks > DSK_TRACKMAX) { // compare against upper limit
      drive->tracks = DSK_TRACKMAX; // limit to maximum
   }
   drive->sides = disk_format[iFormat].sides;
   if (drive->sides > DSK_SIDEMAX) { // abort if more than maximum
      iRetCode = ERR_DSK_SIDES;
      goto exit;
   }
   drive->sides--; // zero base number of sides
   for (track = 0; track < drive->tracks; track++) { // loop for all tracks
      for (uLong side = 0; side <= drive->sides; side++) { // loop for all sides
         uLong dwSectorSize = 0x80 << disk_format[iFormat].sector_size; // determine sector size in bytes
         uLong dwSectors = disk_format[iFormat].sectors;
         if (dwSectors > DSK_SECTORMAX) { // abort if sector count greater than maximum
            iRetCode = ERR_DSK_SECTORS;
            goto exit;
         }
         uLong dwTrackSize = dwSectorSize * dwSectors; // determine track size in bytes, minus track header
         drive->track[track][side].sectors = dwSectors; // store sector count
         drive->track[track][side].size = dwTrackSize; // store track size
         drive->track[track][side].data = (Byte *)malloc(dwTrackSize); // attempt to allocate the required memory
         if (drive->track[track][side].data == NULL) { // abort if not enough
            iRetCode = ERR_OUT_OF_MEMORY;
            goto exit;
         }
         Byte *pbDataPtr = drive->track[track][side].data; // pointer to start of memory buffer
         Byte *pbTempPtr = pbDataPtr; // keep a pointer to the beginning of the buffer for the current track
         Byte CHRN[4];
         CHRN[0] = (Byte)track;
         CHRN[1] = (Byte)side;
         CHRN[3] = (Byte)disk_format[iFormat].sector_size;
         for (uLong sector = 0; sector < dwSectors; sector++) { // loop for all sectors
            CHRN[2] = disk_format[iFormat].sector_ids[side][sector];
            memcpy(drive->track[track][side].sector[sector].CHRN, CHRN, 4); // copy CHRN
            drive->track[track][side].sector[sector].size = dwSectorSize;
            drive->track[track][side].sector[sector].data = pbDataPtr; // store pointer to sector data
            pbDataPtr += dwSectorSize;
         }
         memset(pbTempPtr, disk_format[iFormat].filler_byte, dwTrackSize);
      }
   }
   drive->altered = 1; // flag disk as having been modified

exit:
   if (iRetCode != 0) { // on error, 'eject' disk from drive
      dsk_eject(drive);
   }
   return iRetCode;
}



static void tape_eject (void)
{
   free(pbTapeImage);
   pbTapeImage = NULL;
}



static int tape_insert (const TCHAR *pchFileName)
{
   long lFileSize;
   int iBlockLength;
   Byte bID;
   Byte *pbPtr, *pbBlock;

   tape_eject();
   if ((pfileObject = _tfopen(pchFileName, _T("rb"))) == NULL) {
      return ERR_FILE_NOT_FOUND;
   }
   fread(pbGPBuffer, 10, 1, pfileObject); // read CDT header
   pbPtr = pbGPBuffer;
   if (memcmp(pbPtr, "ZXTape!\032", 8) != 0) { // valid CDT file?
      fclose(pfileObject);
      return ERR_TAP_INVALID;
   }
   if (*(pbPtr + 0x08) != 1) { // major version must be 1
      fclose(pfileObject);
      return ERR_TAP_INVALID;
   }
   lFileSize = file_size(fileno(pfileObject)) - 0x0a;
   if (lFileSize <= 0) { // the tape image should have at least one block...
      fclose(pfileObject);
      return ERR_TAP_INVALID;
   }
   pbTapeImage = (Byte *)malloc(lFileSize+6);
   *pbTapeImage = 0x20; // start off with a pause block
   *(word *)(pbTapeImage+1) = 2000; // set the length to 2 seconds
   fread(pbTapeImage+3, lFileSize, 1, pfileObject); // append the entire CDT file
   fclose(pfileObject);
   *(pbTapeImage+lFileSize+3) = 0x20; // end with a pause block
   *(word *)(pbTapeImage+lFileSize+3+1) = 2000; // set the length to 2 seconds

   #ifdef DEBUG_TAPE
   fputs("--- New Tape\r\n", pfoDebug);
   #endif
   pbTapeImageEnd = pbTapeImage + lFileSize+6;
   pbBlock = pbTapeImage;
   bool bolGotDataBlock = false;
   while (pbBlock < pbTapeImageEnd) {
      bID = *pbBlock++;
      switch(bID) {
         case 0x10: // standard speed data block
            iBlockLength = *(word *)(pbBlock+2) + 4;
            bolGotDataBlock = true;
            break;
         case 0x11: // turbo loading data block
            iBlockLength = (*(uLong *)(pbBlock+0x0f) & 0x00ffffff) + 0x12;
            bolGotDataBlock = true;
            break;
         case 0x12: // pure tone
            iBlockLength = 4;
            bolGotDataBlock = true;
            break;
         case 0x13: // sequence of pulses of different length
            iBlockLength = *pbBlock * 2 + 1;
            bolGotDataBlock = true;
            break;
         case 0x14: // pure data block
            iBlockLength = (*(uLong *)(pbBlock+0x07) & 0x00ffffff) + 0x0a;
            bolGotDataBlock = true;
            break;
         case 0x15: // direct recording
            iBlockLength = (*(uLong *)(pbBlock+0x05) & 0x00ffffff) + 0x08;
            bolGotDataBlock = true;
            break;
         case 0x20: // pause
            if ((!bolGotDataBlock) && (pbBlock != pbTapeImage+1)) {
               *(word *)pbBlock = 0; // remove any pauses (execept ours) before the data starts
            }
            iBlockLength = 2;
            break;
         case 0x21: // group start
            iBlockLength = *pbBlock + 1;
            break;
         case 0x22: // group end
            iBlockLength = 0;
            break;
         case 0x23: // jump to block
   return ERR_TAP_UNSUPPORTED;
            iBlockLength = 2;
            break;
         case 0x24: // loop start
   return ERR_TAP_UNSUPPORTED;
            iBlockLength = 2;
            break;
         case 0x25: // loop end
   return ERR_TAP_UNSUPPORTED;
            iBlockLength = 0;
            break;
         case 0x26: // call sequence
   return ERR_TAP_UNSUPPORTED;
            iBlockLength = (*(word *)pbBlock * 2) + 2;
            break;
         case 0x27: // return from sequence
   return ERR_TAP_UNSUPPORTED;
            iBlockLength = 0;
            break;
         case 0x28: // select block
   return ERR_TAP_UNSUPPORTED;
            iBlockLength = *(word *)pbBlock + 2;
            break;
         case 0x30: // text description
            iBlockLength = *pbBlock + 1;
            break;
         case 0x31: // message block
            iBlockLength = *(pbBlock+1) + 2;
            break;
         case 0x32: // archive info
            iBlockLength = *(word *)pbBlock + 2;
            break;
         case 0x33: // hardware type
            iBlockLength = (*pbBlock * 3) + 1;
            break;
         case 0x34: // emulation info
            iBlockLength = 8;
            break;
         case 0x35: // custom info block
            iBlockLength = *(uLong *)(pbBlock+0x10) + 0x14;
            break;
         case 0x40: // snapshot block
            iBlockLength = (*(uLong *)(pbBlock+0x01) & 0x00ffffff) + 0x04;
            break;
         case 0x5A: // another tzx/cdt file
            iBlockLength = 9;
            break;

         default: // "extension rule"
            iBlockLength = *(uLong *)pbBlock + 4;
      }

      #ifdef DEBUG_TAPE
      fprintf(pfoDebug, "%02x %d\r\n", bID, iBlockLength);
      #endif

      pbBlock += iBlockLength;
   }
   if (pbBlock != pbTapeImageEnd) {
      tape_eject();
      return ERR_TAP_INVALID;
   }

   Tape_Rewind();

/* char *pchTmpBuffer = new char[MAX_LINE_LEN];
   LoadString(hAppInstance, MSG_TAP_INSERT, chMsgBuffer, sizeof(chMsgBuffer));
   snprintf(pchTmpBuffer, _MAX_PATH-1, chMsgBuffer, CPC.tape_file);
   add_message(pchTmpBuffer);
   delete [] pchTmpBuffer; */
   return 0;
}

static int tape_insert_voc (const TCHAR *pchFileName)
{
   long lFileSize, lOffset, lInitialOffset, lSampleLength;
   int iBlockLength;
   Byte *pbPtr, *pbTapeImagePtr, *pbVocDataBlock, *pbVocDataBlockPtr;
   bool bolDone;

   tape_eject();
   if ((pfileObject = _tfopen(pchFileName, _T("rb"))) == NULL) {
      return ERR_FILE_NOT_FOUND;
   }
   fread(pbGPBuffer, 26, 1, pfileObject); // read VOC header
   pbPtr = pbGPBuffer;
   if (memcmp(pbPtr, "Creative Voice File\032", 20) != 0) { // valid VOC file?
      fclose(pfileObject);
      return ERR_TAP_BAD_VOC;
   }
   lOffset =
   lInitialOffset = *(word *)(pbPtr + 0x14);
   lFileSize = file_size(fileno(pfileObject));
   if ((lFileSize-26) <= 0) { // should have at least one block...
      fclose(pfileObject);
      return ERR_TAP_BAD_VOC;
   }

   #ifdef DEBUG_TAPE
   fputs("--- New Tape\r\n", pfoDebug);
   #endif
   iBlockLength = 0;
   lSampleLength = 0;
   Byte bSampleRate = 0;
   bolDone = false;
   while ((!bolDone) && (lOffset < lFileSize)) {
      fseek(pfileObject, lOffset, SEEK_SET);
      fread(pbPtr, 16, 1, pfileObject); // read block ID + size
      #ifdef DEBUG_TAPE
      fprintf(pfoDebug, "%02x %d\r\n", *pbPtr, *(uLong *)(pbPtr+0x01) & 0x00ffffff);
      #endif
      switch(*pbPtr) {
         case 0x0: // terminator
            bolDone = true;
            break;
         case 0x1: // sound data
            iBlockLength = (*(uLong *)(pbPtr+0x01) & 0x00ffffff) + 4;
            lSampleLength += iBlockLength - 6;
            if ((bSampleRate) && (bSampleRate != *(pbPtr+0x04))) { // no change in sample rate allowed
               fclose(pfileObject);
               return ERR_TAP_BAD_VOC;
            }
            bSampleRate = *(pbPtr+0x04);
            if (*(pbPtr+0x05) != 0) { // must be 8 bits wide
               fclose(pfileObject);
               return ERR_TAP_BAD_VOC;
            }
            break;
         case 0x2: // sound continue
            iBlockLength = (*(uLong *)(pbPtr+0x01) & 0x00ffffff) + 4;
            lSampleLength += iBlockLength - 4;
            break;
         case 0x3: // silence
            iBlockLength = 4;
            lSampleLength += *(word *)(pbPtr+0x01) + 1;
            if ((bSampleRate) && (bSampleRate != *(pbPtr+0x03))) { // no change in sample rate allowed
               fclose(pfileObject);
               return ERR_TAP_BAD_VOC;
            }
            bSampleRate = *(pbPtr+0x03);
            break;
         case 0x4: // marker
            iBlockLength = 3;
            break;
         case 0x5: // ascii
            iBlockLength = (*(uLong *)(pbPtr+0x01) & 0x00ffffff) + 4;
            break;
         default:
            fclose(pfileObject);
            return ERR_TAP_BAD_VOC;
      }
      lOffset += iBlockLength;
   }
   #ifdef DEBUG_TAPE
   fprintf(pfoDebug, "--- %ld bytes\r\n", lSampleLength);
   #endif

   uLong dwTapePulseCycles = 3500000L / (1000000L / (256 - bSampleRate)); // length of one pulse in ZX Spectrum T states
   uLong dwCompressedSize = lSampleLength >> 3; // 8x data reduction
   if (dwCompressedSize > 0x00ffffff) { // we only support one direct recording block right now
      fclose(pfileObject);
      return ERR_TAP_BAD_VOC;
   }
   pbTapeImage = (Byte *)malloc(dwCompressedSize+1+8+6);
   if (pbTapeImage == NULL) { // check if the memory allocation has failed
      fclose(pfileObject);
      return ERR_OUT_OF_MEMORY;
   }
   *pbTapeImage = 0x20; // start off with a pause block
   *(word *)(pbTapeImage+1) = 2000; // set the length to 2 seconds

   *(pbTapeImage+3) = 0x15; // direct recording block
   *(word *)(pbTapeImage+4) = (word)dwTapePulseCycles; // number of T states per sample
   *(word *)(pbTapeImage+6) = 0; // pause after block
   *(pbTapeImage+8) = lSampleLength & 7 ? lSampleLength & 7 : 8; // bits used in last Byte
   *(uLong *)(pbTapeImage+9) = dwCompressedSize & 0x00ffffff; // data length
   pbTapeImagePtr = pbTapeImage + 12;

   lOffset = lInitialOffset;
   bolDone = false;
   uLong dwBit = 8;
   Byte bByte = 0;
   while ((!bolDone) && (lOffset < lFileSize)) {
      fseek(pfileObject, lOffset, SEEK_SET);
      fread(pbPtr, 1, 1, pfileObject); // read block ID
      switch(*pbPtr) {
         case 0x0: // terminator
            bolDone = true;
            break;
         case 0x1: // sound data
         { // MSC
            fread(pbPtr, 3+2, 1, pfileObject); // get block size and sound info
            iBlockLength = (*(uLong *)(pbPtr) & 0x00ffffff) + 4;
            lSampleLength = iBlockLength - 6;
            pbVocDataBlock = (Byte *)malloc(lSampleLength);
            if (pbVocDataBlock == NULL) {
               fclose(pfileObject);
               tape_eject();
               return ERR_OUT_OF_MEMORY;
            }
            fread(pbVocDataBlock, lSampleLength, 1, pfileObject);
            pbVocDataBlockPtr = pbVocDataBlock;
            for (int iBytePos = 0; iBytePos < lSampleLength; iBytePos++) {
               Byte bVocSample = *pbVocDataBlockPtr++;
               dwBit--;
               if (bVocSample > VOC_THRESHOLD) {
                  bByte |= bit_values[dwBit];
               }
               if (!dwBit) { // got all 8 bits?
                  *pbTapeImagePtr++ = bByte;
                  dwBit = 8;
                  bByte = 0;
               }
            }
            free(pbVocDataBlock);
            break;
         } // MSC
         case 0x2: // sound continue
         { // MSC
            fread(pbPtr, 3, 1, pfileObject); // get block size
            iBlockLength = (*(uLong *)(pbPtr) & 0x00ffffff) + 4;
            lSampleLength = iBlockLength - 4;
            pbVocDataBlock = (Byte *)malloc(lSampleLength);
            if (pbVocDataBlock == NULL) {
               fclose(pfileObject);
               tape_eject();
               return ERR_OUT_OF_MEMORY;
            }
            fread(pbVocDataBlock, lSampleLength, 1, pfileObject);
            pbVocDataBlockPtr = pbVocDataBlock;
            for (int iBytePos = 0; iBytePos < lSampleLength; iBytePos++) {
               Byte bVocSample = *pbVocDataBlockPtr++;
               dwBit--;
               if (bVocSample > VOC_THRESHOLD) {
                  bByte |= bit_values[dwBit];
               }
               if (!dwBit) { // got all 8 bits?
                  *pbTapeImagePtr++ = bByte;
                  dwBit = 8;
                  bByte = 0;
               }
            }
            free(pbVocDataBlock);
            break;
         } // MSC
         case 0x3: // silence
         { // MSC
            iBlockLength = 4;
            lSampleLength = *(word *)(pbPtr) + 1;
            for (int iBytePos = 0; iBytePos < lSampleLength; iBytePos++) {
               dwBit--;
               if (!dwBit) { // got all 8 bits?
                  *pbTapeImagePtr++ = bByte;
                  dwBit = 8;
                  bByte = 0;
               }
            }
            break;
         } // MSC
         case 0x4: // marker
            iBlockLength = 3;
            break;
         case 0x5: // ascii
            iBlockLength = (*(uLong *)(pbPtr) & 0x00ffffff) + 4;
            break;
      }
      lOffset += iBlockLength;
   }
   fclose(pfileObject);

   *pbTapeImagePtr = 0x20; // end with a pause block
   *(word *)(pbTapeImagePtr+1) = 2000; // set the length to 2 seconds

   pbTapeImageEnd = pbTapeImagePtr + 3;
/*
   #ifdef DEBUG_TAPE
   if ((pfileObject = _tfopen("./test.cdt", "wb")) != NULL) {
      fwrite(pbTapeImage, (int)((pbTapeImagePtr+3)-pbTapeImage), 1, pfileObject);
      fclose(pfileObject);
   }
   #endif
*/
   Tape_Rewind();

/* char *pchTmpBuffer = new char[MAX_LINE_LEN];
   LoadString(hAppInstance, MSG_TAP_INSERT, chMsgBuffer, sizeof(chMsgBuffer));
   snprintf(pchTmpBuffer, _MAX_PATH-1, chMsgBuffer, CPC.tape_file);
   add_message(pchTmpBuffer);
   delete [] pchTmpBuffer; */
   return 0;
}



void vdu_init (bool bolInit)
{
   int vw = CPC_VISIBLE_SCR_WIDTH;
   //if(ALESTE & alesteExtend.bit.HIGHTX)
	//	vw *=2;
   if (CPC.scr_fs_width > (vw * dwXScale)) {
      video_rect.x = (CPC.scr_fs_width - (vw * dwXScale)) / 2;
      video_rect.w = 0; // not used
      back_rect.x = 0;
      back_rect.w = vw * dwXScale;
   } else {
      video_rect.x = 0;
      video_rect.w = 0; // not used
      back_rect.x = ((vw * dwXScale) - CPC.scr_fs_width) / 2;
      back_rect.w = CPC.scr_fs_width;
   }

   if (CPC.scr_fs_height > (CPC_VISIBLE_SCR_HEIGHT * dwYScale)) {
      video_rect.y = (CPC.scr_fs_height - (CPC_VISIBLE_SCR_HEIGHT * dwYScale)) / 2;
      video_rect.h = 0; // not used
      back_rect.y = 0;
      back_rect.h = CPC_VISIBLE_SCR_HEIGHT * dwYScale;
   } else {
      video_rect.y = 0;
      video_rect.h = 0; // not used
      back_rect.y = ((CPC_VISIBLE_SCR_HEIGHT * dwYScale) - CPC.scr_fs_height) / 2;
      back_rect.h = CPC.scr_fs_height;
   }

   if (bolInit) {
	  if(ALESTE & alesteExtend.bit.HIGHTX){
	      VDU.hwidth = vw / 4;
	      VDU.hstart = 14;
	  }  else {
	      VDU.hstart = 7;
	      VDU.hwidth = vw / 8;
	  }
      VDU.vstart = 27;
      VDU.vheight = CPC_VISIBLE_SCR_HEIGHT;
   }
}

static int emulator_patch_ROM (void)
{
   TCHAR chPath[_MAX_PATH + 1];

   _tcsncpy(chPath, CPC.rom_path, _countof(chPath)-2);
   _tcscat(chPath, _T("/"));
   _tcsncat(chPath, chROMFile[CPC.model], _countof(chPath)-1 - _tcslen(chPath)); // determine the ROM image name for the selected model
   
   if (load_rom(chPath, pbROMlo, 2*16384))
   {
   }
   else 
   {
      return ERR_CPC_ROM_MISSING;
   }
   //if (CPC.kbd_layout)
   {
      Byte* pbPtr = pbROMlo;
      switch(CPC.model) 
      {
         case 0: // 464
            pbPtr[offsetof(CPCROM_464_FIRMWARE, mode)] = CPC.default_mode;
            if (CPC.kbd_layout)
            {
               memcpy(pbPtr + offsetof(CPCROM_464_FIRMWARE, keyboard), kbd_layout[CPC.kbd_layout-1], 240); // patch the CPC OS ROM with the chosen keyboard layout
               memcpy_keyboard(pbPtr + offsetof(CPCROM_464_FIRMWARE, font), CPC.kbd_layout-1, FALSE);
            }
            break;
         case 1: // 664
         case 2: // 6128
            pbPtr[offsetof(CPCROM_6128_FIRMWARE, mode)] = CPC.default_mode;
            if (CPC.kbd_layout)
            {
               memcpy(pbPtr + offsetof(CPCROM_6128_FIRMWARE, keyboard), kbd_layout[CPC.kbd_layout-1], 240); // patch the CPC OS ROM with the chosen keyboard layout
               memcpy_keyboard(pbPtr + offsetof(CPCROM_6128_FIRMWARE, font), CPC.kbd_layout-1, FALSE);
            }
            break;
      }
   }
   return 0;
}



void emulator_reset (bool bolMF2Reset)
{
   int n, val1, val2;

// Z80
   memset(&z80, 0, sizeof(z80)); // clear all Z80 registers and support variables
   _IX =
   _IY = 0xffff; // IX and IY are FFFF after a reset!
   _F = Zflag; // set zero flag
   z80.break_point = 0xffffffff; // clear break point
// ALESTE
   if(ALESTE){
	   alesteReset();
   }

// CPC
   CPC.cycle_count = CYCLE_COUNT_INIT;
   memset(keyboard_matrix, 0xFF, sizeof(keyboard_matrix)); // clear CPC keyboard matrix
   //keyboard_matrix[8]=~0x04;
   CPC.tape_motor = 0;
   CPC.tape_play_button = 0;
   CPC.printer_port = 0xff;
   KeyboardScanned = false;

// CRTC
   memset(&CRTC, 0, sizeof(CRTC)); // clear CRTC data structure
   for (n = 0; n < 14; n++) { // program CRTC with 'valid' data
      CRTC.registers[n] = CRTC_values[(CPC.jumpers & 0x10)>>4][n];
   }
   CRTC.flags = HDT_flag | VDT_flag;
   CRTC.hsw =
   CRTC.hsw_active = CRTC.registers[3] & 0x0f;
   CRTC.vsw = CRTC.registers[3] >> 4;
   CRTC.vt_adjust = CRTC.registers[5] & 0x1f;
   CRTC.skew = (CRTC.registers[8] >> 4) & 3;
   if (CRTC.skew == 3) { // no output?
      CRTC.skew = 0xff;
   }
   CRTC.max_raster = CRTC.registers[9] << 3;
   val1 = CRTC.registers[12] & 0x3f;
   val2 = val1 & 0x0f; // isolate screen size
   val1 = (val1 << 1) & 0x60; // isolate CPC RAM bank
   val2 |= val1; // combine
   CRTC.addr =
   CRTC.requested_addr = (CRTC.registers[13] + (val2 << 8)) << 1;
   CRTC.last_hdisp = 0x28;

// VDU
   memset(&VDU, 0, sizeof(VDU)); // clear VDU data structure
   VDU.hsw =
   VDU.hsw_active = 4;
   VDU.scanline_min = 272; //240;
   vdu_init(true);

// Gate Array
   memset(&GateArray, 0, sizeof(GateArray)); // clear GA data structure
   GateArray.scr_mode =
   GateArray.requested_scr_mode = mode_handler[1]; // set to normal mode 1 handler
   GateArray.scr_border = border_handler; // set to normal border handler
   ga_init_banking();

// PPI
   memset(&PPI, 0, sizeof(PPI)); // clear PPI data structure

// PSG
   PSG.control = 0;
   ResetAYChipEmulation();

// FDC
   memset(&FDC, 0, sizeof(FDC)); // clear FDC data structure
   FDC.phase = CMD_PHASE;
   FDC.flags = STATUSDRVA_flag | STATUSDRVB_flag;

// memory
   if (bolMF2Reset) {
      memset(pbRAM, 0, 64*1024); // clear only the first 64K of CPC memory
   } else {
      memset(pbRAM, 0, CPC.ram_size*1024); // clear all memory used for CPC RAM
      if (pbMF2ROM) {
         memset(pbMF2ROM+8192, 0, 8192); // clear the MF2's RAM area
      }
   }
   for (n = 0; n < 4; n++) { // initialize active read/write bank configuration
      membank_read[n] = (Byte*)membank_config[0][n];
      membank_write[n] = (Byte*)membank_config[0][n];
   }
   membank_read[0] = pbROMlo; // 'page in' lower ROM
   membank_read[3] = pbROMhi; // 'page in' upper ROM

// Multiface 2
   dwMF2Flags = 0;
   dwMF2ExitAddr = 0xffffffff; // clear MF2 return address
   if ((pbMF2ROM) && (pbMF2ROMbackup)) {
      memcpy(pbMF2ROM, pbMF2ROMbackup, 8192); // copy the MF2 ROM to its proper place
   }
}



int emulator_init (void)
{
   int iErr, iRomNum;
   TCHAR chPath[_MAX_PATH + 1];
   char *pchRomData;

   pbGPBuffer = new Byte [128*1024]; // attempt to allocate the general purpose buffer
   pbRAM = new Byte [CPC.ram_size*1024]; // allocate memory for desired amount of RAM
   pbROMlo = new Byte [32*1024]; // allocate memory for 32K of ROM
   if ((!pbGPBuffer) || (!pbRAM) || (!pbROMlo)) {
      return ERR_OUT_OF_MEMORY;
   }
   pbROMhi =
   pbExpansionROM = pbROMlo + 16384;
   memset(memmap_ROM, 0, sizeof(memmap_ROM[0]) * 256); // clear the expansion ROM map
   ga_init_banking(); // init the CPC memory banking map
   if ((iErr = emulator_patch_ROM())) {
      return iErr;
   }

   for (iRomNum = 2; iRomNum < 16; iRomNum++) { // loop for ROMs 2-15
      if (CPC.rom_file[iRomNum][0])
      { // is a ROM image specified for this slot?
         bool internal = (*CPC.rom_file[iRomNum] == '<');
         pchRomData = new char [16384]; // allocate 16K
         memset(pchRomData, 0, 16384); // clear memory
         if (internal)
         {
            _tcsncpy(chPath, CPC.rom_file[iRomNum], _countof(chPath));
         }
         else
         {
            _tcsncpy(chPath, CPC.rom_path, _countof(chPath)-2);
            _tcscat(chPath, _T("/"));
            _tcsncat(chPath, CPC.rom_file[iRomNum], _countof(chPath)-1 - _tcslen(chPath));
         }
         if ((!internal) && (pfileObject = _tfopen(chPath, _T("rb"))) != NULL) { // attempt to open the ROM image
            fread(pchRomData, 128, 1, pfileObject); // read 128 bytes of ROM data
            if ((pchRomData[0] == char(0x01)) || (pchRomData[0] == char(0x02))) { // is it a valid CPC ROM image?
               fread(pchRomData+128, 16384-128, 1, pfileObject); // read the rest of the ROM file
               memmap_ROM[iRomNum] = (Byte *)pchRomData; // update the ROM map
            } else { // try one more time, as the ROM might have a header
               fread(pchRomData, 128, 1, pfileObject); // read 128 bytes of ROM data
               if ((pchRomData[0] == char(0x01)) || (pchRomData[0] == char(0x02))) { // is it a valid CPC ROM image?
                  fread(pchRomData+128, 16384-128, 1, pfileObject); // read the rest of the ROM file
                  memmap_ROM[iRomNum] = (Byte *)pchRomData; // update the ROM map
               } else { // not a valid ROM file
                  fprintf(stderr, "ERROR: %s is not a CPC ROM file - clearing ROM slot %d.\n", CPC.rom_file[iRomNum], iRomNum);
                  delete [] pchRomData; // free memory on error
                  CPC.rom_file[iRomNum][0] = 0;
               }
            }
            fclose(pfileObject);
         }
         else if (load_rom(chPath, pchRomData, 16384))
         {
            memmap_ROM[iRomNum] = (Byte *)pchRomData; // update the ROM map
         }
         else
         { // file not found
            fprintf(stderr, "ERROR: The %s file is missing - clearing ROM slot %d.\n", CPC.rom_file[iRomNum], iRomNum);
            delete [] pchRomData; // free memory on error
            CPC.rom_file[iRomNum][0] = 0;
         }
      }
   }
   if (CPC.mf2) { // Multiface 2 enabled?
      if (!pbMF2ROM) {
         pbMF2ROM = new Byte [16384]; // allocate the space needed for the Multiface 2: 8K ROM + 8K RAM
         pbMF2ROMbackup = new Byte [8192]; // allocate the space needed for the backup of the MF2 ROM
         if ((!pbMF2ROM) || (!pbMF2ROMbackup)) {
            return ERR_OUT_OF_MEMORY;
         }
         memset(pbMF2ROM, 0, 16384); // clear memory
         _tcsncpy(chPath, CPC.rom_path, _countof(chPath)-2);
         _tcscat(chPath, _T("/"));
         _tcsncat(chPath, CPC.rom_mf2, _countof(chPath)-1 - _tcslen(chPath)); // combine path and file name
         if ((pfileObject = _tfopen(chPath, _T("rb"))) != NULL) { // attempt to open the ROM image
            fread(pbMF2ROMbackup, 8192, 1, pfileObject);
            if (memcmp(pbMF2ROMbackup+0x0d32, "MULTIFACE 2", 11) != 0) { // does it have the required signature?
               fprintf(stderr, "ERROR: The file selected as the MF2 ROM is either corrupt or invalid.\n");
               delete [] pbMF2ROMbackup;
               delete [] pbMF2ROM;
               pbMF2ROM = NULL;
               CPC.rom_mf2[0] = 0;
               CPC.mf2 = 0; // disable MF2 support
            }
            fclose(pfileObject);
         } else { // error opening file
            fprintf(stderr, "ERROR: The file selected as the MF2 ROM is either corrupt or invalid.\n");
            delete [] pbMF2ROMbackup;
            delete [] pbMF2ROM;
            pbMF2ROM = NULL;
            CPC.rom_mf2[0] = 0;
            CPC.mf2 = 0; // disable MF2 support
         }
      }
   }

   emulator_reset(false);
   CPC.paused &= ~1;

   return 0;
}



void emulator_shutdown (void)
{
   int iRomNum;

   delete [] pbMF2ROMbackup;
   delete [] pbMF2ROM;
   pbMF2ROM = NULL;
   for (iRomNum = 2; iRomNum < 16; iRomNum++) // loop for ROMs 2-15
   {
      if (memmap_ROM[iRomNum] != NULL) // was a ROM assigned to this slot?
         delete [] memmap_ROM[iRomNum]; // if so, release the associated memory
   }

   delete [] pbROMlo;
   delete [] pbRAM;
   delete [] pbGPBuffer;
}



int printer_start (void)
{
   if (!pfoPrinter) {
      if(!(pfoPrinter = _tfopen(CPC.printer_file, _T("wb")))) {
         return 0; // failed to open/create file
      }
   }
   return 1; // ready to capture printer output
}



void printer_stop (void)
{
   if (pfoPrinter) {
      fclose(pfoPrinter);
   }
   pfoPrinter = NULL;
}



void audio_update (void *userdata, Byte *stream, int len)
{
   memcpy(stream, pbSndStream, len);
   pbSndStream += len;
   if (pbSndStream >= pbSndBufferEnd) {
      pbSndStream = pbSndBuffer;
   }
}



int audio_align_samples (int given)
{
   int actual = 1;
   while (actual < given) {
      actual <<= 2;
   }
   return actual; // return the closest match as 2^n
}




int audio_init (void)
{
   SDL_AudioSpec *desired, *obtained;

   if (!CPC.snd_enabled) {
      return 0;
   }

   //desired = (SDL_AudioSpec *)malloc(sizeof(SDL_AudioSpec));
   //obtained = (SDL_AudioSpec *)malloc(sizeof(SDL_AudioSpec));
   desired = (SDL_AudioSpec *)calloc(1, sizeof(SDL_AudioSpec));
   obtained = (SDL_AudioSpec *)calloc(1, sizeof(SDL_AudioSpec));

   desired->freq = freq_table[CPC.snd_playback_rate];
   desired->format = CPC.snd_bits ? AUDIO_S16LSB : AUDIO_S8;
   desired->channels = CPC.snd_stereo+1;
   desired->samples = audio_align_samples(desired->freq / 50); // desired is 20ms at the given frequency
   desired->callback = audio_update;
   desired->userdata = NULL;

   if (SDL_OpenAudio(desired, obtained) < 0) {
      fprintf(stderr, "Could not open audio: %s\n", SDL_GetError());
      return 1;
   }

   free(desired);
   audio_spec = obtained;

   CPC.snd_buffersize = audio_spec->size; // size is samples * channels * bytes per sample (1 or 2)
   pbSndBuffer = (Byte *)malloc(CPC.snd_buffersize*6); // allocate a ring buffer with 10 segments
   pbSndBufferEnd = pbSndBuffer + (CPC.snd_buffersize*6);
   pbSndStream = pbSndBuffer; // put the play cursor at the start
   memset(pbSndBuffer, 0, CPC.snd_buffersize*6);
   CPC.snd_bufferptr = pbSndBuffer + (CPC.snd_buffersize*3); // init write cursor

   dwSndMinSafeDist = CPC.snd_buffersize*2; // the closest together the cursors may be
   dwSndMaxSafeDist = CPC.snd_buffersize*4; // the farthest apart the cursors may be

   InitAY();

   for (int n = 0; n < 16; n++) {
      SetAYRegister(n, PSG.RegisterAY.Index[n]); // init sound emulation with valid values
   }

   return 0;
}



void audio_shutdown (void)
{
   SDL_CloseAudio();
   if (pbSndBuffer) {
      free(pbSndBuffer);
   }
   if (audio_spec) {
      free(audio_spec);
   }
}



void audio_pause (void)
{
   if (CPC.snd_enabled) {
      SDL_PauseAudio(1);
   }
}



void audio_resume (void)
{
   if (CPC.snd_enabled) {
      SDL_PauseAudio(0);
   }
}



void video_init_tables (void)
{
   int idx, n, p1, p2, p3, p4;

   idx = 0;
   for (n = 0; n < 256; n++) { // calculate mode0 Byte-to-pixel translation table
      p1 = ((n & 0x80) >> 7) + ((n & 0x08) >> 2) + ((n & 0x20) >> 3) + ((n & 0x02) << 2);
      p2 = ((n & 0x40) >> 6) + ((n & 0x04) >> 1) + ((n & 0x10) >> 2) + ((n & 0x01) << 3);
      mode0_table[idx++] = p1;
      mode0_table[idx++] = p2;
   }

   idx = 0;
   for (n = 0; n < 256; n++) { // calculate mode1 Byte-to-pixel translation table
      p1 = ((n & 0x80) >> 7) + ((n & 0x08) >> 2);
      p2 = ((n & 0x40) >> 6) + ((n & 0x04) >> 1);
      p3 = ((n & 0x20) >> 5) +  (n & 0x02);
      p4 = ((n & 0x10) >> 4) + ((n & 0x01) << 1);
      mode1_table[idx++] = p1;
      mode1_table[idx++] = p2;
      mode1_table[idx++] = p3;
      mode1_table[idx++] = p4;
   }
}



int video_set_palette (void)
{
   SDL_Color colours[256];
   int n, m;

   switch(CPC.scr_bpp)
   {
      case 32:
      case 24:
         if (!CPC.scr_tube) {
            int n;
            for (n = 0; n < 32; n++) {
               uLong red = (uLong)(colours_rgb[n][0] * (CPC.scr_intensity / 10.0) * 255);
               if (red > 255) { // limit to the maximum
                  red = 255;
               }
               uLong green = (uLong)(colours_rgb[n][1] * (CPC.scr_intensity / 10.0) * 255);
               if (green > 255) {
                  green = 255;
               }
               uLong blue = (uLong)(colours_rgb[n][2] * (CPC.scr_intensity / 10.0) * 255);
               if (blue > 255) {
                  blue = 255;
               }
               colour_table[n] = blue | (green << 8) | (red << 16);
            }
         } else {
            int n;
            for (n = 0; n < 32; n++) {
               uLong green = (uLong)(colours_green[n] * (CPC.scr_intensity / 10.0) * 255);
               if (green > 255) {
                  green = 255;
               }
               colour_table[n] = green << 8;
            }
         }
         break;

      case 16:
         if (!CPC.scr_tube) {
            int n;
            for (n = 0; n < 32; n++) {
               uLong red = (uLong)(colours_rgb[n][0] * (CPC.scr_intensity / 10.0) * 31);
               if (red > 31) { // limit to the maximum
                  red = 31;
               }
               uLong green = (uLong)(colours_rgb[n][1] * (CPC.scr_intensity / 10.0) * 63);
               if (green > 63) {
                  green = 63;
               }
               uLong blue = (uLong)(colours_rgb[n][2] * (CPC.scr_intensity / 10.0) * 31);
               if (blue > 31) {
                  blue = 31;
               }
               uLong colour = blue | (green << 5) | (red << 11);
               colour_table[n] = colour | (colour << 16);
            }
         } else {
            int n;
            for (n = 0; n < 32; n++) {
               uLong green = (uLong)(colours_green[n] * (CPC.scr_intensity / 10.0) * 63);
               if (green > 63) {
                  green = 63;
               }
               uLong colour = green << 5;
               colour_table[n] = colour | (colour << 16);
            }
         }
         break;

      case 15:
         if (!CPC.scr_tube) {
            int n;
            for (n = 0; n < 32; n++) {
               uLong red = (uLong)(colours_rgb[n][0] * (CPC.scr_intensity / 10.0) * 31);
               if (red > 31) { // limit to the maximum
                  red = 31;
               }
               uLong green = (uLong)(colours_rgb[n][1] * (CPC.scr_intensity / 10.0) * 31);
               if (green > 31) {
                  green = 31;
               }
               uLong blue = (uLong)(colours_rgb[n][2] * (CPC.scr_intensity / 10.0) * 31);
               if (blue > 31) {
                  blue = 31;
               }
               uLong colour = blue | (green << 5) | (red << 10);
               colour_table[n] = colour | (colour << 16);
            }
         } else {
            int n;
            for (n = 0; n < 32; n++) {
               uLong green = (uLong)(colours_green[n] * (CPC.scr_intensity / 10.0) * 31);
               if (green > 31) {
                  green = 31;
               }
               uLong colour = green << 5;
               colour_table[n] = colour | (colour << 16);
            }
         }
         break;

      case 8:
         if (!CPC.scr_tube) {
            int n;
            for (n = 0; n < 32; n++) {
               uLong red = (uLong)(colours_rgb[n][0] * (CPC.scr_intensity / 10.0) * 255);
               if (red > 255) { // limit to the maximum
                  red = 255;
               }
               uLong green = (uLong)(colours_rgb[n][1] * (CPC.scr_intensity / 10.0) * 255);
               if (green > 255) {
                  green = 255;
               }
               uLong blue = (uLong)(colours_rgb[n][2] * (CPC.scr_intensity / 10.0) * 255);
               if (blue > 255) {
                  blue = 255;
               }
               colour_table[n] = blue | (green << 8) | (red << 16);
            }
         } else {
            int n;
            for (n = 0; n < 32; n++) {
               uLong green = (uLong)(colours_green[n] * (CPC.scr_intensity / 10.0) * 255);
               if (green > 255) {
                  green = 255;
               }
               colour_table[n] = green << 8;
            }
         }
         memcpy(colours, video_surface->format->palette->colors, sizeof(colours)); // get the default palette
         for (n = 16, m = 0; n < (16+32); n++, m++) { // insert the 32 colours required for the CPC emulation
            colours[n].r = (colour_table[m] >> 16) & 0xff;
            colours[n].g = (colour_table[m] >> 8) & 0xff;
            colours[n].b = colour_table[m] & 0xff;
            colour_table[m] = n | (n << 8) | (n << 16) | (n << 24); // change table to indices
         }
         if (!SDL_SetPalette(video_surface, SDL_LOGPAL | SDL_PHYSPAL, colours, 0, 256)) {
            return ERR_VIDEO_PALETTE;
         }
         break;

      default:
         return ERR_VIDEO_COLOUR_DEPTH;
   }

   for (n = 0; n < 17; n++) { // loop for all colours + border
      GateArray.palette[n] = colour_table[GateArray.ink_values[n]];
   }
   return 0;
}


void video_set_style_cpc (void)
{
   switch(CPC.scr_bpp)
   {
      case 32:
         switch (CPC.scr_style)
         {
            case 0: // scanlines
               mode_handler[0] = draw32bpp_mode0;
               mode_handler[1] = draw32bpp_mode1;
               mode_handler[2] = draw32bpp_mode2;
               mode_handler[3] = draw32bpp_mode0;
               border_handler = draw32bpp_border;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 1: // line doubling (software)
               mode_handler[0] = draw32bpp_mode0_double;
               mode_handler[1] = draw32bpp_mode1_double;
               mode_handler[2] = draw32bpp_mode2_double;
               mode_handler[3] = draw32bpp_mode0_double;
               border_handler = draw32bpp_border_double;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 2: // line doubling (hardware)
               mode_handler[0] = draw32bpp_mode0;
               mode_handler[1] = draw32bpp_mode1;
               mode_handler[2] = draw32bpp_mode2;
               mode_handler[3] = draw32bpp_mode0;
               border_handler = draw32bpp_border;
               dwXScale = 2;
               dwYScale = 1;
               break;
            case 3: // half size
               mode_handler[0] = draw32bpp_mode0_half;
               mode_handler[1] = draw32bpp_mode1_half;
               mode_handler[2] = draw32bpp_mode2_half;
               mode_handler[3] = draw32bpp_mode0_half;
               border_handler = draw32bpp_border_half;
               dwXScale = 1;
               dwYScale = 1;
               break;
         }
         break;

      case 24:
         switch (CPC.scr_style)
         {
            case 0: // scanlines
               mode_handler[0] = draw24bpp_mode0;
               mode_handler[1] = draw24bpp_mode1;
               mode_handler[2] = draw24bpp_mode2;
               mode_handler[3] = draw24bpp_mode0;
               border_handler = draw24bpp_border;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 1: // line doubling (software)
               mode_handler[0] = draw24bpp_mode0_double;
               mode_handler[1] = draw24bpp_mode1_double;
               mode_handler[2] = draw24bpp_mode2_double;
               mode_handler[3] = draw24bpp_mode0_double;
               border_handler = draw24bpp_border_double;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 2: // line doubling (hardware)
               mode_handler[0] = draw24bpp_mode0;
               mode_handler[1] = draw24bpp_mode1;
               mode_handler[2] = draw24bpp_mode2;
               mode_handler[3] = draw24bpp_mode0;
               border_handler = draw24bpp_border;
               dwXScale = 2;
               dwYScale = 1;
               break;
            case 3: // half size
               mode_handler[0] = draw24bpp_mode0_half;
               mode_handler[1] = draw24bpp_mode1_half;
               mode_handler[2] = draw24bpp_mode2_half;
               mode_handler[3] = draw24bpp_mode0_half;
               border_handler = draw24bpp_border_half;
               dwXScale = 1;
               dwYScale = 1;
               break;
         }
         break;

      case 16:
      case 15:
         switch (CPC.scr_style)
         {
            case 0: // scanlines
               mode_handler[0] = draw16bpp_mode0;
               mode_handler[1] = draw16bpp_mode1;
               mode_handler[2] = draw16bpp_mode2;
               mode_handler[3] = draw16bpp_mode0;
               border_handler = draw16bpp_border;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 1: // line doubling (software)
               mode_handler[0] = draw16bpp_mode0_double;
               mode_handler[1] = draw16bpp_mode1_double;
               mode_handler[2] = draw16bpp_mode2_double;
               mode_handler[3] = draw16bpp_mode0_double;
               border_handler = draw16bpp_border_double;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 2: // line doubling (hardware)
               mode_handler[0] = draw16bpp_mode0;
               mode_handler[1] = draw16bpp_mode1;
               mode_handler[2] = draw16bpp_mode2;
               mode_handler[3] = draw16bpp_mode0;
               border_handler = draw16bpp_border;
               dwXScale = 2;
               dwYScale = 1;
               break;
            case 3: // half size
               mode_handler[0] = draw16bpp_mode0_half;
               mode_handler[1] = draw16bpp_mode1_half;
               mode_handler[2] = draw16bpp_mode2_half;
               mode_handler[3] = draw16bpp_mode0_half;
               border_handler = draw16bpp_border_half;
               dwXScale = 1;
               dwYScale = 1;
               break;
         }
         break;

      case 8:
         switch (CPC.scr_style)
         {
            case 0: // scanlines
               mode_handler[0] = draw8bpp_mode0;
               mode_handler[1] = draw8bpp_mode1;
               mode_handler[2] = draw8bpp_mode2;
               mode_handler[3] = draw8bpp_mode0;
               border_handler = draw8bpp_border;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 1: // line doubling (software)
               mode_handler[0] = draw8bpp_mode0_double;
               mode_handler[1] = draw8bpp_mode1_double;
               mode_handler[2] = draw8bpp_mode2_double;
               mode_handler[3] = draw8bpp_mode0_double;
               border_handler = draw8bpp_border_double;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 2: // line doubling (hardware)
               mode_handler[0] = draw8bpp_mode0;
               mode_handler[1] = draw8bpp_mode1;
               mode_handler[2] = draw8bpp_mode2;
               mode_handler[3] = draw8bpp_mode0;
               border_handler = draw8bpp_border;
               dwXScale = 2;
               dwYScale = 1;
               break;
            case 3: // half size
               mode_handler[0] = draw8bpp_mode0_half;
               mode_handler[1] = draw8bpp_mode1_half;
               mode_handler[2] = draw8bpp_mode2_half;
               mode_handler[3] = draw8bpp_mode0_half;
               border_handler = draw8bpp_border_half;
               dwXScale = 1;
               dwYScale = 1;
               break;
         }
   }
   CPC.scr_line_offs = CPC.scr_bps * dwYScale;

   GateArray.scr_mode =
   GateArray.requested_scr_mode = (void(*)(uInt))mode_handler[GateArray.ROM_config & 3];
   GateArray.scr_border = (void(*)(void))border_handler;
}

void video_set_style_aleste (void)
{
   switch(CPC.scr_bpp)
   {
      case 32:
         switch (CPC.scr_style)
         {
            case 0: // scanlines
               mode_handler[0] = aleste_draw32bpp_mode0;
               mode_handler[1] = aleste_draw32bpp_mode1;
               mode_handler[2] = aleste_draw32bpp_mode2;
               mode_handler[3] = aleste_draw32bpp_mode0;
               border_handler = aleste_draw32bpp_border;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 1: // line doubling (software)
               mode_handler[0] = aleste_draw32bpp_mode0_double;
               mode_handler[1] = aleste_draw32bpp_mode1_double;
               mode_handler[2] = aleste_draw32bpp_mode2_double;
               mode_handler[3] = aleste_draw32bpp_mode0_double;
               border_handler = aleste_draw32bpp_border_double;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 2: // line doubling (hardware)
               mode_handler[0] = aleste_draw32bpp_mode0;
               mode_handler[1] = aleste_draw32bpp_mode1;
               mode_handler[2] = aleste_draw32bpp_mode2;
               mode_handler[3] = aleste_draw32bpp_mode0;
               border_handler = aleste_draw32bpp_border;
               dwXScale = 2;
               dwYScale = 1;
               break;
            case 3: // half size
               mode_handler[0] = aleste_draw32bpp_mode0_half;
               mode_handler[1] = aleste_draw32bpp_mode1_half;
               mode_handler[2] = aleste_draw32bpp_mode2_half;
               mode_handler[3] = aleste_draw32bpp_mode0_half;
               border_handler = aleste_draw32bpp_border_half;
               dwXScale = 1;
               dwYScale = 1;
               break;
         }
         break;
      case 24:
         switch (CPC.scr_style)
         {
            case 0: // scanlines
               mode_handler[0] = aleste_draw24bpp_mode0;
               mode_handler[1] = aleste_draw24bpp_mode1;
               mode_handler[2] = aleste_draw24bpp_mode2;
               mode_handler[3] = aleste_draw24bpp_mode0;
               border_handler = aleste_draw24bpp_border;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 1: // line doubling (software)
               mode_handler[0] = aleste_draw24bpp_mode0_double;
               mode_handler[1] = aleste_draw24bpp_mode1_double;
               mode_handler[2] = aleste_draw24bpp_mode2_double;
               mode_handler[3] = aleste_draw24bpp_mode0_double;
               border_handler = aleste_draw24bpp_border_double;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 2: // line doubling (hardware)
               mode_handler[0] = aleste_draw24bpp_mode0;
               mode_handler[1] = aleste_draw24bpp_mode1;
               mode_handler[2] = aleste_draw24bpp_mode2;
               mode_handler[3] = aleste_draw24bpp_mode0;
               border_handler = aleste_draw24bpp_border;
               dwXScale = 2;
               dwYScale = 1;
               break;
            case 3: // half size
               mode_handler[0] = aleste_draw24bpp_mode0_half;
               mode_handler[1] = aleste_draw24bpp_mode1_half;
               mode_handler[2] = aleste_draw24bpp_mode2_half;
               mode_handler[3] = aleste_draw24bpp_mode0_half;
               border_handler = aleste_draw24bpp_border_half;
               dwXScale = 1;
               dwYScale = 1;
               break;
         }
         break;

      case 16:
      case 15:
         switch (CPC.scr_style)
         {
            case 0: // scanlines
               mode_handler[0] = aleste_draw16bpp_mode0;
               mode_handler[1] = aleste_draw16bpp_mode1;
               mode_handler[2] = aleste_draw16bpp_mode2;
               mode_handler[3] = aleste_draw16bpp_mode0;
               border_handler = aleste_draw16bpp_border;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 1: // line doubling (software)
               mode_handler[0] = aleste_draw16bpp_mode0_double;
               mode_handler[1] = aleste_draw16bpp_mode1_double;
               mode_handler[2] = aleste_draw16bpp_mode2_double;
               mode_handler[3] = aleste_draw16bpp_mode0_double;
               border_handler = aleste_draw16bpp_border_double;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 2: // line doubling (hardware)
               mode_handler[0] = aleste_draw16bpp_mode0;
               mode_handler[1] = aleste_draw16bpp_mode1;
               mode_handler[2] = aleste_draw16bpp_mode2;
               mode_handler[3] = aleste_draw16bpp_mode0;
               border_handler = aleste_draw16bpp_border;
               dwXScale = 2;
               dwYScale = 1;
               break;
            case 3: // half size
               mode_handler[0] = aleste_draw16bpp_mode0_half;
               mode_handler[1] = aleste_draw16bpp_mode1_half;
               mode_handler[2] = aleste_draw16bpp_mode2_half;
               mode_handler[3] = aleste_draw16bpp_mode0_half;
               border_handler = aleste_draw16bpp_border_half;
               dwXScale = 1;
               dwYScale = 1;
               break;
         }
         break;

      case 8:
         switch (CPC.scr_style)
         {
            case 0: // scanlines
               mode_handler[0] = aleste_draw8bpp_mode0;
               mode_handler[1] = aleste_draw8bpp_mode1;
               mode_handler[2] = aleste_draw8bpp_mode2;
               mode_handler[3] = aleste_draw8bpp_mode0;
               border_handler = aleste_draw8bpp_border;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 1: // line doubling (software)
               mode_handler[0] = aleste_draw8bpp_mode0_double;
               mode_handler[1] = aleste_draw8bpp_mode1_double;
               mode_handler[2] = aleste_draw8bpp_mode2_double;
               mode_handler[3] = aleste_draw8bpp_mode0_double;
               border_handler = aleste_draw8bpp_border_double;
               dwXScale = 2;
               dwYScale = 2;
               break;
            case 2: // line doubling (hardware)
               mode_handler[0] = aleste_draw8bpp_mode0;
               mode_handler[1] = aleste_draw8bpp_mode1;
               mode_handler[2] = aleste_draw8bpp_mode2;
               mode_handler[3] = aleste_draw8bpp_mode0;
               border_handler = aleste_draw8bpp_border;
               dwXScale = 2;
               dwYScale = 1;
               break;
            case 3: // half size
               mode_handler[0] = aleste_draw8bpp_mode0_half;
               mode_handler[1] = aleste_draw8bpp_mode1_half;
               mode_handler[2] = aleste_draw8bpp_mode2_half;
               mode_handler[3] = aleste_draw8bpp_mode0_half;
               border_handler = aleste_draw8bpp_border_half;
               dwXScale = 1;
               dwYScale = 1;
               break;
         }
   }
   CPC.scr_line_offs = CPC.scr_bps * dwYScale;

   GateArray.scr_mode = GateArray.requested_scr_mode = (void(*)(uInt))mode_handler[GateArray.ROM_config & 3];
   GateArray.scr_border = (void(*)(void))border_handler;
}

void video_set_style (void){
	if(ALESTE && alesteExtend.bit.HIGHTX)
		video_set_style_aleste();
	else
		video_set_style_cpc();
}

static int video_init (void)
{
   if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) { // initialize the video subsystem
      return ERR_VIDEO_INIT;
   }

   int flags = SDL_HWSURFACE | SDL_ANYFORMAT | SDL_HWPALETTE;
   if (!CPC.scr_window) { // starting up in fullscreen mode?
      flags |= SDL_FULLSCREEN;
   }

   if (!(video_surface = SDL_SetVideoMode(CPC.scr_fs_width, CPC.scr_fs_height, CPC.scr_fs_bpp,
    flags))) { // attempt to set the required video mode
      fprintf(stderr, "Could not set requested video mode: %s\n", SDL_GetError());
      return ERR_VIDEO_SET_MODE;
   }

   CPC.scr_bpp = video_surface->format->BitsPerPixel; // bit depth of the surface

   int iErrCode = video_set_palette(); // init CPC colours and hardware palette (in 8bpp mode)
   if (iErrCode) {
      return iErrCode;
   }

   if (!(back_surface = SDL_CreateRGBSurface( // create the back buffer
    SDL_HWSURFACE,
    CPC_SCR_WIDTH,
    CPC_SCR_HEIGHT*2,
    video_surface->format->BitsPerPixel,
    video_surface->format->Rmask,
    video_surface->format->Gmask,
    video_surface->format->Bmask,
    video_surface->format->Amask))) {
      fprintf(stderr, "Could not allocate back buffer.\n");
      return ERR_VIDEO_SURFACE;
   }

   if (SDL_MUSTLOCK(back_surface)) {
      SDL_LockSurface(back_surface);
   }
   CPC.scr_bps = back_surface->pitch / 4; // rendered screen line length (changing bytes to dwords)
   CPC.scr_base = (uInt*)back_surface->pixels; // memory address of back buffer
   if (SDL_MUSTLOCK(back_surface)) {
      SDL_UnlockSurface(back_surface);
   }

   video_set_style(); // select rendering style
   vdu_init(true); // initialize the monitor emulation

   SDL_FillRect(back_surface, NULL, SDL_MapRGB(back_surface->format, 0, 0, 0)); // clear back buffer
   SDL_ShowCursor(SDL_DISABLE); // hide the mouse cursor

   SDL_WM_SetCaption(CAPTION, "Caprice32");

   return 0;
}



void video_shutdown (void)
{
   if (back_surface) {
      SDL_UnlockSurface(back_surface); // make sure we release any active locks
      SDL_FreeSurface(back_surface); // free the surface we created
   }
   SDL_QuitSubSystem(SDL_INIT_VIDEO);
}



void video_display (void)
{
   SDL_BlitSurface(back_surface, &back_rect, video_surface, &video_rect);
   SDL_UpdateRects(video_surface, 1, &video_rect);
}

void splitPathFileName(TCHAR *pchCombined, TCHAR *pchPath, TCHAR *pchFile)
{
#ifdef _WIN32
   TCHAR  drive[_MAX_PATH], dir[_MAX_PATH], title[_MAX_PATH], ext[_MAX_PATH];
   _tsplitpath(pchCombined, drive, dir, title, ext);
   _tcscpy(pchPath, drive);
   _tcscat(pchPath, dir);
   _tcscpy(pchFile, title);
   _tcscat(pchFile, ext);
#else
   char *pchPtr;

   pchPtr = strrchr(pchCombined, '/'); // start from the end and find the first path delimiter
   if (!pchPtr) {
      pchPtr = strrchr(pchCombined, '\\'); // try again with the alternate form
   }
   if (pchPtr) {
      pchPtr++; // advance the pointer to the next character
      if (pchFile) {
         strcpy(pchFile, pchPtr); // copy the filename
      }
      char chOld = *pchPtr;
      *pchPtr = 0; // cut off the filename part
      if (pchPath != pchCombined) {
         if (pchPath) {
            strcpy(pchPath, pchCombined); // copy the path
         }
         *pchPtr = chOld; // restore original string
      }
   } else {
      if (pchFile) {
         *pchFile = 0; // no filename found
      }
      if (pchPath != pchCombined) {
         if (pchPath) {
            strcpy(pchPath, pchCombined); // copy the path
         }
      }
   }
#endif
}

void doCleanUp (void)
{
   printer_stop();
   emulator_shutdown();

   dsk_eject(&driveA);
   dsk_eject(&driveB);
   tape_eject();
   if (zip_info.pchFileNames) {
      free(zip_info.pchFileNames);
   }

   audio_shutdown();
   video_shutdown();

   #ifdef DEBUG
   fclose(pfoDebug);
   #endif

   audio_spec;
   free((void*)Caprice32_Autotype);

   SDL_Quit();
   CapAutoType_Term();
}

static bool is_numlock()
{
   return (SDL_GetModState() & KMOD_NUM) ? true : false;
}

#ifndef LOBYTE
   #define LOBYTE(w)           ((unsigned char)(w))
#endif
#ifndef HIBYTE
   #define HIBYTE(w)           ((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))
#endif

#ifndef MAKEWORD
   #define MAKEWORD(lo,hi)       ((unsigned short)(((unsigned char)(lo)) | ((unsigned short)((unsigned char)(hi))) << 8))
#endif

static int event2key (SDL_KeyboardEvent event)
{
   int key = CPC_KEY_NULL;
   if ( (event.keysym.sym >= SDLK_KP1) && (event.keysym.sym <= SDLK_KP9) && (!is_numlock()))
   {
      static const int map[] =
      {
         MAKEWORD(CPC_KEY_JOY_DOWN , CPC_KEY_JOY_LEFT ), // doesn't work too well
         MAKEWORD(CPC_KEY_JOY_DOWN , 0                ),
         MAKEWORD(CPC_KEY_JOY_DOWN , CPC_KEY_JOY_RIGHT), // doesn't work too well
         MAKEWORD(CPC_KEY_JOY_LEFT , 0                ),
         MAKEWORD(CPC_KEY_JOY_FIRE1, 0                ),
         MAKEWORD(CPC_KEY_JOY_RIGHT, 0                ),
         MAKEWORD(CPC_KEY_JOY_UP   , CPC_KEY_JOY_LEFT ), // doesn't work too well
         MAKEWORD(CPC_KEY_JOY_UP   , 0                ),
         MAKEWORD(CPC_KEY_JOY_UP   , CPC_KEY_JOY_RIGHT)  // doesn't work too well
      };
      key = map[event.keysym.sym - SDLK_KP1];
   }
   else if (event.keysym.sym < _countof(keyboard_translation))
   {
      key = keyboard_translation[event.keysym.sym];
   }
   return key;
}

static bool toggle_fullscreen()
{
   audio_pause();
   SDL_Delay(20);
   video_shutdown();
   CPC.scr_window = CPC.scr_window ? 0 : 1;
   if (video_init()) {
      fprintf(stderr, "video_init() failed. Aborting.\n");
      return false;
   }
   audio_resume();
   return true;
}

int caprice_main (int argc, TCHAR **argv, BOOL registry)
{
   uLong dwSndDist;
   int iExitCondition;
   bool bolDone;
   SDL_Event event;

   if(ALESTE)
	   alestePowerOn();
   if (SDL_Init(SDL_INIT_AUDIO) < 0) { // initialize SDL
      fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }

   _tgetcwd(chAppPath, sizeof(chAppPath)-1); // get the location of the executable

   loadConfiguration(&CPC, registry, chAppPath); // retrieve the emulator configuration
   if (CPC.printer) {
      if (!printer_start()) { // start capturing printer output, if enabled
         CPC.printer = 0;
      }
   }

   z80_init_tables(); // init Z80 emulation
   video_init_tables(); // generate the Byte-to-pixels translation tables

// init input

   if (video_init()) {
      fprintf(stderr, "video_init() failed. Aborting.\n");
      return EXIT_FAILURE;
   }

   if (audio_init()) {
      fprintf(stderr, "audio_init() failed. Disabling sound.\n");
      CPC.snd_enabled = 0; // disable sound emulation
   }

   if (emulator_init()) {
      fprintf(stderr, "emulator_init() failed. Aborting.\n");
      return EXIT_FAILURE;
   }

   #ifdef DEBUG
   pfoDebug = _tfopen("./debug.txt", "wt");
   #endif

   bool have_DSK = false;
   bool have_SNA = false;
   bool have_TAP = false;
   memset(&driveA, 0, sizeof(t_drive)); // clear disk drive A data structure
   for (int i = 1; i < argc; i++) { // loop for all command line arguments
      int length = _tcslen(argv[i]);
      if (length > 5) { // minumum for a valid filename
         TCHAR path[_MAX_PATH + 1];
         TCHAR extension[5];
         if (argv[i][0] == '"') { // argument passed with quotes?
            length -= 2;
            _tcsncpy(path, &argv[i][1], length); // strip the quotes
         } else {
            _tcsncpy(path, &argv[i][0], _countof(path)-1); // take it as is
         }
         int pos = length - 4;
         if (pos > 0) {
            TCHAR file_name[_MAX_PATH + 1];
            bool zip = false;
            _tcsncpy(extension, &path[pos], 4); // grab the extension
            extension[4] = '\0'; // zero terminate string
            if (strcasecmp(extension, _T(".zip")) == 0) { // are we dealing with a zip archive?
               zip_info.pchZipFile = path;
               zip_info.pchExtension = _T(".dsk.sna.cdt.voc");
               if (zip_dir(&zip_info)) {
                  continue; // error or nothing relevant found
               } else {
                  _tcsncpy(file_name, zip_info.pchFileNames, _countof(file_name)-1); // name of the 1st file in the archive
                  pos = _tcslen(file_name) - 4;
                  _tcsncpy(extension, &file_name[pos], 4); // grab the extension
                  zip = true;
               }
            } else {
               splitPathFileName(path, path, file_name); // split into components
            }
            if ((!have_DSK) && (strcasecmp(extension, _T(".dsk")) == 0)) { // a disk image?
               if (zip) {
                  TCHAR chFileName[_MAX_PATH + 1];
                  TCHAR *pchPtr = zip_info.pchFileNames;
                  zip_info.dwOffset = *(uLong *)(pchPtr + (_tcslen(pchPtr)+1)); // get the offset into the zip archive
                  if (!zip_extract(path, chFileName, zip_info.dwOffset, chAppPath)) {
                     if (!dsk_load(chFileName, &driveA, 'A')) {
                        _tcscpy(CPC.drvA_path, path); // if the image loads, copy the infos to the config structure
                        _tcscpy(CPC.drvA_file, file_name);
                        CPC.drvA_zip = 1;
                        have_DSK = true;
                     }
                     _tremove(chFileName);
                  }
               } else {
                  _tcscat(path, file_name);
                  if(!dsk_load(path, &driveA, 'A')) {
                     _tcscpy(CPC.drvA_path, path);
                     _tcscpy(CPC.drvA_file, file_name);
                     CPC.drvA_zip = 0;
                     have_DSK = true;
                  }
               }
            }
            if ((!have_SNA) && (strcasecmp(extension, _T(".sna")) == 0)) {
               if (zip) {
                  TCHAR chFileName[_MAX_PATH + 1];
                  TCHAR *pchPtr = zip_info.pchFileNames;
                  zip_info.dwOffset = *(uLong *)(pchPtr + (_tcslen(pchPtr)+1));
                  if (!zip_extract(path, chFileName, zip_info.dwOffset, chAppPath)) {
                     if (!snapshot_load(chFileName)) {
                        _tcscpy(CPC.snap_path, path);
                        _tcscpy(CPC.snap_file, file_name);
                        CPC.snap_zip = 1;
                        have_SNA = true;
                     }
                     _tremove(chFileName);
                  }
               } else {
                  _tcscat(path, file_name);
                  if(!snapshot_load(path)) {
                     _tcscpy(CPC.snap_path, path);
                     _tcscpy(CPC.snap_file, file_name);
                     CPC.snap_zip = 0;
                     have_SNA = true;
                  }
               }
            }
            if ((!have_TAP) && (strcasecmp(extension, _T(".cdt")) == 0)) {
               if (zip) {
                  TCHAR chFileName[_MAX_PATH + 1];
                  TCHAR *pchPtr = zip_info.pchFileNames;
                  zip_info.dwOffset = *(uLong *)(pchPtr + (_tcslen(pchPtr)+1));
                  if (!zip_extract(path, chFileName, zip_info.dwOffset, chAppPath)) {
                     if (!tape_insert(chFileName)) {
                        _tcscpy(CPC.tape_path, path);
                        _tcscpy(CPC.tape_file, file_name);
                        CPC.tape_zip = 1;
                        have_TAP = true;
                     }
                     _tremove(chFileName);
                  }
               } else {
                  _tcscat(path, file_name);
                  if(!tape_insert(path)) {
                     _tcscpy(CPC.tape_path, path);
                     _tcscpy(CPC.tape_file, file_name);
                     CPC.tape_zip = 0;
                     have_TAP = true;
                  }
               }
            }
            if ((!have_TAP) && (strcasecmp(extension, _T(".voc")) == 0)) {
               if (zip) {
                  TCHAR chFileName[_MAX_PATH + 1];
                  TCHAR *pchPtr = zip_info.pchFileNames;
                  zip_info.dwOffset = *(uLong *)(pchPtr + (_tcslen(pchPtr)+1));
                  if (!zip_extract(path, chFileName, zip_info.dwOffset, chAppPath)) {
                     if (!tape_insert_voc(chFileName)) {
                        _tcscpy(CPC.tape_path, path);
                        _tcscpy(CPC.tape_file, file_name);
                        CPC.tape_zip = 1;
                        have_TAP = true;
                     }
                     _tremove(chFileName);
                  }
               } else {
                  _tcscat(path, file_name);
                  if(!tape_insert_voc(path)) {
                     _tcscpy(CPC.tape_path, path);
                     _tcscpy(CPC.tape_file, file_name);
                     CPC.tape_zip = 0;
                     have_TAP = true;
                  }
               }
            }
         }
      }
   }

   if ((!have_DSK) && (CPC.drvA_file[0])) { // insert disk in drive A?
      TCHAR chFileName[_MAX_PATH + 1];
      TCHAR *pchPtr;

      if (CPC.drvA_zip) { // compressed image?
         zip_info.pchZipFile = CPC.drvA_path; // pchPath already has path and zip file combined
         zip_info.pchExtension = _T(".dsk");
         if (!zip_dir(&zip_info)) { // parse the zip for relevant files
            uLong n;
            pchPtr = zip_info.pchFileNames;
            for (n = zip_info.iFiles; n; n--) { // loop through all entries
               if (!strcasecmp(CPC.drvA_file, pchPtr)) { // do we have a match?
                  break;
               }
               pchPtr += _tcslen(pchPtr) + 5; // skip offset
            }
            if (n) {
               zip_info.dwOffset = *(uLong *)(pchPtr + (_tcslen(pchPtr)+1)); // get the offset into the zip archive
               if (!zip_extract(CPC.drvA_path, chFileName, zip_info.dwOffset, chAppPath)) {
                  dsk_load(chFileName, &driveA, 'A');
                  _tremove(chFileName);
               }
            }
         } else {
            CPC.drvA_zip = 0;
         }
      } else {
         _tcsncpy(chFileName, CPC.drvA_path, _countof(chFileName)-1);
         _tcsncat(chFileName, CPC.drvA_file, _countof(chFileName)-1 - _tcslen(chFileName));
         dsk_load(chFileName, &driveA, 'A');
      }
   }
   memset(&driveB, 0, sizeof(t_drive)); // clear disk drive B data structure
   if (CPC.drvB_file[0]) { // insert disk in drive B?
      TCHAR chFileName[_MAX_PATH + 1];
      TCHAR *pchPtr;

      if (CPC.drvB_zip) { // compressed image?
         zip_info.pchZipFile = CPC.drvB_path; // pchPath already has path and zip file combined
         zip_info.pchExtension = _T(".dsk");
         if (!zip_dir(&zip_info)) { // parse the zip for relevant files
            uLong n;
            pchPtr = zip_info.pchFileNames;
            for (n = zip_info.iFiles; n; n--) { // loop through all entries
               if (!strcasecmp(CPC.drvB_file, pchPtr)) { // do we have a match?
                  break;
               }
               pchPtr += _tcslen(pchPtr) + 5; // skip offset
            }
            if (n) {
               zip_info.dwOffset = *(uLong *)(pchPtr + (_tcslen(pchPtr)+1)); // get the offset into the zip archive
               if (!zip_extract(CPC.drvB_path, chFileName, zip_info.dwOffset, chAppPath)) {
                  dsk_load(chFileName, &driveB, 'B');
                  _tremove(chFileName);
               }
            }
         }
         else {
            CPC.drvB_zip = 0;
         }
      }
      else {
         _tcsncpy(chFileName, CPC.drvB_path, _countof(chFileName)-1);
         _tcsncat(chFileName, CPC.drvB_file, _countof(chFileName)-1 - _tcslen(chFileName));
         dsk_load(chFileName, &driveB, 'B');
      }
   }
   if ((!have_TAP) && (CPC.tape_file[0])) { // insert a tape?
      int iErrorCode = 0;
      TCHAR chFileName[_MAX_PATH + 1];
      TCHAR *pchPtr;

      if (CPC.tape_zip) { // compressed image?
         zip_info.pchZipFile = CPC.tape_path; // pchPath already has path and zip file combined
         zip_info.pchExtension = _T(".cdt.voc");
         iErrorCode = zip_dir(&zip_info);
         if (!iErrorCode) { // parse the zip for relevant files
            uLong n;
            pchPtr = zip_info.pchFileNames;
            for (n = zip_info.iFiles; n; n--) { // loop through all entries
               if (!strcasecmp(CPC.tape_file, pchPtr)) { // do we have a match?
                  break;
               }
               pchPtr += _tcslen(pchPtr) + 5; // skip offset
            }
            if (n) {
               zip_info.dwOffset = *(uLong *)(pchPtr + (_tcslen(pchPtr)+1)); // get the offset into the zip archive
               iErrorCode = zip_extract(CPC.tape_path, chFileName, zip_info.dwOffset, chAppPath);
            }
            else {
               CPC.tape_zip = 0;
               iErrorCode = 1; // file not found
            }
         }
         else {
            CPC.tape_zip = 0;
         }
      }
      else {
         _tcsncpy(chFileName, CPC.tape_path, _countof(chFileName)-1);
         _tcsncat(chFileName, CPC.tape_file, _countof(chFileName)-1 - _tcslen(chFileName));
      }
      if (!iErrorCode) {
         int iOffset = _tcslen(CPC.tape_file) - 3;
         TCHAR *pchExt = &CPC.tape_file[iOffset > 0 ? iOffset : 0]; // pointer to the extension
         if (strncasecmp(pchExt, _T("cdt"), 3) == 0) { // is it a cdt file?
            iErrorCode = tape_insert(chFileName);
         }
         else if (strncasecmp(pchExt, _T("voc"), 3) == 0) { // is it a voc file?
            iErrorCode = tape_insert_voc(chFileName);
         }
         if (CPC.tape_zip) {
            _tremove(chFileName); // dispose of the temp file
         }
      }
   }

// ----------------------------------------------------------------------------

   dwTicksOffset = (int)(20.0 / (double)((CPC.speed * 25) / 100.0));
   dwTicksTarget = SDL_GetTicks();
   dwTicksTargetFPS = dwTicksTarget;
   dwTicksTarget += dwTicksOffset;

   audio_resume();

   iExitCondition = EC_FRAME_COMPLETE;
   bolDone = false;

   CapAutoType_Init();
   if (Caprice32_Autotype&& *Caprice32_Autotype) CapAutoType_SetString(Caprice32_Autotype, FALSE);

   while (!bolDone) {
      while (SDL_PollEvent(&event)) {
         switch (event.type) {
            case SDL_KEYDOWN:
               {
                  const int cpc_key = event2key(event.key); // translate the PC key to a CPC key
                  if ((cpc_key != CPC_KEY_NULL) && (!CPC.paused))
                  {
                     key_add(LOBYTE(cpc_key));
                     if (HIBYTE(cpc_key)) key_add(HIBYTE(cpc_key));
                  }
               }
               break;

            case SDL_KEYUP:
               {
                  const int cpc_key = event2key(event.key); // translate the PC key to a CPC key
                  if ((!CPC.paused) && (cpc_key != CPC_KEY_NULL)) {
                        key_remove(LOBYTE(cpc_key));
                        if (HIBYTE(cpc_key)) key_remove(HIBYTE(cpc_key));
                  } else { // process non-CPC keys
                     switch ((int)event.key.keysym.sym) {

                        case CAP32_FULLSCRN:
                           if (!toggle_fullscreen()) return EXIT_FAILURE;
                           break;

                        case CAP32_LOADTAPE:
                           if (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) {
                              if (pbTapeImage) {
                                 if (CPC.tape_play_button) {
                                    CPC.tape_play_button = 0;
                                 } else {
                                    CPC.tape_play_button = 0x10;
                                 }
                              }
                           }
                           break;
                        case CAP32_LOADDRVA:

							if(!((int)event.key.keysym.mod & KMOD_SHIFT))
							{
								TCHAR sz[_MAX_PATH] = _T("");
								if (!CPC.scr_window) toggle_fullscreen();
								if (browse_for_dsk(sz, _countof(sz), CPC.drvA_path, _T("Insert Disk - Drive A"), CAPTION))
								{
									if (0 == dsk_load(sz, &driveA, 'A'))
									{
										/*CapAutoType_SetString(_T("|A:CAT"), FALSE);*/
									}
								}
							} else {
								TCHAR sz[_MAX_PATH] = _T("");
								if (!CPC.scr_window) toggle_fullscreen();
								if (browse_for_dsk(sz, _countof(sz), CPC.drvA_path, _T("Insert Disk - Drive A"), CAPTION))
								{
									if (0 == dsk_save(sz, &driveA, 'A'))
									{
										/*CapAutoType_SetString(_T("|B:CAT"), FALSE);*/
									}
								}
	                        }

                           break;
                        case CAP32_SCRNSHOT:
                        {
                           TCHAR sz[_MAX_PATH];
                           TCHAR* sep;

                           _tcscpy(sz, CPC.drvA_file);
                           sep = _tcsrchr(sz, '.');
                           if (sep) *sep = 0;
                           
                           if (!CPC.scr_window) toggle_fullscreen();
                           if (browse_for_bmp(sz, _countof(sz), CPC.sdump_path, _T("Save Screenshot"), CAPTION))
                           {
                           #if defined(UNICODE) || defined(_UNICODE)
                              char temp[_MAX_PATH];
                              wcstombs(temp, sz, _countof(temp));
                              SDL_SaveBMP(video_surface, temp);
                           #else
                              SDL_SaveBMP(video_surface, sz);
                           #endif
                              CPC.sdump_file;
                           }
                           break;
                        }
                        case CAP32_LOADSNAP:
                        if(!((int)event.key.keysym.mod & KMOD_SHIFT)) {
                           TCHAR sz[_MAX_PATH] = _T("");
                           if (!CPC.scr_window) toggle_fullscreen();
                           if (browse_for_snap(sz, _countof(sz), CPC.snap_path, _T("Load Snapshot"), CAPTION, FALSE))
                           {
                              snapshot_load(sz);
                           }
						} else 
						{
                           TCHAR sz[_MAX_PATH];
                           TCHAR* sep;

                           _tcscpy(sz, CPC.drvA_file);
                           sep = _tcsrchr(sz, '.');
                           if (sep) *sep = 0;

                           if (!CPC.scr_window) toggle_fullscreen();
                           if (browse_for_snap(sz, _countof(sz), CPC.snap_path, _T("Save Snapshot"), CAPTION, TRUE))
                           {
							   snapshot_save(sz, CPC.ram_size);
                           }
                        }
                           break;
                        case CAP32_RESET:
							{
								if((int)event.key.keysym.mod & KMOD_SHIFT) {
									if (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) {
										CPC.scr_fps = CPC.scr_fps ? 0 : 1; // toggle fps display on or off
									} else {
										CPC.limit_speed = CPC.limit_speed ? 0 : 1;
									}
								} else {
									emulator_reset(false);
								}
							}
							break;
                        case CAP32_PAUSE:
                           CPC.paused = !CPC.paused;
                           break;
                        case CAP32_EXIT:
                           return EXIT_SUCCESS;

                     }
                  }
               }
               break;

            case SDL_QUIT:
               return EXIT_SUCCESS;
            default:
               break;
         }
      }

      if (!CPC.paused) { // run the emulation, as long as the user doesn't pause it
         
         if (CapAutoType_Active() && KeyboardScanned)
         {
            CapAutoType_Update();
            KeyboardScanned = false;
         }         
         
         dwTicks = SDL_GetTicks();
         if (dwTicks >= dwTicksTargetFPS) { // update FPS counter?
            dwFPS = dwFrameCount;
            dwFrameCount = 0;
            dwTicksTargetFPS = dwTicks + 1000; // prep counter for the next run
         }

         if ((CPC.limit_speed) && (iExitCondition == EC_CYCLE_COUNT)) {
            int iTicksAdj = 0; // no adjustment necessary by default
            if (CPC.snd_enabled) {
               if (pbSndStream < CPC.snd_bufferptr) {
                  dwSndDist = CPC.snd_bufferptr - pbSndStream; // determine distance between play and write cursors
               } else {
                  dwSndDist = (pbSndBufferEnd - pbSndStream) + (CPC.snd_bufferptr - pbSndBuffer);
               }
               if (dwSndDist < dwSndMinSafeDist) {
                  iTicksAdj = -5; // speed emulation up to compensate
               } else if (dwSndDist > dwSndMaxSafeDist) {
                  iTicksAdj = 5; // slow emulation down to compensate
               }
            }
            dwTicks = SDL_GetTicks();
            if (dwTicks < (dwTicksTarget+iTicksAdj)) { // limit speed?
               continue; // delay emulation
            }
            dwTicksTarget = dwTicks + dwTicksOffset; // prep counter for the next run
         }

         if (SDL_MUSTLOCK(back_surface)) {
            if (SDL_LockSurface(back_surface) < 0) { // lock the video buffer
               continue; // skip the emulation if we can't get a lock
            }
         }
         if (iExitCondition == EC_FRAME_COMPLETE) { // did the last call blit the video buffer?
            CPC.scr_base = (uInt*)back_surface->pixels; // begin drawing the next frame
         }

         iExitCondition = z80_execute(); // run the emulation until an exit condition is met

         if (iExitCondition == EC_FRAME_COMPLETE) { // emulation finished rendering a complete frame?
            dwFrameCount++;
            if (CPC.scr_fps) {
               char chStr[15];
               sprintf(chStr, "%3dFPS %3d%%", (int)dwFPS, (int)dwFPS * 100 / 50);
               print((uLong *)back_surface->pixels + CPC.scr_line_offs, chStr, true); // display the frames per second counter
            }
            if (SDL_MUSTLOCK(back_surface)) {
               SDL_UnlockSurface(back_surface); // release the lock on the video buffer
            }
            video_display(); // update PC display
         } else {
            if (SDL_MUSTLOCK(back_surface)) {
               SDL_UnlockSurface(back_surface); // release the lock on the video buffer
            }
         }
      }
   }
   return EXIT_SUCCESS;
}
