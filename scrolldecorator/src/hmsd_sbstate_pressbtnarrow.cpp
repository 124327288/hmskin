#include "stdafx.h"
#include "hmsd_sbstate_pressbtnarrow.h"
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
hmsd_sbstate_pressbtnarrow::hmsd_sbstate_pressbtnarrow( hmsd_scrollbar* pScrollBar, ENUMBTNARROWTYPE eBtnArrowType )
: hmsd_sbstate_base( pScrollBar )
, m_eBtnArrowType( eBtnArrowType ) {

}

hmsd_sbstate_pressbtnarrow::~hmsd_sbstate_pressbtnarrow() {

}

void hmsd_sbstate_pressbtnarrow::OnWndMsg( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg ) {
		assert( FALSE );
		return;
	}
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
	default:
		break;
	}
}

void hmsd_sbstate_pressbtnarrow::_On_WM_LBUTTONDOWN( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_LBUTTONDOWN ) {
		assert( FALSE );
		return;
	}
	assert( FALSE );
}

void hmsd_sbstate_pressbtnarrow::_On_WM_LBUTTONUP( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_LBUTTONUP ) {
		assert( FALSE );
		return;
	}
	_SetLBtnDownPoint( NULL );
	_SetState( hmsd_scrollbar::EHMSDSBSTATE_INIT );
}

void hmsd_sbstate_pressbtnarrow::_On_WM_MOUSEMOVE( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_MOUSEMOVE ) {
		assert( FALSE );
		return;
	}
	POINT ptCursor;

	ptCursor.x = GET_X_LPARAM( pWndMsg->m_lParam );
	ptCursor.y = GET_Y_LPARAM( pWndMsg->m_lParam );

	_CheckMouseHoverPos( ptCursor );
}

void hmsd_sbstate_pressbtnarrow::_On_WM_KILLFOCUS( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_KILLFOCUS ) {
		assert( FALSE );
		return;
	}
	_SetLBtnDownPoint( NULL );
	_SetState( hmsd_scrollbar::EHMSDSBSTATE_INIT );
}



