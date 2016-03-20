#include "stdafx.h"
#include "win\frame\hm_debug_utils.h"

void hm_util_draw_rect( HDC hDC, const RECT& rcDraw )
{
	//
	::MoveToEx( hDC, rcDraw.left, rcDraw.top, NULL );
	::LineTo( hDC, rcDraw.left, rcDraw.bottom );
	::LineTo( hDC, rcDraw.right, rcDraw.bottom );
	::LineTo( hDC, rcDraw.right, rcDraw.top );
	::LineTo( hDC, rcDraw.left, rcDraw.top );

	//X
	::MoveToEx( hDC, rcDraw.left, rcDraw.top, NULL );
	::LineTo( hDC, rcDraw.right, rcDraw.bottom );
	::MoveToEx( hDC, rcDraw.right, rcDraw.top, NULL );
	::LineTo( hDC, rcDraw.left, rcDraw.bottom );
}

void hm_util_draw_rect( HDC hDC, const RECT& rcDraw, const COLORREF& clr )
{
	HBRUSH hBrush;

	hBrush = CreateSolidBrush( clr );
	
	FillRect( hDC, &rcDraw, hBrush );
	
	DeleteObject( hBrush );
}

void hm_util_draw_line( HDC hDC, int x1, int y1, int x2, int y2, const COLORREF& clr, int nWidth, int fnPenStyle ) {
	HPEN hPen, hPenOld;

	hPen = ::CreatePen( fnPenStyle, nWidth, clr );
	hPenOld = (HPEN)::SelectObject( hDC, hPen );

	::MoveToEx( hDC, x1, y1, NULL );
	::LineTo( hDC, x2, y2 );

	::SelectObject( hDC, hPenOld );
	::DeleteObject( hPen );
}