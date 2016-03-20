#ifndef __HM_WMP_DRAWTRIGGER_H__
#define __HM_WMP_DRAWTRIGGER_H__
#include "win\wmp\hm_wndmsgprocessor_i.h"
#include "common\hm_cmn_pattern_observer.h"
#include "win\paint_system\hm_ps_canvas.h"
#include "win\hm_export_defs.h"

class HMLIB_API hm_wmp_drawtrigger: public hm_wndmsgprocessor_i
{
public:
	hm_wmp_drawtrigger( hmskin_event_listener_base* pEventListener = NULL );
	virtual ~hm_wmp_drawtrigger();

	// interface of hm_wndmsgprocessor_i
public:
	DECLARE_MSGBIND()

private:
	void _OnPaint( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );
	void _OnEraseBkGnd( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );
	void _OnSize( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );
	void _OnWindowPosChanged( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );

private:
	hm_ps_canvas m_hmCanvas;
};

#endif //__HM_WMP_DRAWTRIGGER_H__
