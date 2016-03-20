#ifndef __HM_HS_APIHOOK_H__
#define __HM_HS_APIHOOK_H__
#include <string>
#include <deque>
#include "tchar.h"

class hm_hs_apihook{
	// type define 
public:
	typedef std::basic_string< TCHAR > string_type;
	struct apiinfo {
		string_type m_strAPIName;
		string_type m_strLibFileName;
		unsigned char m_originCodeBuf[ 5 ];
		unsigned char m_newCodeBuf[ 5 ];
		bool m_bHooked;
		void* m_pfnOriginAddr;
		HMODULE m_hModule;
		DWORD m_dwPID;
	};
	typedef std::deque< apiinfo* > apiinfo_container_type;
	
	// operation
public:
	bool hookOnTrackPopupMenu( const TCHAR* szAPIName, const TCHAR* szLibFileName );
	bool hookOff( const TCHAR* szAPIName, const TCHAR* szLibFileName );

	// helper
private:
	void _hookStart( apiinfo* pAPIInfo );
	void _hookStop( apiinfo* pAPIInfo );
	bool _hookStart( const TCHAR* szAPIName, const TCHAR* szLibFileName );
	bool _hookStop( const TCHAR* szAPIName, const TCHAR* szLibFileName );
	bool _isHookStarted( const TCHAR* szAPIName, const TCHAR* szLibFileName );
	bool _unregHook( const TCHAR* szAPIName, const TCHAR* szLibFileName );
	bool _isRegHook( const TCHAR* szAPIName, const TCHAR* szLibFileName );
	//
	bool _regHookTrackPopupMenu( const TCHAR* szAPIName, const TCHAR* szLibFileName );
	void _prepareCodeHookTrackPopupMenu( void* pfnOrigin, unsigned char originCodeBuf[ 5 ], unsigned char newCodeBuf[ 5 ] );

	//
private:
	//static BOOL WINAPI hmTrackPopupMenu(
 //   HMENU hMenu,
 //   UINT uFlags,
 //   int x,
 //   int y,
 //   int nReserved,
 //   HWND hWnd,
 //   CONST RECT *prcRect);

public:
	hm_hs_apihook();
	virtual ~hm_hs_apihook();

private:
	apiinfo_container_type m_containerAPIInfo;

};

extern hm_hs_apihook g_instanceAPIHook;
#define APIHOOK_INSTANCE (&g_instanceAPIHook)




#endif //__HM_HS_APIHOOK_H__