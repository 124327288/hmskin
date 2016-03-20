#ifndef __HM_LOADER_COORDINATESYSTEM_H__
#define __HM_LOADER_COORDINATESYSTEM_H__
#include "win\loader\hm_loader_base.h"

class hm_loader_coordinatesystem : public hm_loader_base{
public:
	hm_loader_coordinatesystem();
	virtual ~hm_loader_coordinatesystem();
	
	// interface of hm_loader_base
public:
	virtual bool load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot );
	virtual bool load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot );

private:


};


#endif //__HM_LOADER_COORDINATESYSTEM_H__