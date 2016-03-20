#ifndef __HMSKIN_EVENT_LISTENER_DEMO_H__
#define __HMSKIN_EVENT_LISTENER_DEMO_H__
#include "hmskin_event_listener_base.h"

class hmskin_event_listener_demo : public hmskin_event_listener_base {
public:
	hmskin_event_listener_demo();
	virtual ~hmskin_event_listener_demo();

public:
	virtual void onHKSkinEvent( unsigned int uEventId, void* lParam1, void* lParam2 );
};

#endif //__HMSKIN_EVENT_LISTENER_DEMO_H__