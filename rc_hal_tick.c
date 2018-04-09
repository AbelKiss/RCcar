/*
 *	RC HAL-Tick module
 *	This module contains the Tick specific variables, functions.
 */ 

#include <avr/interrupt.h>
#include "rc_hal_tick.h"


volatile uint32_t msTick = 0;			// Global tick (incremented by 1 in every ms)


/**
 * @brief	Initialize Tick
 */
void HAL_InitTick(void)
{
	TCCR3B |= (1 << WGM32);					// set CTC
	EIMSK |= (1 << OCIE3A);					// enable output compare A match interrupt
	OCR3A = 125;							// set output compare register
	TCCR3B = (1 << CS10) | (1 <<CS11);		// set prescale, start timer
	sei();									// enable all interrupt
}


/**
 * @brief	Get the actual tick value in ms
 */
uint32_t HAL_GetTick(void)
{
	return msTick;
}


/**
 * @brief	Interrupt Service Routine, msTick is incremented by 1 in every ms
 */
ISR (TIMER3_COMPA_vect)
{
	msTick++;
}
