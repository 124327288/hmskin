#ifndef __HM_LOADER_MSGSINK_H__
#define __HM_LOADER_MSGSINK_H__
#include "win\loader\hm_loader_base.h"

class hm_loader_msgsink : public hm_loader_base {
public:
	hm_loader_msgsink();
	virtual ~hm_loader_msgsink();

	// interface of hm_loader_base
public:
	virtual bool load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot );
	virtual bool load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot );
};


#endif //__HM_LOADER_MSGSINK_H__