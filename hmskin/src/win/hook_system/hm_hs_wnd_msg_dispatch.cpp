#include "stdafx.h"
#include <assert.h>
#include "win\hook_system\hm_hs_wnd_msg_dispatch.h"
#include "win\hook_system\hm_hs_wnd_proc_mgr.h"
#include "win\hm_event_defs.h"
#include "win\frame\hm_uiroot.h"
//////////////////////////////////////////////////////////////////////////
static void FindMSCCallBack( HWND hWnd, MsgDispatcher::msg_sink_container_type* pMsgSinkContainer, BOOL* pbContinue, void* pParam );
struct FindMSCParam
{
	HWND hWndDest;
	BOOL m_bFindMSC;
	MsgDispatcher::msg_sink_container_type* m_pMSC;
};
//////////////////////////////////////////////////////////////////////////
static LRESULT CALLBACK WndProcMsgDispatcher( HWND hWndDest, UINT message, WPARAM wParam, LPARAM lParam );
//////////////////////////////////////////////////////////////////////////
msg_sink_i::msg_sink_i()
{}
msg_sink_i::~msg_sink_i()
{
	MSGDISPATCHER_INSTANCE->UnRegMsgSink( this );
	//
	cancelAllWndMsg();
}
////
//void msg_sink_i::notifyWndMsg( HWND hWnd, UINT message, WPARAM& wParam, LPARAM& lParam, WNDPROCPARAM* pParamWndProc )
//{
//}
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FACTORY( msg_sink_i )
//////////////////////////////////////////////////////////////////////////
MsgDispatcher* MsgDispatcher::GetInstance()
{
	static MsgDispatcher s_MsgDispatcher;
	return &s_MsgDispatcher;
}

