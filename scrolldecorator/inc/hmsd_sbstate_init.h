#ifndef _HMSD_SBSTATE_INIT_H__
#define _HMSD_SBSTATE_INIT_H__
#include "hmsd_scrollbar.h"
//
struct hmsd_wndmsg;
//
class hmsd_sbstate_init : public hmsd_sbstate_base{
public:
	hmsd_sbstate_init( hmsd_scrollbar* pScrollBar );
	virtual ~hmsd_sbstate_init();

// interface of hmsd_sbstate_base
public:
	virtual void OnWndMsg( hmsd_wndmsg* pWndMsg );
	
private:
	void _On_WM_LBUTTONDOWN( hmsd_wndmsg* pWndMsg );
	void _On_WM_LBUTTONUP( hmsd_wndmsg* pWndMsg );
	void _On_WM_MOUSEMOVE( hmsd_wndmsg* pWndMsg );
	void _On_WM_KILLFOCUS( hmsd_wndmsg* pWndMsg );
	void _On_WM_SETCURSOR( hmsd_wndmsg* pWndMsg );


};



#endif //_HMSD_SBSTATE_INIT_H__