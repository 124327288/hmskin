#include "stdafx.h"
#include "win\wndctrl_repository\hm_wndctrl_popmenu.h"

hm_wndctrl_popmenu::hm_wndctrl_popmenu() {

}
//
hm_wndctrl_popmenu::~hm_wndctrl_popmenu() {
	
}
//
LRESULT hm_wndctrl_popmenu::WndProc( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL* pbIsCallDefWndProc ) {
	switch ( uMsg )
	{
	case WM_LBUTTONDOWN:{
		}
		break;
	default:
		{
			return hm_wndctrl_base::WndProc( uMsg, wParam, lParam, pbIsCallDefWndProc );
		}
		break;
		
	}
	
	return 0;
}
//
bool hm_wndctrl_popmenu::CreateWnd( int x,
		int y,
		int nWidth,
		int nHeight,
		HWND hWndParent,
		HMENU hMenu,
		HINSTANCE hInstance ) 
{
	DWORD dwExStyle = 0;
	DWORD dwStyle = WS_POPUP;
	
	if( !hm_wndctrl_base::CreateWnd( dwExStyle, _T("hm_popmenu"), dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance ) )
		return false;
	
	return true;
}



