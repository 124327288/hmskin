#include "stdafx.h"
#include "win\hm_win_globals.h"
#include "win\hook_system\hm_hs_wnd_msg_dispatch.h"
#include "win\hook_system\hm_hs_apihook.h"
#include "win\frame\hm_keel_obj.h"
#include "win\wmp\hm_wndmsgprocessor_i.h"
#include "win\frame\hm_coordinate_system_hwnd.h"
#include "win\frame\hm_hook_trackpopupmenu.h"
#include "win\frame\hm_uiroot.h"
#include "common\FuncPack.h"
#include "win\hm_export_defs.h"
//for gdi+ begin
#include <unknwn.h>
#include <Rpc.h>
#include <gdiplus.h>
//for gdi+ end 

////////////////////////////////////////////////////////////////
using namespace Gdiplus;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
CFuncPack g_fpGdiplusDown( GdiplusShutdown, gdiplusToken );
hm_hs_apihook g_instanceAPIHook;
//HMLIB_API msg_sink_factory_type g_factoryMsgSink;
//HMLIB_API hm_wmark_csid_table_type g_tableWndMark2CSId;
//HMLIB_API hm_wmark_msid_table_type g_tableWndMark2MSId;
//HMLIB_API hm_coordsys_factory_type g_factoryCoordSys;
//HMLIB_API hm_keel_obj_factory g_factoryKeelObj;
//HMLIB_API hm_wmp_factory g_factoryWndMsgProcessor;
HMLIB_API hm_uiroot_factory_type g_factoryUIRoot;


