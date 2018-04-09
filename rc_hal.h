
#ifndef RC_HAL_H_
#define RC_HAL_H_

#include <avr/io.h>

// Pins related to the light module
#define LIGHT_SENSOR_PORT	PORTF
#define LIGHT_SENSOR_PIN	PF0
#define RIGHT_FLASH_PORT	PORTF
#define RIGHT_FLASH_PIN		PF1
#define RIGHT_FLASH_DDR		DDRF
#define LEFT_FLASH_PORT		PORTF
#define LEFT_FLASH_PIN		PF2
#define LEFT_FLASH_DDR		DDRF
#define LOW_BEAM_PORT		PORTH
#define LOW_BEAM_PIN		PH3
#define LOW_BEAM_DDR		DDRH

// Pins related to the wifi remote controller
#define REMOTE_UP_PORT		PINH
#define REMOTE_UP_PIN		PINH4
#define REMOTE_UP_DDR		DDRH
#define REMOTE_DOWN_PORT	PINH
#define REMOTE_DOWN_PIN		PINH5
#define REMOTE_DOWN_DDR		DDRH
#define REMOTE_LEFT_PORT	PINB
#define REMOTE_LEFT_PIN		PINB6
#define REMOTE_LEFT_DDR		DDRB
#define REMOTE_RIGHT_PORT	PINB
#define REMOTE_RIGHT_PIN	PINB7
#define REMOTE_RIGHT_DDR	DDRB

// Pins related to the motor controller module
#define MOTOR1_PWM_PORT		PORTB
#define MOTOR1_PWM_PIN		PB5
#define MOTOR2_PWM_PORT		PORTE
#define MOTOR2_PWM_PIN		PE5
#define MOTOR1_CTRL0_PORT	PORTB
#define MOTOR1_CTRL0_PIN	PB4
#define MOTOR1_CTRL0_DDR	DDRB
#define MOTOR1_CTRL1_PORT	PORTH
#define MOTOR1_CTRL1_PIN	PH6
#define MOTOR1_CTRL1_DDR	DDRH
#define MOTOR2_CTRL2_PORT	PORTE
#define MOTOR2_CTRL2_PIN	PE3
#define MOTOR2_CTRL2_DDR	DDRE
#define MOTOR2_CTRL3_PORT	PORTG
#define MOTOR2_CTRL3_PIN	PG5
#define MOTOR2_CTRL3_DDR	DDRG

// This structure contains the input buffers
typedef struct
{
	uint16_t SIA_LightSensor;
	uint8_t SID_WifiControlUp;
	uint8_t SID_WifiControlDown;
	uint8_t SID_WifiControlLeft;
	uint8_t SID_WifiControlRight;
}InputBuffers_t;

typedef enum
{
	IR_NO_CMD = 0,
	IR_UP,
	IR_DOWN,
	IR_LEFT,
	IR_RIGHT,
	NUM_IR
}InputRemote_t;

// This structure contains the output buffers
typedef struct
{
	uint8_t SOD_Motor12_0;
	uint8_t SOD_Motor12_1;
	uint8_t SOD_Motor12_2;
	uint8_t SOD_Motor12_3;
	uint8_t SOD_PWM_EnableMotor1;
	uint8_t SOD_PWM_EnableMotor2;
	uint8_t SOD_LeftFlasher;
	uint8_t SOD_RightFlasher;
	uint8_t SOD_LowBeam;
}OutputBuffers_t;

typedef enum
{
	MOTOR12_0 = 0,
	MOTOR12_1,
	MOTOR12_2,
	MOTOR12_3,
	PWM_EN_MOTOR1,
	PWM_EN_MOTOR2,
	LEFT_FLASHER,
	RIGHT_FLASHER,
	LOW_BEAM,
	NUM_OUTPUT
}Output_t;

typedef enum
{
	STATE_OFF = 0,
	STATE_ON,
}State_t;


void HAL_Init(void);
uint16_t HAL_GetInputLightSensor(void);
State_t HAL_GetRemoteDirectionValue(InputRemote_t direction);
uint8_t HAL_SetOutput(Output_t output, uint8_t value);
void HAL_RefreshInputs(void);
void HAL_RefreshOutputs(void);


#endif /* RC_HAL_H_ */