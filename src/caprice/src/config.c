/* config.c */

#include "cap32.h"
#include <stdlib.h>
#include <string.h>

#define MIN_SPEED_SETTING 2
#define MAX_SPEED_SETTING 32
#define DEF_SPEED_SETTING 4
#define MAX_LINE_LEN 256

#if USE_CFGAPI

#include "..\..\cfgapi\cfg_file.h"
#include "..\..\cfgapi\cfg_reg.h"

const TCHAR* Caprice32_Profile = _T("Caprice32");

void loadConfiguration(t_CPC* CPC, BOOL registry, const TCHAR* chAppPath)
{
   CFGHANDLE profile;
   TCHAR chFileName[_MAX_PATH + 1];
   TCHAR chPath[_MAX_PATH + 1];

   _tcsncpy(chFileName, chAppPath, _countof(chFileName)-10);
   _tcscat(chFileName, _T("/cap32.cfg"));
   memset(CPC, 0, sizeof(*CPC));

#ifdef _WIN32
   if (registry)
   {
      TCHAR sz[80];
      _sntprintf(sz, _countof(sz), _T("Software\\%s"), Caprice32_Profile);
      profile = cfg_reg_topen(NULL, sz);
   }
   else
#endif
   {
      profile = cfg_ini_topen(chFileName, NULL, NULL, TRUE);
   }

   if (CFG_SETSECTION(profile, _T("system")))
   {
      CPC->model = CFG_GETLONG(profile, _T("model"), 2); // CPC 6128
      if (CPC->model > 2) {
         CPC->model = 2;
      }
      CPC->jumpers  = CFG_GETLONG(profile, _T("jumpers"), 0x1e) & 0x1e; // OEM is Amstrad, video refresh is 50Hz
      CPC->ram_size = CFG_GETLONG(profile, _T("ram_size"), 128) & 0x02c0; // 128KB RAM
      if (CPC->ram_size > 576) {
         CPC->ram_size = 576;
      } else if ((CPC->model == 2) && (CPC->ram_size < 128)) {
         CPC->ram_size = 128; // minimum RAM size for CPC 6128 is 128KB
      }
      CPC->speed = CFG_GETLONG(profile, _T("speed"), DEF_SPEED_SETTING); // original CPC speed
      if ((CPC->speed < MIN_SPEED_SETTING) || (CPC->speed > MAX_SPEED_SETTING)) {
         CPC->speed = DEF_SPEED_SETTING;
      }
      CPC->limit_speed = 1;
      CPC->auto_pause = CFG_GETLONG(profile, _T("auto_pause"), 1) & 1;
      CPC->printer    = CFG_GETLONG(profile, _T("printer"   ), 0) & 1;
      CPC->mf2        = CFG_GETLONG(profile, _T("mf2"       ), 0) & 1;
      CPC->joysticks  = CFG_GETLONG(profile, _T("joysticks" ), 1) & 1;
   }

   if (CFG_SETSECTION(profile, _T("video")))
   {
      CPC->scr_fs_width  = CFG_GETLONG(profile, _T("scr_width" ), 800);
      CPC->scr_fs_height = CFG_GETLONG(profile, _T("scr_height"), 600);
      CPC->scr_fs_bpp    = CFG_GETLONG(profile, _T("scr_bpp"   ), 8);
      CPC->scr_style     = CFG_GETLONG(profile, _T("scr_style" ), 0);
      if (CPC->scr_style > 3) {
         CPC->scr_style = 0;
      }
      CPC->scr_vsync     = CFG_GETLONG(profile, _T("scr_vsync"), 1) & 1;
      CPC->scr_led       = CFG_GETLONG(profile, _T("scr_led"  ), 1) & 1;
      CPC->scr_fps       = CFG_GETLONG(profile, _T("scr_fps"  ), 0) & 1;
      CPC->scr_tube      = CFG_GETLONG(profile, _T("scr_tube" ), 0) & 1;
      CPC->scr_intensity = CFG_GETLONG(profile, _T("scr_intensity"), 10);
      if ((CPC->scr_intensity < 5) || (CPC->scr_intensity > 15)) {
         CPC->scr_intensity = 10;
      }
      CPC->scr_window = CFG_GETLONG(profile, _T("scr_window"), 0) & 1;
      CPC->default_mode = CFG_GETLONG(profile, _T("mode"), 1);
   }

   if (CFG_SETSECTION(profile, _T("sound")))
   {
      CPC->snd_enabled         = CFG_GETLONG(profile, _T("enabled"), 1) & 1;
      CPC->snd_playback_rate   = CFG_GETLONG(profile, _T("playback_rate"), 2);
      if (CPC->snd_playback_rate > (MAX_FREQ_ENTRIES-1)) {
         CPC->snd_playback_rate = 2;
      }
      CPC->snd_bits   = CFG_GETLONG(profile, _T("bits"  ), 1) & 1;
      CPC->snd_stereo = CFG_GETLONG(profile, _T("stereo"), 1) & 1;
      CPC->snd_volume = CFG_GETLONG(profile, _T("volume"), 80);
      if ((CPC->snd_volume < 0) || (CPC->snd_volume > 100)) {
         CPC->snd_volume = 80;
      }
      CPC->snd_pp_device = CFG_GETLONG(profile, _T("pp_device"), 0) & 1;
   }

   if (CFG_SETSECTION(profile, _T("control")))
   {
      CPC->kbd_layout = CFG_GETLONG(profile, _T("kbd_layout"), 0);
      if (CPC->kbd_layout > MAX_KBD_LAYOUTS) {
         CPC->kbd_layout = 0;
      }
   }

   if (CFG_SETSECTION(profile, _T("file")))
   {
      int i;
      int iFmt = FIRST_CUSTOM_DISK_FORMAT;

      CPC->max_tracksize = CFG_GETLONG(profile, _T("max_track_size"), 6144-154);
      _tcsncpy(chPath, chAppPath, _countof(chPath)-7);
      _tcscat(chPath, _T("/snap"));
      CFG_GETSTRING(profile, _T("snap_path"), CPC->snap_path, _countof(CPC->snap_path)-1, chPath);
      if (CPC->snap_path[0] == '\0') {
         _tcscpy(CPC->snap_path, chPath);
      }
      CFG_GETSTRING(profile, _T("snap_file"), CPC->snap_file, _countof(CPC->snap_file)-1, _T(""));
      CPC->snap_zip = CFG_GETLONG(profile, _T("snap_zip"), 0) & 1;
      _tcsncpy(chPath, chAppPath, _countof(chPath)-7);
      _tcscat(chPath, _T("/disk"));
      CFG_GETSTRING(profile, _T("drvA_path"), CPC->drvA_path, _countof(CPC->drvA_path)-1, chPath);
      if (CPC->drvA_path[0] == '\0') {
         _tcscpy(CPC->drvA_path, chPath);
      }
      CFG_GETSTRING(profile, _T("drvA_file"), CPC->drvA_file, _countof(CPC->drvA_file)-1, _T(""));
      CPC->drvA_zip    = CFG_GETLONG(profile, _T("drvA_zip"), 0) & 1;
      CPC->drvA_format = CFG_GETLONG(profile, _T("drvA_format"), DEFAULT_DISK_FORMAT);
      CFG_GETSTRING(profile, _T("drvB_path"), CPC->drvB_path, _countof(CPC->drvB_path)-1, chPath);
      if (CPC->drvB_path[0] == '\0') {
         _tcscpy(CPC->drvB_path, chPath);
      }
      CFG_GETSTRING(profile, _T("drvB_file"), CPC->drvB_file, _countof(CPC->drvB_file)-1, _T(""));
      CPC->drvB_zip    = CFG_GETLONG(profile, _T("drvB_zip"   ), 0) & 1;
      CPC->drvB_format = CFG_GETLONG(profile, _T("drvB_format"), DEFAULT_DISK_FORMAT);
      _tcsncpy(chPath, chAppPath, _countof(chPath)-7);
      _tcscat(chPath, _T("/tape"));
      CFG_GETSTRING(profile, _T("tape_path"), CPC->tape_path, _countof(CPC->tape_path)-1, chPath);
      if (CPC->tape_path[0] == '\0') {
         _tcscpy(CPC->tape_path, chPath);
      }
      CFG_GETSTRING(profile, _T("tape_file"), CPC->tape_file, _countof(CPC->tape_file)-1, _T(""));
      CPC->tape_zip = CFG_GETLONG(profile, _T("tape_zip"), 0) & 1;

      for (i = iFmt; i < MAX_DISK_FORMAT; i++) { // loop through all user definable disk formats
         TCHAR chFmtStr[256];
         uLong dwVal;
         TCHAR *pchTail;
         TCHAR chFmtId[14];
         disk_format[iFmt].label[0] = 0; // clear slot
         _sntprintf(chFmtId, _countof(chFmtId), _T("fmt%02d"), i); // build format ID
         CFG_GETSTRING(profile, chFmtId, chFmtStr, _countof(chFmtStr)-1, _T(""));
         if (chFmtStr[0] != 0) { // found format definition for this slot?
            int iSide, iSector;
            TCHAR chDelimiters[] = _T(",");
            TCHAR *pchToken;
            pchToken = _tcstok(chFmtStr, chDelimiters); // format label
            _tcsncpy((TCHAR*)disk_format[iFmt].label, pchToken, _countof(disk_format[iFmt].label)-1);
            pchToken = _tcstok(NULL, chDelimiters); // number of tracks
            if (pchToken == NULL) { // value missing?
               continue;
            }
            dwVal = _tcstoul(pchToken, &pchTail, 0);
            if ((dwVal < 1) || (dwVal > DSK_TRACKMAX)) { // invalid value?
               continue;
            }
            disk_format[iFmt].tracks = dwVal;
            pchToken = _tcstok(NULL, chDelimiters); // number of sides
            if (pchToken == NULL) { // value missing?
               continue;
            }
            dwVal = _tcstoul(pchToken, &pchTail, 0);
            if ((dwVal < 1) || (dwVal > DSK_SIDEMAX)) { // invalid value?
               continue;
            }
            disk_format[iFmt].sides = dwVal;
            pchToken = _tcstok(NULL, chDelimiters); // number of sectors
            if (pchToken == NULL) { // value missing?
               continue;
            }
            dwVal = _tcstoul(pchToken, &pchTail, 0);
            if ((dwVal < 1) || (dwVal > DSK_SECTORMAX)) { // invalid value?
               continue;
            }
            disk_format[iFmt].sectors = dwVal;
            pchToken = _tcstok(NULL, chDelimiters); // sector size as N value
            if (pchToken == NULL) { // value missing?
               continue;
            }
            dwVal = _tcstoul(pchToken, &pchTail, 0);
            if ((dwVal < 1) || (dwVal > 6)) { // invalid value?
               continue;
            }
            disk_format[iFmt].sector_size = dwVal;
            pchToken = _tcstok(NULL, chDelimiters); // gap#3 length
            if (pchToken == NULL) { // value missing?
               continue;
            }
            dwVal = _tcstoul(pchToken, &pchTail, 0);
            if ((dwVal < 1) || (dwVal > 255)) { // invalid value?
               continue;
            }
            disk_format[iFmt].gap3_length = dwVal;
            pchToken = _tcstok(NULL, chDelimiters); // filler Byte
            if (pchToken == NULL) { // value missing?
               continue;
            }
            dwVal = _tcstoul(pchToken, &pchTail, 0);
            disk_format[iFmt].filler_byte = (Byte)dwVal;
            for (iSide = 0; iSide < (int)disk_format[iFmt].sides; iSide++) {
               for (iSector = 0; iSector < (int)disk_format[iFmt].sectors; iSector++) {
                  pchToken = _tcstok(NULL, chDelimiters); // sector ID
                  if (pchToken == NULL) { // value missing?
                     dwVal = iSector+1;
                  } else {
                     dwVal = _tcstoul(pchToken, &pchTail, 0);
                  }
                  disk_format[iFmt].sector_ids[iSide][iSector] = (Byte)dwVal;
               }
            }
            iFmt++; // entry is valid
         }
      }
      _tcsncpy(chPath, chAppPath, _countof(chPath)-13);
      _tcscat(chPath, _T("/printer.dat"));
      CFG_GETSTRING(profile, _T("printer_file"), CPC->printer_file, _countof(CPC->printer_file)-1, chPath);
      if (CPC->printer_file[0] == '\0') {
         _tcscpy(CPC->printer_file, chPath);
      }
      _tcsncpy(chPath, chAppPath, _countof(chPath)-12);
      _tcscat(chPath, _T("/screen.png"));

      CFG_GETSTRING(profile, _T("sdump_path"), CPC->sdump_path, _countof(CPC->sdump_path)-1, chPath);
      if (*CPC->sdump_path == 0) _tcscpy(CPC->sdump_path, chPath);
      
      CFG_GETSTRING(profile, _T("sdump_file"), CPC->sdump_file, _countof(CPC->sdump_file)-1, chPath);
      if (*CPC->sdump_file == 0) _tcscpy(CPC->sdump_file, chPath);
   }

   if (CFG_SETSECTION(profile, _T("rom")))
   {
      int iRomNum;
      FILE* pfileObject;
      _tcsncpy(chPath, chAppPath, _countof(chPath)-5);
      _tcscat(chPath, _T("/rom"));
      CFG_GETSTRING(profile, _T("rom_path"), CPC->rom_path, _countof(CPC->rom_path)-1, chPath);
      for (iRomNum = 2; iRomNum < 16; iRomNum++) { // loop for ROMs 2-15
         TCHAR chRomId[14];
         _sntprintf(chRomId, _countof(chRomId), _T("slot%02d"), iRomNum); // build ROM ID
         CFG_GETSTRING(profile, chRomId, CPC->rom_file[iRomNum], _countof(CPC->rom_file[iRomNum])-1, _T(""));
      }
      if (CPC->rom_path[0] == '\0') { // if the path is empty, set it to the default
         _tcscpy(CPC->rom_path, chPath);
      }
      pfileObject = _tfopen(chFileName, _T("rt"));
      if (pfileObject == NULL) {
         _tcscpy(CPC->rom_file[7], _T(AMSDOS)); // insert AMSDOS in slot 7 if the config file does not exist yet
      } else {
         fclose(pfileObject);
      }
      CFG_GETSTRING(profile, _T("rom_mf2"), CPC->rom_mf2, _countof(CPC->rom_mf2)-1, _T(""));
   }
   CFG_CLOSE(&profile);
}

