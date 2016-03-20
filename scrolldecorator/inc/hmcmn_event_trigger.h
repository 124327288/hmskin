/////////////////////////////////////////////////////////////////////////////////
//
// file name:
//    hmcmn_event_trigger.h
//
// abstract:
//    This file is define for event trigger.
//
// environment:
//    vc2008
//
// revision history:
//    09/15/2006 : created by rom.wang
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef __HMCMN_EVENT_H__
#define __HMCMN_EVENT_H__
#include <deque>
#include <assert.h>
//
namespace hmcmn {

template< typename ret_type >
class hmcmn_event_trigger_arg0 {
	typedef ret_type (*fnNotifyProcType)( void* pParam );
	class funcobj_base {
	public:
		funcobj_base() {};
		virtual ~funcobj_base(){};
		virtual void invoke() = 0;
	};
	typedef std::deque< funcobj_base* > funcobj_container_type;
	//
	class staticfuncobj : public funcobj_base{
	public:
		staticfuncobj( fnNotifyProcType fnNotifyProc, void* pParam) : m_fnNotifyProc( fnNotifyProc ), m_pParam( pParam ) {};
		virtual ~staticfuncobj() {}
	public:
		virtual void invoke() { m_fnNotifyProc( m_pParam ); };
	public:
		fnNotifyProcType m_fnNotifyProc;
		void* m_pParam;
	};
	//
	template< typename inst_type >
	class memfuncobj : public funcobj_base{
	public:
		memfuncobj( inst_type* pInst, ret_type (inst_type::*pmfunc)() )
			: m_pInst( pInst )
			, m_pmfunc( pmfunc ) {}
		virtual ~memfuncobj() {}
	public:
		virtual void invoke() {
			(m_pInst->*m_pmfunc)();
		};
	public:
		inst_type* m_pInst;
		ret_type (inst_type::*m_pmfunc)();
	};
	//
	class _invoker {
	public:
		_invoker(){}
		~_invoker(){ _clearAllFuncObjs(); }
	public:
		void invoke();
		void pushbackFuncObj( funcobj_base* pFuncObj );
	private:
		void _clearAllFuncObjs();

	public:
		funcobj_container_type m_containerFuncObjs;
	};

public:
	hmcmn_event_trigger_arg0() {

	}
	virtual ~hmcmn_event_trigger_arg0() {}

public:
	void bind( fnNotifyProcType pfnNotifyProc, void* pParam = NULL ) {
		staticfuncobj* pStaticFuncObj = new staticfuncobj( pfnNotifyProc, pParam );
		m_invoker.pushbackFuncObj( pStaticFuncObj );
	}
	template< typename cls_type >
	void bind( cls_type* pCls, ret_type(cls_type::*pmfunc)() ) {
		memfuncobj< cls_type >* pMemFuncObj = new memfuncobj< cls_type >( pCls, pmfunc );
		m_invoker.pushbackFuncObj( pMemFuncObj );
	}
	void unbind( fnNotifyProcType pfnNotifyProc ) {
		m_invoker.eraseFunc( pfnNotifyProc );
	}
	void invoke() {
		m_invoker.invoke();
	}

private:
	_invoker m_invoker;
};

template<typename ret_type>
void hmcmn_event_trigger_arg0< ret_type >::_invoker::invoke() {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		(*itFuncObj)->invoke();
	}
}

template<typename ret_type>
void hmcmn_event_trigger_arg0< ret_type >::_invoker::pushbackFuncObj( funcobj_base* pFuncObj ) {
	if ( !pFuncObj )
		return;
	m_containerFuncObjs.push_back( pFuncObj );
}

template<typename ret_type>
void hmcmn_event_trigger_arg0< ret_type >::_invoker::_clearAllFuncObjs() {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	funcobj_base* pFuncObjBase = NULL;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		pFuncObjBase = (*itFuncObj);
		delete pFuncObjBase;
		pFuncObjBase = NULL;
	}
	m_containerFuncObjs.clear();
}

