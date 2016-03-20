#ifndef __HM_LOADER_BASE_H__
#define __HM_LOADER_BASE_H__
#include "win\loader\hm_manifest_json.h"
#include "win\loader\hm_manifest_xml.h"
//
class hm_uiroot;
//
class hm_loader_base {
public:
	hm_loader_base(){};
	virtual ~hm_loader_base(){};

	// interface of hm_loader_base
public:
	virtual bool load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot ) = 0;
	virtual bool load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot ) = 0;

};




#endif //__HM_LOADER_BASE_H__