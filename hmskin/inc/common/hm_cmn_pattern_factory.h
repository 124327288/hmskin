#ifndef __HM_CMN_PATTERN_FACTORY_H__
#define __HM_CMN_PATTERN_FACTORY_H__
#include "common\hm_cmn_envcfg.h"
#include "win\hm_export_defs.h"
#include <map>
#include <stdexcept>
CMN_NAMESPACE_START

#define FACTORY_TYPE( obj_base_type ) obj_base_type##_factory

#define DECLARE_FACTORY( obj_base_type ) \
	DECLARE_FACTORY_HEAD( obj_base_type ) \
	DECLARE_FACTORY_BODY( obj_base_type )

#define DECLARE_FACTORY_EXPORTS( obj_base_type ) \
	DECLARE_FACTORY_HEAD_EXPORTS( obj_base_type ) \
	DECLARE_FACTORY_BODY( obj_base_type )

#define DECLARE_FACTORY_HEAD( obj_base_type ) \
	class obj_base_type##_factory 

#define DECLARE_FACTORY_HEAD_EXPORTS( obj_base_type ) \
	class HMLIB_API obj_base_type##_factory 

#define DECLARE_FACTORY_BODY( obj_base_type ) \
	{ \
	public: \
		typedef unsigned int obj_id_type; \
		typedef std::map< obj_id_type, obj_base_type* > map_id2obj_type; \
		typedef void (*fnEnumObjsProcType)( obj_base_type*, void* pParam ); \
		typedef void (*fnEnumConstObjsProcType)( const obj_base_type*, void* pParam ); \
		enum { ERR_OBJ_ID = 0, OBJ_ID_BASE_START }; \
	public: \
		obj_base_type##_factory(); \
		~obj_base_type##_factory(); \
	public: \
		template< typename obj_derived_type > \
		obj_id_type createObj(); /*throw std::runtime_error*/ \
		template< typename obj_derived_type > \
		obj_derived_type* createObj( obj_id_type objId ); /*throw std::runtime_error*/ \
		template< typename obj_derived_type, typename init_param_type > \
		obj_id_type createObj( init_param_type initParam ); \
		template< typename obj_derived_type, typename init_param_type > \
		obj_derived_type* createObj( obj_id_type objId, init_param_type initParam ); \
		template< typename obj_derived_type, typename arg1_type, typename arg2_type > \
		obj_id_type createObj( arg1_type arg1, arg2_type arg2 ); \
		template< typename obj_derived_type, typename arg1_type, typename arg2_type > \
		obj_derived_type* createObj( obj_id_type objId, arg1_type arg1, arg2_type arg2 ); \
	    template< typename obj_derived_type, typename arg1_type, typename arg2_type, typename arg3_type > \
		obj_id_type createObj( arg1_type arg1, arg2_type arg2, arg3_type arg3 ); \
        template< typename obj_derived_type, typename arg1_type, typename arg2_type, typename arg3_type > \
		obj_derived_type* createObj( obj_id_type objId, arg1_type arg1, arg2_type arg2, arg3_type arg3 ); \
	public: \
		obj_base_type* getObj( obj_id_type objId ); \
		BOOL getObjId( const obj_base_type* pObj, obj_id_type& objId ) const; \
		bool destroyObj( obj_id_type objId ); \
		void enumObjs( fnEnumObjsProcType pfnEnumObjsProc, void* pParam ); \
		void enumObjs( fnEnumConstObjsProcType pfnEnumConstObjsProc, void* pParam ) const; \
	private: \
		bool _hasObj( obj_id_type objId ) const; \
		obj_base_type* _getObj( obj_id_type objId ); \
		BOOL _getObjId( const obj_base_type* pObj, obj_id_type& objId ) const; \
		obj_id_type _allocateId(){ return ++s_objIdBase; } \
	private: \
		static obj_id_type s_objIdBase; \
		map_id2obj_type m_mapId2Obj; \
	}; \
	template< typename obj_derived_type > \
	obj_base_type##_factory::obj_id_type obj_base_type##_factory::createObj(){ \
		obj_derived_type* pNewObj = NULL; \
		obj_id_type objIdNew; \
		objIdNew = _allocateId(); \
		if ( _hasObj( objIdNew ) ) { \
			throw std::runtime_error( "id overlap." ); \
			return ERR_OBJ_ID; \
		} \
		pNewObj = new obj_derived_type(); \
		m_mapId2Obj[ objIdNew ] = pNewObj; \
		return objIdNew; \
	} \
	template< typename obj_derived_type > \
	obj_derived_type* obj_base_type##_factory::createObj( obj_id_type objId ) { \
		obj_derived_type* pNewObj = NULL; \
		if ( _hasObj( objId ) ) { \
			throw std::runtime_error( "  id overlap." ); \
			return NULL; \
		} \
		if ( objId >= s_objIdBase ) { \
			::OutputDebugString(_T("1234567890")); \
			s_objIdBase = objId + 100; \
		} \
		pNewObj = new obj_derived_type(); \
		m_mapId2Obj[ objId ] = pNewObj; \
		return pNewObj; \
	} \
	template< typename obj_derived_type, typename init_param_type > \
	obj_base_type##_factory::obj_id_type obj_base_type##_factory::createObj( init_param_type initParam ){ \
		obj_derived_type* pNewObj = NULL; \
		obj_id_type objIdNew; \
		objIdNew = _allocateId(); \
		if ( _hasObj( objIdNew ) ) { \
			throw std::runtime_error( "id overlap." ); \
			return ERR_OBJ_ID; \
		} \
		pNewObj = new obj_derived_type( initParam ); \
		m_mapId2Obj[ objIdNew ] = pNewObj; \
		return objIdNew; \
	} \
	template< typename obj_derived_type, typename init_param_type > \
	obj_derived_type* obj_base_type##_factory::createObj( obj_id_type objId, init_param_type initParam ){ \
		obj_derived_type* pNewObj = NULL; \
		if ( _hasObj( objId ) ) { \
			throw std::runtime_error( "  id overlap." ); \
			return NULL; \
		} \
		if ( objId >= s_objIdBase ) { \
			s_objIdBase = objId + 100; \
		} \
		pNewObj = new obj_derived_type( initParam ); \
		m_mapId2Obj[ objId ] = pNewObj; \
		return pNewObj; \
	} \
	template< typename obj_derived_type, typename arg1_type, typename arg2_type > \
	obj_base_type##_factory::obj_id_type obj_base_type##_factory::createObj( arg1_type arg1, arg2_type arg2 ) { \
	    obj_derived_type* pNewObj = NULL; \
	    obj_id_type objIdNew; \
        objIdNew = _allocateId(); \
		if ( _hasObj( objIdNew ) ) { \
		    throw std::runtime_error( "id overlap." ); \
            return ERR_OBJ_ID; \
		} \
		pNewObj = new obj_derived_type( arg1, arg2 ); \
		m_mapId2Obj[ objIdNew ] = pNewObj; \
		return objIdNew; \
    } \
	template< typename obj_derived_type, typename arg1_type, typename arg2_type > \
	obj_derived_type* obj_base_type##_factory::createObj( obj_id_type objId, arg1_type arg1, arg2_type arg2 ) { \
		obj_derived_type* pNewObj = NULL; \
		if ( _hasObj( objId ) ) { \
		    throw std::runtime_error( "id overlap." ); \
			return NULL; \
		} \
		if ( objId >= s_objIdBase ) { \
		    s_objIdBase = objId + 100; \
		} \
		pNewObj = new obj_derived_type( arg1, arg2 ); \
        m_mapId2Obj[ objId ] = pNewObj; \
		return pNewObj; \
	} \
	template< typename obj_derived_type, typename arg1_type, typename arg2_type, typename arg3_type > \
	obj_base_type##_factory::obj_id_type obj_base_type##_factory::createObj( arg1_type arg1, arg2_type arg2, arg3_type arg3 ) { \
        obj_derived_type* pNewObj = NULL; \
		obj_id_type objIdNew; \
		objIdNew = _allocateId(); \
		if ( _hasObj( objIdNew ) ) { \
		    throw std::runtime_error( "id overlap." ); \
			return ERR_OBJ_ID; \
		} \
		pNewObj = new obj_derived_type( arg1, arg2, arg3 ); \
		m_mapId2Obj[ objIdNew ] = pNewObj; \
		return objIdNew; \
	} \
	template< typename obj_derived_type, typename arg1_type, typename arg2_type, typename arg3_type > \
	obj_derived_type* obj_base_type##_factory::createObj( obj_id_type objId, arg1_type arg1, arg2_type arg2, arg3_type arg3 ) { \
        obj_derived_type* pNewObj = NULL; \
		if ( _hasObj( objId ) ) { \
		    throw std::runtime_error( "id overlap." ); \
            return NULL; \
		} \
		if ( objId >= s_objIdBase ) { \
		    s_objIdBase = objId + 100; \
		} \
		pNewObj = new obj_derived_type( arg1, arg2, arg3 ); \
	    m_mapId2Obj[ objId ] = pNewObj; \
		return pNewObj; \
	}

