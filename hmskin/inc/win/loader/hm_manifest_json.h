#ifndef __HM_MANIFEST_JSON_H__
#define __HM_MANIFEST_JSON_H__
#include "hm_manifest_base.h"
#include "json.h"

class hm_manifest_json : public hm_manifest_base{
public:
	hm_manifest_json( const TCHAR* szManifestFilePath );
	virtual ~hm_manifest_json();

	// interface of hm_manifest_base
public:
	virtual bool isAvailable();
	virtual bool visit( hm_loader_base* pLoader, hm_uiroot* pHMUIRoot );

public:
	Json::Value& getRootVal() { return m_rootVal; };

private:
	bool m_bAvailable;
	Json::Value m_rootVal;
	Json::Reader m_jsReader;
};


#endif //__HM_MANIFEST_JSON_H__