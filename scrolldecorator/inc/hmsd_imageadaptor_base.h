#ifndef __HMSD_IMAGEADAPTOR_BASE_H__
#define __HMSD_IMAGEADAPTOR_BASE_H__
#include "hmsd_export_defs.h"
//
class hmsd_scrollbar;
//
class HMSD_API hmsd_imageadaptor_base {
public:
	typedef enum EBTNSTATETYPE { 
		EBTNSTATE_NOR = 0,
		EBTNSTATE_HOV,
		EBTNSTATE_PRE
	};

public:
	hmsd_imageadaptor_base();
	virtual ~hmsd_imageadaptor_base();

public:
	virtual void DrawScrollBar( HDC hDC, hmsd_scrollbar* pScrollBar ) = 0;	
	virtual BOOL CalcWidthRaw( unsigned int& uWidthRaw ) = 0;
	virtual BOOL CalcBtnStartThick( unsigned int& uThick ) = 0;
	virtual BOOL CalcBtnEndThick( unsigned int& uThick ) = 0;

protected:
	void _GetBtnStartRect( RECT& rcBtnStart, hmsd_scrollbar* pScrollBar );
	void _GetBtnEndRect( RECT& rcBtnEnd, hmsd_scrollbar* pScrollBar );
	BOOL _GetBtnThumbRect( RECT& rcBtnThumb, hmsd_scrollbar* pScrollBar );
	void _GetBkRect( RECT& rcBk, hmsd_scrollbar* pScrollBar );
	EBTNSTATETYPE _GetBtnStartState( hmsd_scrollbar* pScrollBar );
	EBTNSTATETYPE _GetBtnEndState( hmsd_scrollbar* pScrollBar );
	EBTNSTATETYPE _GetBtnThumbState( hmsd_scrollbar* pScrollBar );

};

#endif //__HMSD_IMAGEADAPTOR_BASE_H__