#define IMPLEMENT_FACTORY( obj_base_type ) \
	obj_base_type##_factory::obj_id_type obj_base_type##_factory::s_objIdBase = obj_base_type##_factory::OBJ_ID_BASE_START; \
	obj_base_type##_factory::obj_base_type##_factory() {} \
	obj_base_type##_factory::~obj_base_type##_factory() { \
		map_id2obj_type::iterator itObj, iendObj; \
		iendObj = m_mapId2Obj.end(); \
		for ( itObj = m_mapId2Obj.begin(); itObj != iendObj; ++itObj ) { \
			delete itObj->second; \
		} \
		m_mapId2Obj.clear(); \
	} \
	obj_base_type* obj_base_type##_factory::getObj( obj_id_type objId ) { \
		return _getObj( objId ); \
	} \
	BOOL obj_base_type##_factory::getObjId( const obj_base_type* pObj, obj_id_type& objId ) const{ \
		return _getObjId( pObj, objId ); \
    } \
	void obj_base_type##_factory::enumObjs( fnEnumObjsProcType pfnEnumObjsProc, void* pParam ) { \
		map_id2obj_type::iterator itObj, iendObj; \
		iendObj = m_mapId2Obj.end(); \
		for ( itObj = m_mapId2Obj.begin(); itObj!=iendObj; ++itObj ) { \
			pfnEnumObjsProc( itObj->second, pParam ); \
		} \
    } \
	void obj_base_type##_factory::enumObjs( fnEnumConstObjsProcType pfnEnumConstObjsProc, void* pParam ) const { \
		map_id2obj_type::const_iterator citObj, ciendObj; \
		ciendObj = m_mapId2Obj.end(); \
		for ( citObj = m_mapId2Obj.begin(); citObj!=ciendObj; ++citObj ) { \
			pfnEnumConstObjsProc( citObj->second, pParam ); \
		} \
	} \
	bool obj_base_type##_factory::destroyObj( obj_id_type objId ) { \
		obj_base_type* pObj = NULL; \
		map_id2obj_type::iterator itObj; \
		itObj = m_mapId2Obj.find( objId ); \
		if ( itObj == m_mapId2Obj.end() ) return false; \
		pObj = itObj->second; \
		if ( !pObj ) return false; \
		delete pObj; \
		pObj = NULL; \
		m_mapId2Obj.erase( itObj ); \
		return true; \
	} \
	bool obj_base_type##_factory::_hasObj( obj_id_type objId ) const { \
		return m_mapId2Obj.find( objId ) != m_mapId2Obj.end(); \
	} \
	obj_base_type* obj_base_type##_factory::_getObj( obj_id_type objId ) { \
	    if ( m_mapId2Obj.size() == 0 ) return NULL; \
		map_id2obj_type::iterator itObj; \
		itObj = m_mapId2Obj.find( objId ); \
		return ( itObj == m_mapId2Obj.end() ) ? NULL : itObj->second; \
	} \
	BOOL  obj_base_type##_factory::_getObjId( const obj_base_type* pObj, obj_id_type& objId ) const { \
		if ( !pObj ) return FALSE; \
		map_id2obj_type::const_iterator citObj, ciendObj; \
		ciendObj = m_mapId2Obj.end(); \
		for ( citObj = m_mapId2Obj.begin(); citObj!=ciendObj; ++citObj ) { \
			if ( citObj->second == pObj ) { \
				objId = citObj->first; \
				TCHAR szMsg[100]; \
				_stprintf_s( szMsg, _T("in _getObjId, id:%d pObj:%p\n"), objId, pObj ); \
				::OutputDebugString( szMsg ); \
				return TRUE; \
			} \
		} \
		return FALSE; \
	} 

CMN_NAMESPACE_END
#endif //__HM_CMN_PATTERN_FACTORY_H__