//////////////////////////////////////////////////////////////////////////
template< typename ret_type, typename arg1_type >
class hmcmn_event_trigger_arg1 {
	typedef ret_type (*fnNotifyProcType)( arg1_type arg1, void* pParam );
	class funcobj_base {
	public:
		funcobj_base() {};
		virtual ~funcobj_base(){};
		virtual void invoke( arg1_type arg1 ) = 0;
	};
	typedef std::deque< funcobj_base* > funcobj_container_type;
	//
	class staticfuncobj : public funcobj_base{
	public:
		staticfuncobj( fnNotifyProcType fnNotifyProc, void* pParam) : m_fnNotifyProc( fnNotifyProc ), m_pParam( pParam ) {};
		virtual ~staticfuncobj() {}
	public:
		virtual void invoke( arg1_type arg1 ) { m_fnNotifyProc( arg1, m_pParam ); };
	public:
		fnNotifyProcType m_fnNotifyProc;
		void* m_pParam;
	};
	//
	template< typename inst_type >
	class memfuncobj : public funcobj_base{
	public:
		memfuncobj( inst_type* pInst, ret_type (inst_type::*pmfunc)( arg1_type ) )
			: m_pInst( pInst )
			, m_pmfunc( pmfunc ) {}
		virtual ~memfuncobj() {}
	public:
		virtual void invoke( arg1_type arg1 ) {
			(m_pInst->*m_pmfunc)( arg1 );
		};
	public:
		inst_type* m_pInst;
		ret_type (inst_type::*m_pmfunc)( arg1_type );
	};
	//
	class _invoker {
	public:
		_invoker(){}
		~_invoker(){}
	public:
		void invoke( arg1_type& arg1 );
		void pushbackFuncObj( funcobj_base* pFuncObj );
	private:
		void _clearAllFuncObj();
	public:
		funcobj_container_type m_containerFuncObjs;
	};

public:
	hmcmn_event_trigger_arg1() {
	}
	virtual ~hmcmn_event_trigger_arg1() {}

public:
	void bind( fnNotifyProcType pfnNotifyProc, void* pParam = NULL ) {
		staticfuncobj* pStaticFuncObj = new staticfuncobj( pfnNotifyProc, pParam );
		m_invoker.pushbackFuncObj( pStaticFuncObj );
	}
	template< typename cls_type >
	void bind( cls_type* pCls, ret_type(cls_type::*pmfunc)( arg1_type ) ) {
		memfuncobj< cls_type >* pMemFuncObj = new memfuncobj< cls_type >( pCls, pmfunc );
		m_invoker.pushbackFuncObj( pMemFuncObj );
	}
	void invoke( arg1_type arg1 ) {
		m_invoker.invoke( arg1 );
	}
	
private:
	_invoker m_invoker;
};

template<typename ret_type, typename arg1_type>
void hmcmn_event_trigger_arg1< ret_type, arg1_type >::_invoker::invoke( arg1_type& arg1 ) {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		(*itFuncObj)->invoke( arg1 );
	}
}

template<typename ret_type, typename arg1_type>
void hmcmn_event_trigger_arg1< ret_type, arg1_type >::_invoker::pushbackFuncObj( funcobj_base* pFuncObj ) {
	if ( !pFuncObj )
		return;
	m_containerFuncObjs.push_back( pFuncObj );
}

template<typename ret_type, typename arg1_type>
void hmcmn_event_trigger_arg1< ret_type, arg1_type >::_invoker::_clearAllFuncObj() {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	funcobj_base* pFuncObjBase = NULL;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		pFuncObjBase = (*itFuncObj);
		delete pFuncObjBase;
		pFuncObjBase = NULL;
	}
	m_containerFuncObjs.clear();
}

