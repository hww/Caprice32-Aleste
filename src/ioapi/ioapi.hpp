// ioapi.hpp
// Copyright 2004 by Troels K.

#ifndef __IOAPI_HPP__
#define __IOAPI_HPP__

#ifndef ZLIB_H
#include "zlib.h"
#endif
#ifndef _ZLIBIOAPI_H
#include "unzip\ioapi.h"
#endif
#include "bool.h"

/////////////////////////////////////////////////////////////////////////////
// CFileZ

class CFileZ : public zlib_filefunc_def_s
{
// Attributes
public:
   //int (*m_SetLength)(voidpf opaque, voidpf stream, uLong size);
   voidpf m_stream;

// Contruction
public:
   CFileZ();

// Operations
public:
   BOOL IsOpen(void) const;
   long SetPosition(DWORD dwPosition);
   long Seek(LONG lOff, UINT nFrom);
	//BOOL SetLength(DWORD dwNewLen);
	uLong GetLength() const;
	uLong Read(void* lpBuf, UINT nCount);
	uLong Write(const void* lpBuf, UINT nCount);
	BOOL Open(const char* lpszFileName, int mode);
	uLong GetPosition(void) const;
	
// Implemenation
public:
   virtual ~CFileZ(void);
	virtual void Close();
};

/////////////////////////////////////////////////////////////////////////////
// CFileZ_MFC

#ifdef __AFX_H__
class CFileZ_MFC : public CFile, public CFileZ
{
// Attributes
public:

// Contruction
public:
   CFileZ_MFC();

// Operations
public:
   DWORD SetPosition(DWORD dwPosition);
	
// Implemenation
public:
   virtual ~CFileZ_MFC(void);

   virtual LONG Seek(LONG lOff, UINT nFrom);
	//virtual void SetLength(DWORD dwNewLen);
	virtual DWORD GetLength() const;
	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual void Write(const void* lpBuf, UINT nCount);
	virtual BOOL Open(const char* lpszFileName, UINT nOpenFlags, CFileException* pError = NULL);
	virtual void Close();
	virtual DWORD GetPosition(void) const;
};
#endif

#include "ioapi.inl"

#endif // __IOAPI_HPP__

/////////////////////////////////////////////////////////////////////////////
