#include "stdafx.h"
#include "hmsd_scrollbar.h"
#include "hmsd_sbstate_init.h"
#include "hmsd_sbstate_pressbtnarrow.h"
#include "hmsd_sbstate_pressbtnthumb.h"
#include "hmsd_imageadaptor_base.h"
#include "hmsd_defs.h"
#include "FuncPack.h"
#include <assert.h>
//
#define IMOSBFLAG_NONE ( 0x00000000 )
#define IMOSBFLAG_VISIBLE ( 0x00000001 )
//
#define IMOSB_THUMB_THICK_MIN (16)
//
hmsd_sbstate_base::hmsd_sbstate_base( hmsd_scrollbar* pScrollBar ) 
: m_pScrollBar( pScrollBar ){
}

hmsd_sbstate_base::~hmsd_sbstate_base() {

}

void hmsd_sbstate_base::_GetBtnStartRect( RECT& rectDest ) {
	m_pScrollBar->_GetBtnStartRect( rectDest );
}

void hmsd_sbstate_base::_GetBtnEndRect( RECT& rectDest ) {
	m_pScrollBar->_GetBtnEndRect( rectDest );
}

BOOL hmsd_sbstate_base::_GetBtnThumbRect( RECT& rectDest ) {
	return m_pScrollBar->_GetBtnThumbRect( rectDest );
}

BOOL hmsd_sbstate_base::_GetBlankStartRect( RECT& rectDest ) {
	return m_pScrollBar->_GetBlankStartRect( rectDest );
}

BOOL hmsd_sbstate_base::_GetBlankEndRect( RECT& rectDest ) {
	return m_pScrollBar->_GetBlankEndRect( rectDest );
}

void hmsd_sbstate_base::_SetLBtnDownPoint( const POINT* pPtLBtnDown ) {
	if ( !m_pScrollBar ) {
		assert( FALSE );
		return;
	}
	m_pScrollBar->_SetLBtnDownPoint( pPtLBtnDown );
}

BOOL hmsd_sbstate_base::_GetLBtnDownPoint( POINT& ptLBtnDown ) {
	if ( !m_pScrollBar ) {
		assert( FALSE );
		return TRUE;
	}
	return m_pScrollBar->_GetLBtnDownPoint( ptLBtnDown );
}

int hmsd_sbstate_base::_GetState() {
	return m_pScrollBar->_GetState(); 
}

BOOL hmsd_sbstate_base::_SetState( int eState ) {
	return m_pScrollBar->_SetState( (hmsd_scrollbar::ENUMHMSDSBSTATE)eState );
}

int hmsd_sbstate_base::_GetLBtnDownPos()  {
	return m_pScrollBar->_GetLBtnDownPos();
}

unsigned int hmsd_sbstate_base::_GetSpace() {
	return m_pScrollBar->_GetSpace();
}

void hmsd_sbstate_base::_CheckMouseHoverPos( POINT ptCursor ) {
	m_pScrollBar->_CheckMouseHoverPos( ptCursor );
}

void hmsd_sbstate_base::_NotifyLBtnDown( ENUMSBDISTRICT eDistrict ) {
	m_pScrollBar->_NotifyLBtnDown( eDistrict );
}

//
hmsd_scrollbar::hmsd_scrollbar( ENUMSCROLLTYPE eType )
: m_hWndAttached( NULL )
, m_eScrollType( eType )
, m_uBtnStartThick( 10 )
, m_uBtnEndThick( 10 )
, m_uBtnThumbThick( 40 )
, m_nStartPos( 0 )
, m_nEndPos( 100 )
, m_nCurPos( 50 )
, m_nLBtnDownPosMark( 0 )
, m_uWidthRaw( 10 )
, m_uFlag( IMOSBFLAG_VISIBLE )
, m_eState( EHMSDSBSTATE_INIT )
, m_pPtLBtnDown( NULL )
, m_eMouseHoverPos( EMHOVERPOS_NONE )
, m_pImageAdaptor( NULL )
{
	memset( &m_rect, 0, sizeof(RECT) );

	m_aryStateProcessors[ EHMSDSBSTATE_INIT ] = new hmsd_sbstate_init( this );
	m_aryStateProcessors[ EHMSDSBSTATE_PRESS_BTN_START ] = new hmsd_sbstate_pressbtnarrow( this, hmsd_sbstate_pressbtnarrow::EBTNARROW_START );
	m_aryStateProcessors[ EHMSDSBSTATE_PRESS_BTN_END ] = new hmsd_sbstate_pressbtnarrow( this, hmsd_sbstate_pressbtnarrow::EBTNARROW_END );
	m_aryStateProcessors[ EHMSDSBSTATE_PRESS_BTN_THUMB ] = new hmsd_sbstate_pressbtnthumb( this );
}

