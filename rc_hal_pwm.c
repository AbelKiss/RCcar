/*
 *	RC HAL-PWM module
 *	This module contains the PWM specific variables, functions.
 */ 

#include <avr/io.h>
#include "rc_hal.h"


/**
 * @brief	Initialize PWM
 */
void HAL_PwmInit(void)
{
	// Set PWM mode & clear OCR0A, OCR1A on Compare Match
	TCCR0A = (1U << WGM00) | (1U << COM0A1);
	TCCR1A = (1U << WGM10) | (1U << COM1A1);

	// initialize output compare registers
	OCR0A = 0;
	OCR1A = 0;
}


/**
 * @brief	Set PWM
 * @param id: id of the PWM to be set
 * @param value: value of the pwm
 */
void HAL_SetPwm(Pwm_t id, uint8_t value)
{
	if ((value >= 0) && (value <= 255))
	{
		switch (id)
		{
			case PWM_ID0:
				OCR0A = value;
				break;
			case PWM_ID1:
				OCR1A = value;
				break;
			default:
				break;
		}
	}
}