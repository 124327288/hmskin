#ifndef __hm_loader_rawpic_H__
#define __hm_loader_rawpic_H__
#include "win\loader\hm_loader_base.h"

class hm_loader_rawpic : public hm_loader_base {
public: 
	hm_loader_rawpic();
	virtual ~hm_loader_rawpic();

	// interface of hm_loader_base
public:
	virtual bool load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot );
	virtual bool load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot );

};


#endif //__hm_loader_rawpic_H__
