#ifndef __HM_PS_PAINT_LAYER_PIC_H__
#define __HM_PS_PAINT_LAYER_PIC_H__
#include "hm_ps_paint_layer_i.h"

class hm_ps_paint_layer_pic : public hm_ps_paint_layer_i
{
public:
	hm_ps_paint_layer_pic();
	hm_ps_paint_layer_pic( hm_ps_pl_id_type id );
	virtual ~hm_ps_paint_layer_pic();

public:
	virtual void doDraw( HDC hDC, const RECT& rcCanvas, const RECT& rcUpdate );
	

};


#endif //__PAINT_LAYER_PIC_H__