#include "stdafx.h"
#include "hmsd_sbstate_pressbtnthumb.h"
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
hmsd_sbstate_pressbtnthumb::hmsd_sbstate_pressbtnthumb( hmsd_scrollbar* pScrollBar ) 
: hmsd_sbstate_base( pScrollBar ) {
}

hmsd_sbstate_pressbtnthumb::~hmsd_sbstate_pressbtnthumb() {

}

void hmsd_sbstate_pressbtnthumb::OnWndMsg( hmsd_wndmsg* pWndMsg ) {
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

void hmsd_sbstate_pressbtnthumb::_On_WM_LBUTTONDOWN( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_LBUTTONDOWN ) {
		assert( FALSE );
		return;
	}

	assert( FALSE );
}

void hmsd_sbstate_pressbtnthumb::_On_WM_LBUTTONUP( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_LBUTTONUP ) {
		assert( FALSE );
		return;
	}
	_SetLBtnDownPoint( NULL );
	_SetState( hmsd_scrollbar::EHMSDSBSTATE_INIT );
}

void hmsd_sbstate_pressbtnthumb::_On_WM_MOUSEMOVE( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_MOUSEMOVE ) {
		assert( FALSE );
		return;
	}
	POINT ptMouseCur;
	POINT ptLBtnDown;
	int nLBtnDownPos;
	int nCurPosCalc;
	
	// ptMouseCur
	ptMouseCur.x = GET_X_LPARAM( pWndMsg->m_lParam );
	ptMouseCur.y = GET_Y_LPARAM( pWndMsg->m_lParam );
	//
	_CheckMouseHoverPos( ptMouseCur );
		
	// get ptLBtnDown
	if ( !_GetLBtnDownPoint( ptLBtnDown ) ) {
		assert( FALSE );
		return;
	}
	
	// get nLBtnDownPos
	nLBtnDownPos = _GetLBtnDownPos();
	
	// get nCurPosCalc
	if ( !_CalcCurPos( ptLBtnDown, ptMouseCur, nLBtnDownPos, nCurPosCalc ) )
		return;

	// set current position.
	m_pScrollBar->SetCurPos( nCurPosCalc, TRUE, TRUE );


}

BOOL hmsd_sbstate_pressbtnthumb::_CalcCurPos( POINT ptLBtnDown, POINT ptMouseCur, int nPosLBtnDown, int& nPosCurCalc ) {
	int nPosStart, nPosEnd;
	unsigned int uSpace;
	hmsd_scrollbar::ENUMSCROLLTYPE eType;

	// get nPosStart nPosEnd.
	m_pScrollBar->GetRange( nPosStart, nPosEnd );
	// get uSpace.
	uSpace = _GetSpace();
	if ( uSpace == 0 ) {
		return FALSE;
	}
	// get eType
	eType = m_pScrollBar->GetType();

	switch ( eType )
	{
	case hmsd_scrollbar::ESB_VERT:
		{
			int nMoveSpan;

			nMoveSpan = ptMouseCur.y - ptLBtnDown.y;
			nPosCurCalc = nPosLBtnDown + (nPosEnd - nPosStart)*(nMoveSpan)/(int)uSpace;
			nPosCurCalc = max( min ( nPosCurCalc, nPosEnd ), nPosStart );
			return TRUE;
		}
		break;
	case hmsd_scrollbar::ESB_HORZ:
		{
			int nMoveSpan;

			nMoveSpan = ptMouseCur.x - ptLBtnDown.x;
			nPosCurCalc = nPosLBtnDown + (nPosEnd - nPosStart)*(nMoveSpan)/(int)uSpace;
			nPosCurCalc = max( min ( nPosCurCalc, nPosEnd ), nPosStart );
			return TRUE;
		}
		break;
	default:
		assert( FALSE );
		return FALSE;
		break;
	}
	
	assert( FALSE );
	return FALSE;
}

void hmsd_sbstate_pressbtnthumb::_On_WM_KILLFOCUS( hmsd_wndmsg* pWndMsg ) {
	if ( !pWndMsg || pWndMsg->m_message != WM_KILLFOCUS ) {
		assert( FALSE );
		return;
	}
	_SetLBtnDownPoint( NULL );
	_SetState( hmsd_scrollbar::EHMSDSBSTATE_INIT );
}


