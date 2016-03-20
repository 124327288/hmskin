#ifndef __WND_PROC_MGR_H__
#define __WND_PROC_MGR_H__
#include <map>

//////////////////////////////////////////////////////////////////////////
// WndProcMgr
class WndProcMgr
{
//type define
public:
	typedef std::map< HWND, WNDPROC > map_hwnd2wndproc_type;

public:
	static WndProcMgr* GetInstance();
	virtual ~WndProcMgr();
 
public:
	BOOL Attach( HWND hWndDest, WNDPROC pfnWndProcNew );
	BOOL Detach( HWND hWndDest );
	BOOL WasAttached( HWND hWndDest );
	WNDPROC GetWndProcOld( HWND hWndDest );
	
private:
	WndProcMgr();
	
private:
#pragma warning(push)
#pragma warning(disable:4251) 
	map_hwnd2wndproc_type m_mapHwnd2WndProc;
#pragma warning(pop)
	
};
#define WNDPROCMGR_INSTANCE WndProcMgr::GetInstance()

#endif //__WND_PROC_MGR_H__