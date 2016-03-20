#ifndef __HM_HS_MOUSE_PROC_HOOK_H__
#define __HM_HS_MOUSE_PROC_HOOK_H__

bool hs_mouse_proc_hook_start( HINSTANCE hInstance );
void hs_mouse_proc_hook_stop();

bool hs_mouse_ll_proc_hook_start( HINSTANCE hInstance );
void hs_mouse_ll_proc_hook_stop();

#endif //__HM_HS_MOUSE_PROC_HOOK_H__