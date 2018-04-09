/*
 *	RC Main module
 *	This module contains the Main application.
 */ 

#include "rc_hal.h"
#include "rc_light.h"
#include "rc_remote.h"
#include "rc_motor.h"


int main(void)
{
	HAL_Init();			// Initialize HAL
	Light_Init();		// Initialize Light module
	Motor_Init();		// Initialize Motor module
	Remote_Init();		// Initialize Remote module
	
    while (1)
    {
		HAL_RefreshInputs();			// Refresh inputs
		
		// Turn on low beam if needed
		if (Light_IsLowBeamNeeded())
		{
			HAL_SetOutput(LOW_BEAM, 1);
		}
		else
		{
			HAL_SetOutput(LOW_BEAM, 0);
		}
		
		RemoteState = Remote_GetInputWifiControl();		// Get the actual state of the remote controller
		
		switch (RemoteState)
		{
			case WIFI_CONTROL_NO_CMD:
				Motor_SlowDown();					// If no command, slow down the car
				Motor_Turn(TURN_OFF);				// Stop turning
				Light_Flash(FLASH_OFF);				// Turn off flashing
				break;
			case WIFI_CONTROL_UP:
				Motor_Turn(TURN_OFF);				// Stop turning
				Light_Flash(FLASH_OFF);				// Turn off flashing
				if (AccelerateDirection == ACC_OFF)
				{
					// If the car is not moving, then set FORWARD moving
					AccelerateDirection = ACC_FORWARD;
					Motor_SetState(MOTOR_ACCELERATE, AccelerateDirection);
				}
				if (AccelerateDirection == ACC_FORWARD)			// If the car is moving forward, then increase speed (accelerate)
				{
					Motor_Accelerate();
				}
				if (AccelerateDirection == ACC_BACKWARD)		// If the car is moving backward, then decrease speed (brake)
				{
					Motor_Brake();
				}
				break;
			case WIFI_CONTROL_DOWN:
				Motor_Turn(TURN_OFF);				// Stop turning
				Light_Flash(FLASH_OFF);				// Turn off flashing
				if (AccelerateDirection == ACC_OFF)
				{
					// If the car is not moving, then set BACKWARD moving
					AccelerateDirection = ACC_BACKWARD;
					Motor_SetState(MOTOR_ACCELERATE, AccelerateDirection);
				}
				if (AccelerateDirection == ACC_FORWARD)			// If the car is moving forward, then decrease speed (brake)
				{
					Motor_Brake();
				}
				if (AccelerateDirection == ACC_BACKWARD)		// If the car is moving backward, then increase speed (accelerate in reverse)
				{
					Motor_Accelerate();
				}
				break;
			case WIFI_CONTROL_LEFT:
				Motor_Turn(TURN_LEFT);			// Turn wheels left
				Light_Flash(FLASH_LEFT);		// Turn on left flasher
				break;
			case WIFI_CONTROL_RIGHT:
				Motor_Turn(TURN_RIGHT);			// Turn wheels right
				Light_Flash(FLASH_RIGHT);		// Turn on right flasher
				break;
			default:
				break;
		}
		HAL_RefreshOutputs();	// Refresh outputs
    }
	return 0;
}
