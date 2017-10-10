// cfgapi.hpp
// Copyright (c) 2004 by Troels K.

#ifndef __CFG_API_HPP__
#define __CFG_API_HPP__

#ifndef __CFG_API_H__
#include "cfgapi.h"
#endif

class CxProfile
{
// Attributes
public:
   CFGHANDLE m_handle;

// Construction
public:
   CxProfile();

// Operations
public:
   BOOL      Attach(CFGHANDLE);
   CFGHANDLE Detach(void);

   BOOL IsOpen(void) const;

   BOOL SetSection(const TCHAR*);
   
   BOOL SetValue  (const TCHAR* value,               LPCTSTR lpszValueName);
   BOOL QueryValue(      TCHAR* buf  , int buf_size, LPCTSTR lpszValueName) const;

   BOOL SetValue  (long  value, LPCTSTR lpszValueName);
   BOOL QueryValue(long* value, LPCTSTR lpszValueName) const;
   BOOL QueryValue(int*  value, LPCTSTR lpszValueName) const;

   BOOL SetValue  (const void* buf, size_t buf_size, LPCTSTR lpszValueName);
   BOOL QueryValue(      void* buf, size_t buf_size, LPCTSTR lpszValueName) const;

   BOOL QueryValue(bool* value, LPCTSTR lpszValueName) const;

#ifdef __AFX_H__
   BOOL QueryValue(CString*   , LPCTSTR lpszValueName);
   BOOL QueryValue(CByteArray*, LPCTSTR lpszValueName) const;
#endif

// Implementation
public:
   virtual ~CxProfile();
   virtual void Close(void);
};

#include "cfgapi.inl"
  
#endif /* __CFG_API_HPP__ */
