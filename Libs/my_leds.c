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

const uint8_t e_to_x_sq_78vals[] = {
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    2,
    3,
    4,
    5,
    7,
    9,
    12,
    16,
    20,
    25,
    31,
    38,
    46,
    55,
    65,
    76,
    89,
    102,
    117,
    131,
    147,
    162,
    178,
    192,
    206,
    219,
    230,
    240,
    247,
    252,
    254,
    255,
    252,
    247,
    240,
    230,
    219,
    206,
    192,
    178,
    162,
    147,
    131,
    117,
    102,
    89,
    76,
    65,
    55,
    46,
    38,
    31,
    25,
    20,
    16,
    12,
    9,
    7,
    5,
    4,
    3,
    2,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
};

void RAINBOW_RUN(uint8_t spd, uint8_t pos, uint8_t n_of_rainbows)
{
	uint8_t nor = saturate(n_of_rainbows, 1, 8);

	for (int n = 0; n < (78 / nor); n++)
	{
		uint8_t r = e_to_x_sq_78vals[(nor*n+pos+0)%78];
		uint8_t g = e_to_x_sq_78vals[(nor*n+pos+26)%78];
		uint8_t b = e_to_x_sq_78vals[(nor*n+pos+52)%78];
		for (int set = 0; set < nor; set++)
		{
			ARGB_SetRGB(n + set * (78 / nor), r, g, b);
		}
		if (n < 78 % n_of_rainbows)
		{
			ARGB_SetRGB(n + nor * (78 / nor), r, g, b);
		}
	}
	UPDT_LED(spd);
}

