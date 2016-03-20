#ifndef __HM_MANIFEST_LOADER_H__
#define __HM_MANIFEST_LOADER_H__
#include "win\loader\hm_manifest_base.h"
#include <deque>
#include <string>
#include "tchar.h"

class hm_loader_base;
class hm_uiroot;
class hm_manifest_loader {
public:
	typedef std::deque< hm_loader_base* > loader_container_type;
	typedef std::basic_string< TCHAR > string_type;

public:
	hm_manifest_loader( const TCHAR* szUIManifestFilePath );
	virtual ~hm_manifest_loader();
 
public:
	bool load( hm_uiroot* pHMUIRoot );

private:
	void init();
	void clear();

private:
	string_type m_strManifestFilePath;
	hm_manifest_base* m_pManifestData;
	loader_container_type m_containerLoader;
};


#endif //__HM_MANIFEST_LOADER_H__