BOOL MsgDispatcher::RegMsgSink( HWND hWndDest, msg_sink_i* pMsgSink )
{
	if ( HasMsgSink( hWndDest, pMsgSink ) )
		return FALSE;
	m_mapHwnd2MSC[ hWndDest ].push_back( pMsgSink );
	
	if ( m_mapHwnd2MSC[ hWndDest ].size() == 1 )
		StartMsgSink( hWndDest, TRUE );
	
	//notify start sink msg event
	pMsgSink->OnStartSink( hWndDest );
	
	return TRUE;
}
//
void MsgDispatcher::UnRegMsgSink( msg_sink_i* pMsgSink )
{
	if ( m_mapHwnd2MSC.size() == 0 )
		return;
	map_hwnd2msc_type::iterator itContainer, iendContainer;
	msg_sink_container_type::iterator itSink, iendSink;
	bool bMatch = false;
	
	bMatch = false;
	iendContainer = m_mapHwnd2MSC.end();
	for ( itContainer = m_mapHwnd2MSC.begin(); itContainer!=iendContainer; ++itContainer )
	{
		if ( itContainer->second.size() == 0 )
			continue;
		iendSink = itContainer->second.end();
		for ( itSink = itContainer->second.begin(); itSink!=iendSink; ++itSink )
		{
			if ( (*itSink) == pMsgSink )
			{
				itContainer->second.erase( itSink );
				bMatch = true;
				break;
			}
		}
		//
		if ( itContainer->second.size() == 0 )
		{
			StartMsgSink( itContainer->first, FALSE );
		}
		//
		if ( bMatch )
			break;
	}
}
//
void MsgDispatcher::UnRegMsgSink( HWND hWndDest, msg_sink_i* pMsgSink )
{
	if ( !HasMsgSink( hWndDest, pMsgSink ) )
		return;
	msg_sink_container_type::iterator it, iend;
	
	iend = m_mapHwnd2MSC[ hWndDest ].end();
	for ( it = m_mapHwnd2MSC[ hWndDest ].begin(); it<iend; ++it ) 
	{
		if ( *it == pMsgSink )
		{
			m_mapHwnd2MSC[ hWndDest ].erase( it );
			pMsgSink->OnStopSink( hWndDest );
			break;
		}
	}
	
	if ( m_mapHwnd2MSC[ hWndDest ].size() == 0 )
		StartMsgSink( hWndDest, FALSE );
}
//
void MsgDispatcher::UnRegMsgSinks( HWND hWndDest )
{
	if ( m_mapHwnd2MSC.find( hWndDest ) == m_mapHwnd2MSC.end() )
		return;
	msg_sink_container_type::iterator it, iend;
	msg_sink_i* pMsgSink;

	//notify stop sink
	iend = m_mapHwnd2MSC[ hWndDest ].end();
	for ( it = m_mapHwnd2MSC[ hWndDest ].begin(); it<iend; ++it ) 
	{
		pMsgSink = *it;
		m_mapHwnd2MSC[ hWndDest ].erase( it );
		pMsgSink->OnStopSink( hWndDest );
	}
	
	m_mapHwnd2MSC[ hWndDest ].clear();
	m_mapHwnd2MSC.erase( hWndDest );
	StartMsgSink( hWndDest, FALSE );
}
//
void MsgDispatcher::UnRegAllMsgSinks()
{
	map_hwnd2msc_type::iterator h2mIt, h2mIend;
	msg_sink_container_type::iterator it, iend;
	msg_sink_i* pMsgSink = NULL;
	
	h2mIend = m_mapHwnd2MSC.end();
	for ( h2mIt = m_mapHwnd2MSC.begin(); h2mIt!=h2mIend; ++h2mIt ) 
	{
		iend = h2mIt->second.end();
		for ( it = h2mIt->second.begin(); it<iend; ++it ) 
		{
			pMsgSink = (*it);
			pMsgSink->OnStopSink( h2mIt->first );
			//don't hold the liftcycle of msg_sink_i
			//so don't delete pMsgSink; 
		}
		
		h2mIt->second.clear();
		StartMsgSink( h2mIt->first, FALSE );
	}
	
	m_mapHwnd2MSC.clear();
}
//
BOOL MsgDispatcher::HasMsgSink( HWND hWndDest, const msg_sink_i* pMsgSink ) const
{
	if ( m_mapHwnd2MSC.find( hWndDest ) == m_mapHwnd2MSC.end() )
		return FALSE;
	msg_sink_container_type::const_iterator c_it, c_iend;

	c_iend = m_mapHwnd2MSC.find( hWndDest )->second.end();
	for ( c_it = m_mapHwnd2MSC.find( hWndDest )->second.begin(); c_it!=c_iend; ++c_it ) 
	{
		if ( *c_it == pMsgSink )
			return TRUE;
	}
	return FALSE;
}
//
void MsgDispatcher::EnumMsgSink( pfnEnumMsgSinkCallBackType pfnEnumMsgSinkCallBack, void* pParam )
{
	BOOL bContinue;
	map_hwnd2msc_type::iterator it, iend;
	
	bContinue = TRUE;
	iend = m_mapHwnd2MSC.end();
	for ( it = m_mapHwnd2MSC.begin(); it!=iend; ++it ) 
	{
		pfnEnumMsgSinkCallBack( it->first, &(it->second), &bContinue, pParam );
		if ( !bContinue )
			break;
	}
}
//
BOOL MsgDispatcher::StartAllMsgSink( BOOL bStart, BOOL bForce )
{
	map_hwnd2msc_type::iterator it, iend;
	std::map< HWND, BOOL > mapHwnd2SinkStateOld;
	
	//save old sink state
	iend = m_mapHwnd2MSC.end();
	for ( it = m_mapHwnd2MSC.begin(); it!=iend; ++it ) 
		mapHwnd2SinkStateOld[ it->first ] = IsSinkingMsg( it->first );
	
	//start/stop message sink state
	iend = m_mapHwnd2MSC.end();
	for ( it = m_mapHwnd2MSC.begin(); it!=iend; ++it ) 
	{
		if ( !StartMsgSink( it->first, bStart ) )
		{	
			if ( !bForce )
				goto err;
		}
	}
	return TRUE;

err:
	//restore old sink state
	iend = m_mapHwnd2MSC.end();
	for ( it = m_mapHwnd2MSC.begin(); it!=iend; ++it ) 
		StartMsgSink( it->first, mapHwnd2SinkStateOld[ it->first ] );
	return FALSE;
}
//	
BOOL MsgDispatcher::StartMsgSink( HWND hWndDest, BOOL bStart )
{
	if ( bStart )
	{ //start message sink
		if ( WNDPROCMGR_INSTANCE->WasAttached( hWndDest ) )
			return TRUE;
		WNDPROCMGR_INSTANCE->Attach( hWndDest, WndProcMsgDispatcher );
		return TRUE;
	}
	else
	{ //stop message sink
		if ( !WNDPROCMGR_INSTANCE->WasAttached( hWndDest ) )
			return TRUE;
		WNDPROCMGR_INSTANCE->Detach( hWndDest );
		return TRUE;
	}
	
	assert( FALSE );
	return FALSE;
}
//	
BOOL MsgDispatcher::IsSinkingMsg( HWND hWndDest ) const
{
	//may be need more code to fix the bug that WndProc maybe set at outside of MsgDispatcher
	return WNDPROCMGR_INSTANCE->WasAttached( hWndDest );
}
//
MsgDispatcher::~MsgDispatcher()
{
	StartAllMsgSink( FALSE );

	UnRegAllMsgSinks();
}
//
MsgDispatcher::MsgDispatcher()
{}
//
LRESULT CALLBACK WndProcMsgDispatcher( HWND hWndDest, UINT message, WPARAM wParam, LPARAM lParam )
{
	FindMSCParam paramFindMSC;
	WNDPROC pfnWndProcOld = NULL;
	MsgDispatcher::msg_sink_container_type* pMSC = NULL;
	MsgDispatcher::msg_sink_container_type::iterator it, iend;
	msg_sink_i* pMsgSink = NULL;
	msg_sink_i::WNDPROCPARAM paramWndProc;
	
	//find message sink container that belong to hWndDest
	paramFindMSC.hWndDest = hWndDest;
	paramFindMSC.m_bFindMSC = FALSE;
	paramFindMSC.m_pMSC = NULL;
	MSGDISPATCHER_INSTANCE->EnumMsgSink( FindMSCCallBack, &paramFindMSC );
	paramWndProc.m_flagEatMsg = EATMSGFLAG_DISABLE_NONE;
	paramWndProc.m_bValidRes = FALSE;
	paramWndProc.m_lResult = 0;
	
	if ( paramFindMSC.m_bFindMSC )
	{ //find msg sink container
		
		pMSC = paramFindMSC.m_pMSC;
		iend = pMSC->end();
		for ( it = pMSC->begin(); it<iend; ++it ) 
		{
			pMsgSink = *it;
			pMsgSink->WndProc( hWndDest, message, wParam, lParam, &paramWndProc );
			
			if ( paramWndProc.m_flagEatMsg & EATMSGFLAG_DISABLE_OTHER_MSGSINK )
			{ //eat message
				break;
			}
		}
	}
	
	if ( paramWndProc.m_bValidRes )
		return paramWndProc.m_lResult;
	else if ( paramWndProc.m_flagEatMsg & EATMSGFLAG_DISABLE_OLD_WNDPROC )
	{ //disenable to call old wndproc
		return 0;
	}

	assert( WNDPROCMGR_INSTANCE->WasAttached( hWndDest ) );
	pfnWndProcOld = WNDPROCMGR_INSTANCE->GetWndProcOld( hWndDest );
	return CallWindowProc( pfnWndProcOld, hWndDest, message, wParam, lParam );

}
//
void FindMSCCallBack( HWND hWnd, MsgDispatcher::msg_sink_container_type* pMsgSinkContainer, BOOL* pbContinue, void* pParam )
{
	assert( pMsgSinkContainer );
	assert( pbContinue );
	assert( pParam );
	FindMSCParam* pFindMSCParam;
	
	pFindMSCParam = (FindMSCParam*)pParam;
	if ( pFindMSCParam->hWndDest == hWnd )
	{
		pFindMSCParam->m_pMSC = pMsgSinkContainer;
		pFindMSCParam->m_bFindMSC = TRUE;
		*pbContinue = FALSE;
	}
}


