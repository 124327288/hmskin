#ifndef __HM_WMP_LAYOUT_H__
#define __HM_WMP_LAYOUT_H__
#include "win\wmp\hm_wndmsgprocessor_i.h"
#include "win\hm_export_defs.h"

class HMLIB_API hm_wmp_layouttrigger: public hm_wndmsgprocessor_i {
public:
	hm_wmp_layouttrigger( hmskin_event_listener_base* pEventListener = NULL );
	virtual ~hm_wmp_layouttrigger();

	// interface of hm_wndmsgprocessor_i
public:
	DECLARE_MSGBIND()
	
private:
	void _OnSize( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );
	void _OnWindowPosChange( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );
	
};


#endif //__HM_WMP_LAYOUT_H__