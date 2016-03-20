#include "stdafx.h"
#include "win\loader\hm_loader_msgsink.h"
#include "win\hook_system\hm_hs_wnd_msg_dispatch.h"
#include "win\frame\hm_msg_sink.h"
#include "win\frame\hm_uiroot.h"

hm_loader_msgsink::hm_loader_msgsink() {}
hm_loader_msgsink::~hm_loader_msgsink() {}

bool hm_loader_msgsink::load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot ) {
	if ( !pManifestData ) return false;
	Json::Value& rootVal = pManifestData->getRootVal();
	Json::Value aryMsgSinkVal;
	Json::Value msgsinkVal;
	Json::Value valTmp;
	unsigned int uIndex, uCount;
	msg_sink_factory_type::obj_id_type idMsgSink;
	std::string strWndMarkFlag;
	hm_rs_wndmark wndMark;
	
	aryMsgSinkVal = rootVal["MsgSink"];
	if ( !aryMsgSinkVal.isArray() )
		return false; //check if it has MsgSink item.
	uCount = aryMsgSinkVal.size();
	for ( uIndex = 0; uIndex < uCount; ++uIndex ) {
		msgsinkVal = aryMsgSinkVal[ uIndex ];
		if ( !msgsinkVal.isObject() )
			return false;

		// id 
		valTmp = msgsinkVal["id"];
		if ( !valTmp.isInt() )
			return false;
		idMsgSink = valTmp.asInt();

		// WndMarkFlag
		valTmp = msgsinkVal["WndMark"];
		if ( !valTmp.isString() )
			return false;
		strWndMarkFlag = valTmp.asString();
		if ( 0 == strcmp( "PropId", strWndMarkFlag.c_str() ) ) {
			wndMark.m_eflag = hm_rs_wndmark::WNDMARK_WNDPROPID;
		} else if ( 0 == strcmp( "CtrlId", strWndMarkFlag.c_str() ) ) {
			wndMark.m_eflag = hm_rs_wndmark::WNDMARK_CTRLID;
		} else {
			return false;
		}
		
		// 
		switch ( wndMark.m_eflag )
		{
		case hm_rs_wndmark::WNDMARK_WNDPROPID:
			{
				valTmp = msgsinkVal["PropId"];
				if ( !valTmp.isInt() )
					return false;
				wndMark.m_uWndPropID = valTmp.asInt();
			}
			break;
		case hm_rs_wndmark::WNDMARK_CTRLID:
			{
				valTmp = msgsinkVal["CtrlId"];
				if ( !valTmp.isInt() )
					return false;
				wndMark.m_uCtrlID = valTmp.asInt();
			}
			break;
		default:
			return false;
			break;
		}

		//
		if ( !pHMUIRoot->m_pMsgSinkFactory->createObj< hm_msg_sink >( idMsgSink ) )
			return false;
		if ( !pHMUIRoot->m_pWndMark2MSIdTable->bindObjId2WndMark( idMsgSink, wndMark ) ) {
			pHMUIRoot->m_pMsgSinkFactory->destroyObj( idMsgSink );
			return false;
		}
	}
	
	return true;
}

bool hm_loader_msgsink::load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot ) {

	return true;
}