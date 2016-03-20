#ifndef __IMOSCROLLBAR_H__
#define __IMOSCROLLBAR_H__
#include <map>
#include "hmcmn_event_trigger.h"
//////////////////////////////////////////////////////////////////////////
class hmsd_scrollbar;
struct hmsd_wndmsg;
enum ENUMSBDISTRICT {
	ESBDISTRICT_START_BUTTON = 0,
	ESBDISTRICT_END_BUTTON,
	ESBDISTRICT_START_BLANK,
	ESBDISTRICT_END_BLANK,
	ESBDISTRICT_THUMB
} ;
//////////////////////////////////////////////////////////////////////////
class hmsd_sbstate_base {
public:
	hmsd_sbstate_base( hmsd_scrollbar* pScrollBar );
	virtual ~hmsd_sbstate_base();
	
public:
	virtual void OnWndMsg( hmsd_wndmsg* pWndMsg ) = 0;
	
protected:
	void _GetBtnStartRect( RECT& rectDest );
	void _GetBtnEndRect( RECT& rectDest );
	BOOL _GetBtnThumbRect( RECT& rectDest );
	BOOL _GetBlankStartRect( RECT& rectDest );
	BOOL _GetBlankEndRect( RECT& rectDest );
	void _SetLBtnDownPoint( const POINT* pPtLBtnDown );
	BOOL _GetLBtnDownPoint( POINT& ptLBtnDown );
	int _GetState();
	BOOL _SetState( int eState );
	int _GetLBtnDownPos();
	unsigned int _GetSpace();
	void _CheckMouseHoverPos( POINT ptCursor );
	void _NotifyLBtnDown( ENUMSBDISTRICT eDistrict );

protected:
	hmsd_scrollbar* m_pScrollBar;
};
//////////////////////////////////////////////////////////////////////////
// hmsd_scrollbar:
//
// horizontal( ESB_HORZ ):
//		|-------------------------------------------------------------------|         ------
//		|	<	|					|	=	|						|	>	|         m_widthRaw
//		|-------------------------------------------------------------------|         ------
//		m_uBtnStartThick		m_uBtnThumbThick					 m_uBtnEndThick
//
//
// vertical( ESB_VERT ):
//		|------|     -----
//		|  ^   |	m_uBtnStartThick 
//		|------|	 -----	
//		|      |	   	
//		|      |		
//		|      |	
//		|      |	   
//		|------|	-----
//		|      |		
//		|  ||  |	m_uBtnThumbThick 
//		|      |		
//		|------|	-----
//		|      |		
//		|      |		
//		|      |		
//		|      |		
//		|      |		
//		|      |		
//		|      |		
//		|      |		
//		|      |		
//		|------|	-----	
//		|  v   |	m_uBtnEndThick	
//		|------|    -----
//
//      |      |
//      m_widthRaw
//
//////////////////////////////////////////////////////////////////////////
#define SPCCID_INVALID (0)
#define SBSCCID_INVALID (0)
#define SBLBDCID_INVALID (0)
class hmsd_scrollbar {
	friend class hmsd_sbstate_base;
	friend class hmsd_imageadaptor_base;
public:
	typedef enum _ENUMSCROLLTYPE { 
		ESB_HORZ = 0, // Sets standard horizontal scroll bar.
		ESB_VERT      // Sets standard vertical scroll bar.
	} ENUMSCROLLTYPE;
	typedef enum _ENUMHMSDSBSTATE{
		EHMSDSBSTATE_INIT = 0,
		EHMSDSBSTATE_PRESS_BTN_START,
		EHMSDSBSTATE_PRESS_BTN_END,
		EHMSDSBSTATE_PRESS_BTN_THUMB,
		EHMSDSBSTATE_COUNT,
	} ENUMHMSDSBSTATE;
	typedef enum _ENUMMOUSEHOVERPOS {
		EMHOVERPOS_NONE = 0,
		EMHOVERPOS_BTN_START,
		EMHOVERPOS_BTN_END,
		EMHOVERPOS_BTN_THUMB,
		EMHOVERPOS_COUNT,
	} ENUMMOUSEHOVERPOS;
public:
	hmsd_scrollbar( ENUMSCROLLTYPE eType );
	virtual ~hmsd_scrollbar();
	
public:
	void OnWndMsg( hmsd_wndmsg* pWndMsg );
	