hmsd_scrollbar::~hmsd_scrollbar() {
	unsigned int uIMOSBStateIndex;

	for ( uIMOSBStateIndex = 0; uIMOSBStateIndex<EHMSDSBSTATE_COUNT; ++uIMOSBStateIndex ) {
		delete m_aryStateProcessors[ uIMOSBStateIndex ];
		m_aryStateProcessors[ uIMOSBStateIndex ] = NULL;
	}
	
	if ( m_pPtLBtnDown ) {
		delete m_pPtLBtnDown;
		m_pPtLBtnDown = NULL;
	}
}

void hmsd_scrollbar::SetVisible( BOOL bVisible ) {
	if ( bVisible ) {
		m_uFlag |= IMOSBFLAG_VISIBLE;
	} else {
		m_uFlag &= ~IMOSBFLAG_VISIBLE;
	}
}

BOOL hmsd_scrollbar::IsVisible() {
	return (m_uFlag & IMOSBFLAG_VISIBLE);
}

hmsd_imageadaptor_base* hmsd_scrollbar::SetImageAdaptor( hmsd_imageadaptor_base* pImageAdaptorNew ) {
	hmsd_imageadaptor_base* pImageAdaptorOld = NULL;

	pImageAdaptorOld = m_pImageAdaptor;
	m_pImageAdaptor = pImageAdaptorNew;

	return pImageAdaptorOld;
}

void hmsd_scrollbar::AttachWindow( HWND hWnd ) {
	m_hWndAttached = hWnd;
}

void hmsd_scrollbar::Move( int X, int Y, int nWidth, int nHeight, BOOL bRepaint ) {
	if ( !m_hWndAttached )
		return;
	if ( ( m_rect.left == X ) && ( m_rect.right == ( X + nWidth ) )
		&& ( m_rect.top == Y ) && ( m_rect.bottom == ( Y + nHeight ) ) )
		return;

	//
	::SetRect( &m_rect, X, Y, X + nWidth, Y + nHeight );

	if ( bRepaint )  {
		HDC hDC;
		
		hDC = ::GetDC( m_hWndAttached );
		CFuncPack fpkReleaseDC( ::ReleaseDC, m_hWndAttached, hDC );
		// draw
		this->Draw( hDC, m_rect );
	}
}

void hmsd_scrollbar::GetRect( RECT& rect ) {
	rect = m_rect;
}

void hmsd_scrollbar::OnWndMsg( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg ) {
		assert( FALSE );
		return;
	}
	if ( m_eState >= EHMSDSBSTATE_COUNT ) {
		assert( FALSE );
		return;
	}
	m_aryStateProcessors[ m_eState ]->OnWndMsg( pWndMsg );
}

BOOL hmsd_scrollbar::SetRange( int nStartPos, int nEndPos ) {
	m_nStartPos = nStartPos;
	m_nEndPos = nEndPos;
	return TRUE;
}

BOOL hmsd_scrollbar::SetCurPos( int nCurPos, BOOL bRePaint, BOOL bNotify2OutSide ) {
	//
	if ( !_IsPosInRange( nCurPos ) )
		return FALSE;
	//if ( m_nCurPos == nCurPos )
	//	return TRUE;
	//
	m_nCurPos = nCurPos;
	//
	if ( bRePaint ) {
		HDC hDC;

		hDC = ::GetDC( m_hWndAttached );
		Draw( hDC, m_rect );
		::ReleaseDC( m_hWndAttached, hDC );
	}
	//
	if ( bNotify2OutSide ) {
		_NotifyCurPosChange();
	}

	return TRUE;
}

void hmsd_scrollbar::_CheckMouseHoverPos( POINT ptCursor ) {
	RECT rcBtnStart;
	RECT rcBtnEnd;
	RECT rcBtnThumb;

	//
	_GetBtnStartRect( rcBtnStart );
	_GetBtnEndRect( rcBtnEnd );
	_GetBtnThumbRect( rcBtnThumb );
	
	// check 
	if ( ::PtInRect( &rcBtnStart, ptCursor ) ) {
		_SetMouseHoverPos( hmsd_scrollbar::EMHOVERPOS_BTN_START );
		return;
	} else if ( ::PtInRect( &rcBtnEnd, ptCursor ) ) {
		_SetMouseHoverPos( hmsd_scrollbar::EMHOVERPOS_BTN_END );
		return;
	} else if ( ::PtInRect( &rcBtnThumb, ptCursor ) ) {
		_SetMouseHoverPos( hmsd_scrollbar::EMHOVERPOS_BTN_THUMB );
		return;
	} else {
		_SetMouseHoverPos( hmsd_scrollbar::EMHOVERPOS_NONE );
		return;
	}
}

