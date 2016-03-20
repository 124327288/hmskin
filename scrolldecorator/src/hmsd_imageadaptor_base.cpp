#include "stdafx.h"
#include "hmsd_imageadaptor_base.h"
#include "hmsd_scrollbar.h"
#include <assert.h>

hmsd_imageadaptor_base::hmsd_imageadaptor_base() {}

hmsd_imageadaptor_base::~hmsd_imageadaptor_base() {}

void hmsd_imageadaptor_base::_GetBtnStartRect( RECT& rcBtnStart, hmsd_scrollbar* pScrollBar ) {
	if ( !pScrollBar ) {
		assert( FALSE );
		return;
	}
	pScrollBar->_GetBtnStartRect( rcBtnStart );
}

void hmsd_imageadaptor_base::_GetBtnEndRect( RECT& rcBtnEnd, hmsd_scrollbar* pScrollBar ) {
	if ( !pScrollBar ) {
		assert( FALSE );
		return;
	}
	pScrollBar->_GetBtnEndRect( rcBtnEnd );
}

BOOL hmsd_imageadaptor_base::_GetBtnThumbRect( RECT& rcBtnThumb, hmsd_scrollbar* pScrollBar ) {
	if ( !pScrollBar ) {
		assert( FALSE );
		return FALSE;
	}
	return pScrollBar->_GetBtnThumbRect( rcBtnThumb );
}

void hmsd_imageadaptor_base::_GetBkRect( RECT& rcBk, hmsd_scrollbar* pScrollBar ) {
	if ( !pScrollBar ) {
		assert( FALSE );
		return;
	}
	rcBk = pScrollBar->m_rect;
}

hmsd_imageadaptor_base::EBTNSTATETYPE hmsd_imageadaptor_base::_GetBtnStartState( hmsd_scrollbar* pScrollBar ) {
	if ( !pScrollBar ) {
		assert( FALSE );
		return EBTNSTATE_NOR;
	}
	
	if ( pScrollBar->m_eState == hmsd_scrollbar::EHMSDSBSTATE_PRESS_BTN_START )
		return EBTNSTATE_PRE;
	else if ( ( pScrollBar->m_eState == hmsd_scrollbar::EHMSDSBSTATE_INIT ) && ( pScrollBar->m_eMouseHoverPos == hmsd_scrollbar::EMHOVERPOS_BTN_START ) )
		return EBTNSTATE_HOV;
	else
		return EBTNSTATE_NOR;

	assert( FALSE );
	return EBTNSTATE_NOR;
}

hmsd_imageadaptor_base::EBTNSTATETYPE hmsd_imageadaptor_base::_GetBtnEndState( hmsd_scrollbar* pScrollBar ) {
	if ( !pScrollBar ) {
		assert( FALSE );
		return EBTNSTATE_NOR;
	}

	if ( pScrollBar->m_eState == hmsd_scrollbar::EHMSDSBSTATE_PRESS_BTN_END )
		return EBTNSTATE_PRE;
	else if ( ( pScrollBar->m_eState == hmsd_scrollbar::EHMSDSBSTATE_INIT ) && ( pScrollBar->m_eMouseHoverPos == hmsd_scrollbar::EMHOVERPOS_BTN_END ) )
		return EBTNSTATE_HOV;
	else
		return EBTNSTATE_NOR;

	assert( FALSE );
	return EBTNSTATE_NOR;
}

hmsd_imageadaptor_base::EBTNSTATETYPE hmsd_imageadaptor_base::_GetBtnThumbState( hmsd_scrollbar* pScrollBar ) {
	if ( !pScrollBar ) {
		assert( FALSE );
		return EBTNSTATE_NOR;
	}

	if ( pScrollBar->m_eState == hmsd_scrollbar::EHMSDSBSTATE_PRESS_BTN_THUMB )
		return EBTNSTATE_PRE;
	else if ( ( pScrollBar->m_eState == hmsd_scrollbar::EHMSDSBSTATE_INIT ) && ( pScrollBar->m_eMouseHoverPos == hmsd_scrollbar::EMHOVERPOS_BTN_THUMB ) )
		return EBTNSTATE_HOV;
	else
		return EBTNSTATE_NOR;

	assert( FALSE );
	return EBTNSTATE_NOR;
}