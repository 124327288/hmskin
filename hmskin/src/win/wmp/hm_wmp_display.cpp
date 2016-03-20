#include "stdafx.h"
#include "win\wmp\hm_wmp_display.h"


hm_wmp_display::hm_wmp_display( hmskin_event_listener_base* pEventListener )
: hm_wndmsgprocessor_i( pEventListener )
, m_pDrawTool( NULL ) {
}
//
hm_wmp_display::~hm_wmp_display() {
	_clearAllDistrictObjs();
	//if ( m_pDrawTool )
	//	delete m_pDrawTool;
	m_pDrawTool = NULL;
}
//
void hm_wmp_display::setDrawTool( hm_ps_drawtool_i* pDrawTool ) { 
	// different drawtool need different resource, so when we change the drawtool, need reload resource that drawtool need.

	// unload resource
	if ( m_pDrawTool ) {
		map_id2district_type::iterator itDistrictObj, iendDistrictObj;
		hm_districtobj* pDistrictObj = NULL; 

		iendDistrictObj = m_mapId2District.end();
		for ( itDistrictObj = m_mapId2District.begin(); itDistrictObj!=iendDistrictObj; ++itDistrictObj ) {
			pDistrictObj = itDistrictObj->second;
			pDistrictObj->unloadRes( m_pDrawTool );
		}
		//
		//delete m_pDrawTool;
		m_pDrawTool = NULL;
	}
	
	m_pDrawTool = pDrawTool; 

	// load resource
	if ( m_pDrawTool ) {
		map_id2district_type::iterator itDistrictObj, iendDistrictObj;
		hm_districtobj* pDistrictObj = NULL;

		iendDistrictObj = m_mapId2District.end();
		for ( itDistrictObj = m_mapId2District.begin(); itDistrictObj!=iendDistrictObj; ++itDistrictObj ) {
			pDistrictObj = itDistrictObj->second;
			pDistrictObj->loadRes( m_pDrawTool );
		}
	}

};
//
bool hm_wmp_display::_setDistrictObj( district_id_type idDistrict, hm_districtobj* pDistrictObj ) {
	if ( !pDistrictObj ) return false;
	map_id2district_type::iterator itDistrictObj;
	
	//
	itDistrictObj = m_mapId2District.find( idDistrict );
	if ( itDistrictObj != m_mapId2District.end() ) {
		hm_districtobj* pDistrictObjOld = itDistrictObj->second;
		
		if ( m_pDrawTool )
			pDistrictObjOld->unloadRes( m_pDrawTool );
		delete pDistrictObjOld;
		pDistrictObjOld = NULL;
		m_mapId2District.erase( itDistrictObj );
	}
	//
	m_mapId2District[ idDistrict ] = pDistrictObj;
	
	if ( m_pDrawTool )
		pDistrictObj->loadRes( m_pDrawTool );

	return true;
}
//
bool hm_wmp_display::getDistrictObj( district_id_type idDistrict, hm_districtobj** ppDistrictObj ) {
	return _getDistrictObj( idDistrict, ppDistrictObj );
}
//
bool hm_wmp_display::_hasDistrictObj( district_id_type idDistrict ) {
	map_id2district_type::iterator itDistrictObj;
	
	itDistrictObj = m_mapId2District.find( idDistrict );

	return itDistrictObj!=m_mapId2District.end();
}
//
bool hm_wmp_display::_getDistrictObj( district_id_type idDistrict, hm_districtobj** ppDistrictObj ) {
	map_id2district_type::iterator itDistrictObj;

	itDistrictObj = m_mapId2District.find( idDistrict );
	if ( itDistrictObj==m_mapId2District.end() ) return false;
	
	*ppDistrictObj = itDistrictObj->second;
	return true;
}
//
bool hm_wmp_display::_clearAllDistrictObjs() {
	map_id2district_type::iterator itDistrictObj, iendDistrictObj;

	iendDistrictObj = m_mapId2District.end();
	for ( itDistrictObj = m_mapId2District.begin(); itDistrictObj!=iendDistrictObj; ++itDistrictObj ) {
		delete itDistrictObj->second;
		itDistrictObj->second = NULL;
	}
	m_mapId2District.clear(); // 
	return true;
}
//
void hm_wmp_display::getAllDistrictId( district_id_container_type& containerIds ) {
	_getAllDistrictId( containerIds );
}
////////////////////////////////////////
hm_showobj::hm_showobj( hm_rs_uires_i* pUIRes, hm_pos_decoder_i* pPosDecoder )
: m_pUIRes( pUIRes )
, m_pPosDecoder( pPosDecoder )
{}
//
hm_showobj::~hm_showobj() {
	if ( m_pUIRes ) { 
		delete m_pUIRes;
		m_pUIRes = NULL;
	}
	if ( m_pPosDecoder ) {
		delete m_pPosDecoder;
		m_pPosDecoder = NULL;
	}
}
//
void hm_showobj::show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool ) {
	RECT rcShowObj;
	
	if ( !m_pUIRes ) return;
	if ( m_pPosDecoder ) {
		if ( !m_pPosDecoder->getPosition( rcCanvas, rcShowObj ) ) return;
	} else {
		rcShowObj = rcCanvas;
	}
	// 
	m_pUIRes->show( hDC, rcShowObj, pDrawTool );
}
//
bool hm_showobj::loadRes( hm_ps_drawtool_i* pDrawTool ) {
	if ( !m_pUIRes || !pDrawTool ) return false;
	
	m_pUIRes->loadRawRes( pDrawTool );
	return true;
}
//
bool hm_showobj::unloadRes( hm_ps_drawtool_i* pDrawTool ) {
	if ( !m_pUIRes || !pDrawTool ) return false;
	
	m_pUIRes->unloadRawRes( pDrawTool );
	return true;	
}
////////////////////////////////////////
//
hm_districtobj::hm_districtobj( hm_pos_decoder_i* pPosDecoder ) { 
	m_pPosDecoder = pPosDecoder;
};
//
hm_districtobj::~hm_districtobj() { 
	_clearAllShowObj(); 
	//
	if ( m_pPosDecoder ) {
		delete m_pPosDecoder;
		m_pPosDecoder = NULL;
	}

};
//
bool hm_districtobj::pushBackShowObj( hm_showobj* pShowObj ) {
	if ( !pShowObj ) return false;
	m_containerShowObjs.push_back( pShowObj );
	return true;
}
//
bool hm_districtobj::pushFrontShowObj( hm_showobj* pShowObj ) {
	if ( !pShowObj ) return false;
	m_containerShowObjs.push_front( pShowObj );
	return true;
}
//
void hm_districtobj::_clearAllShowObj() {
	showobj_container_type::iterator itShowObj, iendShowObj;
	hm_showobj* pShowObj = NULL;

	iendShowObj = m_containerShowObjs.end();
	for ( itShowObj = m_containerShowObjs.begin(); itShowObj!=iendShowObj; ++itShowObj ) {
		pShowObj = (*itShowObj);
		delete pShowObj;
	}
	m_containerShowObjs.clear();
}
//
void hm_districtobj::show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool, void* pContext ) {
	RECT rcDistrict;
	showobj_container_type::iterator itShowObj, iendShowObj;
	hm_showobj* pShowObj = NULL;

	// get rcDistrict
	if ( m_pPosDecoder ) {
		m_pPosDecoder->getPosition( rcCanvas, rcDistrict );
	} else {
		rcDistrict = rcCanvas;
	}
	
	// show showobj
	iendShowObj = m_containerShowObjs.end();
	for ( itShowObj = m_containerShowObjs.begin(); itShowObj!=iendShowObj; ++itShowObj ) {
		pShowObj = *itShowObj;
		if ( !pShowObj ) continue;
		pShowObj->show( hDC, rcDistrict, pDrawTool );
	}

}
//
void hm_districtobj::getDistrictRect( const RECT& rcCanvas, RECT& rcDistrictObj ) {
	if ( m_pPosDecoder ) {
		m_pPosDecoder->getPosition( rcCanvas, rcDistrictObj );
	} else {
		rcDistrictObj = rcCanvas;
	}
}
//
bool hm_districtobj::loadRes( hm_ps_drawtool_i* pDrawTool ) {
	if ( !pDrawTool ) return false;
	showobj_container_type::iterator itShowObj, iendShowObj;
	hm_showobj* pShowObj = NULL;

	iendShowObj = m_containerShowObjs.end();
	for ( itShowObj = m_containerShowObjs.begin(); itShowObj!=iendShowObj; ++itShowObj ) {
		pShowObj = *itShowObj;
		if ( !pShowObj ) continue;
		pShowObj->loadRes( pDrawTool );
	}
	return true;
}
//
bool hm_districtobj::unloadRes( hm_ps_drawtool_i* pDrawTool ) {
	if ( !pDrawTool ) return false;
	showobj_container_type::iterator itShowObj, iendShowObj;
	hm_showobj* pShowObj = NULL;
	
	iendShowObj = m_containerShowObjs.end();
	for ( itShowObj = m_containerShowObjs.begin(); itShowObj!=iendShowObj; ++itShowObj ) {
		pShowObj = *itShowObj;
		if ( !pShowObj ) continue;
		pShowObj->unloadRes( pDrawTool );
	}
	return true;
}

hm_showobj* hm_districtobj::getShowObj( unsigned int uIndex ) {
	if ( uIndex >= m_containerShowObjs.size() ) {
		return NULL;
	}
	return m_containerShowObjs[ uIndex ];
} 
