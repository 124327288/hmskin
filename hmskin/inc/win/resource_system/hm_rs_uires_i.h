#ifndef __HM_RS_UIRES_I_H__
#define __HM_RS_UIRES_I_H__
#include "WinDef.h"
#include "win\hm_export_defs.h"
//
class hm_ps_drawtool_i;
class HMLIB_API hm_rs_uires_i
{
public:
	hm_rs_uires_i() {};
	virtual ~hm_rs_uires_i() {};

public:
	// rcCanvas - specify draw hm_rs_uires_i to which rectangle part of HDC.
	virtual void show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool ) = 0;
	//
	virtual bool loadRawRes( hm_ps_drawtool_i* pDrawTool ) = 0;
	//
	virtual bool unloadRawRes( hm_ps_drawtool_i* pDrawTool ) = 0;
};




#endif //__HM_RS_UIRES_I_H__