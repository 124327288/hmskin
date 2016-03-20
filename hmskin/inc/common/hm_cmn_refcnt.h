#ifndef __HM_CMN_REFCNT_H__
#define __HM_CMN_REFCNT_H__
#include "win\hm_export_defs.h"
#include <map>

class HMLIB_API hm_cmn_refcnt{
public:
	typedef unsigned int refres_id_type;
	typedef int refcount_type;
	typedef std::map< refres_id_type, refcount_type > map_rrid2refcount_type;

public:
	hm_cmn_refcnt();
	virtual ~hm_cmn_refcnt();

public:
	void addResRefCnt( refres_id_type rrId );
	void releaseResRefCnt( refres_id_type rrId );

protected:
	virtual void doFirstRef( refres_id_type rrId ) = 0;
	virtual void doFinalRelase( refres_id_type rrId ) = 0;

protected:
	void _addRefCount( refres_id_type rrId );
	void _releaseRefCount( refres_id_type rrId );

private:
	bool _hasEventId( refres_id_type rrId );
private:
#pragma warning(push)
#pragma warning(disable:4251)
	map_rrid2refcount_type m_mapEventId2RefCount;
#pragma warning(pop)
};



#endif //__HM_CMN_REFCNT_H__