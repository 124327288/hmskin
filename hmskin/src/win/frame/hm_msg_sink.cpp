#include "stdafx.h"
#include "win\frame\hm_msg_sink.h"
#include "win\frame\hm_uiroot.h"
//////////////////////////////////////////////////////////////////////////
hm_msg_sink::hm_msg_sink()
{}
//
hm_msg_sink::~hm_msg_sink()
{}

void hm_msg_sink::OnStartSink( HWND hWndDest )
{
	
}

void hm_msg_sink::OnStopSink( HWND hWndDest )
{
	
}

void hm_msg_sink::WndProc( HWND hWndDest, UINT message, WPARAM& wParam, LPARAM& lParam, WNDPROCPARAM* pParamWndProc )
{
	notifyWndMsg( hWndDest, message, wParam, lParam, pParamWndProc );
}

HMLIB_API msg_sink_i* hmmsgsink_create( hm_uiroot* pHMUIRoot, msg_sink_factory_type::obj_id_type idMsgSink ) {
	if ( !pHMUIRoot )
		return NULL;
	msg_sink_i* pMsgSink = NULL;
	
	pMsgSink = pHMUIRoot->m_pMsgSinkFactory->createObj< hm_msg_sink >( idMsgSink );
	
	return pMsgSink;
}