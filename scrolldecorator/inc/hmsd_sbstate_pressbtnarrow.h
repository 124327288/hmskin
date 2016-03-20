#ifndef __HMSD_SBSTATE_PRESSBTNARROW_H__
#define __HMSD_SBSTATE_PRESSBTNARROW_H__
#include "hmsd_scrollbar.h"
//
struct hmsd_wndmsg;
//
class hmsd_sbstate_pressbtnarrow : public hmsd_sbstate_base{
public:
	typedef enum _ENUMBTNARROWTYPE {
		EBTNARROW_START = 0,
		EBTNARROW_END,
	} ENUMBTNARROWTYPE;
public:
	hmsd_sbstate_pressbtnarrow( hmsd_scrollbar* pScrollBar, ENUMBTNARROWTYPE eBtnArrowType );
	virtual ~hmsd_sbstate_pressbtnarrow();

	// interface of hmsd_sbstate_base
public:
	virtual void OnWndMsg( hmsd_wndmsg* pWndMsg );

private:
	void _On_WM_LBUTTONDOWN( hmsd_wndmsg* pWndMsg );
	void _On_WM_LBUTTONUP( hmsd_wndmsg* pWndMsg );
	void _On_WM_MOUSEMOVE( hmsd_wndmsg* pWndMsg );
	void _On_WM_KILLFOCUS( hmsd_wndmsg* pWndMsg );

protected:
	ENUMBTNARROWTYPE m_eBtnArrowType;
};



#endif //__HMSD_SBSTATE_PRESSBTNARROW_H__