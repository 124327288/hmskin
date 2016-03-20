#include "stdafx.h"
#include "win\loader\hm_loader_coordinatesystem.h"
#include "win\frame\hm_coordinate_system_hwnd.h"
#include "win\frame\hm_uiroot.h"
#include <string>
#include "tchar.h"

hm_loader_coordinatesystem::hm_loader_coordinatesystem() {

}

hm_loader_coordinatesystem::~hm_loader_coordinatesystem() {

}

bool hm_loader_coordinatesystem::load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot ) {
	if ( !pManifestData || !pManifestData->isAvailable() )
		return false;
	Json::Value ValTmp;
	Json::Value coordsysVal;
	Json::Value coordsysAryVal;
	unsigned int uIndex, uCount;
	std::string strWndMarkFlag;
	hm_coordsys_factory_type::obj_id_type idCoordSysMainWnd;
	hm_rs_wndmark wndMark;
	coordinate_system_hwnd::ENUMCSHTYPE eCSHType;
	std::string strType;
	
	Json::Value& rootVal = pManifestData->getRootVal();
	coordsysAryVal = rootVal[ "CoordinateSystem" ];
	if ( coordsysAryVal.isNull() )
		return false;
	if ( !coordsysAryVal.isArray() )
		return false;
	uCount = coordsysAryVal.size();
	for ( uIndex = 0; uIndex!=uCount; ++uIndex ) {
		coordsysVal = coordsysAryVal[ uIndex ];
		
		// get idCoordSysMainWnd
		ValTmp = coordsysVal["CSId"];
		if ( !ValTmp.isInt() ) 
			return false;
		idCoordSysMainWnd = ValTmp.asUInt();

		//
		ValTmp = coordsysVal["WndMarkFlag"];
		if ( !ValTmp.isString() )
			return false;
		strWndMarkFlag = ValTmp.asString();
		if ( 0 == strcmp( strWndMarkFlag.c_str(), "PropId" ) ) {
			wndMark.m_eflag = hm_rs_wndmark::WNDMARK_WNDPROPID;
		} else if ( 0 == strcmp( strWndMarkFlag.c_str(), "CtrlId" ) ) {
			wndMark.m_eflag = hm_rs_wndmark::WNDMARK_CTRLID;
		} else {
			return false;
		}

		//
		switch ( wndMark.m_eflag )
		{
		case hm_rs_wndmark::WNDMARK_WNDPROPID:
			{
				ValTmp = coordsysVal["PropId"];
				if ( !ValTmp.isInt() )
					return false;
				wndMark.m_uWndPropID = ValTmp.asUInt();
			} break;
		case hm_rs_wndmark::WNDMARK_CTRLID:
			{
				ValTmp = coordsysVal["CtrlId"];
				if ( !ValTmp.isInt() )
					return false;
				wndMark.m_uCtrlID = ValTmp.asUInt();
			} break;
		default:
			return false;
			break;
		}
		
		//
		ValTmp = coordsysVal["Type"];
		if ( !ValTmp.isString() )
			return false;
		strType = ValTmp.asString();
		if ( 0 == strcmp( "Client", strType.c_str() ) ) {
			eCSHType = coordinate_system_hwnd::CSH_CLIENT_TYPE;
		} else if ( 0 == strcmp( "Window", strType.c_str() ) ) {
			eCSHType = coordinate_system_hwnd::CSH_WINDOW_TYPE;
		} else {
			return false;
		}
		
		//
		if ( !pHMUIRoot->m_pWndMark2CSIdTable->bindObjId2WndMark( idCoordSysMainWnd, wndMark ) )
			return false;
		if ( !pHMUIRoot->m_pCoordSysFactory->createObj< coordinate_system_hwnd, coordinate_system_hwnd::ENUMCSHTYPE >( idCoordSysMainWnd, eCSHType ) ) {
			return false;
		}
	}

	return true;
}

bool hm_loader_coordinatesystem::load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot ) {
	return true;
}