//////////////////////////////////////////////////////////////////////////
template< typename ret_type, typename arg1_type, typename arg2_type >
class hmcmn_event_trigger_arg2 {
	typedef ret_type (*fnNotifyProcType)( arg1_type arg1, arg2_type arg2, void* pParam );
	class funcobj_base {
	public:
		funcobj_base() {};
		virtual ~funcobj_base(){};
		virtual void invoke( arg1_type arg1, arg2_type arg2 ) = 0;
	};
	typedef std::deque< funcobj_base* > funcobj_container_type;
	//
	class staticfuncobj : public funcobj_base{
	public:
		staticfuncobj( fnNotifyProcType fnNotifyProc, void* pParam) : m_fnNotifyProc( fnNotifyProc ), m_pParam( pParam ) {};
		virtual ~staticfuncobj() {}
	public:
		virtual void invoke( arg1_type arg1, arg2_type arg2 ) { m_fnNotifyProc( arg1, arg2, m_pParam ); };
	public:
		fnNotifyProcType m_fnNotifyProc;
		void* m_pParam;
	};
	//
	template< typename inst_type >
	class memfuncobj : public funcobj_base{
	public:
		memfuncobj( inst_type* pInst, ret_type (inst_type::*pmfunc)( arg1_type, arg2_type ) )
			: m_pInst( pInst )
			, m_pmfunc( pmfunc ) {}
		virtual ~memfuncobj() {}
	public:
		virtual void invoke( arg1_type arg1, arg2_type arg2 ) {
			(m_pInst->*m_pmfunc)( arg1, arg2 );
		};
	public:
		inst_type* m_pInst;
		ret_type (inst_type::*m_pmfunc)( arg1_type, arg2_type );
	};
	//
	class _invoker {
	public:
		_invoker(){}
		~_invoker(){}
	public:
		void invoke( arg1_type& arg1, arg2_type& arg2 );
		void pushbackFuncObj( funcobj_base* pFuncObj );
	private:
		void _clearAllFuncObj();
	public:
		funcobj_container_type m_containerFuncObjs;
	};

public:
	hmcmn_event_trigger_arg2() {
	}
	virtual ~hmcmn_event_trigger_arg2() {}

public:
	void bind( fnNotifyProcType pfnNotifyProc, void* pParam = NULL ) {
		staticfuncobj* pStaticFuncObj = new staticfuncobj( pfnNotifyProc, pParam );
		m_invoker.pushbackFuncObj( pStaticFuncObj );
	}
	template< typename cls_type >
	void bind( cls_type* pCls, ret_type(cls_type::*pmfunc)( arg1_type, arg2_type ) ) {
		memfuncobj< cls_type >* pMemFuncObj = new memfuncobj< cls_type >( pCls, pmfunc );
		m_invoker.pushbackFuncObj( pMemFuncObj );
	}
	void invoke( arg1_type arg1, arg2_type arg2 ) {
		m_invoker.invoke( arg1, arg2 );
	}

private:
	_invoker m_invoker;
};

template<typename ret_type, typename arg1_type, typename arg2_type>
void hmcmn_event_trigger_arg2< ret_type, arg1_type, arg2_type >::_invoker::invoke( arg1_type& arg1, arg2_type& arg2 ) {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		(*itFuncObj)->invoke( arg1, arg2 );
	}
}

template<typename ret_type, typename arg1_type, typename arg2_type>
void hmcmn_event_trigger_arg2< ret_type, arg1_type, arg2_type >::_invoker::pushbackFuncObj( funcobj_base* pFuncObj ) {
	if ( !pFuncObj )
		return;
	m_containerFuncObjs.push_back( pFuncObj );
}

template<typename ret_type, typename arg1_type, typename arg2_type>
void hmcmn_event_trigger_arg2< ret_type, arg1_type, arg2_type >::_invoker::_clearAllFuncObj() {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	funcobj_base* pFuncObjBase = NULL;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		pFuncObjBase = (*itFuncObj);
		delete pFuncObjBase;
		pFuncObjBase = NULL;
	}
	m_containerFuncObjs.clear();
}