void hmsd_scrollbar::_SetMouseHoverPos( ENUMMOUSEHOVERPOS eMouseHoverPos ) {
	ENUMMOUSEHOVERPOS eMouseHoverPosOld;

	eMouseHoverPosOld = m_eMouseHoverPos;
	m_eMouseHoverPos = eMouseHoverPos;

	if ( eMouseHoverPosOld != m_eMouseHoverPos ) {
		Update2Wnd();
	}
}

void hmsd_scrollbar::_NotifyCurPosChange() {
	m_eventTriggerPosChange.invoke( this, m_nCurPos );
}

void hmsd_scrollbar::_NotifyStateChange( ENUMHMSDSBSTATE eStateNew, ENUMHMSDSBSTATE eStateOld ) {
	m_eventTriggerSBStateChange.invoke( this, eStateNew, eStateOld );
}

void hmsd_scrollbar::_NotifyLBtnDown( ENUMSBDISTRICT eDistrictLBtnDown ) {
	m_eventTriggerLBtnDown.invoke( this, eDistrictLBtnDown );
}

BOOL hmsd_scrollbar::_IsPosInRange( int nPosTest )  const {
	if ( m_nStartPos < m_nEndPos ) {
		return ( nPosTest >= m_nStartPos ) && ( nPosTest <= m_nEndPos );
	} else {
		return ( nPosTest >= m_nEndPos ) && ( nPosTest <= m_nStartPos );
	}

	assert( FALSE );
	return FALSE;
}

BOOL hmsd_scrollbar::_GetBlankStartRect( RECT& rcBlankStart ) {
	switch ( m_eScrollType )
	{
	case ESB_VERT:
		{
			unsigned int uSpace;

			uSpace = _GetSpace();
			if ( uSpace == 0 )
				return FALSE;
			if ( !_IsPosInRange( m_nCurPos ) )
				return FALSE;
			
			rcBlankStart.left = m_rect.left;
			rcBlankStart.right = m_rect.right;
			rcBlankStart.top = m_rect.top + m_uBtnStartThick;
			rcBlankStart.bottom = m_rect.top + m_uBtnStartThick 
				+ ( ( m_nEndPos - m_nStartPos ) == 0 ? 0 : uSpace * ( m_nCurPos - m_nStartPos ) / ( m_nEndPos - m_nStartPos ) );
			return rcBlankStart.top < rcBlankStart.bottom;
		}
		break;
	case ESB_HORZ:
		{
			unsigned int uSpace;

			uSpace = _GetSpace();
			if ( uSpace == 0 )
				return FALSE;
			if ( !_IsPosInRange( m_nCurPos ) )
				return FALSE;

			rcBlankStart.top = m_rect.top;
			rcBlankStart.bottom = m_rect.bottom;
			rcBlankStart.left = m_rect.left + m_uBtnStartThick;
			rcBlankStart.right = m_rect.left + m_uBtnStartThick
				+ ( ( m_nEndPos - m_nStartPos ) == 0 ? 0 : uSpace * ( m_nCurPos - m_nStartPos ) / ( m_nEndPos - m_nStartPos ) );
			return rcBlankStart.left < rcBlankStart.right;
		}
		break;
	default:
		break;
	}

	assert( FALSE );
	return FALSE;
}

BOOL hmsd_scrollbar::_GetBlankEndRect( RECT& rcBlankEnd ) {
	switch ( m_eScrollType )
	{
	case ESB_VERT:
		{
			unsigned int uSpace;

			uSpace = _GetSpace();
			if ( uSpace == 0 )
				return FALSE;
			if ( !_IsPosInRange( m_nCurPos ) )
				return FALSE;

			rcBlankEnd.left = m_rect.left;
			rcBlankEnd.right = m_rect.right;
			rcBlankEnd.top = m_rect.top + m_uBtnStartThick 
				+ ( ( m_nEndPos - m_nStartPos ) == 0 ? 0 : uSpace * ( m_nCurPos - m_nStartPos ) / ( m_nEndPos - m_nStartPos ) );
			rcBlankEnd.bottom = m_rect.bottom - m_uBtnEndThick;
			return rcBlankEnd.top < rcBlankEnd.bottom;
		}
		break;
	case ESB_HORZ:
		{
			unsigned int uSpace;

			uSpace = _GetSpace();
			if ( uSpace == 0 )
				return FALSE;
			if ( !_IsPosInRange( m_nCurPos ) )
				return FALSE;

			rcBlankEnd.top = m_rect.top;
			rcBlankEnd.bottom = m_rect.bottom;
			rcBlankEnd.left = m_rect.left + m_uBtnStartThick
				+ ( ( m_nEndPos - m_nStartPos ) == 0 ? 0 : uSpace * ( m_nCurPos - m_nStartPos ) / ( m_nEndPos - m_nStartPos ) );
			rcBlankEnd.right = m_rect.right - m_uBtnEndThick;
			return rcBlankEnd.left < rcBlankEnd.right;
		}
		break;
	default:
		break;
	}

	assert( FALSE );
	return FALSE;
}

