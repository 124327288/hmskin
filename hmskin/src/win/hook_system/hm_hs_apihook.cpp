#include "stdafx.h"
#include <assert.h>
#include "win\hook_system\hm_hs_apihook.h"
#include "AtlConv.h"
#include "win\frame\hm_hook_trackpopupmenu.h"

bool hm_hs_apihook::hookOnTrackPopupMenu( const TCHAR* szAPIName, const TCHAR* szLibFileName ) {
	if ( _isRegHook( szAPIName, szLibFileName ) ) 
		return false;
	if ( !_regHookTrackPopupMenu( szAPIName, szLibFileName ) )
		return false;
	
	//
	_hookStart( szAPIName, szLibFileName );
	
	return true;
}

bool hm_hs_apihook::hookOff( const TCHAR* szAPIName, const TCHAR* szLibFileName ) {
	apiinfo_container_type::iterator itAPIInfo, iendAPIInfo;
	
	if ( !_isRegHook( szAPIName, szLibFileName ) ) 
		return false;
	if ( _isHookStarted( szAPIName, szLibFileName ) ) {
		if ( !_hookStop( szAPIName, szLibFileName ) )
			return false;
	}

	return _unregHook( szAPIName, szLibFileName );
}
//
bool hm_hs_apihook::_regHookTrackPopupMenu( const TCHAR* szAPIName, const TCHAR* szLibFileName ) {
	if ( _isRegHook( szAPIName, szLibFileName ) ) return false;
	apiinfo* pAPIInfo = NULL;
	void* pfnOrigin = NULL;
	HMODULE hModule;

	USES_CONVERSION;
	hModule = LoadLibrary( szLibFileName ); // just increase a referrence count
	if ( !hModule ) return false;
	pfnOrigin = GetProcAddress( hModule, T2A(szAPIName) );
	if ( !pfnOrigin ) {
		::FreeLibrary( hModule );
		return false;
	}
	
	pAPIInfo = new apiinfo();
	//
	_prepareCodeHookTrackPopupMenu( pfnOrigin, pAPIInfo->m_originCodeBuf, pAPIInfo->m_newCodeBuf );
	pAPIInfo->m_strAPIName = szAPIName;
	pAPIInfo->m_strLibFileName = szLibFileName;
	pAPIInfo->m_bHooked = false;
	pAPIInfo->m_pfnOriginAddr = pfnOrigin;
	pAPIInfo->m_hModule = hModule;
	pAPIInfo->m_dwPID = ::GetCurrentProcessId();
	
	//
	m_containerAPIInfo.push_back( pAPIInfo );
	return true;
}

bool hm_hs_apihook::_unregHook( const TCHAR* szAPIName, const TCHAR* szLibFileName ) {
	if ( !_isRegHook( szAPIName, szLibFileName ) ) return false;
	if ( _isHookStarted( szAPIName, szLibFileName ) ) {
		apiinfo_container_type::iterator itAPIInfo, iendAPIInfo;
		iendAPIInfo = m_containerAPIInfo.end();
		for ( itAPIInfo = m_containerAPIInfo.begin(); itAPIInfo!=iendAPIInfo; ++itAPIInfo ) {
			if ( ( _tcscmp( (*itAPIInfo)->m_strAPIName.c_str(), szAPIName ) == 0 )
			&& ( _tcscmp( (*itAPIInfo)->m_strLibFileName.c_str(), szLibFileName ) == 0 ) ) {
				if ( (*itAPIInfo)->m_bHooked ) {
					_hookStop( (*itAPIInfo) );
				}
				//
				::FreeLibrary( (*itAPIInfo)->m_hModule );
				delete (*itAPIInfo);
				m_containerAPIInfo.erase( itAPIInfo );
				//
				return true;
			}
		}
	}

	return false;
}

bool hm_hs_apihook::_isRegHook( const TCHAR* szAPIName, const TCHAR* szLibFileName ) {
	apiinfo_container_type::iterator itAPIInfo, iendAPIInfo;
	
	iendAPIInfo = m_containerAPIInfo.end();
	for ( itAPIInfo = m_containerAPIInfo.begin(); itAPIInfo!=iendAPIInfo; ++itAPIInfo ) {
		if ( ( _tcscmp( (*itAPIInfo)->m_strAPIName.c_str(), szAPIName ) == 0 )
			&& ( _tcscmp( (*itAPIInfo)->m_strLibFileName.c_str(), szLibFileName ) == 0 ) ) {
			return true;
		}
	}
	
	return false;
}

void hm_hs_apihook::_prepareCodeHookTrackPopupMenu( void* pfnOrigin, unsigned char originCodeBuf[ 5 ], unsigned char newCodeBuf[ 5 ] ) {
	unsigned char OriginCodeTmp[5];
	unsigned char NewCodeTmp[5];
	_asm 
	{ 
		lea edi,OriginCodeTmp 
			mov esi,pfnOrigin 
			cld 
			movsd
			movsb
	} 
	NewCodeTmp[0]=0xe9; 
	_asm 
	{ 
		lea eax,hmTrackPopupMenu 
			mov ebx,pfnOrigin 
			sub eax,ebx
			sub eax,5
			mov dword ptr [NewCodeTmp+1],eax
	}

	memcpy( originCodeBuf, OriginCodeTmp, 5 );
	memcpy( newCodeBuf, NewCodeTmp, 5 );
}

