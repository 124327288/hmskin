#ifndef __HMSD_SBSTATE_PRESSBTNTHUMB_H__
#define __HMSD_SBSTATE_PRESSBTNTHUMB_H__
#include "hmsd_scrollbar.h"
//
struct hmsd_wndmsg;
//
class hmsd_sbstate_pressbtnthumb : public hmsd_sbstate_base{
public:
	hmsd_sbstate_pressbtnthumb( hmsd_scrollbar* pScrollBar );
	virtual ~hmsd_sbstate_pressbtnthumb();

	// interface of hmsd_sbstate_base
public:
	virtual void OnWndMsg( hmsd_wndmsg* pWndMsg );

private:
	void _On_WM_LBUTTONDOWN( hmsd_wndmsg* pWndMsg );
	void _On_WM_LBUTTONUP( hmsd_wndmsg* pWndMsg );
	void _On_WM_MOUSEMOVE( hmsd_wndmsg* pWndMsg );
	void _On_WM_KILLFOCUS( hmsd_wndmsg* pWndMsg );

private:
	int _CalcCurPos( POINT ptLBtnDown, POINT ptMouseCur, int nPosLBtnDown, int& nPosCurCalc );
};



#endif //__HMSD_SBSTATE_PRESSBTNTHUMB_H__