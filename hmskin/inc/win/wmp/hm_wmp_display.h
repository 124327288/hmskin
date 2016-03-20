#ifndef __hm_wmp_display_H__
#define __hm_wmp_display_H__
#include "win\paint_system\hm_ps_drawtool_i.h"
#include "win\resource_system\hm_rs_uires_i.h"
#include "win\wmp\hm_wndmsgprocessor_i.h"
#include "win\frame\hm_pos_decoders.h"
#include "win\hm_export_defs.h"
#include <map>
#include <stdexcept>

///////////////////////////////////////////////////////////////
struct HMLIB_API hm_showobj {
	hm_showobj( hm_rs_uires_i* pUIRes = NULL, hm_pos_decoder_i* pPosDecoder = NULL );
	~hm_showobj();

	//
	void show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool );
	bool loadRes( hm_ps_drawtool_i* pDrawTool );
	bool unloadRes( hm_ps_drawtool_i* pDrawTool );

	hm_rs_uires_i* m_pUIRes;
	hm_pos_decoder_i* m_pPosDecoder;
};

///////////////////////////////////////////////////////////////
class HMLIB_API hm_districtobj {
public:
	typedef std::deque< hm_showobj* > showobj_container_type;

public:
	hm_districtobj( hm_pos_decoder_i* pPosDecoder = NULL );
	~hm_districtobj();
	
public:
	//
	bool pushBackShowObj( hm_showobj* pShowObj );
	//
	bool pushFrontShowObj( hm_showobj* pShowObj );
	//
	unsigned int getShowObjCount() { return m_containerShowObjs.size(); };
	//
	hm_showobj* getShowObj( unsigned int uIndex );
	//
	void show( HDC hDC, const RECT& rcCanvas, hm_ps_drawtool_i* pDrawTool, void* pContext = NULL );
	//
	void getDistrictRect( const RECT& rcCanvas, RECT&  );
	//
	bool loadRes( hm_ps_drawtool_i* pDrawTool );
	//
	bool unloadRes( hm_ps_drawtool_i* pDrawTool );
	//
	hm_pos_decoder_i* getPosDecoder() { return m_pPosDecoder; }
	//
	void setPosDecoder( hm_pos_decoder_i* pPosDecoder ) { m_pPosDecoder = pPosDecoder; }

private:
	void _clearAllShowObj();
	
private:
#pragma warning(push)
#pragma warning(disable:4251)
	showobj_container_type m_containerShowObjs;
#pragma warning(pop)
	hm_pos_decoder_i* m_pPosDecoder;
};

///////////////////////////////////////////////////////////////
class HMLIB_API hm_wmp_display : public hm_wndmsgprocessor_i {
public:
	typedef int district_id_type;
	typedef std::map< district_id_type, hm_districtobj* > map_id2district_type;
	typedef std::deque< district_id_type > district_id_container_type;
public:
	hm_wmp_display( hmskin_event_listener_base* pEventListener = NULL );
	virtual ~hm_wmp_display();

public:
	void getAllDistrictId( district_id_container_type& containerIds );

	// interface
protected:
	virtual void _createDistrictObjs() = 0;
private:
	virtual void _getAllDistrictId( district_id_container_type& containerIds ) = 0;
	
public:
	void setDrawTool( hm_ps_drawtool_i* pDrawTool );
	bool hasDrawTool() const { return m_pDrawTool!=NULL; }
	bool getDistrictObj( district_id_type idDistrict, hm_districtobj** ppDistrictObj );

protected:
	bool _setDistrictObj( district_id_type idDistrict, hm_districtobj* pDistrictObj );
	bool _hasDistrictObj( district_id_type idDistrict );
	bool _getDistrictObj( district_id_type idDistrict, hm_districtobj** ppDistrictObj );
	bool _clearAllDistrictObjs();
	
protected:
	hm_ps_drawtool_i* m_pDrawTool;
#pragma warning(push)
#pragma warning(disable:4251)
	map_id2district_type m_mapId2District;
#pragma warning(pop)
};


#endif //__hm_wmp_display_H__