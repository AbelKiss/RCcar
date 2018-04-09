
#ifndef LIGHT_H_
#define LIGHT_H_

#define DARK_THRESHOLD		(300U)
#define BRIGHT_THRESHOLD	(500U)

#define FLASH_ON_MS			(340U)
#define FLASH_OFF_MS		(420U)

typedef enum
{
	FLASH_OFF = 0,
	FLASH_LEFT,
	FLASH_RIGHT
}Flash_t;

void Light_Init(void);
void Light_Flash(Flash_t state);
uint8_t Light_IsLowBeamNeeded(void)

#endif /* LIGHT_H_ */