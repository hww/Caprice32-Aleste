// cfgapi.inl

inline CxProfile::CxProfile(void) : m_handle(NULL)
{
}

inline CxProfile::~CxProfile(void)
{
   if (IsOpen()) Close();
}

inline BOOL CxProfile::Attach(CFGHANDLE handle)
{
   _ASSERTE(m_handle == NULL);
   m_handle = handle;
   return (m_handle != NULL);
}

inline CFGHANDLE CxProfile::Detach(void)
{
   _ASSERTE(m_handle != NULL);
   CFGHANDLE handle = m_handle;
   m_handle = NULL;
   return handle;
}

inline void CxProfile::Close(void)
{
   _ASSERTE(m_handle != NULL);
   (*m_handle->api.close)(&m_handle);
}

inline BOOL CxProfile::IsOpen(void) const
{ 
   return (m_handle != NULL); 
}

inline BOOL CxProfile::SetSection(const TCHAR* section)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api.set_section)(m_handle, section);
}
   
inline BOOL CxProfile::SetValue(const TCHAR* value, LPCTSTR lpszValueName)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api.put_string)(m_handle, lpszValueName, value);
}
   
inline BOOL CxProfile::QueryValue(TCHAR* buf, int buf_size, LPCTSTR lpszValueName) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api.get_string)(m_handle, lpszValueName, buf, buf_size, buf);
}
   
inline BOOL CxProfile::SetValue(long value, LPCTSTR lpszValueName)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api.put_long)(m_handle, lpszValueName, value);
}
   
inline BOOL CxProfile::QueryValue(long* value, LPCTSTR lpszValueName) const
{
   _ASSERTE(m_handle != NULL);
   *value = (*m_handle->api.get_long)(m_handle, lpszValueName, *value);
   return TRUE;
}

inline BOOL CxProfile::QueryValue(int* value, LPCTSTR lpszValueName) const
{
   _ASSERTE(m_handle != NULL);
   *value = (*m_handle->api.get_long)(m_handle, lpszValueName, *value);
   return TRUE;
}

inline BOOL CxProfile::QueryValue(bool* value, LPCTSTR lpszValueName) const
{
   _ASSERTE(m_handle != NULL);
   *value = (*m_handle->api.get_long)(m_handle, lpszValueName, *value) ? true : false;
   return TRUE;
}
  
inline BOOL CxProfile::SetValue(const void* buf, size_t buf_size, LPCTSTR lpszValueName)
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api.put_binary)(m_handle, lpszValueName, buf, buf_size);
}
   
inline BOOL CxProfile::QueryValue(void* buf, size_t buf_size, LPCTSTR lpszValueName) const
{
   _ASSERTE(m_handle != NULL);
   return (*m_handle->api.get_binary)(m_handle, lpszValueName, buf, buf_size);
}

#ifdef __AFX_H__
inline BOOL CxProfile::QueryValue(CString* str, LPCTSTR lpszValueName)
{
   BOOL bOK = QueryValue(str->GetBuffer(512), 512, lpszValueName);
   str->ReleaseBuffer();
   return bOK;
}

inline BOOL CxProfile::QueryValue(CByteArray* array, LPCTSTR lpszValueName) const
{
   return QueryValue(array->GetData(), array->GetSize(), lpszValueName);
}
#endif
