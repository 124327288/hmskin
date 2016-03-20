#ifndef __HM_KEELCTRL_SCROLLVIEW_H__
#define __HM_KEELCTRL_SCROLLVIEW_H__
#include "win\keelctrl_repository\hm_keelctrl_base.h"
#include "win\wmp\hm_wmp_scrollbar.h"
#include "win\wmp\hm_wmp_viewbkcontent.h"
//
#define FLAG_CONTENTVISIBLE_DIRTY (0x00000001)
//
//class hm_keelctrl_scrollview : public hm_keelctrl_base {
//public:
//	typedef enum _ENUMSUBKEELMARKTYPE {
//		ESKM_SCROLLBAR_V = 0,
//		ESKM_SCROLLBAR_H,
//		ESKM_INNER_VIEW
//	} ENUMSUBKEELMARKTYPE;
//	typedef struct _INITIDSET {
//	    hm_keel_obj_factory::obj_id_type idScrollBarV; 
//		hm_keel_obj_factory::obj_id_type idScrollBarH;
//		hm_keel_obj_factory::obj_id_type idViewContent;
//		hm_wmp_id_type wmpIdScrollBarV;
//		hm_wmp_id_type wmpIdScrollBarH;
//		hm_wmp_id_type wmpIdViewContent;
//	} INITIDSET;
//
//public:
//	hm_keelctrl_scrollview( const INITIDSET& initIdSet );
//	virtual ~hm_keelctrl_scrollview();
// 
//	// interface of hm_cmn_observer_i
//public:
//	virtual void update( void* pSubject, UINT idEvent, long pEventParam, long pEventParam2, BOOL* pbContinue );
//
//public:
//	hm_keel_obj* getKeelObjScrollBarV();
//	hm_keel_obj* getKeelObjScrollBarH();
//	hm_keel_obj* getKeelObjViewContent();
//	hm_wmp_scrollbar* getWMPScrollBarV();
//	hm_wmp_scrollbar* getWMPScrollBarH();
//	hm_wmp_viewbkcontent* getWMPViewContent();
//
//public:
//	void setContentHeight( unsigned int nHeight );
//	void setContentWidth( unsigned int nWidth );
//	unsigned int getContentHeight() { return m_uContentHeight; }
//	unsigned int getContentWidth() { return m_uContentWidth; }
//	void getContentVisibleRect( RECT& rcContentVisible ) { rcContentVisible = m_rcContentVisible; }
//	bool isContentVisibleRectDirty() { return FLAG_CONTENTVISIBLE_DIRTY & m_uFlag; }
//	void calcContentVisibleRect( const SIZE& sizeCanvas );	
//	void updateScrollBarPos();
//
//private:
//	void _init( const INITIDSET& initIdSet );
//	void _uninit();
//
//private:
//	hm_wmp_scrollbar* m_pWMPScrollBarV;
//	hm_wmp_scrollbar* m_pWMPScrollBarH;
//	hm_wmp_viewbkcontent* m_pWMPViewBKGND;
//	unsigned m_uContentWidth;
//	unsigned m_uContentHeight;
//	RECT m_rcContentVisible;
//	unsigned int m_uFlag;
//	HWND m_hWndCanvas; 
//};


#endif //__HM_KEELCTRL_SCROLLVIEW_H__

