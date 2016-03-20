#ifndef __HM_WNDMSG_DEFS_H__
#define __HM_WNDMSG_DEFS_H__
#include <WinUser.h>

/////////////////////////////////////////////////
#define HMWM_BEGIN (WM_USER+600)
/////////////////////////////////////////////////
// HMWM_BINDMENU
// wParam - HMENU hMenu
#define HMWM_BINDMENU ( HMWM_BEGIN + 1 )
/////////////////////////////////////////////////
// HMWM_MOUSEWHEEL
// wParam - specify the m_uNoTriggerTagCount ( the tag count after last trigger. )
// lParam - specify the pointer of m_containerWTD ( container of wheel tag data. )
#define HMWM_MOUSEWHEEL ( HMWM_BEGIN + 2 )



#endif //__HM_WNDMSG_DEFS_H__