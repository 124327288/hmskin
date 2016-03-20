#include "stdafx.h"
#include "win\loader\hm_manifest_xml.h"
#include "win\loader\hm_manifest_base.h"
#include "win\frame\hm_uiroot.h"

hm_manifest_xml::hm_manifest_xml( const TCHAR* szManifestFilePath ) {

}

hm_manifest_xml::~hm_manifest_xml() {

}

bool hm_manifest_xml::isAvailable() {

	return false;
}

bool hm_manifest_xml::visit( hm_loader_base* pLoader, hm_uiroot* pHMUIRoot ) {

	return true;
}