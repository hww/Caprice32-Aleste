/* cfg_file.c */
/* Copyright (c) 2004 by Troels K. */

#include <windows.h>

#include "cfg_reg.h"
#include "cfgapi.h"

typedef struct _CFGIMPLA
{
   HKEY root;
   HKEY section;
} REGISTRYPROFILEA;

HKEY cfg_reg_getkey(CFGHANDLEA handle)
{
   return handle->impl->section;
}

static void close_impl(CFGHANDLEA* handle)
{
   RegCloseKey((*handle)->impl->section);
   free((*handle)->impl);
   free(*handle);
   *handle = NULL;
}

static BOOL put_string(CFGHANDLEA handle, const char* szEntry, const char* szValue)
{
	BOOL bOK = (ERROR_SUCCESS == RegSetValueExA(handle->impl->section, szEntry, 0, REG_SZ, (LPBYTE)szValue, (lstrlenA(szValue)+1)*sizeof(char)));
   return bOK;
}

static int get_string(CFGHANDLEA handle, const char* szEntry, char* szBuffer, int buffer_count, const char* szDefault)
{
	DWORD dwType, dwCount = buffer_count * sizeof(char);
	BOOL bOK = (ERROR_SUCCESS == RegQueryValueExA(handle->impl->section, (LPSTR)szEntry, NULL, &dwType, (LPBYTE)szBuffer, &dwCount));
   if (bOK)
   {
		bOK = ((dwType == REG_SZ) || (dwType == REG_EXPAND_SZ));
   }
   if (!bOK)
   {
      bOK = (szDefault != NULL);
      if (bOK)
      {
         strncpy(szBuffer, szDefault, buffer_count);
         bOK = put_string(handle, szEntry, szDefault);
      }
   }
   return bOK ? dwCount : 0;
}

static BOOL put_long(CFGHANDLEA handle, const char* szEntry, long nValue)
{
   return (RegSetValueExA(handle->impl->section, szEntry, 0, REG_DWORD, (LPBYTE)(&nValue), sizeof(nValue)) == ERROR_SUCCESS);
}

static long get_long(CFGHANDLEA handle, const char* szEntry, long nDefault)
{
	UINT nValue = 0;
	DWORD dwType = REG_DWORD, dwCount = sizeof(nValue);
   BOOL bOK = (ERROR_SUCCESS == RegQueryValueExA(handle->impl->section, szEntry, 0, &dwType, (LPBYTE)&nValue, &dwCount));
   if (!bOK)
   {
      nValue = nDefault;
      bOK = put_long(handle, szEntry, nDefault);
   }
   return bOK ? nValue : 0;
}

static BOOL put_binary(CFGHANDLEA handle, const char* szEntry, const void* buffer, size_t buf_size)
{
	return (ERROR_SUCCESS == RegSetValueExA(handle->impl->section, szEntry, 0, REG_BINARY, (BYTE*)buffer, buf_size));
}

static BOOL get_binary(CFGHANDLEA handle, const char* szEntry,       void* buffer, size_t buf_size)
{
	DWORD dwType = REG_BINARY, dwCount = buf_size;
   BOOL bOK = (ERROR_SUCCESS == RegQueryValueExA(handle->impl->section, szEntry, 0, &dwType, (BYTE*)buffer, &dwCount));
   if (!bOK)
   {
      bOK = put_binary(handle, szEntry, buffer, buf_size);
   }
   return bOK;
}

static BOOL set_section_impl(CFGHANDLEA handle, const char* section)
{
   HKEY subkey;
   BOOL bOK = (RegOpenKeyA(handle->impl->root, section, &subkey) == ERROR_SUCCESS);
   if (!bOK)
   {
      bOK = (RegCreateKeyA(handle->impl->root, section, &subkey) == ERROR_SUCCESS);
   }
   if (bOK) handle->impl->section = subkey;
   return bOK;
}

static void fill(struct _CFGAPIA* api)
{
   api->set_section = set_section_impl;
   api->close       = close_impl;
   api->get_string  = get_string;
   api->put_string  = put_string;
   api->get_long    = get_long;
   api->put_long    = put_long;
   api->get_binary  = get_binary;
   api->put_binary  = put_binary;
   api->opaque      = NULL;
}

CFGHANDLEA cfg_reg_attach(HKEY key)
{
   CFGHANDLEA handle = (CFGDATAA*)malloc(sizeof(CFGDATAA));
   handle->impl = (REGISTRYPROFILEA*)malloc(sizeof(REGISTRYPROFILEA));
   handle->impl->root = handle->impl->section = key;
   fill(&handle->api);
   return handle;
}

CFGHANDLEA cfg_reg_open(HKEY root, const char* section)
{
   CFGHANDLEA handle = NULL;
   HKEY subkey;
   BOOL bOK;

   if (root == NULL) root = HKEY_CURRENT_USER;
   bOK = (RegOpenKeyA(root, section, &subkey) == ERROR_SUCCESS);
   if (!bOK)
   {
      bOK = (RegCreateKeyA(root, section, &subkey) == ERROR_SUCCESS);
   }
   if (bOK)
   {
      handle = cfg_reg_attach(subkey);
   }
   return handle;
}

#if !defined(_MSDOS)

