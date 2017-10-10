// emushell.inl

#ifndef _ASSERTE
   #define _ASSERTE(a)
#endif

inline CEmuShell::CEmuShell(void) : m_handle(NULL)
{ 
}

inline CEmuShell::~CEmuShell()
{
   if (IsOpen()) Close();
}

inline BOOL CEmuShell::IsOpen(void) const
{ 
   return (m_handle != NULL); 
}

inline BOOL CEmuShell::Open(const EMUAPI* api, LPCTSTR szPath)
{
   _ASSERTE(m_handle == NULL);
   BOOL bOK = (NULL != api->open);
   if (bOK)
   {
      m_handle = (*api->open)(szPath);
      bOK = (m_handle != NULL);
   }
   return bOK;
}

inline BOOL CEmuShell::PutExePath(LPCTSTR lpszPath)
{
   _ASSERTE(m_handle != NULL);
   BOOL bOK = (m_handle->api->put_exe_path != NULL);
   if (bOK)
   {
      (*m_handle->api->put_exe_path)(m_handle, lpszPath);
   }
   return bOK;
}

inline HANDLE CEmuShell::Run(HWND hwndParent, int argc, TCHAR* argv[])
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->run)(m_handle, hwndParent, argc, argv);
}

inline BOOL CEmuShell::GetDisk(int no, LPTSTR lpszBuffer, int cbBuffer) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_disk)(m_handle, no, lpszBuffer, cbBuffer);
}

inline BOOL CEmuShell::PutDisk(int no, LPCTSTR lpszBuffer)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->put_disk)(m_handle, no, lpszBuffer);
}

inline BOOL CEmuShell::GetPath(enum emupath index, LPTSTR lpszBuffer, int cbBuffer) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_path)(m_handle, index, lpszBuffer, cbBuffer);
}

inline BOOL CEmuShell::PutPath(enum emupath index, LPCTSTR lpszBuffer)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->put_path)(m_handle, index, lpszBuffer);
}

inline BOOL CEmuShell::GetRom(int no, LPTSTR lpszBuffer, int cbBuffer) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_rom)(m_handle, no, lpszBuffer, cbBuffer);
}

inline BOOL CEmuShell::PutRom(int no, LPCTSTR lpszName)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->put_rom)(m_handle, no, lpszName);
}

inline int  CEmuShell::GetName(LPTSTR lpszBuffer, int cbBuffer) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_name)(m_handle, lpszBuffer, cbBuffer);
}

inline BOOL CEmuShell::GetFileProfile(LPTSTR lpszBuffer, int cbBuffer) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_fileprofile)(m_handle, lpszBuffer, cbBuffer);
}

inline BOOL CEmuShell::GetVideoMode(int* mode) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_video_mode)(m_handle, mode);
}

inline BOOL CEmuShell::PutVideoMode(int mode)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->put_video_mode)(m_handle, mode);
}

inline BOOL CEmuShell::GetFullscreen(void) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_fullscreen)(m_handle);
}

inline BOOL CEmuShell::PutFullscreen(BOOL bEnable)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->put_fullscreen)(m_handle, bEnable);
}

inline void CEmuShell::Close()
{
   _ASSERTE(m_handle != NULL);
   (*m_handle->api->close)(&m_handle);
}



inline BOOL CEmuShell::GetTextMode(int* mode) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_text_mode)(m_handle, mode);
}

inline BOOL CEmuShell::PutTextMode(int mode)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->put_text_mode)(m_handle, mode);
}

inline BOOL CEmuShell::GetKeyboard(int* mode) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->get_keyboard)(m_handle, mode);
}

inline BOOL CEmuShell::PutKeyboard(int mode)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api->put_keyboard)(m_handle, mode);
}


#ifdef __AFX_H__
inline CString CEmuShell::GetDisk(int no) const
{
   CString str;
   GetDisk(no, str.GetBuffer(_MAX_PATH), _MAX_PATH);
   str.ReleaseBuffer();
   return str;
}

inline CString CEmuShell::GetPath(enum emupath index) const
{
   CString str;
   GetPath(index, str.GetBuffer(_MAX_PATH), _MAX_PATH);
   str.ReleaseBuffer();
   return str;
}

inline CString CEmuShell::GetRom(int no) const
{
   CString str;
   GetRom(no, str.GetBuffer(_MAX_PATH), _MAX_PATH);
   str.ReleaseBuffer();
   return str;
}

inline CString CEmuShell::GetName(void) const
{
   CString str;
   GetName(str.GetBuffer(_MAX_PATH), _MAX_PATH);
   str.ReleaseBuffer();
   return str;
}

inline CString CEmuShell::GetFileProfile(void) const
{
   CString str;
   GetFileProfile(str.GetBuffer(_MAX_PATH), _MAX_PATH);
   str.ReleaseBuffer();
   return str;
}

/*
inline CString CEmuShell::GetFileProfileName(void) const
{
   CString strPath = GetFileProfile();
   TCHAR sz;
   _tsplitpath();
   str.ReleaseBuffer();
   return str;
}
*/
#endif
