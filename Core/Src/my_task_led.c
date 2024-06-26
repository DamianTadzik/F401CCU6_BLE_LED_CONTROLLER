/*
 * task_led.c
 *
 *  Created on: Apr 18, 2024
 *      Author: brzan
 */

#include <ARGB.h>
#include "my_leds.h"
#include "main.h"
#include "cmsis_os2.h"

extern my_leds_mode_t leds_mode;

extern int r_comp, g_comp, b_comp;

int speed = 16;

int brightness = 255;

int num_of_rainbows = 1;

void StartLedTask(void *argument)
{
	ARGB_Init();
	ARGB_Clear();
	UPDT_LED(0);

	while (1)
	{
		switch (leds_mode)
		{
		case my_leds_manual:
			ARGB_FillRGB((uint8_t)r_comp, (uint8_t)g_comp, (uint8_t)b_comp);
			UPDT_LED(100);
			break;
		case my_leds_auto:
			RGB_SWEEP_ALPHA(223, speed);
			break;
		case my_leds_rainbow_run:
			static uint8_t pos = 0;
			RAINBOW_RUN(speed, ++pos, num_of_rainbows);
			if (pos == 77) pos = 0;
			break;
		default:
			ARGB_Clear();
			UPDT_LED(200);
			break;
		}
		ARGB_SetBrightness(brightness);
	}
}
