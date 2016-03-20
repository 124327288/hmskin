#ifndef __HM_KEELCTRL_BASE_H__
#define __HM_KEELCTRL_BASE_H__
#include "win\frame\hm_keel_obj.h"
#include <map>

//class hm_keelctrl_base : public hm_keel_obj {
//public:
//	typedef unsigned int subkeel_mark_type;
//	typedef std::map< subkeel_mark_type, hm_keel_obj_factory::obj_id_type > map_mark2keelid_type;
//
//public:
//	hm_keelctrl_base();
//	virtual ~hm_keelctrl_base();
//
//public:
//	bool setSubKeelId( subkeel_mark_type mark, hm_keel_obj_factory::obj_id_type keelId );
//	bool hasSubKeelId( subkeel_mark_type mark ) const;
//	bool getSubKeelId( subkeel_mark_type mark, hm_keel_obj_factory::obj_id_type& keelId ) const;
//	bool getSubKeelObj( subkeel_mark_type mark, hm_keel_obj** ppKeelObj );
//
//private:
//	bool _hasSubKeelId( subkeel_mark_type mark ) const;
//
//protected:
//	map_mark2keelid_type m_mapMark2KeelId;
//};




#endif //__HM_KEELCTRL_BASE_H__