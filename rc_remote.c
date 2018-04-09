/*
 *	RC Remote module
 *	This module contains the Remote specific variables, functions.
 */ 

#include "rc_remote.h"
#include "rc_hal.h"

RemoteState_t RemoteState = WIFI_CONTROL_NO_CMD;

void Remote_Init(void)
{
	// Set pins as input
	REMOTE_UP_DDR &= ~(1U << REMOTE_UP_PIN);
	REMOTE_DOWN_DDR &= ~(1U << REMOTE_DOWN_PIN);
	REMOTE_LEFT_DDR &= ~(1U << REMOTE_LEFT_PIN);
	REMOTE_RIGHT_DDR &= ~(1U << REMOTE_RIGHT_PIN);
}


/**
 * @brief	Get the actual state of the wifi remote controller
 */
RemoteState_t Remote_GetInputWifiControl(void)
{
	RemoteState_t result = WIFI_CONTROL_NO_CMD;		// If no remote button is active, return with No Command state
	RemoteState_t direction = WIFI_CONTROL_NO_CMD;
	while (direction < NUM_REMOTE)
	{
		// If current direction remote button is active, return with the actual direction
		if (HAL_GetRemoteDirectionValue(direction))
		{
			result = direction;
			break;				// Only one button can be active, so if an active was found, then break
		}
		direction++;			// Check all remote input, until an active was found
	}
	return result;
}