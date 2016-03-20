#include "stdafx.h"
#include "win\resource_system\hm_rs_uires_pic.h"
#include "win\paint_system\hm_ps_drawtool_i.h"
//
hm_rs_uires_pic::hm_rs_uires_pic( hm_rawres_pic_factory::obj_id_type idRawRes )
: m_idRawRes( idRawRes )
, m_pRawResPic( NULL )
, m_ufixL( 0 )
, m_ufixT( 0 )
, m_ufixR( 0 )
, m_ufixB( 0 )
{
	memset( &m_rcSelect, 0, sizeof( RECT ) );
}
//
hm_rs_uires_pic::hm_rs_uires_pic( hm_rawres_pic_factory::obj_id_type idRawRes, const RECT& rcSelect )
: m_idRawRes( idRawRes )
, m_pRawResPic( NULL )
, m_rcSelect( rcSelect )
, m_ufixL( 0 )
, m_ufixT( 0 )
, m_ufixR( 0 )
, m_ufixB( 0 )
{}
//
hm_rs_uires_pic::~hm_rs_uires_pic() {}
//
void hm_rs_uires_pic::show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool ) {
	if ( !pDrawTool ) return;
	RECT rcRawResPart;
	RECT rcCanvasPart;
	RECT rcRawRes;
	hm_rs_rawres_pic* pRawResPic = NULL;
	
	pRawResPic = getRawResPic();
	//
	if ( m_rcSelect.right || m_rcSelect.bottom ) {
		rcRawRes = m_rcSelect;
	} else {
		SIZE sizePic;
			
		pRawResPic->fetchSize( sizePic );
		rcRawRes.left = 0;
		rcRawRes.top = 0;
		rcRawRes.right = sizePic.cx;
		rcRawRes.bottom = sizePic.cy;
	}

	// left-top
	calcRectLT( rcRawRes, rcRawResPart );
	calcRectLT( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	// left-bottom
	calcRectLB( rcRawRes, rcRawResPart );
	calcRectLB( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	// right-top
	calcRectRT( rcRawRes, rcRawResPart );
	calcRectRT( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	// right-bottom
	calcRectRB( rcRawRes, rcRawResPart );
	calcRectRB( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	// top
	calcRectT( rcRawRes, rcRawResPart );
	calcRectT( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	// left
	calcRectL( rcRawRes, rcRawResPart );
	calcRectL( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	// right
	calcRectR( rcRawRes, rcRawResPart );
	calcRectR( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	// bottom
	calcRectB( rcRawRes, rcRawResPart );
	calcRectB( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	// center
	calcRectC( rcRawRes, rcRawResPart );
	calcRectC( rcCanvas, rcCanvasPart );
	pDrawTool->draw( hDC, rcCanvasPart, m_pRawResPic, rcRawResPart );
	

}
//
hm_rs_rawres_pic* hm_rs_uires_pic::getRawResPic() {
	if ( m_pRawResPic ) return m_pRawResPic;
	
	m_pRawResPic = RAWPICFACTORY_INSTANCE->getObj( m_idRawRes );
	return m_pRawResPic;
}
//
bool hm_rs_uires_pic::loadRawRes( hm_ps_drawtool_i* pDrawTool ) {
	if ( !pDrawTool ) return false;
	hm_rs_rawres_pic* pRawResPic = NULL;

	pRawResPic = getRawResPic();
	if ( !pRawResPic )
		return false;
	
	return pDrawTool->loadRes( pRawResPic );
}
//
bool hm_rs_uires_pic::unloadRawRes( hm_ps_drawtool_i* pDrawTool ) {
	if ( !pDrawTool ) return false;
	hm_rs_rawres_pic* pRawResPic = NULL;

	pRawResPic = getRawResPic();
	if ( !pRawResPic )
		return false;
	
	return pDrawTool->unloadRes( pRawResPic );
}


//
bool hm_rs_uires_pic::calcRectLT( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.left;
	rcOut.top = rcRef.top;
	rcOut.right = rcRef.left + m_ufixL;
	rcOut.bottom = rcRef.top + m_ufixT;
	return true;
}

//
bool hm_rs_uires_pic::calcRectLB( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.left;
	rcOut.right = rcRef.left + m_ufixL;
	rcOut.top = rcRef.bottom - m_ufixB;
	rcOut.bottom = rcRef.bottom;
	return true;
}

//
bool hm_rs_uires_pic::calcRectRT( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.right - m_ufixR;
	rcOut.top = rcRef.top;
	rcOut.right = rcRef.right;
	rcOut.bottom = rcRef.top + m_ufixT;
	return true;
}

//
bool hm_rs_uires_pic::calcRectRB( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.right - m_ufixR;
	rcOut.top = rcRef.bottom - m_ufixB;
	rcOut.right = rcRef.right;
	rcOut.bottom = rcRef.bottom;
	return true;
}

//
bool hm_rs_uires_pic::calcRectT( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.left + m_ufixL;
	rcOut.right = rcRef.right - m_ufixR;
	rcOut.top = rcRef.top;
	rcOut.bottom = rcRef.top + m_ufixT;
	return true;
}

//
bool hm_rs_uires_pic::calcRectL( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.left;
	rcOut.right = rcRef.left + m_ufixL;
	rcOut.top = rcRef.top + m_ufixT;
	rcOut.bottom = rcRef.bottom - m_ufixB;
	return true;
}

//
bool hm_rs_uires_pic::calcRectB( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.left + m_ufixL;
	rcOut.right = rcRef.right - m_ufixR;
	rcOut.top = rcRef.bottom - m_ufixB;
	rcOut.bottom = rcRef.bottom;
	return true;
}

//
bool hm_rs_uires_pic::calcRectR( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.right - m_ufixR;
	rcOut.top = rcRef.top + m_ufixT;
	rcOut.bottom = rcRef.bottom - m_ufixB;
	rcOut.right = rcRef.right;
	return true;
}

//
bool hm_rs_uires_pic::calcRectC( const RECT& rcRef, RECT& rcOut ) {
	rcOut.left = rcRef.left + m_ufixL;
	rcOut.right = rcRef.right - m_ufixR;
	rcOut.top = rcRef.top + m_ufixT;
	rcOut.bottom = rcRef.bottom - m_ufixB;
	return true;
}

