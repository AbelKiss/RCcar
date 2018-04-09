
#ifndef REMOTE_H_
#define REMOTE_H_

typedef enum
{
	WIFI_CONTROL_NO_CMD = 0,
	WIFI_CONTROL_UP,
	WIFI_CONTROL_DOWN,
	WIFI_CONTROL_LEFT,
	WIFI_CONTROL_RIGHT,
	NUM_REMOTE
}RemoteState_t;

extern RemoteState_t RemoteState;

void Remote_Init(void);
RemoteState_t Remote_GetInputWifiControl(void);

#endif /* REMOTE_H_ */