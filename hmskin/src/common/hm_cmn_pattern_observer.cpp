#include "stdafx.h"
#include "common\hm_cmn_pattern_observer.h"
#include <assert.h>

USING_NAMESPACE_CMN
//观察者模式 begin////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//class hm_cmn_subject
void hm_cmn_subject::Notify(UINT idEvent, long pEventParam, long pEventParam2 )
{
	BOOL bContinue = TRUE;
	
	obs_ptr_container_type::const_iterator it2, itend2;
	itend2 = m_pObsContainer.end();
	for( it2 = m_pObsContainer.begin(); it2!=itend2; ++it2 )
	{
		if( !bContinue )
			return;
		if( it2->second == idEvent )
		{
			it2->first->update( this, idEvent, pEventParam, pEventParam2, &bContinue );	
		}
	}

}

void hm_cmn_subject::EraseAllRegister()
{	
	m_pObsContainer.clear();
}

void hm_cmn_subject::Register( obs_ptr_type pObserver, event_id_type idEvent )
{
	assert(!HasRegister(pObserver, idEvent));

	m_pObsContainer.push_back( std::pair<obs_ptr_type, event_id_type>( pObserver, idEvent ) );
	
	assert(HasRegister(pObserver, idEvent));
}

bool hm_cmn_subject::HasRegister( obs_ptr_type pObserver, event_id_type idEvent ) const
{
	obs_ptr_container_type::const_iterator it, itend;
	
	itend = m_pObsContainer.end();
	for( it = m_pObsContainer.begin(); it<itend; ++it )
	{
		if( it->first == pObserver && it->second == idEvent )
			return TRUE;
	}
	
	return FALSE;
}

bool hm_cmn_subject::HasRegister( obs_ptr_type pObserver ) const
{
	obs_ptr_container_type::const_iterator it, itend;
	
	itend = m_pObsContainer.end();
	for( it = m_pObsContainer.begin(); it<itend; ++it )
	{
		if( it->first == pObserver )
			return TRUE;
	}
	
	return FALSE;
}

void hm_cmn_subject::UnRegister( obs_ptr_type pObserver, event_id_type idEvent)
{

	assert(HasRegister(pObserver, idEvent));
	
	obs_ptr_container_type::iterator it, itend;

	itend = m_pObsContainer.end();
	for(it = m_pObsContainer.begin(); it<itend; ++it)
	{
		if( it->first == pObserver && it->second == idEvent )
		{
			m_pObsContainer.erase(it);
			break;
		}
	}
	
	assert(!HasRegister( pObserver, idEvent ) );
}
//观察者模式 end////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// QParamBox
void QParamBox::SetParamInt( param_flag_type flag, int value )
{
	m_mapFlag2Int[ flag ] = value;
}

BOOL QParamBox::HasParamInt( param_flag_type flag ) const
{
	return m_mapFlag2Int.find( flag ) != m_mapFlag2Int.end();
}

BOOL QParamBox::Flag2ParamInt( param_flag_type flag, int& value )
{
	if ( !HasParamInt( flag ) )
		return FALSE;

	value = m_mapFlag2Int[ flag ];
	return TRUE;
}

int QParamBox::Flag2ParamInt( param_flag_type flag )
{
	assert( HasParamInt( flag ) );
	return m_mapFlag2Int[ flag ];
}

void QParamBox::ClearAllParamInt()
{
	m_mapFlag2Int.clear();
}

void QParamBox::EraseParamInt( param_flag_type flag )
{
	if ( !HasParamInt( flag ) )
		return;

	m_mapFlag2Int.erase( flag );
}

void QParamBox::SetParamStr( param_flag_type flag, const string_type& strValue )
{
	m_mapFlag2Str[ flag ] = strValue;
}

BOOL QParamBox::HasParamStr( param_flag_type flag ) const
{
	return m_mapFlag2Str.find( flag ) != m_mapFlag2Str.end();
}

BOOL QParamBox::Flag2ParamStr( param_flag_type flag, string_type& strValue )
{
	if ( !HasParamStr( flag ) )
		return FALSE;
	strValue = m_mapFlag2Str[ flag ];
	return TRUE;
}

QParamBox::string_type QParamBox::Flag2ParamStr( param_flag_type flag )
{
	assert( HasParamStr( flag ) );
	return m_mapFlag2Str[ flag ];
}

void QParamBox::ClearAllParamStr()
{
	m_mapFlag2Str.clear();
}

void QParamBox::EraseParamStr( param_flag_type flag )
{
	if ( !HasParamStr( flag ) )
		return;
	m_mapFlag2Str.erase( flag );
}