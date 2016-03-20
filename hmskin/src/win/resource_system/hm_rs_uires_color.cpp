#include "stdafx.h"
#include "win\resource_system\hm_rs_uires_color.h"
#include "win\paint_system\hm_ps_drawtool_i.h"

hm_rs_uires_color::hm_rs_uires_color( hm_rs_rawres_color_factory::obj_id_type idRawResColor )
: m_idRawResColor( idRawResColor ) {

}

hm_rs_uires_color::~hm_rs_uires_color() {

}

void hm_rs_uires_color::show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool ) {
	hm_rs_rawres_color* pRawResColor = NULL;

	pRawResColor = getRawResColor();
	pDrawTool->draw( hDC, rcCanvas, pRawResColor );
}
//
bool hm_rs_uires_color::loadRawRes( hm_ps_drawtool_i* pDrawTool ) {
	if ( !pDrawTool ) return false;
	hm_rs_rawres_color* pRawResColor = NULL;

	pRawResColor = getRawResColor();
	return pDrawTool->loadRes( pRawResColor );
}
//
bool hm_rs_uires_color::unloadRawRes( hm_ps_drawtool_i* pDrawTool ) {
	if ( !pDrawTool ) return false;
	hm_rs_rawres_color* pRawResColor = NULL;

	pRawResColor = getRawResColor();
	return pDrawTool->unloadRes( pRawResColor );
}

hm_rs_rawres_color* hm_rs_uires_color::getRawResColor() {
	return RAWCOLORFACTORY_INSTANCE->getObj( m_idRawResColor );
}