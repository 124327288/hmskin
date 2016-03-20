#ifndef __HM_LOADER_FONT_H__
#define __HM_LOADER_FONT_H__
#include "win\loader\hm_loader_base.h"

class hm_loader_font : public hm_loader_base {
public:
	hm_loader_font();
	virtual ~hm_loader_font();

	// interface of hm_loader_base
public:
	virtual bool load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot );
	virtual bool load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot );
};


#endif //__HM_LOADER_FONT_H__