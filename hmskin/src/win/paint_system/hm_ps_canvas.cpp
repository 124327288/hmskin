#include "stdafx.h"
#include "win\paint_system\hm_ps_canvas.h"
#include "common\FuncPack.h"
#include "common\MemFuncPack.h"
#include <assert.h>
//
#define DEFAULT_MEMBITMAP_WIDTH (200)
#define DEFAULT_MEMBITMAP_HEIGHT (200)
//
hm_ps_canvas::hm_ps_canvas() 
: m_hMemDC( NULL )
, m_hMemBitmap( NULL )
, m_hMemBitmapOld( NULL ) {
	memset( &m_sizeMemBitmap, 0, sizeof(SIZE) );
	_init();
}

hm_ps_canvas::~hm_ps_canvas() {
	_unInit();
}

BOOL hm_ps_canvas::_init() {
	if ( m_hMemDC || m_hMemBitmap ) {
		assert( FALSE );
		return FALSE;
	}
	HWND hWndDeskTop;
	HDC hDCDeskTop;

	hWndDeskTop = ::GetDesktopWindow();
	hDCDeskTop = ::GetDC( hWndDeskTop );
	CFuncPack fpkReleaseDesktopDC( ::ReleaseDC, hWndDeskTop, hDCDeskTop );
	//
	m_hMemDC = ::CreateCompatibleDC( hDCDeskTop );
	if ( !m_hMemDC ) {
		assert( FALSE );
		return FALSE;
	}
	CFuncPack fpkDeleteDC( ::DeleteDC, m_hMemDC );
	//
	m_hMemBitmap = ::CreateCompatibleBitmap( hDCDeskTop, DEFAULT_MEMBITMAP_WIDTH, DEFAULT_MEMBITMAP_HEIGHT );
	if ( !m_hMemBitmap ) {
		assert( FALSE );
		return FALSE;
	}
	CFuncPack fpkDeleteObject( ::DeleteObject, m_hMemBitmap );
	m_sizeMemBitmap.cx = DEFAULT_MEMBITMAP_WIDTH;
	m_sizeMemBitmap.cy = DEFAULT_MEMBITMAP_HEIGHT;
	m_hMemBitmapOld = (HBITMAP)::SelectObject( m_hMemDC, m_hMemBitmap );

	//
	fpkDeleteDC.Cancel();
	fpkDeleteObject.Cancel();
	return TRUE;
}

void hm_ps_canvas::_unInit() {
	HBITMAP hBitmapTmp;
	
	if ( m_hMemBitmap ) {
		assert( m_hMemDC );
		hBitmapTmp = (HBITMAP)::SelectObject( m_hMemDC, m_hMemBitmapOld );
		assert( hBitmapTmp == m_hMemBitmap );
		::DeleteObject( m_hMemBitmap );
		m_hMemBitmap = NULL;
	}
	if ( m_hMemDC ) {
		::DeleteDC( m_hMemDC );
		m_hMemDC = NULL;
	}
}

BOOL hm_ps_canvas::updateMemBitmapSize( SIZE newSize ) {
	return _updateMemBitmapSize( newSize );
}

BOOL hm_ps_canvas::_updateMemBitmapSize( SIZE newSize ) {
	if ( ( newSize.cx < m_sizeMemBitmap.cx ) && ( newSize.cy < m_sizeMemBitmap.cy ) )
		return TRUE;
	HWND hWndDesktop;
	HDC hDCDesktop;
	HDC hMemDCTmp;
	SIZE sizeMemBitmapNew;
	HBITMAP hMemBitmapNew = NULL;
	HBITMAP hMemBitmapTmpOld = NULL;
	HBITMAP hBitmapTmp = NULL;

	if ( newSize.cx > m_sizeMemBitmap.cx )
		newSize.cx += 100;
	if ( newSize.cy > m_sizeMemBitmap.cy )
		newSize.cy += 100;
	sizeMemBitmapNew.cx = max( newSize.cx, m_sizeMemBitmap.cx );
	sizeMemBitmapNew.cy = max( newSize.cy, m_sizeMemBitmap.cy );
	hWndDesktop = ::GetDesktopWindow();
	hDCDesktop = ::GetDC( hWndDesktop );
	if ( !hDCDesktop )
		return FALSE;
	CFuncPack fpkReleaseDesktopDC( ::ReleaseDC, hWndDesktop, hDCDesktop );
	hMemDCTmp = ::CreateCompatibleDC( hDCDesktop );
	if ( !hMemDCTmp )
		return FALSE;
	CFuncPack fpkDeleteMemDCTmp( ::DeleteDC, hMemDCTmp );
	hMemBitmapNew = ::CreateCompatibleBitmap( hDCDesktop, sizeMemBitmapNew.cx, sizeMemBitmapNew.cy );
	if ( !hMemBitmapNew )
		return FALSE;
	CFuncPack fpkDeleteMemBitmapNew( ::DeleteObject, hMemBitmapNew );
	hMemBitmapTmpOld = (HBITMAP)::SelectObject( hMemDCTmp, hMemBitmapNew );
	CFuncPack fpkSelectMemBitmapTmpOldBack( ::SelectObject, hMemDCTmp, hMemBitmapTmpOld );
	//
	if ( !::BitBlt( hMemDCTmp, 0, 0, m_sizeMemBitmap.cx, m_sizeMemBitmap.cy, m_hMemDC, 0, 0, SRCCOPY ) )
		return FALSE;
	//
	fpkSelectMemBitmapTmpOldBack.Do();
	fpkDeleteMemBitmapNew.Cancel();
	hBitmapTmp = (HBITMAP)::SelectObject( m_hMemDC, hMemBitmapNew );
	assert( hBitmapTmp == m_hMemBitmap );
	::DeleteObject( m_hMemBitmap );
	m_hMemBitmap = hMemBitmapNew;
	m_sizeMemBitmap = sizeMemBitmapNew;

	return TRUE;
}