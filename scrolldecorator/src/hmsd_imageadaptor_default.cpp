#include "stdafx.h"
#include "hmsd_imageadaptor_default.h"
#include "funcpack.h"
#include "memfuncpack.h"
#include "atlconv.h"
#include "Gdiplus.h"
#include <assert.h>

hmsd_imageadaptor_default::hmsd_imageadaptor_default( const string_type& strRawImagePath ) 
: m_strRawImagePath( strRawImagePath )
, m_pImage( NULL ) {
	_Init();
}

hmsd_imageadaptor_default::~hmsd_imageadaptor_default() {
	_UnInit();
}

void hmsd_imageadaptor_default::_Init() {
	// create m_pImage.
	if ( m_pImage ) {
		assert( FALSE );
		delete m_pImage;
		m_pImage = NULL;
	}
#ifdef _UNICODE
	USES_CONVERSION;
	m_pImage = new Gdiplus::Image( m_strRawImagePath.c_str(), FALSE );
#else
	USES_CONVERSION;
	m_pImage = new Gdiplus::Image( CT2W( m_strRawImagePath.c_str() ), FALSE );
#endif //_UNICODE
	if ( !m_pImage ) {
		assert( FALSE );
		return;
	}
	m_sizeImage.cx = m_pImage->GetWidth();
	m_sizeImage.cy = m_pImage->GetHeight();
}