//////////////////////////////////////////////////////////////////////////
template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type >
class hmcmn_event_trigger_arg3 {
	typedef ret_type (*fnNotifyProcType)( arg1_type arg1, arg2_type arg2, arg3_type arg3, void* pParam );
	class funcobj_base {
	public:
		funcobj_base() {};
		virtual ~funcobj_base(){};
		virtual void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3 ) = 0;
	};
	typedef std::deque< funcobj_base* > funcobj_container_type;
	//
	class staticfuncobj : public funcobj_base{
	public:
		staticfuncobj( fnNotifyProcType fnNotifyProc, void* pParam) : m_fnNotifyProc( fnNotifyProc ), m_pParam( pParam ) {};
		virtual ~staticfuncobj() {}
	public:
		virtual void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3 ) { m_fnNotifyProc( arg1, arg2, arg3, m_pParam ); };
	public:
		fnNotifyProcType m_fnNotifyProc;
		void* m_pParam;
	};
	//
	template< typename inst_type >
	class memfuncobj : public funcobj_base{
	public:
		memfuncobj( inst_type* pInst, ret_type (inst_type::*pmfunc)( arg1_type, arg2_type, arg3_type ) )
			: m_pInst( pInst )
			, m_pmfunc( pmfunc ) {}
		virtual ~memfuncobj() {}
	public:
		virtual void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3 ) {
			(m_pInst->*m_pmfunc)( arg1, arg2, arg3 );
		};
	public:
		inst_type* m_pInst;
		ret_type (inst_type::*m_pmfunc)( arg1_type, arg2_type, arg3_type );
	};
	//
	class _invoker {
	public:
		_invoker(){}
		~_invoker(){}
	public:
		void invoke( arg1_type& arg1, arg2_type& arg2, arg3_type& arg3 );
		void pushbackFuncObj( funcobj_base* pFuncObj );
	private:
		void _clearAllFuncObj();
	public:
		funcobj_container_type m_containerFuncObjs;
	};

public:
	hmcmn_event_trigger_arg3() {
	}
	virtual ~hmcmn_event_trigger_arg3() {}

public:
	void bind( fnNotifyProcType pfnNotifyProc, void* pParam = NULL ) {
		staticfuncobj* pStaticFuncObj = new staticfuncobj( pfnNotifyProc, pParam );
		m_invoker.pushbackFuncObj( pStaticFuncObj );
	}
	template< typename cls_type >
	void bind( cls_type* pCls, ret_type(cls_type::*pmfunc)( arg1_type, arg2_type, arg3_type ) ) {
		memfuncobj< cls_type >* pMemFuncObj = new memfuncobj< cls_type >( pCls, pmfunc );
		m_invoker.pushbackFuncObj( pMemFuncObj );
	}
	void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3 ) {
		m_invoker.invoke( arg1, arg2, arg3 );
	}

private:
	_invoker m_invoker;
};

template<typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type>
void hmcmn_event_trigger_arg3< ret_type, arg1_type, arg2_type, arg3_type >::_invoker::invoke( arg1_type& arg1, arg2_type& arg2, arg3_type& arg3 ) {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		(*itFuncObj)->invoke( arg1, arg2, arg3 );
	}
}

template<typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type>
void hmcmn_event_trigger_arg3< ret_type, arg1_type, arg2_type, arg3_type >::_invoker::pushbackFuncObj( funcobj_base* pFuncObj ) {
	if ( !pFuncObj )
		return;
	m_containerFuncObjs.push_back( pFuncObj );
}

template<typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type>
void hmcmn_event_trigger_arg3< ret_type, arg1_type, arg2_type, arg3_type >::_invoker::_clearAllFuncObj() {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	funcobj_base* pFuncObjBase = NULL;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		pFuncObjBase = (*itFuncObj);
		delete pFuncObjBase;
		pFuncObjBase = NULL;
	}
	m_containerFuncObjs.clear();
}

