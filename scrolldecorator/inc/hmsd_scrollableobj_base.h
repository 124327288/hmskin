#ifndef __HMSD_SCROLLABLEOBJ_BASE_H__
#define __HMSD_SCROLLABLEOBJ_BASE_H__
#include "hmsd_scrollbar.h"
//

//
class hmsd_scrollableobj_base {
public:
	hmsd_scrollableobj_base();
	virtual ~hmsd_scrollableobj_base();

	// interface
public:
	virtual void onScrollBarPosChange( hmsd_scrollbar* pScrollBar, int nCurPos ) {}
	virtual void onScrollBarStateChange( hmsd_scrollbar* pScrollBar, 
		hmsd_scrollbar::ENUMHMSDSBSTATE eStateNew, hmsd_scrollbar::ENUMHMSDSBSTATE eStateOld ) {}
	virtual void onScrollBarLBtnDown( hmsd_scrollbar* pScrollBar, ENUMSBDISTRICT eDistrict ) {}

protected:
	void _attachWindow( HWND hWnd );
	void _setSBImageAdaptor( hmsd_imageadaptor_base* pSBImageAdaptor );
private:
	void _init();
private:
	hmsd_scrollbar* m_pScrollbarH;
	hmsd_scrollbar* m_pScrollbarV;
};



#endif //__HMSD_SCROLLABLEOBJ_BASE_H__