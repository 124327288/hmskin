#ifndef __HM_WIN_MISC_H__
#define __HM_WIN_MISC_H__
#include <string>
#include "tchar.h"

typedef std::basic_string<TCHAR> tstring_type;

BOOL GetCurModuleDirPath( tstring_type& strModuleDirPath );

BOOL MultiByteToWideChar( const std::string& strMultiByte, std::basic_string<WCHAR>& wstrWideChar, unsigned int CodePage = CP_ACP, DWORD dwFlags = 0 );

BOOL MultiByteToTChar( const std::string&  strMultiByte, std::basic_string<TCHAR>& tstrTChar );


#endif //__HM_WIN_MISC_H__