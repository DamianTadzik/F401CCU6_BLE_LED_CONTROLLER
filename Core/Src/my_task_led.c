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
			uint8_t spd = rand() % 32;
			RGB_SWEEP_ALPHA(223, spd);
			RGB_SWEEP_ALPHA(31, spd);
			break;
		default:
			ARGB_Clear();
			UPDT_LED(200);
			break;
		}
	}
}
