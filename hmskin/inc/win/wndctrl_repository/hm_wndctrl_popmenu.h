#ifndef __HM_WNDCTRL_POPMENU_H__
#define __HM_WNDCTRL_POPMENU_H__
#include "win\wndctrl_repository\hm_wndctrl_base.h"
#include "common\hm_wndmsg_publisher.h"
#include "win\frame\hm_keel_obj.h"

class hm_wndctrl_popmenu : public hm_wndctrl_base
{
public:
	hm_wndctrl_popmenu();
	virtual ~hm_wndctrl_popmenu();

	// interface of hm_wndctrl_popmenu.
public:
	virtual LRESULT WndProc( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL* pbIsCallDefWndProc );

	// operation.
public:
	bool CreateWnd( int x,
		int y,
		int nWidth,
		int nHeight,
		HWND hWndParent,
		HMENU hMenu,
		HINSTANCE hInstance );
};


#endif //__HM_WNDCTRL_POPMENU_H__