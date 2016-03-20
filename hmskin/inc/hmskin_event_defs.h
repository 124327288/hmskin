#ifndef __HMSKIN_EVENT_DEFS_H__
#define __HMSKIN_EVENT_DEFS_H__
//////////////////////////////////////////////////////////////////////////
#define HMSKIN_EVENT_BEGIN (0x00000000)
//////////////////////////////////////////////////////////////////////////
// HMSKIN_EVENT_BTN_CLICK
// lParam1 - specify the pointer of keel object.
// lParam2 - none.
#define HMSKIN_EVENT_BTN_CLICK (0x00000001)
//////////////////////////////////////////////////////////////////////////
// HMSKIN_EVENT_CHECKBOX_CLICK
// lParam1 - specify the pointer of keel object.
// lParam2 - none.
#define HMSKIN_EVENT_CHECKBOX_CLICK (0x00000002) 
//////////////////////////////////////////////////////////////////////////
// HMSKIN_EVENT_NCABTN_CLICK
// lParam1 - specify the pointer of keel object.
// lParam2 - none.
#define HMSKIN_EVENT_NCABTN_CLICK (0x00000003)
//////////////////////////////////////////////////////////////////////////
// HMSKIN_EVENT_TABBTN_CLICK
// lParam1 - specify the pointer of keel object.
// lParam2 - the uIndex of table button.
#define HMSKIN_EVENT_TABBTN_CLICK (0x00000004)

#endif //__HMSKIN_EVENT_DEFS_H__