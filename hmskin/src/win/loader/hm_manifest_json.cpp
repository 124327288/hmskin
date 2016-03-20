#include "stdafx.h"
#include "win\loader\hm_manifest_json.h"
#include "win\loader\hm_loader_base.h"
#include "tchar.h"
#include "common\FuncPack.h"
#include <assert.h>

hm_manifest_json::hm_manifest_json( const TCHAR* szManifestFilePath )
: m_rootVal( Json::Value::null )
, m_bAvailable( false ) {
	if ( !szManifestFilePath || ( 0 != _taccess( szManifestFilePath, 0 ) ) )
		return;
	HANDLE hFile;
	DWORD dwFileSize;
	char* pBufManifestData = NULL;
	DWORD dwRead;

	hFile = ::CreateFile( szManifestFilePath, FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	CFuncPack fpkColseHandle( CloseHandle, hFile );
	dwFileSize = ::GetFileSize( hFile, NULL );
	pBufManifestData = new char[ dwFileSize + 1 ];
	CFuncPack fpkDelBuf( gfnDelArray<char>, pBufManifestData );
	if ( !::ReadFile( hFile, pBufManifestData, dwFileSize, &dwRead, NULL ) )
		return;
	pBufManifestData[ dwRead ] = '\0';
	if ( !m_jsReader.parse( pBufManifestData, m_rootVal ) ) {
		assert( FALSE );
		return;
	}
	
	m_bAvailable = true;
}

hm_manifest_json::~hm_manifest_json() {

}

bool hm_manifest_json::isAvailable() {
	return m_bAvailable;
}

bool hm_manifest_json::visit( hm_loader_base* pLoader, hm_uiroot* pHMUIRoot ) {
	if ( !pLoader ) return false;
	return pLoader->load( this, pHMUIRoot );
}