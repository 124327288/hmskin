#include "stdafx.h"
#include "hmsd_sbstate_init.h"
#include "hmsd_defs.h"
#include <assert.h>
//
#ifndef GET_X_LPARAM
#	define GET_X_LPARAM( lParam ) (INT16)LOWORD( lParam )
#endif //GET_X_LPARAM
//
#ifndef GET_Y_LPARAM
#	define GET_Y_LPARAM( lParam ) (INT16)HIWORD( lParam )
#endif //GET_Y_LPARAM
//
hmsd_sbstate_init::hmsd_sbstate_init( hmsd_scrollbar* pScrollBar )
: hmsd_sbstate_base( pScrollBar ) {
}

hmsd_sbstate_init::~hmsd_sbstate_init() {

}

void hmsd_sbstate_init::OnWndMsg(  hmsd_wndmsg* pWndMsg ) {
	switch ( pWndMsg->m_message )
	{
	case WM_LBUTTONDOWN:
		{
			_On_WM_LBUTTONDOWN( pWndMsg );
		}
		break;
	case WM_LBUTTONUP:
		{
			_On_WM_LBUTTONUP( pWndMsg );
		}
		break;
	case WM_MOUSEMOVE:
		{
			_On_WM_MOUSEMOVE( pWndMsg );
		}
		break;
	case WM_KILLFOCUS:
		{
			_On_WM_KILLFOCUS( pWndMsg );
		}
		break;
	case WM_SETCURSOR:
		{
			_On_WM_SETCURSOR( pWndMsg );
		}
		break;
	default:
		break;
	}
}

void hmsd_sbstate_init::_On_WM_SETCURSOR( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_SETCURSOR ) {
		assert( FALSE );
		return;
	}
	POINT ptInScreen;
	POINT ptInClient;
	RECT rcSB;

	if ( !::GetCursorPos( &ptInScreen ) ) {
		return;
	}
	ptInClient = ptInScreen;
	::ScreenToClient( pWndMsg->m_hWnd, &ptInClient );
	m_pScrollBar->GetRect( rcSB );
	if ( !PtInRect( &rcSB, ptInClient ) )
		return;
	
	::SetCursor( ::LoadCursor( NULL, IDC_ARROW ) ) ;
	pWndMsg->m_bEatWndMsg = TRUE;
	pWndMsg->m_lRes = TRUE;
}

void hmsd_sbstate_init::_On_WM_LBUTTONDOWN( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_LBUTTONDOWN ) {
		assert( FALSE );
		return;
	}
	POINT ptLBtnDown;
	RECT rcBtnStart;
	RECT rcBtnEnd;
	RECT rcBtnThumb;

	ptLBtnDown.x = GET_X_LPARAM( pWndMsg->m_lParam );
	ptLBtnDown.y = GET_Y_LPARAM( pWndMsg->m_lParam );
	_GetBtnStartRect( rcBtnStart );
	_GetBtnEndRect( rcBtnEnd );
	_GetBtnThumbRect( rcBtnThumb );
	//
	_SetLBtnDownPoint( &ptLBtnDown );

	// check if need enter other state.
	if ( ::PtInRect( &rcBtnStart, ptLBtnDown ) ) {
		_SetState( hmsd_scrollbar::EHMSDSBSTATE_PRESS_BTN_START );
		_NotifyLBtnDown( ESBDISTRICT_START_BUTTON );
		return;
	} else if ( ::PtInRect( &rcBtnEnd, ptLBtnDown ) ) {
		_SetState( hmsd_scrollbar::EHMSDSBSTATE_PRESS_BTN_END );
		_NotifyLBtnDown( ESBDISTRICT_END_BUTTON );
		return;
	} else if ( ::PtInRect( &rcBtnThumb, ptLBtnDown ) ) {
		_SetState( hmsd_scrollbar::EHMSDSBSTATE_PRESS_BTN_THUMB );
		_NotifyLBtnDown( ESBDISTRICT_THUMB );
		return;
	} 
	
	//
	RECT rcBlankStart;
	RECT rcBlankEnd;
	if ( _GetBlankStartRect( rcBlankStart ) ) {
		if ( ::PtInRect( &rcBlankStart, ptLBtnDown ) ) {
			_NotifyLBtnDown( ESBDISTRICT_START_BLANK );
			return;
		}
	}
	if ( _GetBlankEndRect( rcBlankEnd ) ) {
		if ( ::PtInRect( &rcBlankEnd, ptLBtnDown ) ) {
			_NotifyLBtnDown( ESBDISTRICT_END_BLANK );
			return;
		}
	}

}

void hmsd_sbstate_init::_On_WM_LBUTTONUP( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_LBUTTONUP ) {
		assert( FALSE );
		return;
	}
	_SetLBtnDownPoint( NULL );
}

void hmsd_sbstate_init::_On_WM_MOUSEMOVE( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_MOUSEMOVE ) {
		assert( FALSE );
		return;
	}
	POINT ptCursor;
	
	ptCursor.x = GET_X_LPARAM( pWndMsg->m_lParam );
	ptCursor.y = GET_Y_LPARAM( pWndMsg->m_lParam );

	_CheckMouseHoverPos( ptCursor );
}

void hmsd_sbstate_init::_On_WM_KILLFOCUS( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_KILLFOCUS ) {
		assert( FALSE );
		return;
	}
	_SetLBtnDownPoint( NULL );
}

