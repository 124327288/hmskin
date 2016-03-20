#include "stdafx.h"
#include "win\wmp\hm_wmp_layouttrigger.h"
#include "win\frame\hm_layout_obj.h"
//
hm_wmp_layouttrigger::hm_wmp_layouttrigger( hmskin_event_listener_base* pEventListener )
: hm_wndmsgprocessor_i( pEventListener ) {}
//
hm_wmp_layouttrigger::~hm_wmp_layouttrigger() {}
//

MSGBIND_BEGIN( hm_wmp_layouttrigger )
	MSGBIND( WM_SIZE, _OnSize )
	MSGBIND( WM_WINDOWPOSCHANGED, _OnWindowPosChange ) 
MSGBIND_END()
//
ORDERWNDMSG_BEGIN( hm_wmp_layouttrigger )
	ORDERWNDMSG( WM_SIZE )
	ORDERWNDMSG( WM_WINDOWPOSCHANGED )
ORDERWNDMSG_END()
//

void hm_wmp_layouttrigger::_OnSize( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc ) 
{
	hm_layout_obj* pLayoutObj = NULL;
	
	pLayoutObj = pKeelObj->getLayoutObj();
	pLayoutObj->calcPosition();
}

void hm_wmp_layouttrigger::_OnWindowPosChange( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc ) {
	hm_layout_obj* pLayoutObj = NULL;
	WINDOWPOS* pWndPos = NULL;
	
	pWndPos = (WINDOWPOS*)pWP->lParam;
	if ( !( pWndPos->flags & SWP_FRAMECHANGED ) ) {
		if ( pWndPos->flags & SWP_NOSIZE )
			return;
	}
	pLayoutObj = pKeelObj->getLayoutObj();
	pLayoutObj->calcPosition();
}