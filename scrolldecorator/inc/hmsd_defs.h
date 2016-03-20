#ifndef __HMSD_DEFS_H__
#define __HMSD_DEFS_H__

struct hmsd_wndmsg {
	hmsd_wndmsg( HWND hWnd = 0, UINT message = 0, WPARAM wParam = 0, LPARAM lParam = 0 );
	~hmsd_wndmsg();
	HWND m_hWnd;
	UINT m_message;
	WPARAM m_wParam;
	LPARAM m_lParam;
	LRESULT m_lRes;
	BOOL m_bEatWndMsg;
};


#endif //__HMSD_DEFS_H__