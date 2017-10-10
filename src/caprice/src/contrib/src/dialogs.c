/* dialogs.c */

#include <tchar.h>

#include "../include/dialogs.h"

#ifdef _WIN32
#include <windows.h>

// File Dialog Stuff
//
// Written by Mark Incley, October '96

static void InitFileDlg(HWND hwnd, OPENFILENAME *ofn, const TCHAR *DefExt, const TCHAR *Filter, DWORD Flags)
{
	ofn->lStructSize		= sizeof(OPENFILENAME);
	ofn->hwndOwner			= hwnd;
	ofn->hInstance			= NULL;
	ofn->lpstrFilter		= Filter;
	ofn->lpstrCustomFilter	= 0;
	ofn->nMaxCustFilter		= 0;
	ofn->nFilterIndex		= 0;
	ofn->lpstrFile			= NULL;
	ofn->nMaxFile			= MAX_PATH;
	ofn->lpstrFileTitle		= NULL;
	ofn->nMaxFileTitle		= MAX_PATH;	/*MAX_FNAME + MAX_EXT;*/
	ofn->lpstrInitialDir	= NULL;
	ofn->lpstrTitle			= NULL;
	ofn->Flags				= Flags;
	ofn->nFileOffset		= 0;
	ofn->nFileExtension		= 0;
	ofn->lpstrDefExt		= DefExt;
	ofn->lCustData			= 0L;
	ofn->lpfnHook			= NULL;
	ofn->lpTemplateName		= NULL;
}

static BOOL GetFileNameFromDlg(HWND hwnd, OPENFILENAME *ofn, const TCHAR *SuggestName, const TCHAR *Title, TCHAR *Buffer, const TCHAR *Directory)
{
	ofn->hwndOwner		= hwnd;
	ofn->lpstrFile		= Buffer;
	//ofn->Flags			&= (~OFN_HIDEREADONLY);
	ofn->lpstrTitle		= Title;
	ofn->lpstrInitialDir = Directory;

	return GetOpenFileName(ofn);
}

static BOOL GetSaveNameFromDlg(HWND hwnd, OPENFILENAME *ofn, const TCHAR *SuggestName, const TCHAR *Title, TCHAR *Buffer, const TCHAR *Directory)
{
	ofn->hwndOwner		= hwnd;
	ofn->lpstrFile		= Buffer;
	//ofn->Flags			|= OFN_HIDEREADONLY;
	ofn->lpstrTitle		= Title;
	ofn->lpstrInitialDir = Directory;
	return GetSaveFileName(ofn);
}

BOOL browse_for_dsk(TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption)
{
   HWND hwnd = FindWindowA(NULL, app_caption);
   OPENFILENAME ofn;

   InitFileDlg(hwnd,&ofn, _T("*.dsk"), _T("Disk Image (*.dsk)\0*.dsk\0All files (*.*)\0*.*\0\0"),OFN_EXPLORER);
	return GetFileNameFromDlg(hwnd,&ofn,NULL,caption,FilenameBuffer, path);
}

BOOL browse_for_bmp(TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption)
{
   HWND hwnd = FindWindowA(NULL, app_caption);
   OPENFILENAME ofn;

   InitFileDlg(hwnd,&ofn, _T("*.bmp"), _T("Screenshots (*.bmp)\0*.bmp\0All files (*.*)\0*.*\0\0"),OFN_EXPLORER | OFN_OVERWRITEPROMPT);
	return GetSaveNameFromDlg(hwnd,&ofn,NULL,caption,FilenameBuffer, path);
}

BOOL browse_for_snap(TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption, BOOL save)
{
   HWND hwnd = FindWindowA(NULL, app_caption);
   OPENFILENAME ofn;

   InitFileDlg(hwnd,&ofn, _T("*.sna"), _T("CPC Snapshots (*.sna)\0*.sna\0All files (*.*)\0*.*\0\0"),OFN_EXPLORER | OFN_OVERWRITEPROMPT);

   return save ? GetSaveNameFromDlg(hwnd,&ofn,NULL,caption,FilenameBuffer, path) : GetFileNameFromDlg(hwnd,&ofn,NULL,caption,FilenameBuffer, path);
}

#else


BOOL browse_for_dsk (TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption)
{
   return FALSE;
}

BOOL browse_for_bmp (TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption)
{
   return FALSE;
}

BOOL browse_for_snap(TCHAR* FilenameBuffer, int cb, const TCHAR* path, const TCHAR* caption, const char* app_caption, BOOL save)
{
   return FALSE;
}

#endif
