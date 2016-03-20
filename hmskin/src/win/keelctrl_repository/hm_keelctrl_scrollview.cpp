#include "stdafx.h"
#include "win\keelctrl_repository\hm_keelctrl_scrollview.h"
#include "win\frame\hm_layout_decoders.h"
#include "win\wmp\hm_wndmsgprocessor_i.h"
#include "win\wmp\hm_wmp_scrollbar.h"
#include "win\paint_system\hm_ps_drawtool_gdi.h"
#include "win\hm_event_defs.h"
 
//hm_keelctrl_scrollview::hm_keelctrl_scrollview( const INITIDSET& initIdSet ) 
//: m_pWMPScrollBarV( NULL )
//, m_pWMPScrollBarH( NULL )
//, m_pWMPViewBKGND( NULL )
//, m_uContentWidth( 100 )
//, m_uContentHeight( 100 )
//, m_uFlag( 0 )
//, m_hWndCanvas( NULL ) {
//	KEELOBJ_FACTORY->createObj< hm_keel_obj >( initIdSet.idScrollBarV );
//	setSubKeelId( ESKM_SCROLLBAR_V, initIdSet.idScrollBarV );
//	//m_wmpIdScrollBarV = initIdSet.wmpIdScrollBarV;
//	//
//	KEELOBJ_FACTORY->createObj< hm_keel_obj >( initIdSet.idScrollBarH );
//	setSubKeelId( ESKM_SCROLLBAR_H, initIdSet.idScrollBarH );
//	//m_wmpIdScrollBarH = initIdSet.wmpIdScrollBarH;
//	//
//	KEELOBJ_FACTORY->createObj< hm_keel_obj >( initIdSet.idViewContent );
//	setSubKeelId( ESKM_INNER_VIEW, initIdSet.idViewContent );
//	//m_wmpIdViewContent = initIdSet.wmpIdViewContent;
//	//
//
//	_init( initIdSet );
//}
//
//hm_keelctrl_scrollview::~hm_keelctrl_scrollview() {
//	hm_keel_obj_factory::obj_id_type idKeelObj;
//	
//	//
//	_uninit();
//	//
//	getSubKeelId( ESKM_SCROLLBAR_V, idKeelObj );
//	KEELOBJ_FACTORY->destroyObj( idKeelObj );
//	//
//	getSubKeelId( ESKM_SCROLLBAR_H, idKeelObj );
//	KEELOBJ_FACTORY->destroyObj( idKeelObj );
//	//
//	getSubKeelId( ESKM_INNER_VIEW, idKeelObj );
//	KEELOBJ_FACTORY->destroyObj( idKeelObj );
//}
//
//hm_keel_obj* hm_keelctrl_scrollview::getKeelObjScrollBarV() {
//	hm_keel_obj* pKeelObj = NULL;
//	if ( !getSubKeelObj( ESKM_SCROLLBAR_V, &pKeelObj ) )
//		return NULL;
//	return pKeelObj;
//}
//
//hm_keel_obj* hm_keelctrl_scrollview::getKeelObjScrollBarH() {
//	hm_keel_obj* pKeelObj = NULL;
//	if ( !getSubKeelObj( ESKM_SCROLLBAR_H, &pKeelObj ) )
//		return NULL;
//	return pKeelObj;
//}
//
//hm_keel_obj* hm_keelctrl_scrollview::getKeelObjViewContent() {
//	hm_keel_obj* pKeelObj = NULL;
//	if ( !getSubKeelObj( ESKM_INNER_VIEW, &pKeelObj ) )
//		return NULL;
//	return pKeelObj;
//}
//
//hm_wmp_scrollbar* hm_keelctrl_scrollview::getWMPScrollBarV() {
//	return m_pWMPScrollBarV;
// //   hm_wmp_scrollbar* pWMP = NULL;
//
//	//pWMP = (hm_wmp_scrollbar*)WMPFACTORY_INSTANCE->getObj( m_wmpIdScrollBarV );
//	//return pWMP;
//}
//
//hm_wmp_scrollbar* hm_keelctrl_scrollview::getWMPScrollBarH() {
//	return m_pWMPScrollBarH;
// //   hm_wmp_scrollbar* pWMP = NULL;
//
//	//pWMP = (hm_wmp_scrollbar*)WMPFACTORY_INSTANCE->getObj( m_wmpIdScrollBarH );
//	//return pWMP;
//}
//
//hm_wmp_viewbkcontent* hm_keelctrl_scrollview::getWMPViewContent() {
//	return m_pWMPViewBKGND;
//	//hm_wmp_viewbkcontent* pWMP = NULL;
//
//	//pWMP = (hm_wmp_viewbkcontent*)WMPFACTORY_INSTANCE->getObj( m_wmpIdViewContent );
//	//return pWMP;
//}
//
//void hm_keelctrl_scrollview::setContentHeight( unsigned int nHeight ) { 
//	m_uFlag |= FLAG_CONTENTVISIBLE_DIRTY; 
//	m_uContentHeight = nHeight; 
//}
//
//void hm_keelctrl_scrollview::setContentWidth( unsigned int nWidth ) { 
//	m_uFlag |= FLAG_CONTENTVISIBLE_DIRTY; 
//	m_uContentWidth = nWidth; 
//}
//
//void hm_keelctrl_scrollview::_init( const INITIDSET& initIdSet ) {
//    hm_keel_obj* pKeelObjScrollBarV = NULL;
//    hm_keel_obj* pKeelObjScrollBarH = NULL;
//    hm_keel_obj* pKeelObjInnerView = NULL;
//	hm_layout_obj* pLayoutObj = NULL;
//	hm_layoutdecoder_dock* ptr_layout_decoder_dock = NULL;
//	hm_layoutdecoder_offset* ptr_layout_decoder_offset = NULL;
//	hm_wmp_scrollbar* pWMPScrollBar = NULL;
//	hm_wmp_viewbkcontent* pWMPViewBKGND = NULL;
//
//	// innerView
//	getSubKeelObj( ESKM_INNER_VIEW, &pKeelObjInnerView );
//	pKeelObjInnerView->switchWndMsgSource( this );
//	pKeelObjInnerView->setParent( this ); 
//	//
//	pLayoutObj = new hm_layout_obj();
//	ptr_layout_decoder_offset = new hm_layoutdecoder_offset( pLayoutObj );
//	ptr_layout_decoder_offset->m_nOffsetT = 0;
//	ptr_layout_decoder_offset->m_nOffsetL = 0;
//	ptr_layout_decoder_offset->m_nOffsetR = -20;
//	ptr_layout_decoder_offset->m_nOffsetB = -20;
//	pLayoutObj->setLayoutDecoder( ptr_layout_decoder_offset );
//	pKeelObjInnerView->setLayoutObj( pLayoutObj );
//	//
//	//pWMPViewBKGND = WMPFACTORY_INSTANCE->createObj< hm_wmp_viewbkcontent >( initIdSet.wmpIdViewContent, 500, 500 );
//	pWMPViewBKGND = WMPFACTORY_INSTANCE->createObj< hm_wmp_viewbkcontent >( initIdSet.wmpIdViewContent );
//	setContentHeight( 500 );
//	setContentWidth( 500 );
//
//	pKeelObjInnerView->pushbackWMP( initIdSet.wmpIdViewContent );
//	pKeelObjInnerView->Register( pWMPViewBKGND, HMKEELOBJEVENT_DRAWSELF );
//	//
//	this->Register( pWMPViewBKGND, HM_EVENT_MOVE_VIEWCONTENT );
//	pWMPViewBKGND->Register( this, HM_EVENT_MOUSEWHELL );
//	m_pWMPViewBKGND = pWMPViewBKGND;
//
//	// scrollbarV
//	getSubKeelObj( ESKM_SCROLLBAR_V, &pKeelObjScrollBarV );
//	pKeelObjScrollBarV->switchWndMsgSource( this );
//	pKeelObjScrollBarV->setParent( this );
//	//
//	pLayoutObj = new hm_layout_obj();
//	ptr_layout_decoder_dock = new hm_layoutdecoder_dock( pLayoutObj );
//	ptr_layout_decoder_dock->m_space1 = 0;
//	ptr_layout_decoder_dock->m_space2 = 0;
//	ptr_layout_decoder_dock->m_space3 = 20;
//	ptr_layout_decoder_dock->m_thickness = 20;
//	ptr_layout_decoder_dock->m_eDockType = hm_layoutdecoder_dock::DOCK_RIGHT;
//	pLayoutObj->setLayoutDecoder( ptr_layout_decoder_dock );
//	pKeelObjScrollBarV->setLayoutObj( pLayoutObj );
//	//
//	pWMPScrollBar = WMPFACTORY_INSTANCE->createObj< hm_wmp_scrollbar, hm_wmp_scrollbar::ENUMDIRECTIONTYPE >( initIdSet.wmpIdScrollBarV, hm_wmp_scrollbar::T2B_TYPE );
//	pKeelObjScrollBarV->pushbackWMP( initIdSet.wmpIdScrollBarV );
//	pKeelObjScrollBarV->Register( pWMPScrollBar, HMKEELOBJEVENT_DRAWSELF ); 
//	//
//	pWMPScrollBar->Register( this, HM_EVENT_TRACKTHUMB_MOVED );
//	m_pWMPScrollBarV = pWMPScrollBar;
//
//	// scrollbarH
//	getSubKeelObj( ESKM_SCROLLBAR_H, &pKeelObjScrollBarH );
//	pKeelObjScrollBarH->switchWndMsgSource( this );
//	pKeelObjScrollBarH->setParent( this );
//	//
//	pLayoutObj = new hm_layout_obj();
//	ptr_layout_decoder_dock = new hm_layoutdecoder_dock( pLayoutObj );
//	ptr_layout_decoder_dock->m_space1 = 0;
//	ptr_layout_decoder_dock->m_space2 = 0;
//	ptr_layout_decoder_dock->m_space3 = 20;
//	ptr_layout_decoder_dock->m_thickness = 20;
//	ptr_layout_decoder_dock->m_eDockType = hm_layoutdecoder_dock::DOCK_BOTTOM;
//	pLayoutObj->setLayoutDecoder( ptr_layout_decoder_dock );
//	pKeelObjScrollBarH->setLayoutObj( pLayoutObj );
//	//
//	pWMPScrollBar = WMPFACTORY_INSTANCE->createObj< hm_wmp_scrollbar, hm_wmp_scrollbar::ENUMDIRECTIONTYPE >( initIdSet.wmpIdScrollBarH, hm_wmp_scrollbar::L2R_TYPE );
//	pKeelObjScrollBarH->pushbackWMP( initIdSet.wmpIdScrollBarH );
//	pKeelObjScrollBarH->Register( pWMPScrollBar, HMKEELOBJEVENT_DRAWSELF ); 
//	//
//	pWMPScrollBar->Register( this, HM_EVENT_TRACKTHUMB_MOVED );
//	m_pWMPScrollBarH = pWMPScrollBar;
//
//		
//	
//}
//
//void hm_keelctrl_scrollview::_uninit() {
//    hm_keel_obj* pKeelObj = NULL;
//
//	getSubKeelObj( ESKM_SCROLLBAR_V, &pKeelObj );
//	pKeelObj->switchWndMsgSource( NULL );
//	pKeelObj->setParent( NULL );
//
//	getSubKeelObj( ESKM_SCROLLBAR_H, &pKeelObj );
//	pKeelObj->switchWndMsgSource( NULL );
//	pKeelObj->setParent( NULL );
//
//	getSubKeelObj( ESKM_INNER_VIEW, &pKeelObj );
//	pKeelObj->switchWndMsgSource( NULL );
//	pKeelObj->setParent( NULL );
//
//
//}
//
//void hm_keelctrl_scrollview::update( void* pSubject, UINT idEvent, long pEventParam, long pEventParam2, BOOL* pbContinue ) {
//    switch ( idEvent ) 
//	{
//	case HMKEELOBJEVENT_DRAWSUBOBJS:
//		{
//			HDC hDC = ( HDC )pEventParam;
//			HWND hWndCanvas = (HWND)pEventParam2;
//			//
//			m_hWndCanvas = hWndCanvas;
//			// 
//			// hm_keelctrl_base::update() will helper me do this job, now, we just need save hWndCanvas.
//		}
//		break;
//	case cmn::ID_EVENT_POSCHANGED:
//		{
//			SIZE sizeCanvas;
//			hm_layout_obj* pLayoutObj = NULL;
//		
//			memset( &sizeCanvas, 0, sizeof( SIZE ) );
//			// calc content visible rect
//			pLayoutObj = getKeelObjViewContent()->getLayoutObj();
//			sizeCanvas.cx = pLayoutObj->m_rect.right - pLayoutObj->m_rect.left;
//			sizeCanvas.cy = pLayoutObj->m_rect.bottom - pLayoutObj->m_rect.top;
//			// do calc content visible rectangle.
//			calcContentVisibleRect( sizeCanvas );
//			
//			// update scrollbar position
//			updateScrollBarPos();
//		}
//		break;
//	case HMKEELOBJEVENT_LAYOUTOBJ_CHANGED:
//		{
//			hm_layout_obj* pLayoutObjNew = (hm_layout_obj*)pEventParam;
//			hm_layout_obj* pLayoutObjOld = (hm_layout_obj*)pEventParam2;
//			hm_keel_obj* pKeelObjScrollBarV = NULL;
//			hm_keel_obj* pKeelObjScrollBarH = NULL;
//			hm_keel_obj* pKeelObjInnerView = NULL;
//			hm_layout_obj* pLayoutObj = NULL;
//			hm_layoutdecoder_i* pLayoutDecoder = NULL;
//			
//			//
//			getSubKeelObj( ESKM_SCROLLBAR_V, &pKeelObjScrollBarV );
//			pLayoutObj = pKeelObjScrollBarV->getLayoutObj();
//			pLayoutObj->setCoordinateSystem( pLayoutObjNew->getCoordinateSystem() );
//			pLayoutDecoder = pLayoutObj->getLayoutDecoder();
//			pLayoutDecoder->setLayoutRefObj( pLayoutObjNew );
// 
//			//
//			getSubKeelObj( ESKM_SCROLLBAR_H, &pKeelObjScrollBarH );
//			pLayoutObj = pKeelObjScrollBarH->getLayoutObj();
//			pLayoutObj->setCoordinateSystem( pLayoutObjNew->getCoordinateSystem() );
//			pLayoutDecoder = pLayoutObj->getLayoutDecoder();
//			pLayoutDecoder->setLayoutRefObj( pLayoutObjNew );
//
//			//
//			getSubKeelObj( ESKM_INNER_VIEW, &pKeelObjInnerView );
//			pLayoutObj = pKeelObjInnerView->getLayoutObj();
//			pLayoutObj->setCoordinateSystem( pLayoutObjNew->getCoordinateSystem() );
//			pLayoutDecoder = pLayoutObj->getLayoutDecoder();
//			pLayoutDecoder->setLayoutRefObj( pLayoutObjNew );
//
//		}
//		break;
//	case HM_EVENT_TRACKTHUMB_MOVED:
//		{
//			HETMPARAM* pHETMParam = NULL;
//			HEVMPARAM hevmParam;
//			hm_layout_obj* pLayoutObjInnerView = NULL;
//			int nInnerViewCanvasWidth;
//			int nInnerViewCanvasHeight;
//			int nInnerViewContentWidth;
//			int nInnerViewContentHeight;
//			int nPosMax = 0;
//			int nPosCur = 0;
//			int nValMin = 0;
//			int nValMax = 0;
//			int nValCur = 0;
//			hm_keel_obj* pViewContentKeelObj = NULL;
//			HDC hDCCanvas;
//			HDC hDCMem;
//			HBITMAP hBitmap;
//			HBITMAP hBitmapOld;
//			SIZE sizeCanvas;
//			RECT rcCanvas;
//		
//			pViewContentKeelObj = getKeelObjViewContent();
//			if ( !pViewContentKeelObj ) return;
//			pLayoutObjInnerView = pViewContentKeelObj->getLayoutObj();
//			if ( !pLayoutObjInnerView ) return;
//			nInnerViewCanvasWidth = pLayoutObjInnerView->m_rect.right - pLayoutObjInnerView->m_rect.left;
//			nInnerViewCanvasHeight = pLayoutObjInnerView->m_rect.bottom - pLayoutObjInnerView->m_rect.top;
//			nInnerViewContentWidth = getContentWidth();
//			nInnerViewContentHeight = getContentHeight();
//			//nInnerViewContentWidth = m_uContentWidth;
//			//nInnerViewContentHeight = m_uContentHeight;
//			if ( !pLayoutObjInnerView->mapPosition( m_hWndCanvas, coordinate_system_hwnd::CSH_CLIENT_TYPE, rcCanvas ) )
//				return;
//
//			//
//			pHETMParam = ( HETMPARAM* )pEventParam;
//			if ( !pHETMParam || !pHETMParam->m_pWMPScrollbar ) return;
//
//			// horizontal
//			m_pWMPScrollBarH->getValRange( nValMin, nValMax );
//			m_pWMPScrollBarH->getCurValue( nValCur );
//			nPosMax = nValMax - nValMin;
//			nPosCur = nValCur - nValMin;
//			hevmParam.m_horizontal.m_nContentPosStart = nPosMax == 0 
//											? 0
//											: ( ( nInnerViewContentWidth - nInnerViewCanvasWidth ) < 0 
//												? 0 
//												: ( ( nInnerViewContentWidth - nInnerViewCanvasWidth ) * nPosCur / nPosMax ) );
//			hevmParam.m_horizontal.m_nContentPosEnd = hevmParam.m_horizontal.m_nContentPosStart + min( nInnerViewContentWidth, nInnerViewCanvasWidth );
//			// vertical
//			m_pWMPScrollBarV->getValRange( nValMin, nValMax );
//			m_pWMPScrollBarV->getCurValue( nValCur );
//			nPosMax = nValMax - nValMin;
//			nPosCur = nValCur - nValMin;
//			hevmParam.m_vertical.m_nContentPosStart = nPosMax == 0 
//												? 0
//												: ( ( nInnerViewContentHeight - nInnerViewCanvasHeight ) < 0
//													? 0
//													: ( ( nInnerViewContentHeight - nInnerViewCanvasHeight ) * nPosCur / nPosMax ) );
//			hevmParam.m_vertical.m_nContentPosEnd = hevmParam.m_vertical.m_nContentPosStart + min( nInnerViewContentHeight, nInnerViewCanvasHeight );			
//			//
//			m_rcContentVisible.left = hevmParam.m_horizontal.m_nContentPosStart;
//			m_rcContentVisible.right = hevmParam.m_horizontal.m_nContentPosEnd;
//			m_rcContentVisible.top = hevmParam.m_vertical.m_nContentPosStart;
//			m_rcContentVisible.bottom = hevmParam.m_vertical.m_nContentPosEnd;
//			
//			// prepare dc
//			sizeCanvas.cx = nInnerViewCanvasWidth;
//			sizeCanvas.cy = nInnerViewCanvasHeight;
//			hDCCanvas = ::GetDC( m_hWndCanvas );
//			hDCMem = ::CreateCompatibleDC( hDCCanvas );
//			hBitmap = ::CreateCompatibleBitmap( hDCCanvas, sizeCanvas.cx, sizeCanvas.cy );
//			hBitmapOld = (HBITMAP)::SelectObject( hDCMem, hBitmap );
//			
//			hevmParam.m_pViewContentKeelObj = pViewContentKeelObj;
//			hevmParam.m_hWndCanvas = m_hWndCanvas;
//			hevmParam.m_hDCMem = hDCMem;
//			hevmParam.m_sizeCanvas = sizeCanvas;
//			Notify( HM_EVENT_MOVE_VIEWCONTENT, (long)&hevmParam );
//			//
//			::BitBlt( hDCCanvas, rcCanvas.left, rcCanvas.top, ( rcCanvas.right - rcCanvas.left ), ( rcCanvas.bottom - rcCanvas.top ), hDCMem, 0, 0, SRCCOPY );
//			
//			// release resource.
//			::SelectObject( hDCMem, hBitmapOld );
//			::DeleteObject( hBitmap );
//			::DeleteDC( hDCMem );
//			::ReleaseDC( m_hWndCanvas, hDCCanvas );
//			
//			if ( pHETMParam->m_pWMPScrollbar == m_pWMPScrollBarH ) {
//				// horizontal
//				::OutputDebugString( _T("move scrollbar H\n") );
//			} else if ( pHETMParam->m_pWMPScrollbar == m_pWMPScrollBarV ) {
//				// vertical
//				::OutputDebugString( _T("move scrollbar V\n") );
//			}
//		}
//		break;
//	case HM_EVENT_MOUSEWHELL:
//		{
//			TCHAR szMsg[100];
//			int nDistance;
//			int nValMin;
//			int nValMax;
//			int nValCur;
//
//			//
//			nDistance = (int)pEventParam;
//			if ( nDistance == 0 ) break;
//			//_stprintf_s( szMsg, _T("nDistance:%d\n"), nDistance );
//			//::OutputDebugString( szMsg );
//			
//			//adjust 
//			if ( nDistance < 0 ) {
//				nDistance = -( min( abs( nDistance ), abs( m_rcContentVisible.top ) ) );
//			} else if ( nDistance > 0 ) {
//				nDistance = min( nDistance, ( m_uContentHeight - m_rcContentVisible.bottom ) );
//			}
//			_stprintf_s( szMsg, _T("real nDistance:%d\n"), nDistance );
//			//::OutputDebugString( szMsg );
//			m_rcContentVisible.top += nDistance;
//			m_rcContentVisible.bottom += nDistance;
//			
//			// adjust 
//			m_pWMPScrollBarV->getValRange( nValMin, nValMax );
//			nValCur = nValMin + (nValMax - nValMin)*( m_rcContentVisible.top )/( m_uContentHeight - ( m_rcContentVisible.bottom - m_rcContentVisible.top ) );
//			m_pWMPScrollBarV->setCurValue( nValCur );
//			// need more code to calc thrunk button.
//			m_pWMPScrollBarV->drawSelf();
//
//			//
//			// prepare dc
//			SIZE sizeCanvas;
//			hm_keel_obj* pViewContentKeelObj = NULL;
//			hm_layout_obj* pLayoutObjInnerView = NULL;
//			int nInnerViewCanvasWidth;
//			int nInnerViewCanvasHeight;
//			HDC hDCCanvas;
//			HDC hDCMem;
//			HBITMAP hBitmap;
//			HBITMAP hBitmapOld;
//			HEVMPARAM hevmParam;
//			RECT rcCanvas;
//
//			pViewContentKeelObj = getKeelObjViewContent();
//			if ( !pViewContentKeelObj ) return;
//			pLayoutObjInnerView = pViewContentKeelObj->getLayoutObj();
//			if ( !pLayoutObjInnerView ) return;
//			if ( !pLayoutObjInnerView->mapPosition( m_hWndCanvas, coordinate_system_hwnd::CSH_CLIENT_TYPE, rcCanvas ) )
//				return;
//			nInnerViewCanvasWidth = pLayoutObjInnerView->m_rect.right - pLayoutObjInnerView->m_rect.left;
//			nInnerViewCanvasHeight = pLayoutObjInnerView->m_rect.bottom - pLayoutObjInnerView->m_rect.top;
//			sizeCanvas.cx = nInnerViewCanvasWidth;
//			sizeCanvas.cy = nInnerViewCanvasHeight;
//			hDCCanvas = ::GetDC( m_hWndCanvas );
//			hDCMem = ::CreateCompatibleDC( hDCCanvas );
//			hBitmap = ::CreateCompatibleBitmap( hDCCanvas, sizeCanvas.cx, sizeCanvas.cy );
//			hBitmapOld = (HBITMAP)::SelectObject( hDCMem, hBitmap );
//			
//			hevmParam.m_pViewContentKeelObj = pViewContentKeelObj;
//			hevmParam.m_hWndCanvas = m_hWndCanvas;
//			hevmParam.m_hDCMem = hDCMem;
//			hevmParam.m_sizeCanvas = sizeCanvas;
//			Notify( HM_EVENT_MOVE_VIEWCONTENT, (long)&hevmParam );
//			//
//			::BitBlt( hDCCanvas, rcCanvas.left, rcCanvas.top, ( rcCanvas.right - rcCanvas.left ), ( rcCanvas.bottom - rcCanvas.top ), hDCMem, 0, 0, SRCCOPY );
//			
//			// release resource.
//			::SelectObject( hDCMem, hBitmapOld );
//			::DeleteObject( hBitmap );
//			::DeleteDC( hDCMem );
//			::ReleaseDC( m_hWndCanvas, hDCCanvas );
//		}
//		break;
//	default:
//		break;
//	}
//		
//	hm_keelctrl_base::update( pSubject, idEvent, pEventParam, pEventParam2, pbContinue );
//}
//
//void hm_keelctrl_scrollview::updateScrollBarPos() {
//	int nInnerViewContentWidth;
//	int nInnerViewContentHeight;
//	int nContentVisibleWidth;
//	int nContentVisibleHeight;
//	int nValMin;
//	int nValMax;
//	int nValCur;
//	unsigned int uTotalLen;
//	unsigned int uTrackThumbLen;
//	RECT rcContentVisible;
//
//	// adjust scrollbar position.
//	getContentVisibleRect( rcContentVisible );
//	nContentVisibleWidth = ( rcContentVisible.right - rcContentVisible.left );
//	nContentVisibleHeight = ( rcContentVisible.bottom - rcContentVisible.top );
//	nInnerViewContentWidth = getContentWidth();
//	nInnerViewContentHeight = getContentHeight();
//	// 
//	m_pWMPScrollBarH->getValRange( nValMin, nValMax );
//	if ( ( nInnerViewContentWidth - nContentVisibleWidth ) <= 0 )
//		nValCur = nValMin;
//	else
//		nValCur = nValMin + ( nValMax - nValMin ) * rcContentVisible.left / ( nInnerViewContentWidth - nContentVisibleWidth );
//	m_pWMPScrollBarH->setCurValue( nValCur );
//	//
//	m_pWMPScrollBarV->getValRange( nValMin, nValMax );
//	if ( ( nInnerViewContentHeight - nContentVisibleHeight ) <= 0 )
//		nValCur = nValMin;
//	else
//		nValCur = nValMin + ( nValMax - nValMin ) * rcContentVisible.top / ( nInnerViewContentHeight - nContentVisibleHeight );
//	m_pWMPScrollBarV->setCurValue( nValCur );
//	
//	// adjust trackthumb length.
//	// scroll bar H
//	uTotalLen = getKeelObjScrollBarH()->getLayoutObj()->m_rect.right - getKeelObjScrollBarH()->getLayoutObj()->m_rect.left;
//	uTotalLen -= m_pWMPScrollBarH->getStartThumbPosDecoder()->m_space1 + m_pWMPScrollBarH->getStartThumbPosDecoder()->m_nThickness;
//	uTotalLen -= m_pWMPScrollBarH->getEndThumbPosDecoder()->m_space1 + m_pWMPScrollBarH->getEndThumbPosDecoder()->m_nThickness;
//	uTrackThumbLen = nInnerViewContentWidth ? max( (uTotalLen * nContentVisibleWidth / nInnerViewContentWidth), 20 ) : 20;
//	m_pWMPScrollBarH->setTrackThumbLen( uTrackThumbLen );
//	// scroll bar V
//	uTotalLen = getKeelObjScrollBarV()->getLayoutObj()->m_rect.bottom - getKeelObjScrollBarV()->getLayoutObj()->m_rect.top;
//	uTotalLen -= m_pWMPScrollBarV->getStartThumbPosDecoder()->m_space1 + m_pWMPScrollBarV->getStartThumbPosDecoder()->m_nThickness;
//	uTotalLen -= m_pWMPScrollBarV->getEndThumbPosDecoder()->m_space1 + m_pWMPScrollBarV->getEndThumbPosDecoder()->m_nThickness;
//	uTrackThumbLen = nInnerViewContentHeight ? max( (uTotalLen * nContentVisibleHeight / nInnerViewContentHeight), 20 ) : 20;
//	m_pWMPScrollBarV->setTrackThumbLen( uTrackThumbLen );
//}
//
//void hm_keelctrl_scrollview::calcContentVisibleRect( const SIZE& sizeCanvas ) {
//	RECT rcContentVisibleOld;
//	unsigned int uPosCVL;
//	unsigned int uPosCVT;
//
//	if ( isContentVisibleRectDirty() ) {
//		uPosCVL = 0;
//		uPosCVT = 0;
//	} else {
//		rcContentVisibleOld = m_rcContentVisible;
//		// calc uPosCVL
//		if ( rcContentVisibleOld.left + sizeCanvas.cx < m_uContentWidth )
//			uPosCVL = rcContentVisibleOld.left;
//		else {
//			if ( sizeCanvas.cx < m_uContentWidth )
//				uPosCVL = m_uContentWidth - sizeCanvas.cx;
//			else
//				uPosCVL = 0;
//		}
//		// calc uPosCVT
//		if ( rcContentVisibleOld.top + sizeCanvas.cy < m_uContentHeight )
//			uPosCVT = rcContentVisibleOld.top;
//		else {
//			if ( sizeCanvas.cy < m_uContentHeight )
//				uPosCVT = m_uContentHeight - sizeCanvas.cy;
//			else
//				uPosCVT = 0;
//		}
//	}
//	// calc m_rcContentVisible
//	m_rcContentVisible.left = m_uContentWidth < sizeCanvas.cx 
//						? 0
//						: ( ( uPosCVL + sizeCanvas.cx ) > m_uContentWidth
//							? ( m_uContentWidth - sizeCanvas.cx )
//							: uPosCVL );
//	m_rcContentVisible.right = m_rcContentVisible.left + min( m_uContentWidth, sizeCanvas.cx );
//	m_rcContentVisible.top = m_uContentHeight < sizeCanvas.cy
//						? 0
//						: ( ( uPosCVT + sizeCanvas.cy ) > m_uContentHeight
//							? ( m_uContentHeight - sizeCanvas.cy )
//							: uPosCVT );
//	m_rcContentVisible.bottom = m_rcContentVisible.top + min( m_uContentHeight, sizeCanvas.cy );
//	
//	// cancel FLAG_CONTENTVISIBLE_DIRTY flag
//	m_uFlag &= ~FLAG_CONTENTVISIBLE_DIRTY; 
//}

