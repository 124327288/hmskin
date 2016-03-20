#ifndef __HMSKIN_HELPER_H__
#define __HMSKIN_HELPER_H__

//
unsigned int getWMPDisplayText( void* pWMPDisplayRaw, LPTSTR lpszStringBuf, int nMaxTextCount, int nDistrictId = 0 );
//
#define DISTRICT_ID_ALL (0xFFFFFFFF)
bool setWMPDisplayText( void* pWMPDisplayRaw, LPTSTR lpString, int nDistrictId = DISTRICT_ID_ALL );



#endif //__HMSKIN_HELPER_H__