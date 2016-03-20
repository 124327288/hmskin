#ifndef __HM_PS_DRAWTOOL_GDIPLUS_H__
#define __HM_PS_DRAWTOOL_GDIPLUS_H__
#include "win\hm_export_defs.h"
#include "win\paint_system\hm_ps_drawtool_i.h"

class HMLIB_API hm_ps_drawtool_gdiplus : public hm_ps_drawtool_i {
public:
	virtual ~hm_ps_drawtool_gdiplus();

public:
	static hm_ps_drawtool_gdiplus* getInstance();

public:
	// hm_rs_rawres_pic
	virtual bool loadRes( hm_rs_rawres_pic* pRawResPic );
	virtual bool unloadRes( hm_rs_rawres_pic* pRawResPic );
	virtual void draw( HDC hDC, const RECT& rcCanvas, hm_rs_rawres_pic* pRawResPic, const RECT& rcRawResPart );
	// hm_rs_rawres_font
	virtual bool loadRes( hm_rs_rawres_font* pRawResFont );
	virtual bool unloadRes( hm_rs_rawres_font* pRawResFont );
	// hm_rs_rawres_color
	virtual bool loadRes( hm_rs_rawres_color* pRawResColor );
	virtual bool unloadRes( hm_rs_rawres_color* pRawResColor );
	virtual bool draw( HDC hDC, const RECT& rcCanvas, hm_rs_rawres_color* pRawResColor );
	//
	virtual bool draw( HDC hDC, const RECT& rcCanvas, hm_uires_text_data* pText, hm_rs_rawres_font* pRawResFont, hm_rs_rawres_color* pRawResColor, bool bMultiLine );
	virtual bool calcRect( HDC hDC, RECT& rcCanvas, const TCHAR* szText, hm_rs_rawres_font* pRawResFont, hm_rs_rawres_color* pRawResColor, bool bMultiLine );

private:
	hm_ps_drawtool_gdiplus();
};

#endif //__HM_PS_DRAWTOOL_GDIPLUS_H__