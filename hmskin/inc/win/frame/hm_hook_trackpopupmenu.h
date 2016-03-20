#ifndef __HM_HOOK_TRACKPOPUPMENU_H__
#define __HM_HOOK_TRACKPOPUPMENU_H__

typedef BOOL ( WINAPI *fnTrackPopupMenuType)(          HMENU hMenu,
    UINT uFlags,
    int x,
    int y,
    int nReserved,
    HWND hWnd,
    HWND prcRect
);

BOOL WINAPI hmTrackPopupMenu(          HMENU hMenu,
    UINT uFlags,
    int x,
    int y,
    int nReserved,
    HWND hWnd,
    CONST RECT * prcRect
);


#endif //__HM_HOOK_TRACKPOPUPMENU_H__