void hmsd_imageadaptor_default::_UnInit() {
	if ( m_pImage ) {
		delete m_pImage;
		m_pImage = NULL;
	}
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnStartNor( RECT& rcDest ) {
	rcDest.left = 0;
	rcDest.top = 0;
	rcDest.right = m_sizeImage.cx / 17;
	rcDest.bottom = m_sizeImage.cy / 3;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnStartHov( RECT& rcDest ) {
	rcDest.left = 0;
	rcDest.top = m_sizeImage.cy / 3;
	rcDest.right = m_sizeImage.cx / 17;
	rcDest.bottom = m_sizeImage.cy * 2 / 3;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnStartPre( RECT& rcDest ) {
	rcDest.left = 0;
	rcDest.top = m_sizeImage.cy * 2 / 3;
	rcDest.right = m_sizeImage.cx / 17;
	rcDest.bottom = m_sizeImage.cy;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnEndNor( RECT& rcDest ) {
	rcDest.left = m_sizeImage.cx / 17;
	rcDest.top = 0;
	rcDest.right = m_sizeImage.cx * 2 / 17;
	rcDest.bottom = m_sizeImage.cy / 3;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnEndHov( RECT& rcDest ) {
	rcDest.left = m_sizeImage.cx / 17;
	rcDest.top = m_sizeImage.cy / 3;
	rcDest.right = m_sizeImage.cx * 2 / 17;
	rcDest.bottom = m_sizeImage.cy * 2 / 3;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnEndPre( RECT& rcDest ) {
	rcDest.left = m_sizeImage.cx / 17;
	rcDest.top = m_sizeImage.cy * 2 / 3;
	rcDest.right = m_sizeImage.cx * 2 / 17;
	rcDest.bottom = m_sizeImage.cy;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnThumbNor( RECT& rcDest ) {
	rcDest.left = m_sizeImage.cx * 2 / 17;
	rcDest.top = 0;
	rcDest.right = m_sizeImage.cx * 3 / 17;
	rcDest.bottom = m_sizeImage.cy / 3;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnThumbHov( RECT& rcDest ) {
	rcDest.left = m_sizeImage.cx * 2 / 17;
	rcDest.top = m_sizeImage.cy / 3;
	rcDest.right = m_sizeImage.cx * 3 / 17;
	rcDest.bottom = m_sizeImage.cy * 2 / 3;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnThumbPre( RECT& rcDest ) {
	rcDest.left = m_sizeImage.cx * 2 / 17;
	rcDest.top = m_sizeImage.cy * 2 / 3;
	rcDest.right = m_sizeImage.cx * 3 / 17;
	rcDest.bottom = m_sizeImage.cy;
}

void hmsd_imageadaptor_default::_GetRawImagePartBackground( RECT& rcDest ) {
	rcDest.left = m_sizeImage.cx * 3 / 17;
	rcDest.top = 0;
	rcDest.right = m_sizeImage.cx * 4 / 17;
	rcDest.bottom = m_sizeImage.cy;
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnStart( RECT& rcDest, hmsd_scrollbar* pScrollBar ) {
	hmsd_imageadaptor_base::EBTNSTATETYPE eBtnStateType;

	eBtnStateType = _GetBtnStartState( pScrollBar );
	switch ( eBtnStateType )
	{
	case EBTNSTATE_HOV:
		{
			_GetRawImagePartBtnStartHov( rcDest );
		}
		break;
	case EBTNSTATE_PRE:
		{
			_GetRawImagePartBtnStartPre( rcDest );
		}
		break;
	case EBTNSTATE_NOR:
		{
			_GetRawImagePartBtnStartNor( rcDest );
		}
		break;
	default:
		{
			assert( FALSE );
			_GetRawImagePartBtnStartNor( rcDest );
		}
		break;
	}
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnEnd( RECT& rcDest, hmsd_scrollbar* pScrollBar ) {
	hmsd_imageadaptor_base::EBTNSTATETYPE eBtnStateType;

	eBtnStateType = _GetBtnEndState( pScrollBar );
	switch ( eBtnStateType )
	{
	case EBTNSTATE_HOV:
		{
			_GetRawImagePartBtnEndHov( rcDest );
		}
		break;
	case EBTNSTATE_PRE:
		{
			_GetRawImagePartBtnEndPre( rcDest );
		}
		break;
	case EBTNSTATE_NOR:
		{
			_GetRawImagePartBtnEndNor( rcDest );
		}
		break;
	default:
		{
			assert( FALSE );
			_GetRawImagePartBtnEndNor( rcDest );
		}
		break;
	}
}

void hmsd_imageadaptor_default::_GetRawImagePartBtnThumb( RECT& rcDest, hmsd_scrollbar* pScrollBar ) {
	hmsd_imageadaptor_base::EBTNSTATETYPE eBtnStateType;

	eBtnStateType = _GetBtnThumbState( pScrollBar );
	switch ( eBtnStateType )
	{
	case EBTNSTATE_HOV:
		{
			_GetRawImagePartBtnThumbHov( rcDest );
		}
		break;
	case EBTNSTATE_PRE:
		{
			_GetRawImagePartBtnThumbPre( rcDest );
		}
		break;
	case EBTNSTATE_NOR:
		{
			_GetRawImagePartBtnThumbNor( rcDest );
		}
		break;
	default:
		{
			assert( FALSE );
			_GetRawImagePartBtnThumbNor( rcDest );
		}
		break;
	}
}

BOOL hmsd_imageadaptor_default::CalcWidthRaw( unsigned int& uWidthRaw ) {
	uWidthRaw = m_sizeImage.cx / 17;
	return TRUE;
}

BOOL hmsd_imageadaptor_default::CalcBtnStartThick( unsigned int& uThick ) {
	uThick = m_sizeImage.cy / 3;
	return TRUE;
}

BOOL hmsd_imageadaptor_default::CalcBtnEndThick( unsigned int& uThick ) {
	uThick = m_sizeImage.cy / 3;
	return TRUE;	
}

void hmsd_imageadaptor_default::DrawScrollBar( HDC hDC, hmsd_scrollbar* pScrollBar ) {
	RECT rcBk;
	RECT rcBtnArrow;
	RECT rcBtnThumb;
	RECT rcRawImagePart;
	HDC hMemDC;
	HBITMAP hMemBitmap, hMemBitmapOld;
	Gdiplus::RectF rcfTmp;
	SIZE sizeMemBitmap;
	
	//
	_GetBkRect( rcBk, pScrollBar );
	sizeMemBitmap.cx = rcBk.right - rcBk.left;
	sizeMemBitmap.cy = rcBk.bottom - rcBk.top;
	hMemDC = ::CreateCompatibleDC( hDC );
	CFuncPack fpkDelMemDC( DeleteDC, hMemDC );
	hMemBitmap = ::CreateCompatibleBitmap( hDC, sizeMemBitmap.cx, sizeMemBitmap.cy );
	CFuncPack fpkDelMemBitmap( DeleteObject, hMemBitmap );
	hMemBitmapOld = (HBITMAP)::SelectObject( hMemDC, hMemBitmap );
	CFuncPack fpkSetOldMemBitmapBack( SelectObject, hMemDC, hMemBitmapOld );
	Gdiplus::Graphics graphics( hMemDC );

	// draw background rect.
	_GetBkRect( rcBk, pScrollBar );
	_GetRawImagePartBackground( rcRawImagePart );
	rcfTmp.X = 0;
	rcfTmp.Y = 0;
	rcfTmp.Width = sizeMemBitmap.cx;
	rcfTmp.Height = sizeMemBitmap.cy;
	graphics.DrawImage( m_pImage, rcfTmp, rcRawImagePart.left, rcRawImagePart.top, ( rcRawImagePart.right - rcRawImagePart.left ), ( rcRawImagePart.bottom - rcRawImagePart.top ), Gdiplus::UnitPixel );
	
	// draw btn start rect.
	_GetBtnStartRect( rcBtnArrow, pScrollBar );
	rcfTmp.X = rcBtnArrow.left - rcBk.left;
	rcfTmp.Y = rcBtnArrow.top - rcBk.top;
	rcfTmp.Width = rcBtnArrow.right - rcBtnArrow.left;
	rcfTmp.Height = rcBtnArrow.bottom - rcBtnArrow.top;
	_GetRawImagePartBtnStart( rcRawImagePart, pScrollBar );
	graphics.DrawImage( m_pImage, rcfTmp, rcRawImagePart.left, rcRawImagePart.top, ( rcRawImagePart.right - rcRawImagePart.left ), ( rcRawImagePart.bottom - rcRawImagePart.top ), Gdiplus::UnitPixel );

	// draw btn end rect.
	_GetBtnEndRect( rcBtnArrow, pScrollBar );
	rcfTmp.X = rcBtnArrow.left - rcBk.left;
	rcfTmp.Y = rcBtnArrow.top - rcBk.top;
	rcfTmp.Width = rcBtnArrow.right - rcBtnArrow.left;
	rcfTmp.Height = rcBtnArrow.bottom - rcBtnArrow.top;
	_GetRawImagePartBtnEnd( rcRawImagePart, pScrollBar );
	graphics.DrawImage( m_pImage, rcfTmp, rcRawImagePart.left, rcRawImagePart.top, ( rcRawImagePart.right - rcRawImagePart.left ), ( rcRawImagePart.bottom - rcRawImagePart.top ), Gdiplus::UnitPixel );

	// draw btn thumb rect. // set fix 5 pixel cannot be extrude.
	_GetBtnThumbRect( rcBtnThumb, pScrollBar );
	_GetRawImagePartBtnThumb( rcRawImagePart, pScrollBar );
	rcfTmp.X = rcBtnThumb.left - rcBk.left;
	rcfTmp.Y = rcBtnThumb.top - rcBk.top;
	rcfTmp.Width = rcBtnThumb.right - rcBtnThumb.left;
	rcfTmp.Height = 5;
	graphics.DrawImage( m_pImage, rcfTmp, rcRawImagePart.left, rcRawImagePart.top, ( rcRawImagePart.right - rcRawImagePart.left ), 5, Gdiplus::UnitPixel );
	rcfTmp.X = rcBtnThumb.left - rcBk.left;
	rcfTmp.Y = rcBtnThumb.top - rcBk.top + 5;
	rcfTmp.Width = rcBtnThumb.right - rcBtnThumb.left;
	rcfTmp.Height = (rcBtnThumb.bottom - rcBtnThumb.top - 10);
	graphics.DrawImage( m_pImage, rcfTmp, rcRawImagePart.left, rcRawImagePart.top+5, ( rcRawImagePart.right - rcRawImagePart.left ), ( rcRawImagePart.bottom - rcRawImagePart.top - 10 ), Gdiplus::UnitPixel );
	rcfTmp.X = rcBtnThumb.left - rcBk.left;
	rcfTmp.Y = rcBtnThumb.bottom - rcBk.top - 5;
	rcfTmp.Width = rcBtnThumb.right - rcBtnThumb.left;
	rcfTmp.Height = 5;
	graphics.DrawImage( m_pImage, rcfTmp, rcRawImagePart.left, rcRawImagePart.bottom - 5, ( rcRawImagePart.right - rcRawImagePart.left ), 5, Gdiplus::UnitPixel );
		
	//
	_GetBkRect( rcBk, pScrollBar );
	::BitBlt( hDC, rcBk.left, rcBk.top, sizeMemBitmap.cx, sizeMemBitmap.cy, hMemDC, 0, 0, SRCCOPY );
}
