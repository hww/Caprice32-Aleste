// cfg_file.hpp
// Copyright (c) 2004 by Troels K.

#ifndef __CFG_FILE_HPP__
#define __CFG_FILE_HPP__

#ifndef __CFG_API_HPP__
#include "cfgapi.hpp"
#endif
#ifndef __CFG_FILE_H__
#include "cfg_file.h"
#endif

class CxFileProfile : public CxProfile
{
// Construction
public:
   CxFileProfile();

// Operations
public:
   BOOL Open(const TCHAR* file, const TCHAR* section_root, BOOL modify = TRUE);

   BOOL GetLine(int line, TCHAR* buf, int buf_size) const;
#ifdef __AFX_H__
   BOOL GetLine(int line, CString*) const;
#endif

// Implementation
public:
   virtual ~CxFileProfile();
};

inline CxFileProfile::CxFileProfile(void) : CxProfile()
{
}

inline CxFileProfile::~CxFileProfile(void)
{
}

inline BOOL CxFileProfile::Open(const TCHAR* file, const TCHAR* section_root, BOOL modify)
{
   return CxProfile::Attach(::cfg_ini_topen(file, section_root, NULL, modify));
}

inline BOOL CxFileProfile::GetLine(int line, TCHAR* buf, int buf_size) const
{
   _ASSERTE(m_handle != NULL);
   return ::ini_getline(m_handle, line, buf, buf_size);
}

#ifdef __AFX_H__
inline BOOL CxFileProfile::GetLine(int line, CString* str) const
{
   BOOL bOK = GetLine(line, str->GetBuffer(512), 512);
   str->ReleaseBuffer();
   return bOK;
}
#endif


#endif /* __CFG_FILE_HPP__ */
