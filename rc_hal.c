/*
 *	RC HAL module
 *	This module contains the input/output buffer related functions.
 */ 

#include "rc_hal.h"
#include "rc_hal_adc.h"
#include "rc_hal_pwm.h"
#include "rc_hal_tick.h"


// Initialize input buffers
InputBuffers_t inputBuffers =
{
	.SIA_LightSensor = 1023,
	.SID_WifiControlUp = 0,
	.SID_WifiControlDown = 0,
	.SID_WifiControlLeft = 0,
	.SID_WifiControlRight = 0
};

// Initialize output buffers
OutputBuffers_t outputBuffers =
{
	.SOD_Motor12_0 = 0,
	.SOD_Motor12_1 = 0,
	.SOD_Motor12_2 = 0,
	.SOD_Motor12_3 = 0,
	.SOD_PWM_EnableMotor1 = 0,
	.SOD_PWM_EnableMotor2 = 0,
	.SOD_LeftFlasher = 0,
	.SOD_RightFlasher = 0,
	.SOD_LowBeam = 0
};


/**
 * @brief	Initialize HAL
 */
void HAL_Init(void)
{
	HAL_InitTick();		// Initialize tick
	HAL_InitAdc();		// Initialize ADC
	HAL_PwmInit();		// Initialize PWM
}


/**
 * @brief	Get the value of the light sensor
 */
uint16_t HAL_GetInputLightSensor(void)
{
	return inputBuffers.SIA_LightSensor;
}


/**
 * @brief	Set output values
 * @param output: the output to be set (motor control/pwm, light)
 */
uint8_t HAL_SetOutput(Output_t output, uint8_t value)
{
	uint8_t result = 0;
	if (output < NUM_OUTPUT)
	{
		result = 1;
		switch (output)
		{
			case MOTOR12_0:
				outputBuffers.SOD_Motor12_0 = value;
				break;
			case MOTOR12_1:
				outputBuffers.SOD_Motor12_1 = value;
				break;
			case MOTOR12_2:
				outputBuffers.SOD_Motor12_2 = value;
				break;
			case MOTOR12_3:
				outputBuffers.SOD_Motor12_3 = value;
				break;
			case PWM_EN_MOTOR1:
				outputBuffers.SOD_PWM_EnableMotor1 = value;
				break;
			case PWM_EN_MOTOR2:
				outputBuffers.SOD_PWM_EnableMotor2 = value;
				break;
			case LEFT_FLASHER:
				outputBuffers.SOD_LeftFlasher = value;
				break;
			case RIGHT_FLASHER:
				outputBuffers.SOD_RightFlasher = value;
				break;
			case LOW_BEAM:
				outputBuffers.SOD_LowBeam = value;
				break;
			default:
				result = 0;
				break;
		}
	}
	return result;
}


/**
 * @brief	Get the actual state of a remote direction
 * @param direction: return with the state of this remote direction
 */
State_t HAL_GetRemoteDirectionValue(InputRemote_t direction)
{
	State_t result = STATE_OFF;
	if (direction < NUM_IR)
	{
		switch (direction)
		{
			case IR_NO_CMD:
				result = STATE_OFF;
				break;
			case IR_UP:
				result = (State_t)inputBuffers.SID_WifiControlUp;
				break;
			case IR_DOWN:
				result = (State_t)inputBuffers.SID_WifiControlDown;
				break;
			case IR_LEFT:
				result = (State_t)inputBuffers.SID_WifiControlLeft;
				break;
			case IR_RIGHT:
				result = (State_t)inputBuffers.SID_WifiControlRight;
				break;
			default:
				break;
		}
	}
	return result;
}

/**
 * @brief	Refresh input buffer by getting inputs
 */
void HAL_RefreshInputs(void)
{
	inputBuffers.SIA_LightSensor = HAL_GetAdcValue();
	inputBuffers.SID_WifiControlUp = (REMOTE_UP_PORT & (1U << REMOTE_UP_PIN)) ? 1 : 0;
	inputBuffers.SID_WifiControlDown = (REMOTE_DOWN_PORT & (1U << REMOTE_DOWN_PIN)) ? 1 : 0;
	inputBuffers.SID_WifiControlLeft = (REMOTE_LEFT_PORT & (1U << REMOTE_LEFT_PIN)) ? 1 : 0;
	inputBuffers.SID_WifiControlRight = (REMOTE_RIGHT_PORT & (1U << REMOTE_RIGHT_PIN)) ? 1 : 0;
}


/**
 * @brief	Refresh outputs by setting them using the output buffer
 */
void HAL_RefreshOutputs(void)
{
	HAL_SetPwm(PWM_ID0, outputBuffers.SOD_PWM_EnableMotor1);
	HAL_SetPwm(PWM_ID1, outputBuffers.SOD_PWM_EnableMotor2);
	
	if (outputBuffers.SOD_Motor12_0)
	{
		MOTOR1_CTRL0_PORT &= ~(1U << MOTOR1_CTRL0_PIN);
	}
	else
	{
		MOTOR1_CTRL0_PORT |= (1U << MOTOR1_CTRL0_PIN);
	}
	if (outputBuffers.SOD_Motor12_1)
	{
		MOTOR1_CTRL1_PORT &= ~(1U << MOTOR1_CTRL1_PIN);
	}
	else
	{
		MOTOR1_CTRL1_PORT |= (1U << MOTOR1_CTRL1_PIN);
	}
	if (outputBuffers.SOD_Motor12_2)
	{
		MOTOR2_CTRL2_PORT &= ~(1U << MOTOR2_CTRL2_PIN);
	}
	else
	{
		MOTOR2_CTRL2_PORT |= (1U << MOTOR2_CTRL2_PIN);
	}
	if (outputBuffers.SOD_Motor12_3)
	{
		MOTOR2_CTRL3_PORT &= ~(1U << MOTOR2_CTRL3_PIN);
	}
	else
	{
		MOTOR2_CTRL3_PORT |= (1U << MOTOR2_CTRL3_PIN);
	}
	if (outputBuffers.SOD_LeftFlasher)
	{
		LEFT_FLASH_PORT &= ~(1U << LEFT_FLASH_PIN);
	}
	else
	{
		LEFT_FLASH_PORT |= (1U << LEFT_FLASH_PIN);
	}
	if (outputBuffers.SOD_RightFlasher)
	{
		RIGHT_FLASH_PORT &= ~(1U << RIGHT_FLASH_PIN);
	}
	else
	{
		RIGHT_FLASH_PORT |= (1U << RIGHT_FLASH_PIN);
	}
	if (outputBuffers.SOD_LowBeam)
	{
		LOW_BEAM_PORT &= ~(1U << LOW_BEAM_PIN);
	}
	else
	{
		LOW_BEAM_PORT |= (1U << LOW_BEAM_PIN);
	}
}
