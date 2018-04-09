
#ifndef MOTOR_H_
#define MOTOR_H_

// Defines of the accelerate motor
#define SPEED_MOD_MS	(100U)
#define MIN_SPEED		(0.0f)
#define MAX_SPEED		(255.0f)
#define SLW_DWN_PERCENT	(3.0f)
#define SPD_UP_PERCENT	(3.0f)
#define BRK_DWN_PERCENT	(5.0f)
#define DEC_SLOW_DOWN	((MAX_SPEED / 100) * SLW_DWN_PERCENT)
#define INC_SPEED_UP	((MAX_SPEED / 100) * SPD_UP_PERCENT)
#define DEC_BRAKE_DOWN	((MAX_SPEED / 100) * BRK_DWN_PERCENT)

// Defines of the turning motor
#define TURNING_SPEED	(uint8_t)(80U)

typedef enum
{
	MOTOR_ACCELERATE = 0,
	MOTOR_TURN,
	NUM_MOTOR
}Motor_t;

typedef enum
{
	ACC_OFF = 0,
	ACC_FORWARD,
	ACC_BACKWARD
}Accelerate_t;

typedef enum
{
	TURN_OFF = 0,
	TURN_LEFT,
	TURN_RIGHT
}Turn_t;

typedef enum
{
	SPIN_OFF = 0,
	SPIN_FORWARD,
	SPIN_BACKWARD
}Spin_t;


extern Accelerate_t AccelerateDirection;
extern Accelerate_t TurnDirection;


void Motor_Init(void);
void Motor_SlowDown(void);
void Motor_Accelerate(void);
void Motor_Brake(void);
void Motor_Turn(Turn_t state);
void Motor_SetState(Motor_t motor, Accelerate_t state);

#endif /* MOTOR_H_ */