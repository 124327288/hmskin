#ifndef __HM_MANIFEST_XML_H__
#define __HM_MANIFEST_XML_H__
#include "hm_manifest_base.h"
//
class hm_uiroot;
//
class hm_manifest_xml : public hm_manifest_base {
public:
	hm_manifest_xml( const TCHAR* szManifestFilePath );
	virtual ~hm_manifest_xml();

	// interface of hm_manifest_base
public:
	virtual bool isAvailable();
	virtual bool visit( hm_loader_base* pLoader, hm_uiroot* pHMUIRoot );

};



#endif //__HM_MANIFEST_XML_H__