hm_hs_apihook::hm_hs_apihook() {}
hm_hs_apihook::~hm_hs_apihook() {}

bool hm_hs_apihook::_hookStart( const TCHAR* szAPIName, const TCHAR* szLibFileName ) {
	apiinfo_container_type::iterator itAPIInfo, iendAPIInfo;

	iendAPIInfo = m_containerAPIInfo.end();
	for ( itAPIInfo = m_containerAPIInfo.begin(); itAPIInfo!=iendAPIInfo; ++itAPIInfo ) {
		if ( ( _tcscmp( (*itAPIInfo)->m_strAPIName.c_str(), szAPIName ) == 0 )
		&& ( _tcscmp( (*itAPIInfo)->m_strLibFileName.c_str(), szLibFileName ) == 0 ) ) {
			if ( !(*itAPIInfo)->m_bHooked ) {
				_hookStart( *itAPIInfo );
			}
			return true;
		}
	}
	return false;
}

bool hm_hs_apihook::_hookStop( const TCHAR* szAPIName, const TCHAR* szLibFileName ) {
	apiinfo_container_type::iterator itAPIInfo, iendAPIInfo;

	iendAPIInfo = m_containerAPIInfo.end();
	for ( itAPIInfo = m_containerAPIInfo.begin(); itAPIInfo!=iendAPIInfo; ++itAPIInfo ) {
		if ( ( _tcscmp( (*itAPIInfo)->m_strAPIName.c_str(), szAPIName ) == 0 )
		&& ( _tcscmp( (*itAPIInfo)->m_strLibFileName.c_str(), szLibFileName ) == 0 ) ) {
			if ( (*itAPIInfo)->m_bHooked ) {
				_hookStop( *itAPIInfo );
			}
			return true;
		}
	}
	return false;
}

void hm_hs_apihook::_hookStart( apiinfo* pAPIInfo ) {
	if ( !pAPIInfo || pAPIInfo->m_bHooked ) return;
	HANDLE hProc; 
	DWORD flOldProtect;
	DWORD flNewProtect;
	
	hProc = ::OpenProcess( PROCESS_ALL_ACCESS, 0, pAPIInfo->m_dwPID );
	
	flNewProtect = PAGE_READWRITE;
	::VirtualProtectEx(  hProc, pAPIInfo->m_pfnOriginAddr, 5, flNewProtect, &flOldProtect);
	
	WriteProcessMemory( hProc, pAPIInfo->m_pfnOriginAddr, pAPIInfo->m_newCodeBuf, 5, 0 );
	
	flNewProtect = flOldProtect;
	::VirtualProtectEx( hProc, pAPIInfo->m_pfnOriginAddr, 5, flNewProtect, &flOldProtect );
	
	::CloseHandle( hProc );
	
	pAPIInfo->m_bHooked = true;
}

void hm_hs_apihook::_hookStop( apiinfo* pAPIInfo ) {
	if ( !pAPIInfo || !pAPIInfo->m_bHooked ) return;
	HANDLE hProc; 
	DWORD flOldProtect;
	DWORD flNewProtect;
	
	hProc = ::OpenProcess( PROCESS_ALL_ACCESS, 0, pAPIInfo->m_dwPID );
	
	flNewProtect = PAGE_READWRITE;
	::VirtualProtectEx(  hProc, pAPIInfo->m_pfnOriginAddr, 5, flNewProtect, &flOldProtect);
	
	WriteProcessMemory( hProc, pAPIInfo->m_pfnOriginAddr, pAPIInfo->m_originCodeBuf, 5, 0 );
	
	flNewProtect = flOldProtect;
	::VirtualProtectEx( hProc, pAPIInfo->m_pfnOriginAddr, 5, flNewProtect, &flOldProtect );
	
	::CloseHandle( hProc );
}
	
bool hm_hs_apihook::_isHookStarted( const TCHAR* szAPIName, const TCHAR* szLibFileName ) {
	apiinfo_container_type::iterator itAPIInfo, iendAPIInfo;
	
	iendAPIInfo = m_containerAPIInfo.end();
	for ( itAPIInfo = m_containerAPIInfo.begin(); itAPIInfo!=iendAPIInfo; ++itAPIInfo ) {	
		if ( ( _tcscmp( (*itAPIInfo)->m_strAPIName.c_str(), szAPIName ) == 0 )
			&& ( _tcscmp( (*itAPIInfo)->m_strLibFileName.c_str(), szLibFileName ) == 0 ) ) {
				return (*itAPIInfo)->m_bHooked;
		}
	}
	
	return false;
}

//BOOL WINAPI hm_hs_apihook::hmTrackPopupMenu(
//    HMENU hMenu,
//    UINT uFlags,
//    int x,
//    int y,
//    int nReserved,
//    HWND hWnd,
//	CONST RECT *prcRect) {
//		return ::hmTrackPopupMenu( hMenu, uFlags, x, y, nReserved, hWnd, prcRect );
//}