void hmsd_scrollbar::_GetBtnStartRect( RECT& rcBtnStart ) {
	switch ( m_eScrollType )
	{
	case ESB_VERT:
		{
			rcBtnStart.left = m_rect.left;
			rcBtnStart.right = m_rect.right;
			rcBtnStart.top = m_rect.top;
			rcBtnStart.bottom = m_rect.top + m_uBtnStartThick;
			return;
		}
		break;
	case ESB_HORZ:
		{
			rcBtnStart.top = m_rect.top;
			rcBtnStart.bottom = m_rect.bottom;
			rcBtnStart.left = m_rect.left;
			rcBtnStart.right = m_rect.left + m_uBtnStartThick;
			return;
		}
		break;
	default:
		break;
	}

	assert( FALSE );
}

void hmsd_scrollbar::_GetBtnEndRect( RECT& rcBtnEnd ) {
	switch ( m_eScrollType )
	{
	case ESB_VERT:
		{
			rcBtnEnd.left = m_rect.left;
			rcBtnEnd.right = m_rect.right;
			rcBtnEnd.bottom = m_rect.bottom;
			rcBtnEnd.top = m_rect.bottom - m_uBtnEndThick;
			return;
		}
		break;
	case ESB_HORZ:
		{
			rcBtnEnd.top = m_rect.top;
			rcBtnEnd.bottom = m_rect.bottom;
			rcBtnEnd.right = m_rect.right;
			rcBtnEnd.left = m_rect.right - m_uBtnEndThick;
			return;
		}
		break;
	default:
		break;
	}
	assert( FALSE );
}

BOOL hmsd_scrollbar::_GetBtnThumbRect( RECT& rcBtnThumb ) {
	switch ( m_eScrollType )
	{
	case ESB_VERT:
		{
			unsigned int uSpace;

			uSpace = _GetSpace();
			if ( uSpace == 0 )
				return FALSE;
			if ( !_IsPosInRange( m_nCurPos ) )
				return FALSE;
			
			rcBtnThumb.left = m_rect.left;
			rcBtnThumb.right = m_rect.right;
			rcBtnThumb.top = m_rect.top + m_uBtnStartThick 
				+ ( ( m_nEndPos - m_nStartPos ) == 0 ? 0 : uSpace * ( m_nCurPos - m_nStartPos ) / ( m_nEndPos - m_nStartPos ) );
			rcBtnThumb.bottom = rcBtnThumb.top + m_uBtnThumbThick;

			return TRUE;
		}
		break;
	case ESB_HORZ:
		{
			unsigned int uSpace;

			uSpace = _GetSpace();
			if ( uSpace == 0 )
				return FALSE;
			if ( !_IsPosInRange( m_nCurPos ) )
				return FALSE;

			rcBtnThumb.top = m_rect.top;
			rcBtnThumb.bottom = m_rect.bottom;
			rcBtnThumb.left = m_rect.left + m_uBtnStartThick + uSpace * ( m_nCurPos - m_nStartPos ) / ( m_nEndPos - m_nStartPos );
			rcBtnThumb.right = rcBtnThumb.left + m_uBtnThumbThick;

			return TRUE;
		}
		break;
	default:
		break;
	}
	assert( FALSE );
	return FALSE;
}

void hmsd_scrollbar::_MarkLBtnDownPos() {
	m_nLBtnDownPosMark = m_nCurPos;
}

void hmsd_scrollbar::_SetLBtnDownPoint( const POINT* pPtLBtnDown ) {
	if ( pPtLBtnDown ) {
		if ( !m_pPtLBtnDown ) {
			m_pPtLBtnDown = new POINT;
		}
		m_pPtLBtnDown->x = pPtLBtnDown->x;
		m_pPtLBtnDown->y = pPtLBtnDown->y;
		_MarkLBtnDownPos();
	} else {
		if ( m_pPtLBtnDown )  {
			delete m_pPtLBtnDown;
			m_pPtLBtnDown = NULL;
		}
	}
}

