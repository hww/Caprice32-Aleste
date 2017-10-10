// ioapi.inl

/////////////////////////////////////////////////////////////////////////////
// CFileZ

inline CFileZ::CFileZ() : m_stream(NULL)//, m_SetLength(NULL)
{ 
   zlib_filefunc_def* api = this;
   memset(api, 0, sizeof(*api));
}

inline CFileZ::~CFileZ(void)
{
   if (IsOpen()) Close();
}

inline BOOL CFileZ::IsOpen(void) const
{ 
   return (m_stream != NULL); 
}

inline BOOL CFileZ::Open(const char* lpszFileName, int mode)
{
   _ASSERTE(m_stream == NULL);
   m_stream = (*zopen_file)(opaque, lpszFileName, mode);
   return (m_stream != NULL);
}

inline void CFileZ::Close()
{
   if (IsOpen()) ZCLOSE(*this, m_stream);
   m_stream = NULL;
}

inline long CFileZ::Seek(LONG lOff, UINT nFrom)
{
   _ASSERTE(m_stream != NULL);
   return ZSEEK(*this, m_stream, lOff, nFrom);
}

inline uLong CFileZ::GetLength(void) const
{
   _ASSERTE(m_stream != NULL);
   uLong pos = ZTELL(*this, m_stream);
   ZSEEK(*this, m_stream, 0, ZLIB_FILEFUNC_SEEK_END);
   uLong len = ZTELL(*this, m_stream);
   ZSEEK(*this, m_stream, pos, ZLIB_FILEFUNC_SEEK_SET);
   return len;
}

inline long CFileZ::SetPosition(DWORD dwPosition)
{ 
   _ASSERTE(m_stream != NULL);
   return ZSEEK(*this, m_stream, dwPosition, ZLIB_FILEFUNC_SEEK_SET); 
}

inline uLong CFileZ::Read(void* lpBuf, UINT nCount)
{
   _ASSERTE(m_stream != NULL);
   return ZREAD(*this, m_stream, lpBuf, nCount);
}

inline uLong CFileZ::Write(const void* lpBuf, UINT nCount)
{
   _ASSERTE(m_stream != NULL);
   return ZWRITE(*this, m_stream, lpBuf, nCount);
}

inline uLong CFileZ::GetPosition(void) const
{
   _ASSERTE(m_stream != NULL);
   return ZTELL(*this, m_stream);
}

/*
inline BOOL CFileZ::SetLength(DWORD dwNewLen)
{
   BOOL bOK = (m_SetLength != NULL);
   if (bOK)
   {
      bOK = ((*m_SetLength)(opaque, m_stream, dwNewLen) == 0);
   }
   return bOK;
}
*/

/////////////////////////////////////////////////////////////////////////////
// CFileZ_MFC

#ifdef __AFX_H__

inline CFileZ_MFC::CFileZ_MFC() : CFileZ(), CFile()
{ 
}

inline CFileZ_MFC::~CFileZ_MFC(void)
{
   if (IsOpen()) Close();
}

inline BOOL CFileZ_MFC::Open(const char* lpszFileName, UINT nOpenFlags, CFileException* pException)
{
   int mode = 0;
   BOOL bCreate   = ((nOpenFlags & CFile::modeCreate    ) == CFile::modeCreate);
   BOOL bTruncate = ((nOpenFlags & CFile::modeNoTruncate) != CFile::modeNoTruncate);
   if (nOpenFlags & CFile::modeReadWrite) mode|=ZLIB_FILEFUNC_MODE_READWRITEFILTER;
   if (nOpenFlags & CFile::modeRead     ) mode|=ZLIB_FILEFUNC_MODE_READ;
   if (nOpenFlags & CFile::modeWrite    ) mode|=ZLIB_FILEFUNC_MODE_WRITE;
   BOOL bOK = CFileZ::Open(lpszFileName, mode | ((bCreate && bTruncate) ? ZLIB_FILEFUNC_MODE_CREATE : ZLIB_FILEFUNC_MODE_EXISTING));
   if ((!bOK) && bCreate && (!bTruncate))
   {
      bOK = CFileZ::Open(lpszFileName, mode | ZLIB_FILEFUNC_MODE_CREATE);
   }
   if (bOK)
   {
      m_strFileName = lpszFileName;
   }
   else if (pException)
   {
		pException->m_lOsError = E_FAIL;
		pException->m_cause = CFileException::OsErrorToException(E_FAIL);
      pException->m_strFileName = lpszFileName;
   }
   return bOK;
}

inline void CFileZ_MFC::Close()
{
   CFileZ::Close();
   m_strFileName.Empty();
}

inline LONG CFileZ_MFC::Seek(LONG lOff, UINT nFrom)
{
   C_ASSERT(ZLIB_FILEFUNC_SEEK_SET == CFile::begin);
   C_ASSERT(ZLIB_FILEFUNC_SEEK_END == CFile::end);
   C_ASSERT(ZLIB_FILEFUNC_SEEK_CUR == CFile::current);
   return CFileZ::Seek(lOff, nFrom);
}

/*
inline void CFileZ_MFC::SetLength(DWORD dwNewLen)
{
   if (!CFileZ::SetLength(dwNewLen))
   {
   }
}
*/

inline DWORD CFileZ_MFC::GetLength(void) const
{
   return CFileZ::GetLength();
}

inline DWORD CFileZ_MFC::SetPosition(DWORD dwPosition)
{ 
   return CFileZ::SetPosition(dwPosition);
}

inline UINT CFileZ_MFC::Read(void* lpBuf, UINT nCount)
{
   return CFileZ::Read(lpBuf, nCount);
}

inline void CFileZ_MFC::Write(const void* lpBuf, UINT nCount)
{
   uLong nWritten = CFileZ::Write(lpBuf, nCount);
	if (nWritten != nCount)
		AfxThrowFileException(CFileException::diskFull, -1, m_strFileName);
}

inline DWORD CFileZ_MFC::GetPosition(void) const
{
   return CFileZ::GetPosition();
}

#endif
