#ifndef __HMSKIN_EVENT_LISTENER_H__
#define __HMSKIN_EVENT_LISTENER_H__

class hmskin_event_listener_base {
public:
	hmskin_event_listener_base(){};
	virtual ~hmskin_event_listener_base(){};

public:
	virtual void onHKSkinEvent( unsigned int uEventId, void* lParam1, void* lParam2 ) = 0;
};

#endif //__HMSKIN_EVENT_LISTENER_H__