// demo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "demo.h"
#include "hmskin_cpp.h"
#include "hmskin_event_listener_demo.h"

//////////////////////////////////////////////////////////
#define MAINWND_WNDPROPID (258)
#define KEELOBJID_MAINBKGND (1)
#define KEELOBJID_OWNDRAWBTN (3)
#define KEELOBJID_MAINTAB (4)
#define WMPID_MAINBKGND (1)
#define WMPID_MAINBKGND_LAYOUT (2)
#define WMPID_MAINBKGND_DRAWTRIGGER (3)
#define WMPID_OWNDRAWBTN (4)
#define WMPID_MAINTAB (6)
#define WMPID_MAINTAB_LAYOUT (7)
#define WMPID_MAINTAB_DRAWTRIGGER (8)
#define RAWID_RESBMP_BTN_NOR (1)
#define RAWID_RESBMP_BTN_HOV (2)
#define RAWID_RESBMP_BTN_PRE (3)
#define RAWID_RESBMP_TABBTNS (4)

//hm_rawres_pic_factory::obj_id_type RAWID_RESBMP_BTN_PRE;
void doTest();
bool createUI( HWND hWndParent );
hmskin_event_listener_demo g_HMSkinEventListener;
hm_uiroot* g_pHMRoot = NULL;
//////////////////////////////////////////////////////////
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND g_hWnd;
HWND g_hBtnTest1 = NULL;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	hm_startup_param paramHMStartup( hInstance, &g_HMSkinEventListener );
	TCHAR szCurModulePath[ MAX_PATH +1 ];
	DWORD dwRet;
	TCHAR* posT;
	std::basic_string< TCHAR > strModuleDirPath;
	std::basic_string< TCHAR > strUIManifest;

	dwRet = ::GetModuleFileName( NULL, szCurModulePath, MAX_PATH );
	if ( dwRet == 0 )
		return FALSE;
	posT = _tcsrchr( szCurModulePath, _T('\\') );
	posT+=1;
	*posT = _T('\0');
	strModuleDirPath = szCurModulePath;
	strUIManifest = strModuleDirPath + _T("demo.hm.manifest");

	//start up hm lib
	hm_lib_startup( &paramHMStartup, strUIManifest.c_str(), &g_pHMRoot );

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMO));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//
 	hm_lib_shutdown( g_pHMRoot );

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DEMO);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

	//	
   doTest();

   ////
   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   g_hWnd = CreateWindow( szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
	   100, 100, 400, 600, NULL, NULL, hInstance, NULL);

   if ( !g_hWnd )
   {
      return FALSE;
   }

	HWND hWndParent;
	HWND hWndParent2;

	hWndParent = ::GetParent( g_hWnd );
	if ( hWndParent ) {
		hWndParent2 = ::GetParent( hWndParent );
		int a = 0;
	} else {
		int b = 0;
	}

   //
   ::createUI( g_hWnd );

   //
   hm_wndpropid_connect( g_pHMRoot, g_hWnd, MAINWND_WNDPROPID );

   ShowWindow( g_hWnd, nCmdShow );
   UpdateWindow( g_hWnd );


   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_RBUTTONDOWN:
		{	
			POINT ptCursor;
			MENUITEMINFO menuInfo;
			HMENU hPopMenu;
			
			::GetCursorPos( &ptCursor );
			hPopMenu = ::CreatePopupMenu();
			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fMask = MIIM_STRING;
			menuInfo.fType = MFT_STRING;
			menuInfo.dwTypeData = _T("rom sub menu1");
			::InsertMenuItem( hPopMenu, 208, FALSE, &menuInfo );
			::TrackPopupMenu( hPopMenu, TPM_LEFTALIGN|TPM_TOPALIGN, ptCursor.x, ptCursor.y, 0, hWnd, NULL );
		}
		break;
	case WM_SIZE:
		{
			RECT rcClient;
			TCHAR szMsg[100];

			::GetClientRect( hWnd, &rcClient );
			_stprintf_s( szMsg, _T("rcClient. l:%d,r:%d,t:%d,b:%d\n"), rcClient.left, rcClient.right, rcClient.top, rcClient.bottom );
			::OutputDebugString( szMsg );
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void doTest() {
	//hm_coordsys_factory_type::obj_id_type idCoordSysMainWnd;
	//hm_wnd_mark wndMark;

	//idCoordSysMainWnd = 1;
	//wndMark.m_eflag = hm_wnd_mark::WNDMARK_WNDPROPID;
	//wndMark.m_uWndPropID = MAINWND_WNDPROPID;


	//WNDMARK2CSID_TABLE->bindObjId2WndMark( idCoordSysMainWnd, wndMark );
}

bool createUI( HWND hWndParent ) {
	//button: test1
	{
		DWORD dwCtrlID = 20;
		g_hBtnTest1 = ::CreateWindow( _T( "Button" ), _T( "Test1" ), WS_VISIBLE | WS_CHILD, 0, 200, 80, 30, hWndParent, ( HMENU )dwCtrlID, NULL, NULL );
		if ( !g_hBtnTest1 ) {
			::OutputDebugString( _T("hBtnTest1 == NULL!\n") );
			return false;
		}
	}
	
	
	return true;
}