#else /* USE_CFGAPI=0 */

static int getConfigValueInt (char* pchFileName, char* pchSection, char* pchKey, int iDefaultValue)
{
   FILE* pfoConfigFile;
   char chLine[MAX_LINE_LEN + 1];
   char* pchToken;

   if ((pfoConfigFile = fopen(pchFileName, "r")) != NULL) { // open the config file
      while(fgets(chLine, MAX_LINE_LEN, pfoConfigFile) != NULL) { // grab one line
         pchToken = strtok(chLine, "[]"); // check if there's a section key
         if((pchToken != NULL) && (pchToken[0] != '#') && (strcmp(pchToken, pchSection) == 0)) {
            while(fgets(chLine, MAX_LINE_LEN, pfoConfigFile) != NULL) { // get the next line
               pchToken = strtok(chLine, "\t =\n\r"); // check if it has a key=value pair
               if((pchToken != NULL) && (pchToken[0] != '#') && (strcmp(pchToken, pchKey) == 0)) {
                  char* pchPtr = strtok(NULL, "\t =#\n\r"); // get the value if it matches our key
                  if (pchPtr != NULL) {
                     return (strtol(pchPtr, NULL, 0)); // return as integer
                  } else {
                     return iDefaultValue; // no value found
                  }
               }
            }
         }
      }
      fclose(pfoConfigFile);
   }
   return iDefaultValue; // no value found
}

