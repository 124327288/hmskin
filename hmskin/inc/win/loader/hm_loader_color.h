#ifndef __HM_LOADER_COLOR_H__
#define __HM_LOADER_COLOR_H__
#include "win\loader\hm_loader_base.h"

class hm_loader_color : public hm_loader_base {
public:
	hm_loader_color();
	virtual ~hm_loader_color();

	// interface of hm_loader_base
public:
	virtual bool load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot );
	virtual bool load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot );
};


#endif //__HM_LOADER_COLOR_H__