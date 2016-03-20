#ifndef __HM_PS_CANVAS_H__
#define __HM_PS_CANVAS_H__
#include "win\hm_export_defs.h"

class HMLIB_API hm_ps_canvas {
public:
	hm_ps_canvas();
	virtual ~hm_ps_canvas();

public:
	BOOL updateMemBitmapSize( SIZE newSize );
	HDC GetMemDC() { return m_hMemDC; }

private:
	BOOL _init();
	void _unInit();
	BOOL _updateMemBitmapSize( SIZE newSize );

private:
	HDC m_hMemDC;
	HBITMAP m_hMemBitmap;
	HBITMAP m_hMemBitmapOld;
	SIZE m_sizeMemBitmap;
};

#endif //__HM_PS_CANVAS_H__