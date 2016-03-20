#include "stdafx.h"
#include "hmsd_defs.h"

hmsd_wndmsg::hmsd_wndmsg( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
: m_hWnd( hWnd )
, m_message( message )
, m_wParam( wParam )
, m_lParam( lParam )
, m_lRes( 0 )
, m_bEatWndMsg( FALSE ) {

}

hmsd_wndmsg::~hmsd_wndmsg() {}