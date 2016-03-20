#ifndef __HMSD_IMAGEADAPTOR_DEFAULT_H__
#define __HMSD_IMAGEADAPTOR_DEFAULT_H__
#include "hmsd_imageadaptor_base.h"
#include <string>
#include "tchar.h"
#include "hmsd_export_defs.h"
//
namespace Gdiplus {
	class Image;
};
//
class HMSD_API hmsd_imageadaptor_default : public hmsd_imageadaptor_base {
public:
	typedef std::basic_string< TCHAR > string_type;

public:
	hmsd_imageadaptor_default( const string_type& strRawImagePath );
	virtual ~hmsd_imageadaptor_default();

	// interface of hmsd_imageadaptor_base
public:
	virtual void DrawScrollBar( HDC hDC, hmsd_scrollbar* pScrollBar );
	virtual BOOL CalcWidthRaw( unsigned int& uWidthRaw );
	virtual BOOL CalcBtnStartThick( unsigned int& uThick );
	virtual BOOL CalcBtnEndThick( unsigned int& uThick );
	
private:
	void _Init();
	void _UnInit();
	void _GetRawImagePartBackground( RECT& rcDest );
	void _GetRawImagePartBtnStart( RECT& rcDest, hmsd_scrollbar* pScrollBar );
	void _GetRawImagePartBtnEnd( RECT& rcDest, hmsd_scrollbar* pScrollBar );
	void _GetRawImagePartBtnThumb( RECT& rcDest, hmsd_scrollbar* pScrollBar );
	void _GetRawImagePartBtnStartNor( RECT& rcDest );
	void _GetRawImagePartBtnStartHov( RECT& rcDest );
	void _GetRawImagePartBtnStartPre( RECT& rcDest );
	void _GetRawImagePartBtnEndNor( RECT& rcDest );
	void _GetRawImagePartBtnEndHov( RECT& rcDest );
	void _GetRawImagePartBtnEndPre( RECT& rcDest );
	void _GetRawImagePartBtnThumbNor( RECT& rcDest );
	void _GetRawImagePartBtnThumbHov( RECT& rcDest );
	void _GetRawImagePartBtnThumbPre( RECT& rcDest );

private:
#pragma warning(push)
#pragma warning(disable:4251)
	string_type m_strRawImagePath;
#pragma warning(pop)
	Gdiplus::Image* m_pImage;
	SIZE m_sizeImage;
};


#endif //__HMSD_IMAGEADAPTOR_DEFAULT_H__