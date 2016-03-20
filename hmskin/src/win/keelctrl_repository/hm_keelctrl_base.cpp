#include "stdafx.h"
#include "win\keelctrl_repository\hm_keelctrl_base.h"
#include "win\hm_event_defs.h"

//hm_keelctrl_base::hm_keelctrl_base() {
//	Register( this, HMKEELOBJEVENT_LAYOUTOBJ_CHANGED );
//}
//
//hm_keelctrl_base::~hm_keelctrl_base() {
//	UnRegister( this, HMKEELOBJEVENT_LAYOUTOBJ_CHANGED );
//}
//
//bool hm_keelctrl_base::setSubKeelId( subkeel_mark_type mark, hm_keel_obj_factory::obj_id_type keelId ) {
//	if ( _hasSubKeelId( mark ) )
//		return false;
//
//	m_mapMark2KeelId[ mark ] = keelId;
//	return true;
//}
//
//bool hm_keelctrl_base::hasSubKeelId( subkeel_mark_type mark ) const {
//	return _hasSubKeelId( mark );
//}
//
//bool hm_keelctrl_base::getSubKeelId( subkeel_mark_type mark, hm_keel_obj_factory::obj_id_type& keelId ) const {
//	map_mark2keelid_type::const_iterator c_itMark2Id;
//
//	c_itMark2Id = m_mapMark2KeelId.find( mark );
//	if ( c_itMark2Id != m_mapMark2KeelId.end() ) {
//		keelId = c_itMark2Id->second;
//		return true;	
//	}
//
//	return false;
//}
//
//bool hm_keelctrl_base::getSubKeelObj( subkeel_mark_type mark, hm_keel_obj** ppKeelObj ) {
//	if ( !ppKeelObj ) return false;
//    hm_keel_obj_factory::obj_id_type keelId;
//	
//	if ( !getSubKeelId( mark, keelId ) )
//		return false;
//	*ppKeelObj = KEELOBJ_FACTORY->getObj( keelId );
//	return (*ppKeelObj != NULL);
//}
//
//bool hm_keelctrl_base::_hasSubKeelId( subkeel_mark_type mark ) const {
//	map_mark2keelid_type::const_iterator c_itMark2Id;
//	
//	c_itMark2Id = m_mapMark2KeelId.find( mark );
//	return ( c_itMark2Id != m_mapMark2KeelId.end() );
//}