//
bool ConnectHwnd2MsgSink( hm_uiroot* pHMUIRoot, HWND hWnd, const hm_rs_wndmark& wndMark )
{
	if ( !pHMUIRoot )
		return false;
	hm_wmark_msid_table_type::obj_id_container_type containerObjId;
	hm_wmark_msid_table_type::obj_id_container_type::iterator itObjId, iendObjId;
	msg_sink_i* pMsgSink = NULL;
	
	//
	if ( !pHMUIRoot->m_pWndMark2MSIdTable->getObjIdContainer( wndMark, &containerObjId ) ) {
		return false;
	}
	//
	iendObjId = containerObjId.end();
	for ( itObjId = containerObjId.begin(); itObjId!=iendObjId; ++itObjId )
	{
		pMsgSink = pHMUIRoot->m_pMsgSinkFactory->getObj( *itObjId );
		if ( !pMsgSink )
			continue;
		if ( !MSGDISPATCHER_INSTANCE->HasMsgSink( hWnd, pMsgSink ) ) {
			MSGDISPATCHER_INSTANCE->RegMsgSink( hWnd, pMsgSink );
		} else {
			//it shouldn't happen.
			continue;
		}
	}
	//
	return true;
}

bool DisconnectHwnd2MsgSink( hm_uiroot* pHMUIRoot, HWND hWnd, const hm_rs_wndmark& wndMark ) 
{
	if ( !pHMUIRoot )
		return false;
	hm_wmark_msid_table_type::obj_id_container_type containerMSId;
	hm_wmark_msid_table_type::obj_id_container_type::iterator itMSId,iendMSId;
	msg_sink_i* pMsgSink = NULL;

	if ( !pHMUIRoot->m_pWndMark2MSIdTable->getObjIdContainer( wndMark, &containerMSId ) )
		return false;
	//
	iendMSId = containerMSId.end();
	for ( itMSId = containerMSId.begin(); itMSId!=iendMSId; ++itMSId )
	{
		pMsgSink = pHMUIRoot->m_pMsgSinkFactory->getObj( *itMSId );
		if ( !pMsgSink )
			continue;
		if ( MSGDISPATCHER_INSTANCE->HasMsgSink( hWnd, pMsgSink ) ) {
			MSGDISPATCHER_INSTANCE->UnRegMsgSink( hWnd, pMsgSink );
		} else {
			//it shouldn't happen
			continue;
		}
	}
		
	return true;
}

bool hm_msid2wndmark_bind( hm_uiroot* pHMUIRoot, unsigned int msId, const hm_rs_wndmark& wndMark ) {
	return pHMUIRoot->m_pWndMark2MSIdTable->bindObjId2WndMark( msId, wndMark );
}