/*
 * my_leds.c
 *
 *  Created on: Apr 22, 2024
 *      Author: brzan
 */

#include "my_leds.h"

my_leds_mode_t leds_mode = my_leds_default;
int r_comp = 127, g_comp = 127, b_comp = 127;

static inline uint8_t saturate(uint8_t input, uint8_t lower, uint8_t higher)
{
	if (input > higher) return higher;
	else if (input < lower) return lower;
	else return input;
}


void UPDT_LED(uint32_t delay)
{
	while (ARGB_Ready() == ARGB_BUSY);
	ARGB_Show();
	if (delay) osDelay(delay);
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
			UPDT_LED(0);
			osDelay(speed);
		}
		for(uint8_t a = 0; a < 255 - alpha; a++)
		{
			ARGB_FillRGB((255 - alpha - a)*A + a*C, (255 - alpha - a)*B + a*A, (255 - alpha - a)*C + a*B);
			UPDT_LED(0);
			osDelay(speed);
		}
		for(uint8_t a = 0; a < alpha; a++)
		{
			ARGB_FillRGB((255 - alpha + a)*C,(255 - alpha + a)*A, (255 - alpha + a)*B);
			UPDT_LED(0);
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
