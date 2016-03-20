#ifndef __hm_rs_uires_pic_H__
#define __hm_rs_uires_pic_H__
#include "win\resource_system\hm_rs_uires_i.h"
#include "win\resource_system\hm_rs_rawres_base.h"
#include "win\hm_export_defs.h"

class HMLIB_API hm_rs_uires_pic : public hm_rs_uires_i
{
public:
	hm_rs_uires_pic( hm_rawres_pic_factory::obj_id_type idRawRes );
	hm_rs_uires_pic( hm_rawres_pic_factory::obj_id_type idRawRes, const RECT& rcSelect );
	virtual ~hm_rs_uires_pic();

	// interface of hm_rs_uires_i
public:
	virtual void show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool );
	//
	virtual bool loadRawRes( hm_ps_drawtool_i* pDrawTool );
	//
	virtual bool unloadRawRes( hm_ps_drawtool_i* pDrawTool );
	
	// 
public:
	hm_rs_rawres_pic* getRawResPic();

protected:
	bool calcRectLT( const RECT& rcRef, RECT& rcOut );
	bool calcRectLB( const RECT& rcRef, RECT& rcOut );
	bool calcRectRT( const RECT& rcRef, RECT& rcOut );
	bool calcRectRB( const RECT& rcRef, RECT& rcOut );
	bool calcRectT( const RECT& rcRef, RECT& rcOut );
	bool calcRectL( const RECT& rcRef, RECT& rcOut );
	bool calcRectB( const RECT& rcRef, RECT& rcOut );
	bool calcRectR( const RECT& rcRef, RECT& rcOut );
	bool calcRectC( const RECT& rcRef, RECT& rcOut );

public:
	// specify which part of the picture
	RECT m_rcSelect;
	// specify which part of ui resource is fixed thickness.
	unsigned int m_ufixL;
	unsigned int m_ufixT;
	unsigned int m_ufixR;
	unsigned int m_ufixB;

private:
	hm_rs_rawres_pic* m_pRawResPic;
	hm_rawres_pic_factory::obj_id_type m_idRawRes;
};


#endif //__hm_rs_uires_pic_H__