#include "stdafx.h"
#include "win\loader\hm_manifest_creator.h"
#include "win\loader\hm_manifest_json.h"
#include "win\loader\hm_manifest_xml.h"

#define CHECK_MANIFEST_BEGIN() \
	hm_manifest_base* pManifestData = NULL;

#define CHECK_MANIFEST_FORMAT( manifest_cls_name ) \
	pManifestData = new manifest_cls_name( szManifestFilePath ); \
	if ( pManifestData->isAvailable() ) { \
		return pManifestData; \
	} \
	delete pManifestData; \
	pManifestData = NULL; 

#define CHECK_MANIFEST_END() \
	return NULL;

hm_manifest_base* CreateManifestData( const TCHAR* szManifestFilePath ) {
	CHECK_MANIFEST_BEGIN();

	CHECK_MANIFEST_FORMAT( hm_manifest_json )
	CHECK_MANIFEST_FORMAT( hm_manifest_xml )
	
	CHECK_MANIFEST_END();
}