/*
 * task_led.c
 *
 *  Created on: Apr 18, 2024
 *      Author: brzan
 */

#include <ARGB.h>
#include "main.h"
#include "cmsis_os2.h"

static void UPDT_LED(void);
void RGB_SWEEP_ALPHA(uint8_t alpha, uint8_t speed);
//void RUN(uint8_t spd);

void StartLedTask(void *argument)
{
	ARGB_Init();
	ARGB_Clear();
	UPDT_LED();
	osDelay(2500);

	while (1)
	{
		uint8_t spd = rand() % 32;
		RGB_SWEEP_ALPHA(223, spd);
		RGB_SWEEP_ALPHA(31, spd);
//		RUN(200);
	}
}

static void UPDT_LED(void)
{
	while (ARGB_Ready() == ARGB_BUSY);
	ARGB_Show();
}

static inline uint8_t saturate(uint8_t input, uint8_t lower, uint8_t higher)
{
	if (input > higher) return higher;
	else if (input < lower) return lower;
	else return input;
}

void RGB_SWEEP_ALPHA(uint8_t alpha, uint8_t speed)
{
	for (uint8_t i = 0; i < 0b11; i++)
	{
		uint8_t A, B, C;
		switch (i)
		{
			case 0b00:
			{
				A = 1;
				B = 0;
				C = 0;
				break;
			}
			case 0b01:
			{
				A = 0;
				B = 1;
				C = 0;
				break;
			}
			case 0b10:
			{
				A = 0;
				B = 0;
				C = 1;
				break;
			}
			default:
			{
				A = 1;
				B = 1;
				C = 1;
				break;
			}
		}

		/* RED  TO GREEN TO BLUE*/
		for(uint8_t a = 0; a < alpha ; a++)
		{
			ARGB_FillRGB((255 - a)*A, (255 - a)*B, (255 - a)*C);
			UPDT_LED();
			osDelay(speed);
		}
		for(uint8_t a = 0; a < 255 - alpha; a++)
		{
			ARGB_FillRGB((255 - alpha - a)*A + a*C, (255 - alpha - a)*B + a*A, (255 - alpha - a)*C + a*B);
			UPDT_LED();
			osDelay(speed);
		}
		for(uint8_t a = 0; a < alpha; a++)
		{
			ARGB_FillRGB((255 - alpha + a)*C,(255 - alpha + a)*A, (255 - alpha + a)*B);
			UPDT_LED();
			osDelay(speed);
		}
	}
}


//void RUN(uint8_t spd)
//{
//	for (int i = 0; i < 40; i++)
//	{
//		ARGB_SetRGB(i, 0, 0, 255);
//		if (i > 2)
//		{
//			ARGB_SetRGB(i - 3, 255, 0, 0);
//		}
//		UPDT_LED();
//		osDelay(spd);
//	}
//}
