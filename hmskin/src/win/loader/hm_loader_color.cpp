#include "stdafx.h"
#include "win\loader\hm_loader_color.h"
#include "win\resource_system\hm_rs_rawres_base.h"

hm_loader_color::hm_loader_color() {}
hm_loader_color::~hm_loader_color() {}

bool hm_loader_color::load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot ) {
	if ( !pManifestData ) return false;
	Json::Value& rootVal = pManifestData->getRootVal();
	Json::Value aryColorVal;
	Json::Value colorVal;
	Json::Value valTmp;
	unsigned int uIndex, uCount;
	int RVal, GVal, BVal; // , AVal;
	hm_rawres_color_factory::obj_id_type idResColor;

	aryColorVal = rootVal["Color"];
	if ( aryColorVal.isNull() )
		return false;
	if ( !aryColorVal.isArray() )
		return false;

	uCount = aryColorVal.size();
	for ( uIndex = 0; uIndex < uCount; ++uIndex ) {
		colorVal = aryColorVal[ uIndex ];
		if ( !colorVal.isObject() )
			return false;

		// id 
		valTmp = colorVal["id"];
		if ( !valTmp.isInt() )
			return false;
		idResColor = valTmp.asInt();

		// R Value
		valTmp = colorVal["R"];
		if ( !valTmp.isInt() )
			return false;
		RVal = valTmp.asInt();

		// G Value
		valTmp = colorVal["G"];
		if ( !valTmp.isInt() )
			return false;
		GVal = valTmp.asInt();

		// B Value
		valTmp = colorVal["B"];
		if ( !valTmp.isInt() )
			return false;
		BVal = valTmp.asInt();

		RAWCOLORFACTORY_INSTANCE->createObj< hm_rs_rawres_color, COLORREF >( idResColor, RGB( RVal, GVal, BVal ) );
	}
	
	
	return true;
}

bool hm_loader_color::load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot ) {

	return true;
}