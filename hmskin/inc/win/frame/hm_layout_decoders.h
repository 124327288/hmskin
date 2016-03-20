
#ifndef __HM_LAYOUT_DECODERS_H__
#define __HM_LAYOUT_DECODERS_H__
#include "win\frame\hm_layout_obj.h"
#include "win\hm_export_defs.h"
//
class HMLIB_API hm_layoutdecoder_clientarea : public hm_layoutdecoder_i
{
public:
	hm_layoutdecoder_clientarea( out_obj_ptr_type pOutObj );
	virtual ~hm_layoutdecoder_clientarea();

	//interface
public:
	virtual void decoderLayout();	

};
//
class HMLIB_API hm_layoutdecoder_wndarea : public hm_layoutdecoder_i
{
public:
	hm_layoutdecoder_wndarea( out_obj_ptr_type pOutObj );
	virtual ~hm_layoutdecoder_wndarea();

	//interface
public:
	virtual void decoderLayout();

};

//////////////////////////////////////////////////////////////////////////
//class hm_layoutdecoder_corner
//
// CORNER_LT:
//		-----------------------------------------
//		|m_pRefObj			|					|
//		|				  m_space2				|
//		|					|					|
//		|			----------------- ---		|
//		|		 	|m_pOutObj		|  |		|
//		|- m_space1-|				| m_height	|
//		|			|				|  |		|
//		|			----------------- ---		|
//		|			|--- m_width ---|			|
//		|										|
//		|										|
//		-----------------------------------------
//
// CORNER_LB:
//		-----------------------------------------
//		|m_pRefObj								|
//		|										|
//		|			|--- m_width ---|			|
//		|			----------------- ---		|
//		|		 	|m_pOutObj		|  |		|
//		|- m_space1-|				| m_height	|
//		|			|				|  |		|
//		|			----------------- ---		|
//		|					|					|
//		|				m_space2				|
//		|					|					|
//		-----------------------------------------
//
// CORNER_RB:
//		-----------------------------------------
//		|m_pRefObj								|
//		|										|
//		|			|--- m_width ---|			|
//		|		---	-----------------			|
//		|		 |	|m_pOutObj		|  			|
//		|	m_height|				|- m_space1-|
//		|		 |	|				|  			|
//		|		---	-----------------			|
//		|					|					|
//		|				m_space2				|
//		|					|					|
//		-----------------------------------------
//
// CORNER_RT:
//		-----------------------------------------
//		|m_pRefObj			|					|
//		|				  m_space1				|
//		|					|					|
//		|		---	-----------------			|
//		|		 |	|m_pOutObj		|			|
//		|	m_height|				|- m_space2-|
//		|		 |	|				|			|
//		|		---	-----------------			|
//		|			|--- m_width ---|			|
//		|										|
//		|										|
//		-----------------------------------------
#define LD_CORNER_INT_CORNERTYPE ( 0 )
#define LD_CORNER_INT_SPACE1 ( 1 )
#define LD_CORNER_INT_SPACE2 ( 2 )
#define LD_CORNER_INT_WIDTH ( 3 )
#define LD_CORNER_INT_HEIGHT ( 4 )
class HMLIB_API hm_layoutdecoder_corner : public hm_layoutdecoder_i
{
	//type define
public:
	typedef enum _ENUMCORNERTYPE{
		CORNER_LT = 0,
		CORNER_LB,
		CORNER_RB,
		CORNER_RT
	} ENUMCORNERTYPE;

public:
	hm_layoutdecoder_corner( out_obj_ptr_type pOutObj );
	virtual ~hm_layoutdecoder_corner();
	
	//interface
public:
	virtual void decoderLayout();

public:
	ENUMCORNERTYPE m_eCornerType;
	int m_space1;
	int m_space2;
	int m_width;
	int m_height;
};
///////////////////////////////////////////////////////////////////////////////
// 
// DOCK_TOP:
//		-----------------------------------------
//		|m_pRefObj			|					|
//		|				  m_space1				|
//		|					|					|
//		|		---	-----------------			|
//		|		 |	|m_pOutObj		|			|
//		|m_thickness|				|- m_space3-|
//		|		 |	|				|			|
//		|		---	-----------------			|
//		|- m_space2-|							|
//		|										|
//		|										|
//		-----------------------------------------
// 
// DOCK_LEFT:
//		-----------------------------------------
//		|m_pRefObj			|					|
//		|				  m_space2				|
//		|					|					|
//		|			-----------------			|
//		|		 	|m_pOutObj		|			|
//		|- m_space1-|				|			|
//		|		 	|				|			|
//		|		---	-----------------			|
//		|		 |	|- m_thickness -|			|
//		|	m_space3							|
//		|		 |								|
//		-----------------------------------------
// 
// DOCK_RIGHT:
//		-----------------------------------------
//		|m_pRefObj			|					|
//		|				  m_space2				|
//		|					|					|
//		|			-----------------			|
//		|		 	|m_pOutObj		|			|
//		|			|				|- m_space1-|
//		|		 	|				|			|
//		|		---	-----------------			|
//		|		 |	|- m_thickness -|			|
//		|	m_space3							|
//		|		 |								|
//		-----------------------------------------
// 
// DOCK_BOTTOM:
//		-----------------------------------------
//		|m_pRefObj								|
//		|				  						|
//		|										|
//		|		---	-----------------			|
//		|		 |	|m_pOutObj		|			|
//		|m_thickness|				|- m_space3-|
//		|		 |	|				|			|
//		|		---	-----------------			|
//		|- m_space2-|		|					|
//		|				m_space1				|
//		|					|					|
//		-----------------------------------------
class HMLIB_API hm_layoutdecoder_dock : public hm_layoutdecoder_i
{
	//type define
public:
	typedef enum _ENUMDOCKTYPE {
		DOCK_TOP = 0,
		DOCK_LEFT,
		DOCK_RIGHT,
		DOCK_BOTTOM
	} ENUMDOCKTYPE;

public:
	hm_layoutdecoder_dock( out_obj_ptr_type pOutObj );
	virtual ~hm_layoutdecoder_dock();

	//interface
public:
	virtual void decoderLayout();

public:
	ENUMDOCKTYPE m_eDockType;
	int m_space1;
	int m_space2;
	int m_space3;
	int m_thickness;
};
///////////////////////////////////////////////////////////////////////////////
// 
//		---------------------------------------------
//		|m_pRefObj			|						|
//		|				 m_nOffsetT					|
//		|					|						|
//		|			-----------------				|
//		|		 	|m_pOutObj		|				|
//		|			|				|-  m_nOffsetR -|
//		|		 	|				|				|
//		|			-----------------				|
//		|-m_nOffsetL-|		|						|
//		|				m_nOffsetB					|
//		|					|						|
//		---------------------------------------------
//
class HMLIB_API hm_layoutdecoder_offset : public hm_layoutdecoder_i
{
public:
	hm_layoutdecoder_offset( out_obj_ptr_type pOutObj );
	virtual ~hm_layoutdecoder_offset();

	//interface
public:
	virtual void decoderLayout();
	
public:
	int m_nOffsetL; 
	int m_nOffsetT;
	int m_nOffsetR;
	int m_nOffsetB;
};

#endif //__HM_LAYOUT_DECODERS_H__