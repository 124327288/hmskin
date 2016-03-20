#ifndef __HM_CMN_IDOBJ_T_H__
#define __HM_CMN_IDOBJ_T_H__
//
template< typename obj_id_type = unsigned int, obj_id_type idBaseInit = 0 >
class hm_cmn_idobj_t
{
public:
	hm_cmn_idobj_t();
	hm_cmn_idobj_t( obj_id_type id );
	virtual ~hm_cmn_idobj_t();

public:
	obj_id_type getId() { return m_id; }

private:
	obj_id_type _allocateId();
	static obj_id_type s_idBase;
	
protected:
	obj_id_type m_id;
};
//
template< typename obj_id_type, obj_id_type idBaseInit >
obj_id_type hm_cmn_idobj_t< obj_id_type, idBaseInit >::s_idBase = idBaseInit;
//
template< typename obj_id_type, obj_id_type idBaseInit >
hm_cmn_idobj_t< obj_id_type, idBaseInit >::hm_cmn_idobj_t()
: m_id( _allocateId() )
{}
//
template< typename obj_id_type, obj_id_type idBaseInit >
hm_cmn_idobj_t< obj_id_type, idBaseInit >::hm_cmn_idobj_t( obj_id_type id )
: m_id( id )
{
	if ( s_idBase <= id ) {
		s_idBase += 10;
	}
}
//
template< typename obj_id_type, obj_id_type idBaseInit >
hm_cmn_idobj_t< obj_id_type, idBaseInit >::~hm_cmn_idobj_t()
{}
//
template< typename obj_id_type, obj_id_type idBaseInit >
obj_id_type hm_cmn_idobj_t< obj_id_type, idBaseInit >::_allocateId()
{
	return ++s_idBase;
}



#endif //__HM_CMN_IDOBJ_T_H__