typedef struct _CFGIMPLW
{
   HKEY root;
   HKEY section;
} REGISTRYPROFILEW;

HKEY cfg_reg_wgetkey(CFGHANDLEW handle)
{
   return handle->impl->section;
}

static void wclose_impl(CFGHANDLEW* handle)
{
   RegCloseKey((*handle)->impl->section);
   free((*handle)->impl);
   free(*handle);
   *handle = NULL;
}

static BOOL wput_string(CFGHANDLEW handle, const wchar_t* szEntry, const wchar_t* szValue)
{
	BOOL bOK = (ERROR_SUCCESS == RegSetValueExW(handle->impl->section, szEntry, 0, REG_SZ, (LPBYTE)szValue, (lstrlenW(szValue)+1)*sizeof(wchar_t)));
   return bOK;
}

static int wget_string(CFGHANDLEW handle, const wchar_t* szEntry, wchar_t* szBuffer, int buffer_count, const wchar_t* szDefault)
{
	DWORD dwType, dwCount = buffer_count * sizeof(wchar_t);
	BOOL bOK = (ERROR_SUCCESS == RegQueryValueExW(handle->impl->section, (LPWSTR)szEntry, NULL, &dwType, (LPBYTE)szBuffer, &dwCount));
   if (bOK)
   {
		bOK = ((dwType == REG_SZ) || (dwType == REG_EXPAND_SZ));
   }
   if (!bOK)
   {
      bOK = (szDefault != NULL);
      if (bOK)
      {
         wcsncpy(szBuffer, szDefault, buffer_count);
         bOK = wput_string(handle, szEntry, szDefault);
      }
   }
   return bOK ? dwCount : 0;
}

static BOOL wput_long(CFGHANDLEW handle, const wchar_t* szEntry, long nValue)
{
   return (RegSetValueExW(handle->impl->section, szEntry, 0, REG_DWORD, (LPBYTE)(&nValue), sizeof(nValue)) == ERROR_SUCCESS);
}

static long wget_long(CFGHANDLEW handle, const wchar_t* szEntry, long nDefault)
{
	UINT nValue = 0;
	DWORD dwType = REG_DWORD, dwCount = sizeof(nValue);
   BOOL bOK = (ERROR_SUCCESS == RegQueryValueExW(handle->impl->section, szEntry, 0, &dwType, (LPBYTE)&nValue, &dwCount));
   if (!bOK)
   {
      nValue = nDefault;
      bOK = wput_long(handle, szEntry, nDefault);
   }
   return bOK ? nValue : 0;
}

static BOOL wput_binary(CFGHANDLEW handle, const wchar_t* szEntry, const void* buffer, size_t buf_size)
{
	return (ERROR_SUCCESS == RegSetValueExW(handle->impl->section, szEntry, 0, REG_BINARY, (BYTE*)buffer, buf_size));
}

static BOOL wget_binary(CFGHANDLEW handle, const wchar_t* szEntry,       void* buffer, size_t buf_size)
{
	DWORD dwType = REG_BINARY, dwCount = buf_size;
   BOOL bOK = (ERROR_SUCCESS == RegQueryValueExW(handle->impl->section, szEntry, 0, &dwType, (BYTE*)buffer, &dwCount));
   if (!bOK)
   {
      bOK = wput_binary(handle, szEntry, buffer, buf_size);
   }
   return bOK;
}

static BOOL wset_section_impl(CFGHANDLEW handle, const wchar_t* section)
{
   HKEY subkey;
   BOOL bOK = (RegOpenKeyW(handle->impl->root, section, &subkey) == ERROR_SUCCESS);
   if (!bOK)
   {
      bOK = (RegCreateKeyW(handle->impl->root, section, &subkey) == ERROR_SUCCESS);
   }
   if (bOK) handle->impl->section = subkey;
   return bOK;
}

static void wfill(struct _CFGAPIW* api)
{
   api->set_section = wset_section_impl;
   api->close       = wclose_impl;
   api->get_string  = wget_string;
   api->put_string  = wput_string;
   api->get_long    = wget_long;
   api->put_long    = wput_long;
   api->get_binary  = wget_binary;
   api->put_binary  = wput_binary;
   api->opaque      = NULL;
}

CFGHANDLEW cfg_reg_wattach(HKEY key)
{
   CFGHANDLEW handle = (CFGDATAW*)malloc(sizeof(CFGDATAW));
   handle->impl = (REGISTRYPROFILEW*)malloc(sizeof(REGISTRYPROFILEW));
   handle->impl->root = handle->impl->section = key;
   wfill(&handle->api);
   return handle;
}

CFGHANDLEW cfg_reg_wopen(HKEY root, const wchar_t* section)
{
   CFGHANDLEW handle = NULL;
   HKEY subkey;
   BOOL bOK;

   if (root == NULL) root = HKEY_CURRENT_USER;
   bOK = (RegOpenKeyW(root, section, &subkey) == ERROR_SUCCESS);
   if (!bOK)
   {
      bOK = (RegCreateKeyW(root, section, &subkey) == ERROR_SUCCESS);
   }
   if (bOK)
   {
      handle = cfg_reg_wattach(subkey);
   }
   return handle;
}

#endif
