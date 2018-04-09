/*
 *	RC Motor module
 *	This module contains the Motor specific variables, functions.
 */ 

#include "rc_motor.h"
#include "rc_hal.h"


Accelerate_t AccelerateDirection = ACC_OFF;			// Initialize the actual turning direction of the accelerate motor
Turn_t TurnDirection = TURN_OFF;					// Initialize the actual turning direction of the turning motor
float AccSpeed = 0.0;								// Initialize the actual Speed of the accelerate motor
uint8_t isTurning = 0;								// Store turning state

// Variables for non-blocking delay
uint32_t actualTick = 0;
uint32_t elapsedTick = 0;
uint32_t prevTick = 0;
uint16_t msElapsed = 0;


/**
 * @brief	Initialize motor module
 */
void Motor_Init(void)
{
	// Set control pins as outputs
	MOTOR1_CTRL0_DDR |= MOTOR1_CTRL0_PIN;
	MOTOR1_CTRL1_DDR |= MOTOR1_CTRL1_PIN;
	MOTOR2_CTRL2_DDR |= MOTOR2_CTRL2_PIN;
	MOTOR2_CTRL3_DDR |= MOTOR2_CTRL3_PIN;
	
	// Initialize PWMs
	HAL_PwmInit();
}


/**
 * @brief	Slowing down the car if no command was received from the remote controller
 */
void Motor_SlowDown(void)
{
	actualTick = HAL_GetTick();
	elapsedTick = actualTick - prevTick;
	prevTick = actualTick;
	msElapsed += elapsedTick;

	if (msElapsed >= SPEED_MOD_MS)
	{
		float currSpd = AccSpeed;
		float decSpd = AccSpeed - DEC_SLOW_DOWN;
		if (decSpd < currSpd)
		{
			AccSpeed= decSpd;
		}
		else
		{
			AccSpeed = MIN_SPEED;
			AccelerateDirection = ACC_OFF;
			Motor_SetState(MOTOR_ACCELERATE, SPIN_OFF);
		}
		HAL_SetOutput(PWM_EN_MOTOR1, (uint8_t)AccSpeed);
	}
}


/**
 *	@brief	Speed up the car
 */
void Motor_Accelerate(void)
{
	actualTick = HAL_GetTick();
	elapsedTick = actualTick - prevTick;
	prevTick = actualTick;
	msElapsed += elapsedTick;

	if (msElapsed >= SPEED_MOD_MS)
	{
		float currSpd = AccSpeed;
		float incSpd = AccSpeed + INC_SPEED_UP;
		if (incSpd > currSpd)
		{
			AccSpeed = incSpd;
		}
		else
		{
			AccSpeed = MAX_SPEED;
		}
		HAL_SetOutput(PWM_EN_MOTOR1, (uint8_t)AccSpeed);
	}
}


/**
 * @brief	Brake the car
 */
void Motor_Brake(void)
{
	actualTick = HAL_GetTick();
	elapsedTick = actualTick - prevTick;
	prevTick = actualTick;
	msElapsed += elapsedTick;

	if (msElapsed >= SPEED_MOD_MS)
	{
		float currSpd = AccSpeed;
		float decSpd = AccSpeed - DEC_BRAKE_DOWN;
		if (decSpd < currSpd)
		{
			AccSpeed = decSpd;
		}
		else
		{
			AccSpeed = MIN_SPEED;
			AccelerateDirection = ACC_OFF;
			Motor_SetState(MOTOR_ACCELERATE, SPIN_OFF);
		}
		HAL_SetOutput(PWM_EN_MOTOR1, (uint8_t)AccSpeed);
	}
}


/**
 * @brief	Turning left or right (or stop turning)
 * @param state: State of the turning (Left, 
 */
void Motor_Turn(Turn_t state)
{
	switch (state)
	{
		case TURN_OFF:
			Motor_SetState(MOTOR_TURN, SPIN_OFF);
			isTurning = 0;
			break;
		case TURN_LEFT:
			if (!isTurning)
			{
				Motor_SetState(MOTOR_TURN, SPIN_FORWARD);
				HAL_SetOutput(PWM_EN_MOTOR2, TURNING_SPEED);
				isTurning = 1;
			}
			break;
		case TURN_RIGHT:
			if (!isTurning)
			{
				Motor_SetState(MOTOR_TURN, SPIN_BACKWARD);
				HAL_SetOutput(PWM_EN_MOTOR2, TURNING_SPEED);
				isTurning = 1;
			}
			break;
		default:
			break;
	}	
}


/**
 * @brief	Set motor state
 * @param motor: the state of this motor will be set
 * @param state: the new state of the motor (turn forward, turn backward, stop)
 */
void Motor_SetState(Motor_t motor, Spin_t state)
{
	if (motor < NUM_MOTOR)
	{
		switch (motor)
		{
			case MOTOR_ACCELERATE:
				if (state == SPIN_FORWARD)
				{
					HAL_SetOutput(MOTOR12_0, 1);
					HAL_SetOutput(MOTOR12_1, 0);
				}
				else if (state == SPIN_BACKWARD)
				{
					HAL_SetOutput(MOTOR12_0, 0);
					HAL_SetOutput(MOTOR12_1, 1);
				}
				else
				{
					HAL_SetOutput(MOTOR12_0, 0);
					HAL_SetOutput(MOTOR12_1, 0);
				}
				break;
			case MOTOR_TURN:
				if (state == SPIN_FORWARD)
				{
					HAL_SetOutput(MOTOR12_2, 1);
					HAL_SetOutput(MOTOR12_3, 0);
				}
				else if (state == SPIN_BACKWARD)
				{
					HAL_SetOutput(MOTOR12_2, 0);
					HAL_SetOutput(MOTOR12_3, 1);
				}
				else
				{
					HAL_SetOutput(MOTOR12_2, 0);
					HAL_SetOutput(MOTOR12_3, 0);
				}
				break;
			default:
				break;
		}
	}
}