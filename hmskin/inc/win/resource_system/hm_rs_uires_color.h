#ifndef __HM_RS_UIRES_COLOR_H__
#define __HM_RS_UIRES_COLOR_H__
#include "win\hm_export_defs.h"
#include "hm_rs_uires_i.h"
#include "hm_rs_rawres_base.h"

class HMLIB_API hm_rs_uires_color : public hm_rs_uires_i {
public:
	hm_rs_uires_color( hm_rs_rawres_color_factory::obj_id_type idRawResColor );
	virtual ~hm_rs_uires_color();

	// interface of hm_rs_uires_i
public:
	// rcCanvas - specify draw hm_rs_uires_i to which rectangle part of HDC.
	virtual void show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool );
	//
	virtual bool loadRawRes( hm_ps_drawtool_i* pDrawTool );
	//
	virtual bool unloadRawRes( hm_ps_drawtool_i* pDrawTool );

private:
	hm_rs_rawres_color* getRawResColor();

private:
	hm_rs_rawres_color_factory::obj_id_type m_idRawResColor;
};


#endif //__HM_RS_UIRES_COLOR_H__