	// operation.
public:
	hmsd_imageadaptor_base* SetImageAdaptor( hmsd_imageadaptor_base* pImageAdaptorNew );
	void AttachWindow( HWND hWnd );
	void Move( int X, int Y, int nWidth, int nHeight, BOOL bRepaint = FALSE );
	void GetRect( RECT& rect );
	void Draw( HDC hDC, const RECT& rectInWndNeedUpdate );
	void Update2Wnd();
	unsigned int GetWidthRaw() { return m_uWidthRaw; }
	void SetWidthRaw( unsigned int uWidthRaw ) { m_uWidthRaw = uWidthRaw; }
	void SetVisible( BOOL bVisible );
	BOOL IsVisible();
	BOOL SetRange( int nStartPos, int nEndPos );
	void GetRange( int& nStartPos, int& nEndPos ) const { nStartPos = m_nStartPos; nEndPos = m_nEndPos; };
	BOOL SetCurPos( int nCurPos, BOOL bRePaint = FALSE, BOOL bNotify2OutSide = TRUE );
	int GetCurPos() const { return m_nCurPos; }
	BOOL SetBtnThumbThick( unsigned int uThumbBtnThick, BOOL bRepaint = FALSE );
	unsigned int GetBtnStartThick() { return m_uBtnStartThick; }
	void SetBtnStartThick( unsigned int uBtnStartThick ) { m_uBtnStartThick = uBtnStartThick; }
	unsigned int GetBtnEndThick() { return m_uBtnEndThick; }
	void SetBtnEndThick( unsigned int uBtnEndThick ) { m_uBtnEndThick = uBtnEndThick; }
	unsigned int GetBtnThumbThick() { return m_uBtnThumbThick; }
	ENUMSCROLLTYPE GetType() { return m_eScrollType; }
public:
	hmcmn::hmcmn_event_trigger_arg2<void, hmsd_scrollbar*, int> m_eventTriggerPosChange;
	hmcmn::hmcmn_event_trigger_arg3<void, hmsd_scrollbar*, ENUMHMSDSBSTATE, ENUMHMSDSBSTATE> m_eventTriggerSBStateChange;
	hmcmn::hmcmn_event_trigger_arg2<void, hmsd_scrollbar*, ENUMSBDISTRICT > m_eventTriggerLBtnDown;

private:
	BOOL _IsPosInRange( int nPosTest ) const;
	void _GetBtnStartRect( RECT& rcBtnStart );
	void _GetBtnEndRect( RECT& rcBtnEnd );
	BOOL _GetBtnThumbRect( RECT& rcBtnThumb );
	BOOL _GetBlankStartRect( RECT& rcBlankStart );
	BOOL _GetBlankEndRect( RECT& rcBlankEnd );
	unsigned int _GetSpace();
	void _SetLBtnDownPoint( const POINT* pPtLBtnDown );
	BOOL _GetLBtnDownPoint( POINT& ptLBtnDown );
	ENUMHMSDSBSTATE _GetState() { return m_eState; }
	BOOL _SetState( ENUMHMSDSBSTATE eState );
	void _MarkLBtnDownPos();
	int _GetLBtnDownPos() { return m_nLBtnDownPosMark; };
	void _CheckMouseHoverPos( POINT ptCursor );
	void _SetMouseHoverPos( ENUMMOUSEHOVERPOS eMouseHoverPos );
	void _NotifyCurPosChange();
	void _NotifyStateChange( ENUMHMSDSBSTATE eStateNew, ENUMHMSDSBSTATE eStateOld );
	void _NotifyLBtnDown( ENUMSBDISTRICT eDistrictLBtnDown );
	
private:
	HWND m_hWndAttached;
	ENUMSCROLLTYPE m_eScrollType;
	RECT m_rect;
	unsigned int m_uBtnStartThick;
	unsigned int m_uBtnEndThick;
	unsigned int m_uBtnThumbThick;
	int m_nStartPos;
	int m_nEndPos;
	int m_nCurPos;
	int m_nLBtnDownPosMark; // do a mark record the current position when left button down.
	unsigned int m_uWidthRaw;
	unsigned int m_uFlag;
	hmsd_sbstate_base* m_aryStateProcessors[ EHMSDSBSTATE_COUNT ];
	ENUMHMSDSBSTATE m_eState;
	POINT* m_pPtLBtnDown;
	ENUMMOUSEHOVERPOS m_eMouseHoverPos;
	hmsd_imageadaptor_base* m_pImageAdaptor;
};

#endif //__IMOSCROLLBAR_H__