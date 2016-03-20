#include "stdafx.h"
#include "common\hm_cmn_refcnt.h"
#include <stdexcept>

hm_cmn_refcnt::hm_cmn_refcnt() {
	m_mapEventId2RefCount.clear();
}
//
hm_cmn_refcnt::~hm_cmn_refcnt() {
	
}
//
void hm_cmn_refcnt::addResRefCnt( refres_id_type rrId ) {
	_addRefCount( rrId );
}
//
void hm_cmn_refcnt::releaseResRefCnt( refres_id_type rrId ) {
	_releaseRefCount( rrId );
}
//
void hm_cmn_refcnt::_addRefCount( refres_id_type rrId ) {
	if ( !_hasEventId( rrId ) ) {
		m_mapEventId2RefCount[ rrId ] = 0;
	}
	//
	if ( ++(m_mapEventId2RefCount[ rrId ]) == 1 ) {
		doFirstRef( rrId );
	}
}
//
void hm_cmn_refcnt::_releaseRefCount( refres_id_type rrId ) {
	if ( !_hasEventId( rrId ) || ( m_mapEventId2RefCount[ rrId ] == 0 ) ) {
		throw std::runtime_error( "reference count cannot be less than 0." );
		return;
	}
	//
	if ( --(m_mapEventId2RefCount[ rrId ]) == 0 ) {
		m_mapEventId2RefCount.erase( rrId );
		doFinalRelase( rrId );
	}
}
//
bool hm_cmn_refcnt::_hasEventId( refres_id_type rrId ) {
	map_rrid2refcount_type::iterator itRefCount;

	itRefCount = m_mapEventId2RefCount.find( rrId );
	return itRefCount != m_mapEventId2RefCount.end();
}
