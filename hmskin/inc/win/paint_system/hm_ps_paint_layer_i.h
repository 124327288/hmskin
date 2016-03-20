#ifndef __HM_PS_PAINT_LAYER_I_H__
#define __HM_PS_PAINT_LAYER_I_H__
#include "common\hm_cmn_idobj.h"

typedef unsigned int hm_ps_pl_id_type;
class hm_ps_paint_layer_i : public hm_cmn_idobj_t< hm_ps_pl_id_type >
{
public:
	hm_ps_paint_layer_i();
	hm_ps_paint_layer_i( hm_ps_pl_id_type id );
	virtual ~hm_ps_paint_layer_i(){};

public:
	virtual void doDraw( HDC hDC, const RECT& rcCanvas, const RECT& rcUpdate ) = 0;
	
	
};


#endif //__HM_PS_PAINT_LAYER_I_H__