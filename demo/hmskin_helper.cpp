#include "stdafx.h"
#include "hmskin_helper.h"
#include "win/wmp/hm_wmp_display.h"
#include "win/resource_system/hm_rs_uires_text.h"
#include <assert.h>
//

//
unsigned int getWMPDisplayText( void* pWMPDisplayRaw, LPTSTR lpszStringBuf, int nMaxTextCount, int nDistrictId ) {
	hm_wmp_display* pWMPDisplay = ( hm_wmp_display* )pWMPDisplayRaw;
	hm_districtobj* pDistrictObj = NULL;
	hm_showobj* pShowObj = NULL;
	unsigned int uShowObjCount;
	hm_rs_uires_text* pUIResText = NULL;
	const hm_uires_text_data* pTextData = NULL;
	unsigned int uLenText = 0 ;
	unsigned int uLenTextDoCopy = 0;

	if ( pWMPDisplay->getDistrictObj( nDistrictId, &pDistrictObj ) ) {
		uShowObjCount = pDistrictObj->getShowObjCount();
		for ( unsigned int uShowObjIndex = 0; uShowObjIndex < uShowObjCount; ++uShowObjIndex ) {
			pShowObj = pDistrictObj->getShowObj( uShowObjIndex );
			if ( !pShowObj ) 
				continue;
			pUIResText = dynamic_cast<hm_rs_uires_text*>( pShowObj->m_pUIRes );
			if ( !pUIResText )
				continue;
			pTextData = pUIResText->getData();
			if ( pTextData ) {
				uLenText = pTextData->m_tstrData.length();
				if ( !lpszStringBuf ) {
					return uLenText + 1; // return the charicter count of buffer need.
				} else {
					if ( nMaxTextCount == 0 )
						return 0; // it specify no buffer.
					uLenTextDoCopy = ( unsigned int )min( ( unsigned int )( nMaxTextCount - 1 ), uLenText );
					_tcsncpy_s( lpszStringBuf, nMaxTextCount, pTextData->m_tstrData.c_str(), uLenTextDoCopy );
					return uLenTextDoCopy;
				}
				assert( false );
			}
		}
	}
	
	return 0;
}
//
bool setWMPDisplayText( void* pWMPDisplayRaw, LPTSTR lpString, int nDistrictId ) {
	if ( !pWMPDisplayRaw || !lpString )
		return false;
	hm_wmp_display* pWMPDisplay = ( hm_wmp_display* )pWMPDisplayRaw;
	hm_districtobj* pDistrictObj = NULL;
	hm_showobj* pShowObj = NULL;
	unsigned int uShowObjCount;
	hm_rs_uires_text* pUIResText = NULL;
	const hm_uires_text_data* pTextData = NULL;
	hm_wmp_display::district_id_container_type containerDstIds;
	hm_wmp_display::district_id_container_type::iterator itId, iendId;


	if ( nDistrictId == DISTRICT_ID_ALL ) {
		pWMPDisplay->getAllDistrictId( containerDstIds );
		if ( containerDstIds.size() == 0 )
			return true;
		iendId = containerDstIds.end();
		for ( itId = containerDstIds.begin(); itId != iendId; ++itId ) {
			setWMPDisplayText( pWMPDisplayRaw, lpString, *itId );
		}
		return true;
	} else {
		if ( pWMPDisplay->getDistrictObj( nDistrictId, &pDistrictObj ) ) {
			uShowObjCount = pDistrictObj->getShowObjCount();
			for ( unsigned int uShowObjIndex = 0; uShowObjIndex < uShowObjCount; ++uShowObjIndex ) {
				pShowObj = pDistrictObj->getShowObj( uShowObjIndex );
				if ( !pShowObj )
					continue;
				pUIResText = dynamic_cast< hm_rs_uires_text* >( pShowObj->m_pUIRes );
				if ( !pUIResText )
					continue;
				pUIResText->setText( lpString );
				return true;
			}
			// can not find out hm_rs_uires_text.
			hm_uires_text_data textData;
			textData.m_tstrData = lpString;
			pUIResText = new hm_rs_uires_text( textData );
			pShowObj = new hm_showobj( pUIResText );
			pDistrictObj->pushBackShowObj( pShowObj );
		}
	}

	return true;
}