// cfg_reg.hpp
// Copyright (c) 2004 by Troels K.

#ifndef __CFG_REGISTRY_HPP__
#define __CFG_REGISTRY_HPP__

#ifndef __CFG_API_HPP__
#include "cfgapi.hpp"
#endif
#ifndef __CFG_REGISTRY_H__
#include "cfg_reg.h"
#endif

class CxRegistryProfile : public CxProfile
{
// Construction
public:
   CxRegistryProfile();

// Operations
public:
   BOOL Open(HKEY root, const TCHAR* section_root);
   BOOL Attach(HKEY key);
   operator HKEY(void);

// Implementation
public:
   virtual ~CxRegistryProfile();
};

inline CxRegistryProfile::CxRegistryProfile(void) : CxProfile()
{
}

inline CxRegistryProfile::~CxRegistryProfile(void)
{
}

inline BOOL CxRegistryProfile::Open(HKEY root, const TCHAR* section_root)
{
   return CxProfile::Attach(::cfg_reg_topen(root, section_root));
}

inline BOOL CxRegistryProfile::Attach(HKEY key)
{
   return CxProfile::Attach(::cfg_reg_tattach(key));
}

inline CxRegistryProfile::operator HKEY(void)
{
   _ASSERTE(m_handle != NULL);
   return ::cfg_reg_tgetkey(m_handle);
}

#endif /* __CFG_REGISTRY_HPP__ */