static void getConfigValueString (char* pchFileName, char* pchSection, char* pchKey, char* pchValue, int iSize, char* pchDefaultValue)
{
   FILE* pfoConfigFile;
   char chLine[MAX_LINE_LEN + 1];
   char* pchToken;

   if ((pfoConfigFile = fopen(pchFileName, "r")) != NULL) { // open the config file
      while(fgets(chLine, MAX_LINE_LEN, pfoConfigFile) != NULL) { // grab one line
         pchToken = strtok(chLine, "[]"); // check if there's a section key
         if((pchToken != NULL) && (pchToken[0] != '#') && (strcmp(pchToken, pchSection) == 0)) {
            while(fgets(chLine, MAX_LINE_LEN, pfoConfigFile) != NULL) { // get the next line
               pchToken = strtok(chLine, "\t =\n\r"); // check if it has a key=value pair
               if((pchToken != NULL) && (pchToken[0] != '#') && (strcmp(pchToken, pchKey) == 0)) {
                  char* pchPtr = strtok(NULL, "\t=#\n\r"); // get the value if it matches our key
                  if (pchPtr != NULL) {
                     strncpy(pchValue, pchPtr, iSize); // copy to destination
                     return;
                  } else {
                     strncpy(pchValue, pchDefaultValue, iSize); // no value found, return the default
                     return;
                  }
               }
            }
         }
      }
      fclose(pfoConfigFile);
   }
   strncpy(pchValue, pchDefaultValue, iSize); // no value found, return the default
}

