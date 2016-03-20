/***********************************************
// hm_ps_drawtool_i.h
// hm_ps_drawtool_i likes a visitor in visitor pattern. the menber function likes visit interface function of visitor.
***********************************************/
#ifndef __HM_PS_DRAWTOOL_I_H__
#define __HM_PS_DRAWTOOL_I_H__
#include "win\hm_export_defs.h"
#include "win\resource_system\hm_rs_rawres_base.h"
#include "tchar.h"

struct hm_uires_text_data;

class HMLIB_API hm_ps_drawtool_i {
public:
	hm_ps_drawtool_i(){};
	virtual ~hm_ps_drawtool_i(){};
	
public:
	// hm_rs_rawres_pic
	virtual bool loadRes( hm_rs_rawres_pic* pRawResPic ) = 0;
	virtual bool unloadRes( hm_rs_rawres_pic* pRawResPic ) = 0;
	virtual void draw( HDC hDC, const RECT& rcCanvas, hm_rs_rawres_pic* pRawResPic, const RECT& rcRawResPart ) = 0;
	// hm_rs_rawres_font
	virtual bool loadRes( hm_rs_rawres_font* pRawResFont ) = 0;
	virtual bool unloadRes( hm_rs_rawres_font* pRawResFont ) = 0;
	// hm_rs_rawres_color
	virtual bool loadRes( hm_rs_rawres_color* pRawResColor ) = 0;
	virtual bool unloadRes( hm_rs_rawres_color* pRawResColor ) = 0;
	virtual bool draw( HDC hDC, const RECT& rcCanvas, hm_rs_rawres_color* pRawResColor ) = 0;
	//
	virtual bool draw( HDC hDC, const RECT& rcCanvas, hm_uires_text_data* pText, hm_rs_rawres_font* pRawResFont, hm_rs_rawres_color* pRawResColor, bool bMultiLine ) = 0;
	virtual bool calcRect( HDC hDC, RECT& rcCanvas, const TCHAR* szText, hm_rs_rawres_font* pRawResFont, hm_rs_rawres_color* pRawResColor, bool bMultiLine ) = 0;
	

};


#endif //__HM_PS_DRAWTOOL_I_H__