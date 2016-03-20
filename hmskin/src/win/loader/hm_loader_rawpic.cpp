#include "stdafx.h"
#include "win\loader\hm_loader_rawpic.h"
#include <string>
#include "tchar.h"
#include <io.h>
#include "win\hm_win_misc.h"
#include "win\resource_system\hm_rs_rawres_base.h"

static BOOL getRealPath( const std::string& strDirPathFromManifest, std::basic_string< TCHAR >& strRealPath );

hm_loader_rawpic::hm_loader_rawpic() {

}

hm_loader_rawpic::~hm_loader_rawpic() {

}

bool hm_loader_rawpic::load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot ) {
	if ( !pManifestData || !pManifestData->isAvailable() )
		return false;
	Json::Value valTmp;
	Json::Value manifestRawPicVal;
	Json::Value aryPicFilesVal;
	Json::Value valPicFile;
	std::string strTmp;
	std::basic_string< TCHAR > strImageDirPath;
	std::basic_string< TCHAR > strPicFileName;
	std::basic_string< TCHAR > strImageFilePath;
	hm_rs_rawres_pic_factory::obj_id_type RawPicId;
	unsigned int uIndex, uCount;
	
	Json::Value& rootVal = pManifestData->getRootVal();
	manifestRawPicVal = rootVal["RawPic"];
	if ( manifestRawPicVal.isNull() )
		return false;
	// get image file directory path.
	valTmp = manifestRawPicVal["DirPath"];
	if ( !valTmp.isString() )
		return false;
	strTmp = valTmp.asString();
	if ( !getRealPath( strTmp, strImageDirPath ) )
		return false;
	
	//
	aryPicFilesVal = manifestRawPicVal["PicFiles"];
	if ( !aryPicFilesVal.isArray() )
		return false;

	uCount = aryPicFilesVal.size();
	for ( uIndex = 0; uIndex!=uCount; ++uIndex ) {
		valPicFile = aryPicFilesVal[ uIndex ];

		// get RawPicId
		valTmp = valPicFile["id"];
		if ( !valTmp.isInt() )
			return false;
		RawPicId = valTmp.asInt();

		// get file name
		valTmp = valPicFile["name"];
		if ( !valTmp.isString() )
			return false;
		strTmp = valTmp.asString();
		if ( !MultiByteToTChar( strTmp, strPicFileName ) )
			return false;
		strImageFilePath = strImageDirPath;
		strImageFilePath += _T("\\");
		strImageFilePath += strPicFileName;

		//
		if ( 0 != _taccess( strImageFilePath.c_str(), 0 ) )
			return false;

		//
		if ( !RAWPICFACTORY_INSTANCE->createObj< hm_rs_rawres_pic >( (hm_rs_rawres_pic_factory::obj_id_type)RawPicId, strImageFilePath.c_str() ) )
			return false;
	}
	
	return true;
}

BOOL getRealPath( const std::string& strDirPathFromManifest, std::basic_string< TCHAR >& strRealPath ) {
	// check absolute path
	if ( strchr( strDirPathFromManifest.c_str(), ':' ) ) {
		if ( 0 == _access( strDirPathFromManifest.c_str(), 0 ) ) {
			return MultiByteToTChar( strDirPathFromManifest, strRealPath );
		} else {
			return FALSE;
		}
	}
	
	// check relative path
	std::basic_string< TCHAR > tstrRelativePath;
	std::basic_string< TCHAR > strCurModuleDirPath;
	if ( !MultiByteToTChar( strDirPathFromManifest, tstrRelativePath ) )
		return FALSE;
	if ( !GetCurModuleDirPath( strCurModuleDirPath ) )
		return FALSE;
	strRealPath = strCurModuleDirPath;
	strRealPath += _T("\\");
	strRealPath += tstrRelativePath;
	
	return ( 0 == _taccess( strRealPath.c_str(), 0 ) );
}

bool hm_loader_rawpic::load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot ) {

	return true;
}