void loadConfiguration(t_CPC* CPC, BOOL registry, const TCHAR* chAppPath)
{
   int i;
   int iFmt = FIRST_CUSTOM_DISK_FORMAT;
   int iRomNum;
   FILE* pfileObject;
   char chFileName[_MAX_PATH + 1];
   char chPath[_MAX_PATH + 1];

   strncpy(chFileName, chAppPath, sizeof(chFileName)-10);
   strcat(chFileName, "/cap32.cfg");

   memset(CPC, 0, sizeof(*CPC));
   CPC->model = getConfigValueInt(chFileName, "system", "model", 2); // CPC 6128
   if (CPC->model > 2) {
      CPC->model = 2;
   }
   CPC->jumpers = getConfigValueInt(chFileName, "system", "jumpers", 0x1e) & 0x1e; // OEM is Amstrad, video refresh is 50Hz
   CPC->ram_size = getConfigValueInt(chFileName, "system", "ram_size", 128) & 0x02c0; // 128KB RAM
   if (CPC->ram_size > 576) {
      CPC->ram_size = 576;
   } else if ((CPC->model == 2) && (CPC->ram_size < 128)) {
      CPC->ram_size = 128; // minimum RAM size for CPC 6128 is 128KB
   }
   CPC->speed = getConfigValueInt(chFileName, "system", "speed", DEF_SPEED_SETTING); // original CPC speed
   if ((CPC->speed < MIN_SPEED_SETTING) || (CPC->speed > MAX_SPEED_SETTING)) {
      CPC->speed = DEF_SPEED_SETTING;
   }
   CPC->limit_speed = 1;
   CPC->auto_pause = getConfigValueInt(chFileName, "system", "auto_pause", 1) & 1;
   CPC->printer = getConfigValueInt(chFileName, "system", "printer", 0) & 1;
   CPC->mf2 = getConfigValueInt(chFileName, "system", "mf2", 0) & 1;
   CPC->joysticks = getConfigValueInt(chFileName, "system", "joysticks", 1) & 1;

   CPC->scr_fs_width = getConfigValueInt(chFileName, "video", "scr_width", 800);
   CPC->scr_fs_height = getConfigValueInt(chFileName, "video", "scr_height", 600);
   CPC->scr_fs_bpp = getConfigValueInt(chFileName, "video", "scr_bpp", 8);
   CPC->scr_style = getConfigValueInt(chFileName, "video", "scr_style", 0);
   if (CPC->scr_style > 3) {
      CPC->scr_style = 0;
   }
   CPC->scr_vsync = getConfigValueInt(chFileName, "video", "scr_vsync", 1) & 1;
   CPC->scr_led = getConfigValueInt(chFileName, "video", "scr_led", 1) & 1;
   CPC->scr_fps = getConfigValueInt(chFileName, "video", "scr_fps", 0) & 1;
   CPC->scr_tube = getConfigValueInt(chFileName, "video", "scr_tube", 0) & 1;
   CPC->scr_intensity = getConfigValueInt(chFileName, "video", "scr_intensity", 10);
   if ((CPC->scr_intensity < 5) || (CPC->scr_intensity > 15)) {
      CPC->scr_intensity = 10;
   }
   CPC->scr_window = getConfigValueInt(chFileName, "video", "scr_window", 0) & 1;
   CPC->default_mode = getConfigValueInt(chFileName, "video", "mode", 1);

   CPC->snd_enabled = getConfigValueInt(chFileName, "sound", "enabled", 1) & 1;
   CPC->snd_playback_rate = getConfigValueInt(chFileName, "sound", "playback_rate", 2);
   if (CPC->snd_playback_rate > (MAX_FREQ_ENTRIES-1)) {
      CPC->snd_playback_rate = 2;
   }
   CPC->snd_bits = getConfigValueInt(chFileName, "sound", "bits", 1) & 1;
   CPC->snd_stereo = getConfigValueInt(chFileName, "sound", "stereo", 1) & 1;
   CPC->snd_volume = getConfigValueInt(chFileName, "sound", "volume", 80);
   if ((CPC->snd_volume < 0) || (CPC->snd_volume > 100)) {
      CPC->snd_volume = 80;
   }
   CPC->snd_pp_device = getConfigValueInt(chFileName, "sound", "pp_device", 0) & 1;

   CPC->kbd_layout = getConfigValueInt(chFileName, "control", "kbd_layout", 0);
   if (CPC->kbd_layout > MAX_KBD_LAYOUTS) {
      CPC->kbd_layout = 0;
   }

   CPC->max_tracksize = getConfigValueInt(chFileName, "file", "max_track_size", 6144-154);
   strncpy(chPath, chAppPath, sizeof(chPath)-7);
   strcat(chPath, "/snap");
   getConfigValueString(chFileName, "file", "snap_path", CPC->snap_path, sizeof(CPC->snap_path)-1, chPath);
   if (CPC->snap_path[0] == '\0') {
      strcpy(CPC->snap_path, chPath);
   }
   getConfigValueString(chFileName, "file", "snap_file", CPC->snap_file, sizeof(CPC->snap_file)-1, "");
   CPC->snap_zip = getConfigValueInt(chFileName, "file", "snap_zip", 0) & 1;
   strncpy(chPath, chAppPath, sizeof(chPath)-7);
   strcat(chPath, "/disk");
   getConfigValueString(chFileName, "file", "drvA_path", CPC->drvA_path, sizeof(CPC->drvA_path)-1, chPath);
   if (CPC->drvA_path[0] == '\0') {
      strcpy(CPC->drvA_path, chPath);
   }
   getConfigValueString(chFileName, "file", "drvA_file", CPC->drvA_file, sizeof(CPC->drvA_file)-1, "");
   CPC->drvA_zip = getConfigValueInt(chFileName, "file", "drvA_zip", 0) & 1;
   CPC->drvA_format = getConfigValueInt(chFileName, "file", "drvA_format", DEFAULT_DISK_FORMAT);
   getConfigValueString(chFileName, "file", "drvB_path", CPC->drvB_path, sizeof(CPC->drvB_path)-1, chPath);
   if (CPC->drvB_path[0] == '\0') {
      strcpy(CPC->drvB_path, chPath);
   }
   getConfigValueString(chFileName, "file", "drvB_file", CPC->drvB_file, sizeof(CPC->drvB_file)-1, "");
   CPC->drvB_zip = getConfigValueInt(chFileName, "file", "drvB_zip", 0) & 1;
   CPC->drvB_format = getConfigValueInt(chFileName, "file", "drvB_format", DEFAULT_DISK_FORMAT);
   strncpy(chPath, chAppPath, sizeof(chPath)-7);
   strcat(chPath, "/tape");
   getConfigValueString(chFileName, "file", "tape_path", CPC->tape_path, sizeof(CPC->tape_path)-1, chPath);
   if (CPC->tape_path[0] == '\0') {
      strcpy(CPC->tape_path, chPath);
   }
   getConfigValueString(chFileName, "file", "tape_file", CPC->tape_file, sizeof(CPC->tape_file)-1, "");
   CPC->tape_zip = getConfigValueInt(chFileName, "file", "tape_zip", 0) & 1;

   for (i = iFmt; i < MAX_DISK_FORMAT; i++) { // loop through all user definable disk formats
      char chFmtStr[256];
      uLong dwVal;
      char *pchTail;
      char chFmtId[14];
      disk_format[iFmt].label[0] = 0; // clear slot
      sprintf(chFmtId, "fmt%02d", i); // build format ID
      getConfigValueString(chFileName, "file", chFmtId, chFmtStr, sizeof(chFmtStr)-1, "");
      if (chFmtStr[0] != 0) { // found format definition for this slot?
         int iSide, iSector;
         char chDelimiters[] = ",";
         char *pchToken;
         pchToken = strtok(chFmtStr, chDelimiters); // format label
         strncpy((char *)disk_format[iFmt].label, pchToken, sizeof(disk_format[iFmt].label)-1);
         pchToken = strtok(NULL, chDelimiters); // number of tracks
         if (pchToken == NULL) { // value missing?
            continue;
         }
         dwVal = strtoul(pchToken, &pchTail, 0);
         if ((dwVal < 1) || (dwVal > DSK_TRACKMAX)) { // invalid value?
            continue;
         }
         disk_format[iFmt].tracks = dwVal;
         pchToken = strtok(NULL, chDelimiters); // number of sides
         if (pchToken == NULL) { // value missing?
            continue;
         }
         dwVal = strtoul(pchToken, &pchTail, 0);
         if ((dwVal < 1) || (dwVal > DSK_SIDEMAX)) { // invalid value?
            continue;
         }
         disk_format[iFmt].sides = dwVal;
         pchToken = strtok(NULL, chDelimiters); // number of sectors
         if (pchToken == NULL) { // value missing?
            continue;
         }
         dwVal = strtoul(pchToken, &pchTail, 0);
         if ((dwVal < 1) || (dwVal > DSK_SECTORMAX)) { // invalid value?
            continue;
         }
         disk_format[iFmt].sectors = dwVal;
         pchToken = strtok(NULL, chDelimiters); // sector size as N value
         if (pchToken == NULL) { // value missing?
            continue;
         }
         dwVal = strtoul(pchToken, &pchTail, 0);
         if ((dwVal < 1) || (dwVal > 6)) { // invalid value?
            continue;
         }
         disk_format[iFmt].sector_size = dwVal;
         pchToken = strtok(NULL, chDelimiters); // gap#3 length
         if (pchToken == NULL) { // value missing?
            continue;
         }
         dwVal = strtoul(pchToken, &pchTail, 0);
         if ((dwVal < 1) || (dwVal > 255)) { // invalid value?
            continue;
         }
         disk_format[iFmt].gap3_length = dwVal;
         pchToken = strtok(NULL, chDelimiters); // filler Byte
         if (pchToken == NULL) { // value missing?
            continue;
         }
         dwVal = strtoul(pchToken, &pchTail, 0);
         disk_format[iFmt].filler_byte = (Byte)dwVal;
         for (iSide = 0; iSide < (int)disk_format[iFmt].sides; iSide++) {
            for (iSector = 0; iSector < (int)disk_format[iFmt].sectors; iSector++) {
               pchToken = strtok(NULL, chDelimiters); // sector ID
               if (pchToken == NULL) { // value missing?
                  dwVal = iSector+1;
               } else {
                  dwVal = strtoul(pchToken, &pchTail, 0);
               }
               disk_format[iFmt].sector_ids[iSide][iSector] = (Byte)dwVal;
            }
         }
         iFmt++; // entry is valid
      }
   }
   strncpy(chPath, chAppPath, sizeof(chPath)-13);
   strcat(chPath, "/printer.dat");
   getConfigValueString(chFileName, "file", "printer_file", CPC->printer_file, sizeof(CPC->printer_file)-1, chPath);
   if (CPC->printer_file[0] == '\0') {
      strcpy(CPC->printer_file, chPath);
   }
   strncpy(chPath, chAppPath, sizeof(chPath)-12);
   strcat(chPath, "/screen.png");

   getConfigValueString(chFileName, "file", "sdump_path", CPC->sdump_path, sizeof(CPC->sdump_path)-1, chPath);
   if (*CPC->sdump_path == 0) strcpy(CPC->sdump_path, chPath);

   getConfigValueString(chFileName, "file", "sdump_file", CPC->sdump_file, sizeof(CPC->sdump_file)-1, chPath);
   if (*CPC->sdump_file == 0) strcpy(CPC->sdump_file, chPath);

   strncpy(chPath, chAppPath, sizeof(chPath)-5);
   strcat(chPath, "/rom");
   getConfigValueString(chFileName, "rom", "rom_path", CPC->rom_path, sizeof(CPC->rom_path)-1, chPath);
   for (iRomNum = 2; iRomNum < 16; iRomNum++) { // loop for ROMs 2-15
      char chRomId[14];
      sprintf(chRomId, "slot%02d", iRomNum); // build ROM ID
      getConfigValueString(chFileName, "rom", chRomId, CPC->rom_file[iRomNum], sizeof(CPC->rom_file[iRomNum])-1, "");
   }
   if (CPC->rom_path[0] == '\0') { // if the path is empty, set it to the default
      strcpy(CPC->rom_path, chPath);
   }
   pfileObject = fopen(chFileName, "rt");
   if (pfileObject == NULL) {
      strcpy(CPC->rom_file[7], AMSDOS); // insert AMSDOS in slot 7 if the config file does not exist yet
   } else {
      fclose(pfileObject);
   }
   getConfigValueString(chFileName, "rom", "rom_mf2", CPC->rom_mf2, sizeof(CPC->rom_mf2)-1, "");
}

#endif
