
#ifndef RC_HAL_PWM_H_
#define RC_HAL_PWM_H_

typedef enum
{
	PWM_ID0 = 0,
	PWM_ID1
}Pwm_t;

void HAL_PwmInit(void);
void HAL_SetPwm(Pwm_t id, uint8_t value);


#endif /* RC_HAL_PWM_H_ */