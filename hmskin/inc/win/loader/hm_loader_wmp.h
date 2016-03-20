#ifndef __HM_LOADER_WMP_H__
#define __HM_LOADER_WMP_H__
#include "win\loader\hm_loader_base.h"
//
class hm_wmp_loader_depot;
//
class hm_loader_wmp : public hm_loader_base {
public:
	hm_loader_wmp();
	virtual ~hm_loader_wmp();

	// interface of hm_loader_base
public:
	virtual bool load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot );
	virtual bool load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot );
	
private:
	hm_wmp_loader_depot* m_pWMPLoaderDepot;
};


#endif //__HM_LOADER_WMP_H__