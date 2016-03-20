#ifndef __HM_LOADER_KEELOBJ_H__
#define __HM_LOADER_KEELOBJ_H__
#include "win\loader\hm_loader_base.h"
//
class hm_layout_obj;
class hm_layoutdecoder_i;
class hm_wndmsg_publisher;
//
class hm_loader_keelobj : public hm_loader_base {
public:
	hm_loader_keelobj();
	virtual ~hm_loader_keelobj();

	// interface of hm_loader_base
public:
	virtual bool load( hm_manifest_json* pManifestData, hm_uiroot* pHMUIRoot );
	virtual bool load( hm_manifest_xml* pManifestData, hm_uiroot* pHMUIRoot );

private:
	BOOL _CreateLayoutObj( hm_uiroot* pHMUIRoot, const Json::Value& valLayoutObj, hm_layout_obj** ppLayoutObj );
	BOOL _CreateLayoutDecoder( hm_uiroot* pHMUIRoot, const Json::Value& valLayoutDecoder, hm_layout_obj* pLayoutOutObj, hm_layoutdecoder_i** ppLayoutDecoder );
	BOOL _CreateLayoutDecoderClientArea( hm_uiroot* pHMUIRoot, const Json::Value& valLayoutDecoder, hm_layout_obj* pLayoutOutObj, hm_layoutdecoder_i** ppLayoutDecoder );
	BOOL _CreateLayoutDecoderWndArea( hm_uiroot* pHMUIRoot, const Json::Value& valLayoutDecoder, hm_layout_obj* pLayoutOutObj, hm_layoutdecoder_i** ppLayoutDecoder );
	BOOL _CreateLayoutDecoderCorner( hm_uiroot* pHMUIRoot, const Json::Value& valLayoutDecoder, hm_layout_obj* pLayoutOutObj, hm_layoutdecoder_i** ppLayoutDecoder );
	BOOL _CreateLayoutDecoderDock( hm_uiroot* pHMUIRoot, const Json::Value& valLayoutDecoder, hm_layout_obj* pLayoutOutObj, hm_layoutdecoder_i** ppLayoutDecoder );
	BOOL _CreateLayoutDecoderOffset( hm_uiroot* pHMUIRoot, const Json::Value& valLayoutDecoder, hm_layout_obj* pLayoutOutObj, hm_layoutdecoder_i** ppLayoutDecoder );

	//
private:
	BOOL _GetWndMsgSource( hm_uiroot* pHMUIRoot, const Json::Value& valWndMsgSource, hm_wndmsg_publisher** ppWndMsgPublisher );
	BOOL _GetWndMsgSource_MsgSink( hm_uiroot* pHMUIRoot, const Json::Value& valWndMsgSource, hm_wndmsg_publisher** ppWndMsgPublisher );
	BOOL _GetWndMsgSource_KeelObj( hm_uiroot* pHMUIRoot, const Json::Value& valWndMsgSource, hm_wndmsg_publisher** ppWndMsgPublisher );

};



#endif //__HM_LOADER_KEELOBJ_H__