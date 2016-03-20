#ifndef __HM_WMP_DRAWTRIGGER_NCA_H__
#define __HM_WMP_DRAWTRIGGER_NCA_H__
#include "win\wmp\hm_wndmsgprocessor_i.h"
#include "common\hm_cmn_pattern_observer.h"
#include "win\paint_system\hm_ps_canvas.h"
#include "win\hm_export_defs.h"

class HMLIB_API hm_wmp_drawtrigger_nca: public hm_wndmsgprocessor_i
{
public:
	hm_wmp_drawtrigger_nca( hmskin_event_listener_base* pEventListener = NULL );
	virtual ~hm_wmp_drawtrigger_nca();

	// interface of hm_wndmsgprocessor_i
public:
	DECLARE_MSGBIND()

private:
	void _OnNCPaint( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );
	void _OnNCActivate( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );
	void _OnSize( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );
	void _OnWindowPosChanged( hm_keel_obj* pKeelObj, CWPSTRUCT* pWP, msg_sink_i::WNDPROCPARAM* pParamWndProc );

private:
	void _doTrigger( hm_keel_obj* pKeelObj, HDC hDC, HWND hWnd );
	
private:
	hm_ps_canvas m_hmCanvas;
};

#endif //__HM_WMP_DRAWTRIGGER_NCA_H__