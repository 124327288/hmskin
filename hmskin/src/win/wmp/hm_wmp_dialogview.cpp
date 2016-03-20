#include "stdafx.h"
#include "win\wmp\hm_wmp_dialogview.h"
#include "win\frame\hm_debug_utils.h"
#include "win\resource_system\hm_rs_uires_text.h"
//////////////////////////////////////////////////////////////////////////////
//
#define UNSIGNED_INT_MAX (0xFFFFFFFF)
#define HEIGHT_MSGFROM (26)
#define LEFT_SPACE (10)
hm_dlgmsg_item_default::hm_dlgmsg_item_default( hm_dlgmsg_item_param* pParam ) 
: m_pParam( pParam )
, m_uHeight( UNSIGNED_INT_MAX )
, m_uWidthOld( UNSIGNED_INT_MAX )
{
	hm_uires_text_data textData;
	hm_posdecoder_dock* pPosDecoderDock = NULL;
	hm_posdecoder_offset* pPosDecoderOffset = NULL;
	hm_rs_uires_text* pUIResText = NULL;
	hm_showobj* pShowObj = NULL;
	int heightMsgFrom = HEIGHT_MSGFROM;
	int leftSpace = LEFT_SPACE;

	// msg from
	textData.m_tstrData = pParam->m_strMsgFrom;
	textData.m_idRawResFont = pParam->m_idFontMsgFrom;
	textData.m_idRawResColor = pParam->m_idColorMsgFrom;
	textData.m_eTextFlag = hm_uires_text_data::TEXTFLAG_SINGLELINE;
	pUIResText = new hm_rs_uires_text( textData );
	pPosDecoderDock = new hm_posdecoder_dock( hm_posdecoder_dock::DOCK_TOP, 1, 1, 1, heightMsgFrom );
	pShowObj = new hm_showobj( pUIResText, pPosDecoderDock );
	pushBackShowObj(  pShowObj );

	// msg content.
	textData.m_tstrData = pParam->m_strMsgContent;
	textData.m_idRawResFont = pParam->m_idFontMsgContent;
	textData.m_idRawResColor = pParam->m_idColorMsgContent;
	textData.m_eTextFlag = hm_uires_text_data::TEXTFLAG_MULTILINE;
	pUIResText = new hm_rs_uires_text( textData );
	pPosDecoderOffset = new hm_posdecoder_offset( leftSpace, heightMsgFrom, 1, 1 );
	pShowObj = new hm_showobj( pUIResText, pPosDecoderOffset );
	pushBackShowObj( pShowObj );
}
//
bool hm_dlgmsg_item_default::calcHeight( HDC hDC, hm_ps_drawtool_i* pDrawTool, unsigned int uWidth, unsigned int& uHeight ) {
	if ( !pDrawTool || ( uWidth < LEFT_SPACE ))
		return false;
	if ( m_uHeight != UNSIGNED_INT_MAX && ( m_uWidthOld == uWidth ) ) {
		uHeight = m_uHeight;
		return true;
	}
	RECT rcCanvas;
	hm_rs_rawres_font* pRawResFont = NULL;
	hm_rs_rawres_color* pRawResColor = NULL;
	bool bMultiLine = false;
	unsigned int uHeightFrom = 0;
	unsigned int uHeightContent = 0;

	// measure title height
	bMultiLine = true;
	pRawResFont = RAWFONTFACTORY_INSTANCE->getObj( m_pParam->m_idFontMsgFrom );
	pRawResColor = RAWCOLORFACTORY_INSTANCE->getObj( m_pParam->m_idColorMsgFrom );
	memset( &rcCanvas, 0, sizeof(RECT) );
	rcCanvas.left = LEFT_SPACE;
	rcCanvas.right = uWidth - LEFT_SPACE;
	rcCanvas.bottom = 1;
	pDrawTool->calcRect( hDC, rcCanvas, m_pParam->m_strMsgFrom.c_str(), pRawResFont, pRawResColor, bMultiLine );
	uHeightFrom = ( rcCanvas.bottom - rcCanvas.top );
	//
	bMultiLine = false;
	pRawResFont = RAWFONTFACTORY_INSTANCE->getObj( m_pParam->m_idFontMsgContent );
	pRawResColor = RAWCOLORFACTORY_INSTANCE->getObj( m_pParam->m_idColorMsgContent );
	memset( &rcCanvas, 0, sizeof(RECT) );
	rcCanvas.left = LEFT_SPACE;
	rcCanvas.right = uWidth - LEFT_SPACE;
	rcCanvas.bottom = 1;
	pDrawTool->calcRect( hDC, rcCanvas, m_pParam->m_strMsgContent.c_str(), pRawResFont, pRawResColor, true );
	uHeightContent = ( rcCanvas.bottom - rcCanvas.top );
	
	//
	uHeight = uHeightFrom + 2 + uHeightContent + 2;
	m_uHeight = uHeight;
	m_uWidthOld = uWidth;
	return true;
}
//
hm_dlgmsg_item_default::~hm_dlgmsg_item_default() {
	if ( !m_pParam )
		delete m_pParam;
}