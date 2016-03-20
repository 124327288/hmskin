#include "stdafx.h"
#include "hmsd_scrollableobj_base.h"

hmsd_scrollableobj_base::hmsd_scrollableobj_base()
: m_pScrollbarH( new hmsd_scrollbar( hmsd_scrollbar::ESB_HORZ ) )
, m_pScrollbarV( new hmsd_scrollbar( hmsd_scrollbar::ESB_VERT ) ) {
	_init();
}

hmsd_scrollableobj_base::~hmsd_scrollableobj_base() {
	//
	if ( m_pScrollbarH )
		delete m_pScrollbarH;
	m_pScrollbarH = NULL;
	//
	if ( m_pScrollbarV )
		delete m_pScrollbarV;
	m_pScrollbarV = NULL;
}

void hmsd_scrollableobj_base::_init() {
	m_pScrollbarH->m_eventTriggerPosChange.bind( this, &hmsd_scrollableobj_base::onScrollBarPosChange );
	m_pScrollbarH->m_eventTriggerSBStateChange.bind( this, &hmsd_scrollableobj_base::onScrollBarStateChange );
	m_pScrollbarH->m_eventTriggerLBtnDown.bind( this, &hmsd_scrollableobj_base::onScrollBarLBtnDown );
}
