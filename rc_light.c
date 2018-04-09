/*
 *	RC Light module
 *	This module contains the light specific variables, functions.
 */ 

#include "rc_light.h"
#include "rc_hal.h"

uint8_t isFlashOn = 0;		// Stores flash state
uint8_t isLowBeamOn = 0;	// Stores low beam state

// Variables for non-blocking delay
uint32_t actualTick = 0;
uint32_t elapsedTick = 0;
uint32_t prevTick = 0;
uint16_t msElapsed = 0;


/**
 * @brief	Initialize Light module
 */
void Light_Init(void)
{
	HAL_InitAdc();			// Initialize light sensor
	
	// Set pins as output
	RIGHT_FLASH_DDR |= RIGHT_FLASH_PIN;
	LEFT_FLASH_DDR |= LEFT_FLASH_PIN;
	LOW_BEAM_DDR |= LOW_BEAM_PIN;
}


/**
 * @brief Set flash
 * @param state: state of the flash (off, left, right)
 */
void Light_Flash(Flash_t state)
{
	switch (state)
	{
		case FLASH_OFF:
			HAL_SetOutput(LEFT_FLASHER, 0);
			HAL_SetOutput(RIGHT_FLASHER, 0);
			break;
		case FLASH_LEFT:
			if (isFlashOn)
			{
				actualTick = HAL_GetTick();
				elapsedTick = actualTick - prevTick;
				prevTick = actualTick;
				msElapsed += elapsedTick;

				if (msElapsed >= FLASH_ON_MS)
				{
					HAL_SetOutput(LEFT_FLASHER, 0);
					isFlashOn = 0;
				}
			}
			else
			{
				actualTick = HAL_GetTick();
				elapsedTick = actualTick - prevTick;
				prevTick = actualTick;
				msElapsed += elapsedTick;

				if (msElapsed >= FLASH_OFF_MS)
				{
					HAL_SetOutput(LEFT_FLASHER, 1);
					isFlashOn = 1;
				}
			}
			break;
		case FLASH_RIGHT:
			if (isFlashOn)
			{
				actualTick = HAL_GetTick();
				elapsedTick = actualTick - prevTick;
				prevTick = actualTick;
				msElapsed += elapsedTick;

				if (msElapsed >= FLASH_ON_MS)
				{
					HAL_SetOutput(RIGHT_FLASHER, 0);
					isFlashOn = 0;
				}
			}
			else
			{
				actualTick = HAL_GetTick();
				elapsedTick = actualTick - prevTick;
				prevTick = actualTick;
				msElapsed += elapsedTick;

				if (msElapsed >= FLASH_OFF_MS)
				{
					HAL_SetOutput(RIGHT_FLASHER, 1);
					isFlashOn = 1;
				}
			}
			break;
		default:
			break;
	}
}


/**
 * @brief	Check that low beam is needed
 */
uint8_t Light_IsLowBeamNeeded(void)
{
	uint8_t result = 0;
	if (HAL_GetAdcValue() <= DARK_THRESHOLD)
	{
		result = 1;
		isLowBeamOn = 1;
	}
	else if (HAL_GetAdcValue() >= BRIGHT_THRESHOLD)
	{
		result = 0;
		isLowBeamOn = 0;
	}
	else
	{
		if (isLowBeamOn)
		{
			result = 1;
		}
		else
		{
			result = 0;
		}
	}
	
	return result;
}