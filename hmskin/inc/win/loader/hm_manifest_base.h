#ifndef __HM_MANIFEST_BASE_H__
#define __HM_MANIFEST_BASE_H__

class hm_loader_base;
class hm_uiroot;
class hm_manifest_base
{
public:
	hm_manifest_base(){};
	virtual ~hm_manifest_base(){};

public:
	virtual bool isAvailable() = 0;
	virtual bool visit( hm_loader_base* pLoader, hm_uiroot* pHMUIRoot ) = 0;

};


#endif //__HM_MANIFEST_BASE_H__