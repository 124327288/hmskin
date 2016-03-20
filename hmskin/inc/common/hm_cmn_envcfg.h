#ifndef __HM_CMN_ENVCFG_H__
#define __HM_CMN_ENVCFG_H__

#define CMN_NAMESPACE_START namespace cmn{
#define CMN_NAMESPACE_END }
#define USING_NAMESPACE_CMN using namespace cmn;

CMN_NAMESPACE_START

//事件ID定义 begin////////////////////////////////////////////////////////////////////////
const UINT ID_QEVENT_UILIB_BASE = WM_USER + 200;

//位置Layout位置改变的通知 
const UINT ID_EVENT_POSCHANGED = ID_QEVENT_UILIB_BASE + 1;



CMN_NAMESPACE_END
#endif //__HM_CMN_ENVCFG_H__