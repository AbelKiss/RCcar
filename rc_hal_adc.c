/*
 *	RC HAL-ADC module
 *	This module contains the ADC specific variables, functions.
 */ 

#include <avr/io.h>
#include "rc_hal_adc.h"


/**
 * @brief	Initialize ADC
 */
void HAL_InitAdc(void)
{
	ADMUX |= (1<<REFS0);								// set reference voltage
	ADCSRA |= ((1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2));	// set prescale
	ADCSRA |= (1<<ADEN);								// enable ADC
}


/**
 * @brief	Get actual ADC value
 */
uint16_t HAL_GetAdcValue(void)
{
	uint16_t result;
	ADCSRA |= (1<<ADSC);			// Start Conversion
	while(!(ADCSRA & (1<<ADIF)));	// Interrupt Flag
	
	result = ADC;					// return with the ADC value
}