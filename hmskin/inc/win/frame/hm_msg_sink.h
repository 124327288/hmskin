#ifndef __hm_msg_sink_H__
#define __hm_msg_sink_H__
#include "win\hook_system\hm_hs_wnd_msg_dispatch.h"
#include "common\hm_cmn_patterns.h"
#include <map>
#include "win\hm_export_defs.h"
//
class hm_uiroot;
//
class HMLIB_API hm_msg_sink : public msg_sink_i, public cmn::hm_cmn_subject
{
	friend class hm_msg_sink_factory;
public:
	hm_msg_sink();
	virtual ~hm_msg_sink();

	//interface of msg_sink_i
public:
	virtual void OnStartSink( HWND hWndDest );
	virtual void OnStopSink( HWND hWndDest );
	virtual void WndProc( HWND hWndDest, UINT message, WPARAM& wParam, LPARAM& lParam, WNDPROCPARAM* pParamWndProc );
};

EXTERN_C_START

HMLIB_API msg_sink_i* hmmsgsink_create( hm_uiroot* pHMUIRoot, msg_sink_factory_type::obj_id_type idMsgSink );

EXTERN_C_END
#endif //__hm_msg_sink_H__