//////////////////////////////////////////////////////////////////////////
template< typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type >
class hmcmn_event_trigger_arg4 {
	typedef ret_type (*fnNotifyProcType)( arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, void* pParam );
	class funcobj_base {
	public:
		funcobj_base() {};
		virtual ~funcobj_base(){};
		virtual void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4 ) = 0;
	};
	typedef std::deque< funcobj_base* > funcobj_container_type;
	//
	class staticfuncobj : public funcobj_base{
	public:
		staticfuncobj( fnNotifyProcType fnNotifyProc, void* pParam) : m_fnNotifyProc( fnNotifyProc ), m_pParam( pParam ) {};
		virtual ~staticfuncobj() {}
	public:
		virtual void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4 ) { m_fnNotifyProc( arg1, arg2, arg3, arg4, m_pParam ); };
	public:
		fnNotifyProcType m_fnNotifyProc;
		void* m_pParam;
	};
	//
	template< typename inst_type >
	class memfuncobj : public funcobj_base{
	public:
		memfuncobj( inst_type* pInst, ret_type (inst_type::*pmfunc)( arg1_type, arg2_type, arg3_type, arg4_type ) )
			: m_pInst( pInst )
			, m_pmfunc( pmfunc ) {}
		virtual ~memfuncobj() {}
	public:
		virtual void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4 ) {
			(m_pInst->*m_pmfunc)( arg1, arg2, arg3, arg4 );
		};
	public:
		inst_type* m_pInst;
		ret_type (inst_type::*m_pmfunc)( arg1_type, arg2_type, arg3_type, arg4_type );
	};
	//
	class _invoker {
	public:
		_invoker(){}
		~_invoker(){}
	public:
		void invoke( arg1_type& arg1, arg2_type& arg2, arg3_type& arg3, arg4_type& arg4 );
		void pushbackFuncObj( funcobj_base* pFuncObj );
	private:
		void _clearAllFuncObj();
	public:
		funcobj_container_type m_containerFuncObjs;
	};

public:
	hmcmn_event_trigger_arg4() {
	}
	virtual ~hmcmn_event_trigger_arg4() {}

public:
	void bind( fnNotifyProcType pfnNotifyProc, void* pParam = NULL ) {
		staticfuncobj* pStaticFuncObj = new staticfuncobj( pfnNotifyProc, pParam );
		m_invoker.pushbackFuncObj( pStaticFuncObj );
	}
	template< typename cls_type >
	void bind( cls_type* pCls, ret_type(cls_type::*pmfunc)( arg1_type, arg2_type, arg3_type, arg4_type ) ) {
		memfuncobj< cls_type >* pMemFuncObj = new memfuncobj< cls_type >( pCls, pmfunc );
		m_invoker.pushbackFuncObj( pMemFuncObj );
	}
	void invoke( arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4 ) {
		m_invoker.invoke( arg1, arg2, arg3, arg4 );
	}

private:
	_invoker m_invoker;
};

template<typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type>
void hmcmn_event_trigger_arg4< ret_type, arg1_type, arg2_type, arg3_type, arg4_type >::_invoker::invoke( arg1_type& arg1, arg2_type& arg2, arg3_type& arg3, arg4_type& arg4 ) {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		(*itFuncObj)->invoke( arg1, arg2, arg3, arg4 );
	}
}

template<typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type>
void hmcmn_event_trigger_arg4< ret_type, arg1_type, arg2_type, arg3_type, arg4_type >::_invoker::pushbackFuncObj( funcobj_base* pFuncObj ) {
	if ( !pFuncObj )
		return;
	m_containerFuncObjs.push_back( pFuncObj );
}

template<typename ret_type, typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type>
void hmcmn_event_trigger_arg4< ret_type, arg1_type, arg2_type, arg3_type, arg4_type >::_invoker::_clearAllFuncObj() {
	funcobj_container_type::iterator itFuncObj, iendFuncObj;
	funcobj_base* pFuncObjBase = NULL;

	iendFuncObj = m_containerFuncObjs.end();
	for ( itFuncObj = m_containerFuncObjs.begin(); itFuncObj!=iendFuncObj; ++itFuncObj ) {
		pFuncObjBase = (*itFuncObj);
		delete pFuncObjBase;
		pFuncObjBase = NULL;
	}
	m_containerFuncObjs.clear();
}

};

#endif //__HMCMN_EVENT_H__