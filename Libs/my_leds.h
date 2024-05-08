/*
 * my_leds.h
 *
 *  Created on: Apr 22, 2024
 *      Author: brzan
 */

#ifndef MY_LEDS_H_
#define MY_LEDS_H_

#include "ARGB.h"
#include "main.h"
#include "cmsis_os2.h"

typedef enum {
	my_leds_default,
	my_leds_manual,
	my_leds_rainbow_run,
	my_leds_auto,

	__my_leds_mode_t_padding__ = 0xFFFFFFF0
} my_leds_mode_t __attribute__((aligned(4)));


void UPDT_LED(uint32_t delay);
void RGB_SWEEP_ALPHA(uint8_t alpha, uint8_t speed);
void RAINBOW_RUN(uint8_t spd, uint8_t pos);


#endif /* MY_LEDS_H_ */