BOOL hmsd_scrollbar::_GetLBtnDownPoint( POINT& ptLBtnDown ) {
	if ( !m_pPtLBtnDown ) 
		return FALSE;
	
	ptLBtnDown.x = m_pPtLBtnDown->x;
	ptLBtnDown.y = m_pPtLBtnDown->y;
	return TRUE;
}

BOOL hmsd_scrollbar::_SetState( ENUMHMSDSBSTATE eState ) {
	ENUMHMSDSBSTATE eStateOld;

	eStateOld = m_eState;
	// check data integrity
	switch ( eState )
	{
	case EHMSDSBSTATE_INIT:
		{
			if ( m_pPtLBtnDown ) {
				assert( FALSE );
				return FALSE;
			}
			
		}
		break;
	case EHMSDSBSTATE_PRESS_BTN_START:
		{
			if ( !m_pPtLBtnDown ) {
				assert( FALSE );
				return FALSE;
			}
			if ( m_eState != EHMSDSBSTATE_INIT ) {
				assert( FALSE );
				return FALSE;
			}
		}
		break;
	case EHMSDSBSTATE_PRESS_BTN_END:
		{
			if ( !m_pPtLBtnDown ) {
				assert( FALSE );
				return FALSE;
			}
			if ( m_eState != EHMSDSBSTATE_INIT ) {
				assert( FALSE );
				return FALSE;
			}
		}
		break;
	case EHMSDSBSTATE_PRESS_BTN_THUMB:
		{
			if ( !m_pPtLBtnDown ) {
				assert( FALSE );
				return FALSE;
			}
			if ( m_eState != EHMSDSBSTATE_INIT ) {
				assert( FALSE );
				return FALSE;
			}
		}
		break;
	default:
		{
			assert( FALSE );
			return FALSE;
		}
		break;
	}

	m_eState = eState;
	if ( eStateOld != m_eState ) {
		_NotifyStateChange( m_eState, eStateOld );
		Update2Wnd();
	}

	return TRUE;
}

unsigned int hmsd_scrollbar::_GetSpace() {
	switch ( m_eScrollType )
	{
	case ESB_VERT:
		{
			if ( m_rect.bottom - m_rect.top <= 0 )
				return 0;
			if ( ( m_rect.bottom - m_rect.top ) < ( m_uBtnStartThick + m_uBtnEndThick + m_uBtnThumbThick ) )
				return 0;
			return ( m_rect.bottom - m_rect.top ) - ( m_uBtnStartThick + m_uBtnEndThick + m_uBtnThumbThick );
		}
		break;
	case ESB_HORZ:
		{
			if ( m_rect.right - m_rect.left <= 0 )
				return 0;
			if ( ( m_rect.right - m_rect.left ) < ( m_uBtnStartThick + m_uBtnEndThick + m_uBtnThumbThick ) )
				return 0;
			return ( m_rect.right - m_rect.left ) - ( m_uBtnStartThick + m_uBtnEndThick + m_uBtnThumbThick );			
		}
		break;
	default:
		assert( FALSE );
		break;
	}

	assert( FALSE );
	return 0;
}

BOOL hmsd_scrollbar::SetBtnThumbThick( unsigned int uThumbBtnThick, BOOL bRepaint ) {
	if ( m_rect.bottom - m_rect.top <= 0 )
		return FALSE;
	if ( ( m_rect.bottom - m_rect.top ) <= m_uBtnStartThick + m_uBtnEndThick ) {
		assert( FALSE );
		return FALSE;
	}
	if ( ( m_rect.bottom - m_rect.top - m_uBtnStartThick - m_uBtnEndThick ) < uThumbBtnThick ) {
		assert( FALSE );
		return FALSE;
	}

	m_uBtnThumbThick = max( uThumbBtnThick, IMOSB_THUMB_THICK_MIN );

	if ( bRepaint ) {
		Update2Wnd();
	}
	return uThumbBtnThick >= IMOSB_THUMB_THICK_MIN;
}

void hmsd_scrollbar::Update2Wnd() {
	HDC hDC;

	hDC = ::GetDC( m_hWndAttached );
	Draw( hDC, m_rect );
	::ReleaseDC( m_hWndAttached, hDC );
}

void hmsd_scrollbar::Draw( HDC hDC, const RECT& rectInWndNeedUpdate ) {
	if ( !(m_uFlag & IMOSBFLAG_VISIBLE) )
		return;
	if ( !m_pImageAdaptor ) {
		return;
	}
	m_pImageAdaptor->DrawScrollBar( hDC, this );

	return;
}